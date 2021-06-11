#include "tm4c123gh6pm.h"
#include "DIO_DRIVER.h"
#include "sysTick.h"

void LCD_WriteCommand(char command) 
{
	GPIO_PORTA_DATA_R &= ~(0xE0) ; 
	GPIO_PORTB_DATA_R = command ;
	GPIO_PORTA_DATA_R |= 0x40 ; 
	sysTickWait1Ms(10) ;
	GPIO_PORTA_DATA_R &= ~(0xE0) ; 
	sysTickWait1Ms(10) ;


}
void LCD_WriteData(char data) 
{
	GPIO_PORTA_DATA_R |= 0x80  ; 
	GPIO_PORTA_DATA_R &= ~(0x60); 
	GPIO_PORTB_DATA_R = data;
	GPIO_PORTA_DATA_R |= 0x40; 
	sysTickWait1Ms(10) ;
	GPIO_PORTA_DATA_R &= ~(0x60) ; 
	sysTickWait1Ms(10) ;
}

void Lcd_init()
{
	LCD_WriteCommand(0X30);  
	sysTickWait1Ms(10);
	LCD_WriteCommand(0X38);  
	sysTickWait1Ms(10);
	LCD_WriteCommand(0X01);  
	sysTickWait1Ms(10);
	LCD_WriteCommand(0X0F);  //diplay is on
  sysTickWait1Ms(40);
  

}
void LCD_DisplayString(char *string)
{
	int i=0;
	for ( i=0; string[i]!='\0' ; i++)
	{
		LCD_WriteData(string[i]);
	}
}


