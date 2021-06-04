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
	SYSCTL_RCGCGPIO_R |=0x00000002;
	while((SYSCTL_PRGPIO_R & 0X00000002)==0);
	GPIO_PORTB_LOCK_R=0x4C4F434B;
	GPIO_PORTB_CR_R |= 0XFF;
	GPIO_PORTB_DIR_R |= 0XFF;
	GPIO_PORTB_PUR_R = 0;
	GPIO_PORTB_DEN_R |= 0XFF;
}

void Portb_output(int data)
{
	GPIO_PORTB_DATA_R =data;

}
void Portd_Init_output(void)
{
	SYSCTL_RCGCGPIO_R |=0x00000008;
	while((SYSCTL_PRGPIO_R & 0X00000008)==0);
	GPIO_PORTD_LOCK_R=0x4C4F434B;
	GPIO_PORTD_CR_R |= 0X0F;
	GPIO_PORTD_DIR_R |= 0X0F;
	GPIO_PORTD_PUR_R |= 0X0F;
	GPIO_PORTD_DEN_R |= 0X0F;
}

void Portd_output(int data)
{
	GPIO_PORTD_DATA_R =data;
}