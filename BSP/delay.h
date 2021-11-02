/********************************************************************************************************
 * @file     delay.h
 * @brief    
 * @author	 Zen
 * @date     Aug. 16, 2021
 * @par      None.
 *           
 *******************************************************************************************************/

#ifndef __DELAY_H__
#define __DELAY_H__

/* Includes ------------------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "stm32f1xx_hal.h"
#endif

typedef enum
{
    TIME_IS_ARRIVED = 0,
    TIME_NOT_ARRIVED,
}SysTimeArrivedOrNot_e;

 /**
  * @brief  GetSysTime 获取时间戳
  * @note   None.
  * @param  None.
  * @retval uwTick, 32位时间戳
  */
uint32_t GetSysTime(void);

void GetMS(unsigned long *time);

 /**
  * @brief  SysTimeExceed 判断时间是否到达，用于非阻塞延时
  * @note   最长的延时时间不得大于 2^32 ms.
  * @param  ref: 定时器的启动时间
  * @param  delay_ms: 需要延时的时间 ms
  * @retval SysTimeArrivedOrNot_e: 0: 延时到达  1：未到达
  */
SysTimeArrivedOrNot_e SysTimeExceed(uint32_t ref, uint32_t delay_ms);

 /**
  * @brief  DelayUS 阻塞式延时
  * @note   None.
  * @param  us: 需要延时的时间 us
  * @retval None.
  */
void DelayUS(uint32_t us);

 /**
  * @brief  DelayMS 阻塞式延时
  * @note   None.
  * @param  us: 需要延时的时间 ms
  * @retval None.
  */
void DelayMS(uint32_t ms);

#endif
