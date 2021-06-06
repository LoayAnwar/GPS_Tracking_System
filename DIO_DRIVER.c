#include "tm4c123gh6pm.h"
void Portf_Init_input_Output(void)
{
	SYSCTL_RCGCGPIO_R |=0x00000020;
	while((SYSCTL_PRGPIO_R & 0X00000020)==0);
	GPIO_PORTF_LOCK_R=0x4C4F434B;
	GPIO_PORTF_CR_R |= 0X1F;
	GPIO_PORTF_DIR_R |= 0X0E;
	GPIO_PORTF_PUR_R |= 0X11;
	GPIO_PORTF_DEN_R |= 0X1F;
}
int Portf_input(void)
{
	return 	GPIO_PORTF_DATA_R &0X11;

}
void Portf_output(int data)
{
	GPIO_PORTF_DATA_R =data;

}

void Portb_Init_output(void)
{
	
	SYSCTL_RCGCGPIO_R |=0x00000002;//100000
	while((SYSCTL_PRGPIO_R & 0X00000002)==0);
	GPIO_PORTB_DIR_R |= 0XFF;
	GPIO_PORTB_DEN_R |= 0XFF;
	GPIO_PORTB_DATA_R=0;		
}

void 	portE_init_output(){
	SYSCTL_RCGCGPIO_R |= 0x00000010;
	while((SYSCTL_PRGPIO_R & 0X00000010)==0);
	GPIO_PORTE_DIR_R |= 0x0F;
	GPIO_PORTE_DEN_R |= 0X0F;
}

void Portb_output(char data)
{
	GPIO_PORTB_DATA_R = data;

}

void PortE_output(char data)
{
	GPIO_PORTE_DATA_R = data;

}

void Portd_Init_output(void)
{
	SYSCTL_RCGCGPIO_R |=0x000000008;
	while((SYSCTL_PRGPIO_R & 0X00000008)==0);
	
	GPIO_PORTD_DIR_R |= 0X0F;
	GPIO_PORTD_DEN_R |= 0X0F;
}

void Portd_output(char data)
{
	GPIO_PORTD_DATA_R =data;
}