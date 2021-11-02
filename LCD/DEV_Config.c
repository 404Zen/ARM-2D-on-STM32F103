/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-16
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of theex Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
******************************************************************************/
#include "DEV_Config.h"



// #define SPI_PORT spi1

/**
 * GPIO
**/
GPIO_TypeDef* EPD_RST_PORT;
int EPD_RST_PIN;

GPIO_TypeDef* EPD_DC_PORT;
int EPD_DC_PIN;

GPIO_TypeDef* EPD_CS_PORT;
int EPD_CS_PIN;

GPIO_TypeDef* EPD_BL_PORT;
int EPD_BL_PIN;



/**
 * GPIO read and write
**/
void DEV_Digital_Write(GPIO_TypeDef* Port, uint16_t Pin, uint8_t Value)
{
    HAL_GPIO_WritePin(Port, Pin, Value);
}

uint8_t DEV_Digital_Read(GPIO_TypeDef* Port, uint16_t Pin)
{
    return HAL_GPIO_ReadPin(Port, Pin);
}

/**
 * GPIO Mode
**/
void DEV_GPIO_Mode(GPIO_TypeDef* Port, uint16_t Pin, uint8_t Mode)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if(Mode == 0 || Mode == GPIO_IN) 
    {
        GPIO_InitStruct.Pin = Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  
    } 
    else 
    {
        GPIO_InitStruct.Pin = Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    }
    HAL_GPIO_Init(Port, &GPIO_InitStruct);
}

/**
 * SPI
**/
void DEV_SPI_WriteByte(uint8_t Value)
{
    HAL_SPI_Transmit(&hspi1, &Value, 1, 1000);
}

void DEV_SPI_Write_nByte(uint8_t pData[], uint32_t Len)
{
    /* Blocking mode */
    HAL_SPI_Transmit(&hspi1, pData, Len, 1000);
}





/**
 * delay x ms
**/
void DEV_Delay_ms(UDOUBLE xms)
{
    // sleep_ms(xms);
    DelayMS(xms);
}

void DEV_Delay_us(UDOUBLE xus)
{
    // sleep_us(xus);
    DelayUS(xus);
}



void DEV_GPIO_Init(void)
{
    DEV_GPIO_Mode(EPD_RST_PORT, EPD_RST_PIN, 1);
    DEV_GPIO_Mode(EPD_DC_PORT, EPD_DC_PIN, 1);
    DEV_GPIO_Mode(EPD_CS_PORT, EPD_CS_PIN, 1);
    DEV_GPIO_Mode(EPD_BL_PORT, EPD_BL_PIN, 1);
    
    
    DEV_GPIO_Mode(EPD_CS_PORT, EPD_CS_PIN, 1);
    DEV_GPIO_Mode(EPD_BL_PORT, EPD_BL_PIN, 1);

    DEV_Digital_Write(EPD_CS_PORT, EPD_CS_PIN, 1);
    DEV_Digital_Write(EPD_DC_PORT, EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_BL_PORT, EPD_BL_PIN, 1);
}
/******************************************************************************
function:	Module Initialize, the library and initialize the pins, SPI protocol
parameter:
Info:
******************************************************************************/
UBYTE DEV_Module_Init(void)
{   
    //GPIO PIN
    EPD_RST_PORT    = LCD_RST_GPIO_Port;
    EPD_RST_PIN     = LCD_RST_Pin;
    EPD_DC_PORT     = LCD_DC_GPIO_Port;
    EPD_DC_PIN      = LCD_DC_Pin;
    EPD_BL_PORT     = LCD_BLK_GPIO_Port;
    EPD_BL_PIN      = LCD_BLK_Pin;
    EPD_CS_PORT     = LCD_CS_GPIO_Port;
    EPD_CS_PIN      = LCD_CS_Pin;
    
    // SPI Config
    // GPIO Config
    /* CubeMX已经完成SPI和GPIO的初始化 */
    
    // PWM Config
    /* Remove */
    
    //I2C Config
    /* Remove */

    //printf("DEV_Module_Init OK \r\n");
    return 0;
}

void DEV_SET_PWM(uint8_t Value){
    /* Remove */
}

/******************************************************************************
function:	Module exits, closes SPI and BCM2835 library
parameter:
Info:
******************************************************************************/
void DEV_Module_Exit(void)
{

}
