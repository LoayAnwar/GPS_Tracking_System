
#include "tm4c123gh6pm.h"
#include "DIO_DRIVER.h"
#include "gps.h"

void EnableInterrupts();

void EdgeCounter_Init(void){
SYSCTL_RCGCGPIO_R |= 0x00000020; // activate clock for port F
//FallingEdges = 0;
GPIO_PORTF_DIR_R &= ~0x11; // make PF4 in (built-in button)
GPIO_PORTF_DEN_R |= 0x11; // enable digital I/O on PF4
GPIO_PORTF_PUR_R |= 0x11; // enable weak pull-up on PF4
GPIO_PORTF_IS_R &= ~0x10; // PF4 is edge-sensitive
GPIO_PORTF_IBE_R &= ~0x10; // PF4 is not both edges
GPIO_PORTF_IEV_R &= ~0x10; // PF4 falling edge event
GPIO_PORTF_ICR_R = 0x11; // clear flag4
GPIO_PORTF_IM_R |= 0x11; // arm interrupt on PF4
NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
NVIC_EN0_R = 0x40000000; // (h) enable interrupt 30 in NVIC
EnableInterrupts(); // (i) Enable global Interrupt flag (I)
}

void GPIOPortF_Handler(void){
  int input;
	input = Portf_input();
	if((input & 0x01) == 0){
	      while (1) 
	{	
		read_gps_data();	
	}
	
	}

	else if ((input & 0x10) == 0) {
		Portf_output(0x02);
	}
}
