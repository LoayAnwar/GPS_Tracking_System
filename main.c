#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "DIO_DRIVER.h"
#include "gps.h"
#include "sysTick.h"
#include "LCDdriver.h"
unsigned int total_distance = 0;
extern uint8_t data_start[20]; 
extern unsigned char is_N_or_S, is_E_or_W;

void distanceEqual100(int total_distance)
{
	if(total_distance >= 100)
		{
			Portf_output(0x02);
		}
}
void totalDistance (int distance)
{
	   total_distance += distance;
}
void SystemInit()
{
	Portf_Init_input_Output();
	Portd_Init_output();
	Portb_Init_output();
	sysTickInit();
	LCD_init();
}

int __main (void)
{

 	 float prev_lat;
   float prev_lon;
   float current_lat;
   float current_lon;
   float distance = 0;
	 char total_distance_as_string[6];
   bool first_read = true;
	
		int x ;
		char* name ="loay" ;
		LCD_DisplayString(name);	
	       LCD_intgerToString(100);
	// **************** Read data from gps and compute distance ***************
	while (1) {
		

		/*	
        read_gps_data();
        current_lat = get_latitude(data_start[0]);
        current_lon = get_longitude(data_start[2]);
        if (is_N_or_S == 'S') {
            current_lat *= -1;
        }
        if (is_E_or_W == 'W') {
            current_lon *= -1;
        }
				
        if (first_read) {
            prev_lat = current_lat;
            prev_lon = current_lon;
            first_read = false;
        }
				// get distance in miles
        distance = get_distance(current_lat, current_lon, prev_lat, prev_lon);
				// convert distance from miles to km
        distance = distance * 1.609344;
		*/
				// convert distance from int to string 
				//totalDistance(distance);
				//sprintf(total_distance_as_string, "%d", total_distance);
        //prev_lat = current_lat;
        //prev_lon = current_lon;
				//send distance to be printed to lcd
				//lcd_write_str(total_distance_as_string);
				//distanceEqual100(total_distance);
    }
	
	
}
