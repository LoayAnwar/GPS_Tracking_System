#include "tm4c123gh6pm.h"
#include "LCD_DRIVER.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
char st[50];
void UART2_Init(void){
		SYSCTL_RCGCUART_R |= 0x00000004;    //activate uart2
		SYSCTL_RCGCGPIO_R |= 0x00000008;		//activate port D
		UART2_CTL_R &= ~0x00000001;					//disable UART
		UART2_IBRD_R = 104;			
		UART2_FBRD_R = 11;			
		UART2_LCRH_R = 0x00000070; 			//8 bits, no parity bits, one stop, FIFOs 
		UART2_CTL_R |= 0x00000301;
	GPIO_PORTD_LOCK_R=0x4C4F434B;
	GPIO_PORTD_CR_R |= 0XC0;	//enable UART 
		GPIO_PORTD_AFSEL_R |= 0xC0;			//enable alternate fn on PORT D pins 6,7 & Rx & Tx
		GPIO_PORTD_DEN_R |= 0xC0;
		GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R & 0x00FFFFFF) | 0x11000000;  
		GPIO_PORTD_AMSEL_R &= ~0xC0;			//disable analog on PortD pins 6,7
}

char ReadData_uart2(void){
	char data;
    while((UART2_FR_R &0x0010) != 0);
	 data =((uint8_t)(UART2_DR_R & 0xFF));
		return data;
}



void SendData_UART2(char data){
    while((UART2_FR_R &0x0020) != 0);
		UART2_DR_R= data;
}


void sendString_Uart2(char* string)
{
	while(*string)
	{
		SendData_UART2(*(string++));
	}
}

void senddouble_Uart2(long double num)
{
		sprintf(st ,"%.14Lf" ,num );
		sendString_Uart2(st);
}