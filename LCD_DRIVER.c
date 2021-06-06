#include "tm4c123gh6pm.h"
#include "DIO_DRIVER.h"
#include "sysTick.h"

void LCD_WriteCommand(char Command) 
{
		Portd_output(0);//100
		Portd_output(4);
		Portb_output(Command);
		PortE_output(Command>>4);
		Portd_output(0);
		sysTickWait1Ms(5);
		Portd_output(4);
		sysTickWait1Ms(5);


}
void LCD_WriteData(char data) 
{
		Portd_output(5);
		Portb_output(data);
		PortE_output(data>>4);
		Portd_output(1);
		sysTickWait1Ms(5);
		Portd_output(5);
		sysTickWait1Ms(5);

}

void Lcd_init()
{
		sysTickWait1Ms(40);
	LCD_WriteCommand(56);
		sysTickWait1Ms(5);
	LCD_WriteCommand(15);
		sysTickWait1Ms(5);
	LCD_WriteCommand(1);
		sysTickWait1Ms(5);
	LCD_WriteCommand(3);
}
void LCD_DisplayString(char *string)
{
	int i=0;
	for ( i=0; string[i]!='\0' ; i++)
	{
		LCD_WriteData(string[i]);
	}
}


