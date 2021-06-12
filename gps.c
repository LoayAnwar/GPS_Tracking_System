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
                      

typedef struct {
	char buffer[80]; 
	char data_start[20];
	long double current_lat;
	long double current_lon;
	long double prev_lat;
	long double prev_lon;
	unsigned int total_distance;
} gps_data;	

             
gps_data data;



//char *ptr;

long double get_latitude(unsigned char lat_pointer);
void compute_lat_lon();
long double get_longitude(unsigned char lat_pointer);
long double get_distance();
bool first = true;

void read_gps_data()
{
		//gps_data data;
		long double a;
		uint8_t received_char;		
	//received_char = ReadData_UART0();
		uint8_t CommaCounter = 0;
		volatile unsigned int buffer_index;
		uint8_t  is_GGA = 0;
		char GGA[3];
		 data.buffer[0] = '1';
		 data.buffer[1] = '2';
		 data.buffer[2] = '3';
		 data.buffer[3] = '4';
		 data.buffer[4] = ',';
		 data.buffer[5] = 'N';
		 data.buffer[6] = 'n';
		 data.buffer[7] = 'w';
		 data.buffer[8] = 'a';
		 data.buffer[9] = 'r';
		data.data_start[0] =0;
		data.data_start[2] =0;


    is_GGA = 0;
    do {
				received_char = ReadData();		
        if (received_char == '$') {           
            buffer_index = 0;
            is_GGA = 0;
            CommaCounter = 0;
        }
        else if (is_GGA == 1)
        {        
            if (received_char == ',')
                data.data_start[CommaCounter++] = buffer_index;    
            data.buffer[buffer_index++] = received_char;
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
	long double distance;
 	unsigned char data_begin = data.data_start[0];
	char ay = data.buffer[0];
	data.current_lat = get_latitude(data_begin);
	data_begin = data.data_start[2];
	data.current_lon = get_longitude (data_begin);
	
	
	if (first) {
		data.prev_lat = data.current_lat;
		data.prev_lon = data.current_lon;
		first = false;
	}
	
	distance = get_distance();
	// to convert distance ftom Mile to KM
	distance = distance * 1.609344;
	// to convert distance from KM to Meter
	distance = distance / 1000;
	data.total_distance += distance;
	
	data.prev_lat = data.current_lat;
	data.prev_lon = data.current_lon;
	
}

// ***************** get latitude value ******************
long double get_latitude(unsigned char lat_pointer)
{
		char *ptr;
		unsigned char is_N_or_S;
    unsigned char lat_index = lat_pointer + 1;    
    unsigned char index = 0;
    char lat_buffer[15];
    long double latitude;
   // memset(lat_buffer, 0, 15);
    for (; data.buffer[lat_index] != ','; lat_index++) {
        lat_buffer[index] = data.buffer[lat_index];
        index++;
    }
    lat_index++;
    is_N_or_S = data.buffer[lat_index];
    latitude = strtold(lat_buffer, &ptr); 
		if (is_N_or_S == 'S') {
			latitude *= -1;
		}
		return latitude;
}

//****************** get longitude ************************
long double get_longitude(unsigned char lon_pointer)
{
		char *ptr;
		unsigned char is_E_or_W;
    unsigned char lon_index = lon_pointer + 1;
    unsigned char index = 0;       
    char long_buffer[15];
    float longitude;
   // memset(long_buffer, 0, 15);
    for (; data.buffer[lon_index] != ','; lon_index++) {
        long_buffer[index] = data.buffer[lon_index];
        index++;
    }
    lon_index++;
    is_E_or_W = data.buffer[lon_index];
    longitude = strtold(long_buffer, &ptr);
		if (is_E_or_W == 'W') {
			longitude *= -1;
		}
	return longitude;    
}


//****************** compute distance **********************
double degree_to_rad(double degree) {
    return degree= (degree * pi / 180);
}

double rad_to_degree(double rad) {
    return rad= (rad * 180 / pi);
}

long double get_distance() {
    long double theta, distance;
    if ((data.current_lat == data.prev_lat) && (data.current_lon == data.prev_lon)) {
        return 0;
    }
    else {
        theta = data.current_lon - data.prev_lon;
        distance = sin(degree_to_rad(data.current_lat)) * sin(degree_to_rad(data.prev_lat)) + cos(degree_to_rad(data.current_lat)) * cos(degree_to_rad(data.prev_lat)) * cos(degree_to_rad(theta));
        distance = acos(distance);
        distance = rad_to_degree(distance);
        distance = distance * 60 * 1.1515;
        return (distance);
    }
}


