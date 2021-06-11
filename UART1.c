#include "tm4c123gh6pm.h"
#include "LCD_DRIVER.h"
//activate U
void UART_Init(void){
			SYSCTL_RCGCUART_R |= 0x00000002;    
		SYSCTL_RCGCGPIO_R |= 0x00000004;		//activate port C
		UART1_CTL_R &= ~0x00000001;					//disable UART
		UART1_IBRD_R = 104;			
		UART1_FBRD_R = 11;			
		UART1_LCRH_R = 0x00000070; 			//8 bits, no parity bits, one stop, FIFOs 
		UART1_CTL_R |= 0x00000301;			//enable UART 
		GPIO_PORTC_AFSEL_R |= 0x30;			//enable alternate fn on PORT C pins 4,5 & Tx & Rx
		GPIO_PORTC_DEN_R |= 0x30;
		GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFF00FFFF) | 0x00220000;  
		GPIO_PORTC_AMSEL_R &= ~0x30;			//disable analog on Portc pins 4,5
}

char ReadData(void){
    while((UART1_FR_R &0x0010) != 0);
		LCD_WriteData((char)(UART1_DR_R & 0xFF));
		return ((char)(UART1_DR_R & 0xFF));
}

void UART0_Init(void){
			SYSCTL_RCGCUART_R |= 0x00000001;    
		SYSCTL_RCGCGPIO_R |= 0x00000001;		//activate port C
		UART0_CTL_R &= ~0x00000001;					//disable UART
		UART0_IBRD_R = 104;			
		UART0_FBRD_R = 11;			
		UART0_LCRH_R = 0x00000070; 			//8 bits, no parity bits, one stop, FIFOs 
		UART0_CTL_R |= 0x00000301;			//enable UART 
		GPIO_PORTA_AFSEL_R |= 0x03;			//enable alternate fn on PORT C pins 4,5 & Tx & Rx
		GPIO_PORTA_DEN_R |= 0x03;
		GPIO_PORTA_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFFFFFF00) | 0x00000011;  
		GPIO_PORTA_AMSEL_R &= ~0x03;			//disable analog on Portc pins 4,5
}



void SendData_UART0(char data){
    while((UART0_FR_R &0x0020) != 0);
		UART0_DR_R= data;
}
char ReadData_UART0(void){
	char data ;
  while((UART0_FR_R &0x0010) != 0);
	data =(char)(UART0_DR_R & 0xFF);
	LCD_WriteData(data);
	SendData_UART0(data);
	return ((char)(UART0_DR_R & 0xFF));
		
}
void sendString_Uart0(char* string)
{
	while(*string)
	{
		SendData_UART0(*(string++));
	}
}