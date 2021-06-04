#include "tm4c123gh6pm.h"
void UART_Init(void){
		
		SYSCTL_RCGCUART_R |= 0x00000002;    //activate UART1
		SYSCTL_RCGCGPIO_R |= 0x00000004;		//activate port C
		UART1_CTL_R &= ~0x00000001;					//disable UART
		UART1_IBRD_R = 520;			
		UART1_FBRD_R = 53;			
		UART1_LCRH_R = 0x00000070; 			//8 bits, no parity bits, one stop, FIFOs 
		UART1_CTL_R |= 0x00000301;			//enable UART 
		GPIO_PORTC_AFSEL_R |= 0x30;			//enable alternate fn on PORT C pins 4,5 & Tx & Rx
		GPIO_PORTC_DEN_R |= 0x30;
		GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R & 0xFF00FFFF) + 0x00220000;  
		GPIO_PORTC_AMSEL_R &= ~0x30;			//disable analog on Portc pins 4,5
}

char ReadData(void){
    while((UART1_FR_R & 0x0010) != 0);
    return ((char)(UART1_DR_R & 0xFF));
}