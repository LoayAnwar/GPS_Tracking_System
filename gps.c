#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "UART1.h"
#include "LCD_DRIVER.h"
#define buffer_size 80
#define pi 3.14159265358979323846
                      
uint8_t CommaCounter;
volatile unsigned int buffer_index;
volatile unsigned char  is_GGA = 0;
char buffer[buffer_size];              
char GGA[3];


int i = 0;

void read_gps_data(char* data_start )
{
	char received_char;		
	received_char = ReadData_UART0();
    CommaCounter = 0;
    is_GGA = 0;
    do {
        received_char = ReadData_UART0();
        if (received_char == '$') {           
            buffer_index = 0;
            is_GGA = 0;
            CommaCounter = 0;
        }
        else if (is_GGA == 1)
        {        
            if (received_char == ',')
                data_start[CommaCounter++] = buffer_index;    
            buffer[buffer_index++] = received_char;
        }
        else if (GGA[0] == 'G' && GGA[1] == 'G' && GGA[2] == 'A')
        {
            is_GGA = 1;
            GGA[0] = 0;
            GGA[1] = 0;
            GGA[2] = 0;
        }
        else
        {
            GGA[0] = GGA[1];
            GGA[1] = GGA[2];
            GGA[2] = received_char;
        }
    } while (CommaCounter != 13);
}

// ***************** get latitude value ******************
void get_latitude(int lat_pointer ,char * is_N_or_S,double* l)
{
    int lat_index = lat_pointer + 1;    
    int index = 0;
    char lat_buffer[15];
    float latitude;
    memset(lat_buffer, 0, 15);
    for (; buffer[lat_index] != ','; lat_index++) {
        lat_buffer[index] = buffer[lat_index];
        index++;
    }
    lat_index++;
    *is_N_or_S = buffer[lat_index];
    *l = atof(lat_buffer);     
}

//****************** get longitude ************************
void get_longitude(int lon_pointer  ,char* is_E_or_W,double* l)
{
    int lon_index;
    int index = lon_pointer + 1;       
    char long_buffer[15];
    float longitude;
    lon_index = 0;
    memset(long_buffer, 0, 15);
    for (; buffer[index] != ','; index++) {
        long_buffer[lon_index] = buffer[index];
        lon_index++;
    }
    lon_index++;
    *is_E_or_W = buffer[lon_index];
    *l = atof(long_buffer);    
}


//****************** compute distance **********************
void degree_to_rad(double* degree) {
    *degree= ((*degree) * pi / 180);
}

void rad_to_degree(double* rad) {
    *rad= ((*rad) * 180 / pi);
}

void get_distance(double current_lat, double current_lon, double prev_lat, double prev_lon ,double* distance) {
   /*double theta;
    if ((current_lat == prev_lat) && (current_lon == prev_lon)) {
      *distance =0;  
    }
    else {
        theta = current_lon - prev_lon;
				degree_to_rad(&current_lat) ;
				degree_to_rad(&prev_lat);
				degree_to_rad(&theta);
        *distance = sin(current_lat) * sin(prev_lat) + cos(current_lat) * cos(prev_lat) * cos(theta);
        *distance = acos(*distance);
        rad_to_degree(distance);
        *distance = *distance * 60 * 1.1515;
    }
	*/
}


