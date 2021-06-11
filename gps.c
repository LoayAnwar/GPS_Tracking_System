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
char data_start[20]; 

float current_lon;
float current_lat;
float prev_lon;
float prev_lat;
unsigned char is_N_or_S;
unsigned char is_E_or_W;
float distance;
unsigned int total_distance = 0;

float get_latitude(char lat_pointer);
void compute_lat_lon();
float get_longitude(char lon_pointer);
double get_distance(double current_lat, double current_lon, double prev_lat, double prev_lon);
bool first = true;

int i = 0;

void read_gps_data()
{
	char received_char;		
	//received_char = ReadData_UART0();
    CommaCounter = 0;
    is_GGA = 0;
    do {
        //received_char = ReadData_UART0();
				received_char = ReadData();
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
		compute_lat_lon();
}

//****************** compute lat and lon from gps *********
void compute_lat_lon() {
	current_lat = get_latitude (data_start[0]);
	current_lon = get_longitude (data_start[2]);
	if (is_N_or_S == 'S') {
		current_lat *= -1;
	}
	if (is_E_or_W == 'W') {
		current_lon *= -1;
	}
	if (first) {
		prev_lat = current_lat;
		prev_lon = current_lon;
		first = false;
	}
	
	distance = get_distance (current_lat, current_lon, prev_lat, prev_lon);
	// to convert distance ftom Mile to KM
	distance = distance * 1.609344;
	// to convert distance from KM to Meter
	distance = distance / 1000;
	total_distance += distance;
	
	prev_lat = current_lat;
	prev_lon = current_lon;
}

// ***************** get latitude value ******************
float get_latitude(char lat_pointer)
{
    unsigned char lat_index = lat_pointer + 1;    
    unsigned char index = 0;
    char lat_buffer[15];
    float latitude;
    memset(lat_buffer, 0, 15);
    for (; buffer[lat_index] != ','; lat_index++) {
        lat_buffer[index] = buffer[lat_index];
        index++;
    }
    lat_index++;
    is_N_or_S = buffer[lat_index];
    latitude = atof(lat_buffer); 
		return latitude;
}

//****************** get longitude ************************
float get_longitude(char lon_pointer)
{
    unsigned char lon_index = lon_pointer + 1;
    unsigned char index;       
    char long_buffer[15];
    float longitude;
    lon_index = 0;
    memset(long_buffer, 0, 15);
    for (; buffer[lon_pointer] != ','; lon_pointer++) {
        long_buffer[index] = buffer[lon_pointer];
        index++;
    }
    lon_index++;
    is_E_or_W = buffer[lon_index];
    longitude = atof(long_buffer);
return longitude;    
}


//****************** compute distance **********************
double degree_to_rad(double degree) {
    return degree= (degree * pi / 180);
}

double rad_to_degree(double rad) {
    return rad= (rad * 180 / pi);
}

double get_distance(double current_lat, double current_lon, double prev_lat, double prev_lon) {
    double theta, distance;
    if ((current_lat == prev_lat) && (current_lon == prev_lon)) {
        return 0;
    }
    else {
        theta = current_lon - prev_lon;
        distance = sin(degree_to_rad(current_lat)) * sin(degree_to_rad(prev_lat)) + cos(degree_to_rad(current_lat)) * cos(degree_to_rad(prev_lat)) * cos(degree_to_rad(theta));
        distance = acos(distance);
        distance = rad_to_degree(distance);
        distance = distance * 60 * 1.1515;
        return (distance);
    }
}


