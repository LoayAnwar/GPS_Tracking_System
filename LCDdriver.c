#include "DIO_DRIVER.h"
#include "tm4c123gh6pm.h"

void delay_milli(int n);
void delay_micro(int n);
void LCD_init(void);
void LCD_Cmd(unsigned char command);
void LCD_Data(char data);
void LCD_DisplayString(char *string);

void LCD_init(void) {
	LCD_Cmd(0x38); //8-bits,2 display lines, 5x7 font
	LCD_Cmd(0x06); //increments automatically
	LCD_Cmd(0x0F); //Turn on display
	LCD_Cmd(0x01); //clear display
}

void LCD_Cmd(unsigned char command)
{
	Portd_output(0x00); //RS =0, E=0, RW=0
	delay_milli(5);
	Portd_output(0x04); //E=1 to secure command
	delay_milli(5);
	Portb_output(command);
	delay_milli(5);
	Portd_output(0x00);
	if (command < 4) delay_milli(2); else delay_micro(37);
} 
void LCD_Data(char data) {
	Portd_output(0x01); //RS=1, E=0,RW=0
	delay_milli(5);
	Portb_output(data);
	delay_milli(5);
	Portd_output(0x04);
	delay_milli(5);
	Portd_output(0x00);
	delay_milli(5);
}
void lcd_write_str(char *data) 
{    
	while (*data !='\0')
		 { 
					LCD_Data(*data); 
					data++;           
		 }
}  

void delay_milli(int n) {
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < 3180; j++)
		{
		}
}

void delay_micro(int n) {
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < 3; j++)
		{
		}
}

void LCD_DisplayString(char *string)
{
	int i=0;
	for ( i=0; string[i]!='\0' ; i++)
	{
		LCD_Data(string[i]);
	}
}
void LCD_DisplayInt(int x)
{
	int s;
	while(x!=0)
	{
		s= x%10;
		x /=10;
		LCD_Data(s +'0');
	}
}