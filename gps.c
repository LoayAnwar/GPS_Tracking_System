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
	long double total_distance;
} gps_data;


gps_data data;



//char *ptr;

long double get_latitude(unsigned char lat_pointer);
void compute_lat_lon();
long double get_longitude(unsigned char lat_pointer);
long double get_distance();
double distanceBetween();
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
	  char total_distance_in_string[6];
		 //data.buffer[0] = '1';
		// data.buffer[1] = '2';
		// data.buffer[2] = '3';
		// data.buffer[3] = '4';
		// data.buffer[4] = ',';
		// data.buffer[5] = 'N';
		// data.buffer[6] = 'n';
		// data.buffer[7] = 'w';
		// data.buffer[8] = 'a';
		// data.buffer[9] = 'r';
		//data.data_start[0] =0;
		//data.data_start[2] =0;


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
						{
                data.data_start[CommaCounter++] = buffer_index;
						}
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
		//SendData_UART0('!');
		compute_lat_lon();
		sprintf(total_distance_in_string, "%Lf", data.total_distance);
		LCD_WriteCommand(1);
		LCD_DisplayString(total_distance_in_string);
}

//****************** compute lat and lon from gps *********
void compute_lat_lon() {
	int temp;
	long double temp_2;
	long double distance;
	char valid_bit_index;
	char valid_bit;
 	unsigned char data_begin = data.data_start[0];
	valid_bit_index = data.data_start[4];
	valid_bit_index++;
	valid_bit = data.buffer[valid_bit_index];
	if (valid_bit == '1') {
		data.current_lat = get_latitude(data_begin);
		temp = data.current_lat/100;
		temp_2 = data.current_lat - (temp * 100);
		temp_2 = temp_2 / 60;
		data.current_lat = temp + temp_2;
		data_begin = data.data_start[2];
		data.current_lon = get_longitude (data_begin);
		temp = data.current_lon / 100;
		temp_2 = data.current_lon - (temp * 100);
		temp_2 /= 60;
		data.current_lon = temp + temp_2;


		if (first) {
			data.prev_lat = data.current_lat;
			data.prev_lon = data.current_lon;
			first = false;
		}

		//distance = get_distance();
		distance = distanceBetween();
		// to convert distance ftom Mile to KM
		//distance = distance * 1.609344;
		// to convert distance from KM to Meter
		//distance = distance * 1000;
		data.total_distance += distance;
		data.prev_lat = data.current_lat;
		data.prev_lon = data.current_lon;
	}

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

long double toRadians(const long double degree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (pi) / 180;
    return (one_deg * degree);
}
double distanceBetween()
{
  // returns distance in meters between two positions, both specified
  // as signed decimal-degrees latitude and longitude. Uses great-circle
  // distance computation for hypothetical sphere of radius 6372795 meters.
  // Because Earth is no exact sphere, rounding errors may be up to 0.5%.
  // Courtesy of Maarten Lamers
	double delta;
	double sdlong;
	double cdlong;
	double slat1;
	double clat1;
	double slat2;
	double clat2;
	double denom;
	long double lat1 = data.current_lat;
	long double lat2 = data.prev_lat;
  delta = toRadians(data.current_lon-data.prev_lon);
  sdlong = sin(delta);
  cdlong = cos(delta);
  lat1 = toRadians(lat1);
  lat2 = toRadians(lat2);
  slat1 = sin(lat1);
  clat1 = cos(lat1);
  slat2 = sin(lat2);
  clat2 = cos(lat2);
  delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
  delta = (delta*delta);
  delta += ((clat2 * sdlong)*(clat2 * sdlong));
  delta = sqrt(delta);
  denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
  delta = atan2(delta, denom);
  return delta * 6372795;
}
