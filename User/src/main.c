#include "main.h"

uint8_t s2[20] = "Speed:";
uint32_t speed[] = {9600, 14400, 19200, 38400, 115200};
uint8_t current_speed = 0;
uint8_t max_speed = 5;

uint16_t delay_count = 0;

uint8_t button_count = 0;
uint8_t button_state = 0;

uint16_t max_line = 320;
uint16_t step_line = 10;
uint16_t current_line = 10;

uint8_t recieve_buf[256];
uint8_t end_of_recieve = 1;
uint8_t recieve_count = 0;

//-------------------------------------------------------------
//
//-------------------------------------------------------------
void delay_ms(uint16_t delay_temp)
{
	delay_count = delay_temp;	
	while(delay_count){}	
}

//-------------------------------------------------------------
//
//-------------------------------------------------------------
void USART1_IRQHandler(void)
{	
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		
		recieve_buf[recieve_count] = USART_ReceiveData(USART1);
		recieve_count++;
		
		if(recieve_buf[recieve_count-1] != '\r')
		{
			end_of_recieve = 0;			
		} else {
			end_of_recieve = 1;
		}
	}
}

//-------------------------------------------------------------
//
//-------------------------------------------------------------
void reverse(uint8_t s[100])
{
	uint16_t i, j;
	uint8_t c;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) 
	{
		 c = s[i];
		 s[i] = s[j];
		 s[j] = c;
	}
}
 
//-------------------------------------------------------------
//
//-------------------------------------------------------------
void itoa(int n, uint8_t s[100])
{
	uint16_t i, sign;

	if ((sign = n) < 0)  
		 n = -n;         
	i = 0;
	do 
	{      
		 s[i++] = n % 10 + '0';  
	} 
	while ((n /= 10) > 0);    
	if (sign < 0)
		 s[i++] = '-';
	s[i++] = ' ';
	s[i] = '\0';
	reverse(s);
}
 

uint8_t* modif(uint8_t s1[20])
{	
	uint8_t i = 6, j = 0;
	
	while(s1[j] != '\0')
	{
		s2[i] = s1[j];
		i++;
		j++;
	}
	
	s2[i] = '\0';
	
	return s2;
}
	
 
//-------------------------------------------------------------
//
//-------------------------------------------------------------
 void print_speed()
 {
	 uint8_t *s2;// = "Speed:";
	 uint8_t s1[20];
	 
	 itoa(speed[current_speed], s1);
	 
	 //strcat(s2, s1);	 
	 s2 = modif(s1);
	 
	 LCD_ClearLine(0);
	 LCD_DisplayStringLine(0, s2);
 }
 
//-------------------------------------------------------------
//
//-------------------------------------------------------------
 void choose_speed()
{
	current_speed++;
	if(current_speed == max_speed)
	{
		current_speed = 0;
	}
	
	USART1_set_speed(speed[current_speed]);
	print_speed();
}

//-------------------------------------------------------------
//
//-------------------------------------------------------------
 void print_string(uint8_t s[100])
 {	 
	 s[recieve_count-1]=0x00;	
	 LCD_ClearLine(current_line);
	 LCD_DisplayStringLine(current_line, s);
	 current_line = current_line + step_line;
	 
	 LCD_ClearLine(current_line);
	 LCD_DrawLine(0, current_line, 240, LCD_DIR_HORIZONTAL);
	 
	 if(current_line > max_line - step_line)
		 current_line = 10;
 }
 
 //-------------------------------------------------------------
//
//-------------------------------------------------------------
void SysTick_Handler(void) //1ms
{
	if(delay_count>0)
	{
		delay_count--;
	}
	
	if(BUTTON_READ() == 1)
	{
		if(button_count < 5)
		{
			button_count++;
		} else {
			if(button_state == 0)
			{
				button_state = 1;
				RED_ON();
				
				choose_speed();
			}
		}		
	}
	else
	{
		if(button_count > 0)
		{
			button_count--;
		} else {
			button_state = 0;
			RED_OFF();
		}	
	}
}
 
//-------------------------------------------------------------
//
//-------------------------------------------------------------
int main(void)
{
	SysTick_Config(SystemCoreClock/1000); //1 ms
	
	LEDs_ini();
	BUTTON_ini();
	USART1_ini();	
	LCD_ini();	
	
	USART1_set_speed(speed[current_speed]);
	
	print_speed();	
	LCD_DrawLine(0, 9, 240, LCD_DIR_HORIZONTAL);
	
	while(1)
	{		
		if((end_of_recieve == 1) && (recieve_count>0))
		{			
			GREEN_ON();
			
			print_string(recieve_buf);
			recieve_count=0;
			
			GREEN_OFF();
		}		
	}
}

