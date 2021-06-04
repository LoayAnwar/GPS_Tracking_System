

#ifndef lcd
#define lcd

void delay_milli(int n);
void delay_micro(int n);
void LCD_init(void);
void LCD_Cmd(unsigned char command);
void LCD_Data(unsigned char data);
void lcd_write_str(unsigned char* data);


#endif //lcd.h 