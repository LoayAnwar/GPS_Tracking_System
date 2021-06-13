#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "DIO_DRIVER.h"
#include "gps.h"
#include "sysTick.h"
#include "LCD_DRIVER.h"
#include "UART1.h"
#include "EEPROM.h"

char total_distance_as_string[15];
bool first_read = true;
char NS ,EW ;
char *ptr;
long double a; 
	
void is_distance_greater_or_equal_to_100(int total_distance)
{
	if(total_distance >= 100)
		{
			Portf_output(0x02);
		}
}


int main ()
{
	char lat_buffer_[15];
	long double ha =1.1;
	Portf_Init_input_Output();
	Portb_Init_output();
	porta_init_output();
	sysTickInit();
	Lcd_init();
	UART_Init();
	UART0_Init();
	EEPROM_Init();
	// **************** Read data from gps and compute distance ***************
while (1) 
	{	
		read_gps_data();	
	}
	
}
