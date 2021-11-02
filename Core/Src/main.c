/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "delay.h"
#include "led.h"
#include "LCD_1in3.h"

#include "arm_2d.h"
#include "arm_2d_helper.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static arm_2d_helper_pfb_t s_tPFBHelper;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

static 
IMPL_PFB_ON_LOW_LV_RENDERING(__pfb_render_handler)
{
  const arm_2d_tile_t *ptTile = &(ptPFB->tTile);

  ARM_2D_UNUSED(pTarget);
  ARM_2D_UNUSED(bIsNewFrame);

  GLCD_DrawBitmap(ptTile->tRegion.tLocation.iX,
                  ptTile->tRegion.tLocation.iY,
                  ptTile->tRegion.tSize.iWidth,
                  ptTile->tRegion.tSize.iHeight,
                  (uint16_t*)ptTile->pchBuffer);

  arm_2d_helper_pfb_report_rendering_complete(&s_tPFBHelper, (arm_2d_pfb_t *)ptPFB);
}


static 
IMPL_PFB_ON_DRAW(__pfb_draw_handler)
{
  ARM_2D_UNUSED(pTarget);
  ARM_2D_UNUSED(bIsNewFrame);

  arm_2d_region_t tBox = {
    .tLocation = {50,50},
    .tSize = {100, 100},    /* 为了不超出边界 这里改小了 */
  };
  //! 背景填充白色
  arm_2d_rgb16_fill_colour(ptTile, NULL, 0xFFFF);
  //! 在box指定的区域绘制黑色影子
  arm_2d_rgb16_fill_colour(ptTile, &tBox, 0x0000);
  //! 适当向左上角移动box
  tBox.tLocation.iX -= 10;
  tBox.tLocation.iY -= 10;
  //! 在box指定的区域填充蓝色，并且使用 50%(128/255)的透明效果
  arm_2d_rgb565_fill_colour_with_alpha(   
    ptTile, 
    &tBox, 
    (arm_2d_color_rgb565_t){0x001F}, 
    128);      //!< 透明度

  return arm_fsm_rt_cpl;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  static uint32_t led_timer = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  printf("ARM-2D on STM32F103.\r\n");
  printf("Build Time : "__DATE__" "__TIME__"\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  LEDInit();
  LCD_1IN3_Init(VERTICAL);
  arm_2d_init();

  //! initialise FPB helper
  if (ARM_2D_HELPER_PFB_INIT( 
        &s_tPFBHelper,     //!< FPB Helper object
        240,               //!< screen width
        240,               //!< screen height
        uint16_t,          //!< colour date type
        240,               //!< PFB block width
        1,                 //!< PFB block height
        1,                 //!< number of PFB in the PFB pool
        {
          .evtOnLowLevelRendering = {
          //! callback for low level rendering 
          .fnHandler = &__pfb_render_handler,                         
          },
          .evtOnDrawing = {
          //! callback for drawing GUI 
          .fnHandler = &__pfb_draw_handler, 
        },
      },
      // .FrameBuffer.bSwapRGB16 = true,
    ) < 0) {
    //! error detected
    assert(false);
  }

  led_timer = GetSysTime();
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    if(SysTimeExceed(led_timer, 500) == TIME_IS_ARRIVED)
    {
      led_timer = GetSysTime();

      LEDToggle(led);
    }

    //! call partial framebuffer helper service
    while(arm_fsm_rt_cpl != arm_2d_helper_pfb_task(&s_tPFBHelper, NULL));
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
