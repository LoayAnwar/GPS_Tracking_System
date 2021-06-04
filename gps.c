#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "UART1.h"

#define buffer_size 80
#define data_no 20
#define pi 3.14159265358979323846
                      
uint8_t data_start[data_no]; 
uint8_t CommaCounter;
volatile unsigned int buffer_index;
volatile unsigned char  is_GGA = 0;
char buffer[buffer_size];              
char GGA[3];
unsigned char is_N_or_S, is_E_or_W;

void  read_gps_data()
{
		char received_char;
    CommaCounter = 0;
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
float get_latitude(uint8_t lat_pointer)
{
    uint8_t lat_index = lat_pointer + 1;    
    uint8_t index = 0;
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
float get_longitude(uint8_t lon_pointer)
{
    uint8_t lon_index;
    uint8_t index = lon_pointer + 1;       
    char long_buffer[15];
    float longitude;
    lon_index = 0;
    memset(long_buffer, 0, 15);
    for (; buffer[index] != ','; index++) {
        long_buffer[lon_index] = buffer[index];
        lon_index++;
    }
    lon_index++;
    is_E_or_W = buffer[lon_index];
    longitude = atof(long_buffer);    
    return longitude;                 
}


//****************** compute distance **********************
double degree_to_rad(double degree) {
    return (degree * pi / 180);
}

double rad_to_degree(double rad) {
    return (rad * 180 / pi);
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


