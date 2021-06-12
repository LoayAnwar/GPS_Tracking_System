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
//#define data_no 20

//unsigned int total_distance = 0;
//float prev_lat=0;
//char data_start[data_no]; 

  //float prev_lon=0;
  //double current_lat=0;
  //double current_lon=0;
  //double distance =0;
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
/*void totalDistance (int distance)
{
	   total_distance += distance;
}*/


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
		//Erase();
		read_gps_data();
		
		/*LCD_WriteData('a');
		writeData(ha);
		set_block_and_offset(0,0);
		ha= readData();
		sprintf(total_distance_as_string, "%Lf", ha);
		sendString_Uart0(total_distance_as_string);
		//get_latitude(data_start[0] ,&NS ,&current_lat);
		//get_longitude(data_start[2],&EW,&current_lat);
		LCD_WriteData('D');

		if (NS == 'S') {
				current_lat *= -1 ;
		}
		
		if (EW == 'W') {
				current_lon *= -1;
		}
		
		if (first_read) {
				prev_lat = current_lat;
				prev_lon = current_lon;
				first_read = false;
		}*/

		// get distance in miles
			// get_distance(current_lat, current_lon, prev_lat, prev_lon ,&distance);
		// convert distance from miles to km
		
		/*distance = distance * 1.609344;
		// convert from KM to meter
		distance /= 1000;

		// convert distance from int to string 
		totalDistance(distance);
		sprintf(total_distance_as_string, "%d", total_distance);
		prev_lat = current_lat;
		prev_lon = current_lon;
		//send distance to be printed to lcd
		LCD_DisplayString(total_distance_as_string);
		sendString_Uart0(total_distance_as_string);
		is_distance_greater_or_equal_to_100(total_distance);
	*/	}
	
}
