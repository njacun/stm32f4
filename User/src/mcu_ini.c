#include "mcu_ini.h"

//-------------------------------------------------------------
//
//-------------------------------------------------------------
void LEDs_ini(void)
{
	GPIO_InitTypeDef GPIO_Init_LED;	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);	
	
	GPIO_Init_LED.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;	
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOG, &GPIO_Init_LED);
}

//-------------------------------------------------------------
//
//-------------------------------------------------------------
void BUTTON_ini(void)
{
	GPIO_InitTypeDef GPIO_Init_Button;	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	
	GPIO_Init_Button.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init_Button.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_Button.GPIO_Speed = GPIO_Speed_2MHz;	
	GPIO_Init_Button.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA, &GPIO_Init_Button);
}

//-------------------------------------------------------------
//
//-------------------------------------------------------------
void USART1_ini(void)
{
	GPIO_InitTypeDef GPIO_Init_USART;		
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	
	
	GPIO_Init_USART.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init_USART.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_USART.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init_USART.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_USART.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_Init(GPIOA, &GPIO_Init_USART);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}

void USART1_set_speed(uint16_t speed)
{
	USART_InitTypeDef USART_InitUser;
	
	USART_DeInit(USART1);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	
	
	USART_InitUser.USART_BaudRate = speed;
	USART_InitUser.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitUser.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitUser.USART_Parity = USART_Parity_No;
	USART_InitUser.USART_StopBits = USART_StopBits_1;
	USART_InitUser.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1, &USART_InitUser);
	
	NVIC_EnableIRQ(USART1_IRQn);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART1, ENABLE);
}

void LCD_ini(void)
{
	LCD_Init();
  LCD_LayerInit();
  LCD_SetLayer(LCD_BACKGROUND_LAYER);
  LCD_SetTransparency(0);
  LCD_SetLayer(LCD_FOREGROUND_LAYER);
  LTDC_ReloadConfig(LTDC_IMReload);
	LTDC_Cmd(ENABLE);
	LCD_Clear(LCD_COLOR_WHITE);
	LCD_SetFont(&Font8x8);
}





