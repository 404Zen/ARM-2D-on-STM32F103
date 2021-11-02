/*****************************************************************************
* | File      	:   DEV_Config.h
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
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

// #include "pico/stdlib.h"
// #include "hardware/spi.h"
// #include "stdio.h"
// #include "hardware/i2c.h"
// #include "hardware/pwm.h"

#include <stdio.h>
#include "spi.h"
#include "stm32f1xx_hal.h"
#include "main.h"
#include "delay.h"



/**
 * data
**/
#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define GPIO_IN                         0
#define GPIO_OUT                        1
/**
 * GPIOI config
**/
extern GPIO_TypeDef* EPD_RST_PORT;
extern GPIO_TypeDef* EPD_DC_PORT;
extern GPIO_TypeDef* EPD_CS_PORT;
extern GPIO_TypeDef* EPD_BL_PORT;
extern int EPD_RST_PIN;
extern int EPD_DC_PIN;
extern int EPD_CS_PIN;
extern int EPD_BL_PIN;


/*------------------------------------------------------------------------------------------------------*/
void DEV_Digital_Write(GPIO_TypeDef* Port, uint16_t Pin, uint8_t Value);
uint8_t DEV_Digital_Read(GPIO_TypeDef* Port, uint16_t Pin);

void DEV_GPIO_Mode(GPIO_TypeDef* Port, uint16_t Pin, uint8_t Mode);

void DEV_SPI_WriteByte(UBYTE Value);
void DEV_SPI_Write_nByte(uint8_t *pData, uint32_t Len);

void DEV_Delay_ms(UDOUBLE xms);
void DEV_Delay_us(UDOUBLE xus);


UBYTE DEV_Module_Init(void);
void DEV_Module_Exit(void);


#endif
