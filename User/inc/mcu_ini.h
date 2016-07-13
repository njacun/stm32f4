#ifndef MCU_INI_H
#define MCU_INI_H

#include "stm32f4xx.h" 

#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"

void LEDs_ini(void);
void BUTTON_ini(void);
void USART1_ini(void);
void LCD_ini(void);
void USART1_set_speed(uint16_t speed);

#endif
