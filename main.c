#include <stdlib.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "DIO_DRIVER.h"
#include "gps.h"
//#include "sysTick.h"

void SystemInit()
{
	
}
int __main (void)
{

 	 float prev_lat;
   float prev_lon;
   float current_lat;
   float current_lon;
   float distance = 0;
   float total_distance = 0;
   bool first_read = true;
		
	// **************** Read data from gps and compute distance ***************
	while (1) {
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
        total_distance += distance;
        prev_lat = current_lat;
        prev_lon = current_lon;
    }
	
	
}

