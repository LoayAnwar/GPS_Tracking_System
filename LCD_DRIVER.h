#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

void Lcd_init();
void LCD_DisplayString(char *string);
void LCD_WriteData(char data) ;
void LCD_WriteCommand(char command) ;
#endif