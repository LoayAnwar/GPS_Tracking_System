

#ifndef lcd
#define lcd

void delay_milli(int n);
void delay_micro(int n);
void LCD_init(void);
void LCD_Cmd(unsigned char command);
void LCD_Data(char data);
void lcd_write_str(char* data);
void LCD_DisplayString(char *string);
void LCD_DisplayInt(int x);
void LCD_intgerToString(int data);
#endif //lcd.h 
