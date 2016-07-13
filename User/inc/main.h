#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx.h"                  // Device header

#include "mcu_ini.h"
#include <stdio.h>
#include <string.h>

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"

#define RED_ON() 					GPIO_SetBits(GPIOG, GPIO_Pin_14)
#define RED_OFF() 				GPIO_ResetBits(GPIOG, GPIO_Pin_14)
#define GREEN_ON() 				GPIO_SetBits(GPIOG, GPIO_Pin_13)
#define GREEN_OFF()				GPIO_ResetBits(GPIOG, GPIO_Pin_13)

#define BUTTON_READ()				GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

#endif
