/********************************************************************************************************
 * @file     delay.c
 * @brief    
 * @author	 Zen
 * @date     Aug. 16, 2021
 * @par      None.
 *           
 *******************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "delay.h"

 /**
  * @brief  GetSysTime 获取时间戳
  * @note   None.
  * @param  None.
  * @retval uwTick, 32位时间戳
  */
uint32_t GetSysTime(void)
{
    return HAL_GetTick();
}

void GetMS(unsigned long *time)
{
	*time = (unsigned long)HAL_GetTick();
}

 /**
  * @brief  SysTimeExceed 判断时间是否到达，用于非阻塞延时
  * @note   None.
  * @param  ref: 定时器的启动时间
  * @param  delay_ms: 需要延时的时间 ms
  * @retval SysTimeArrivedOrNot_e: 0: 延时到达  1：未到达
  */
SysTimeArrivedOrNot_e SysTimeExceed(uint32_t ref, uint32_t delay_ms)
{
    uint32_t tnow = 0;
    uint32_t tcount = 0;

    tnow = HAL_GetTick();

    tcount = tnow - ref;
    
    if(tcount >= delay_ms)
        return TIME_IS_ARRIVED;
    else
        return TIME_NOT_ARRIVED;
}

 /**
  * @brief  DelayUS 阻塞式延时
  * @note   None.
  * @param  us: 需要延时的时间 us
  * @retval None.
  */
void DelayUS(uint32_t us)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;        //Load 的值

    ticks = SystemCoreClock/1000000 * us;   //需要的ticks
    told = SysTick->VAL;

    while (1)
    {
        tnow = SysTick->VAL;
        if(tnow != told)
        {
            if(tnow < told)
                tcnt += told - tnow;
            else
                tcnt += reload - tnow + told;

            told = tnow;

            if(tcnt >= ticks)
                break;
        }
    }
}

 /**
  * @brief  DelayMS 阻塞式延时
  * @note   None.
  * @param  us: 需要延时的时间 ms
  * @retval None.
  */
void DelayMS(uint32_t ms)
{
    while (ms--)
    {
        DelayUS(1000);
    }
}


