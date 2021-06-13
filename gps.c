#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "UART1.h"
#include "uart2.h"
#include "LCD_DRIVER.h"
#include "DIO_DRIVER.h"
#define buffer_size 80
#define pi 3.14159265358979323846


typedef struct {
	char buffer[80];
	char data_start[20];
	char buffer_speed[80];
	char data_start_speed[20];
	long double speed;
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
long double get_speed(unsigned char speed_pointer);
long double get_distance();
double distanceBetween();
bool first = true;

void read_gps_data()
{
		long double a;
		uint8_t received_char;
		uint8_t CommaCounter = 0;
		volatile unsigned int buffer_index;
		uint8_t  is_GGA = 0;
	  uint8_t  is_VTG = 0;
		char GGA[3];
	  char VTG[3];
	  char total_distance_in_string[6];
	
	int i;

		/*data.buffer[0] = '$';
		data.buffer[1] = 'G';
	data.buffer[2] = 'P';
		data.buffer[3] = 'V';
	data.buffer[4] = 'T';
	data.buffer[5] = 'G';
	data.buffer[6] = ',';
	data.buffer[7] = '3';
	data.buffer[8] = '6';
	data.buffer[9] = '0';
	data.buffer[10] = '.';
	data.buffer[11] = '0';
	data.buffer[12] = ',';
	data.buffer[13] = 'T';
	data.buffer[14] = ',';
	data.buffer[15] = '3';
	data.buffer[16] = '4';
	data.buffer[17] = '8';
	data.buffer[18] = '.';
	data.buffer[19] = '7';
	data.buffer[20] = ',';
	data.buffer[21] = 'M';
	data.buffer[22] = ',';
	data.buffer[23] = '0';
	data.buffer[24] = '0';
	data.buffer[25] = '0';
	data.buffer[26] = '.';
	data.buffer[27] = '0';
	data.buffer[28] = ',';
	data.buffer[29] = 'N';
	data.buffer[30] = ',';
	data.buffer[31] = '0';
	data.buffer[32] = '1';
	data.buffer[33] = '0';
	data.buffer[34] = '.';
	data.buffer[35] = '2';
	data.buffer[36] = ',';
	data.buffer[37] = 'K';
	*/
	i = 0;
    is_GGA = 0;
	  is_VTG = 0;
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
		
		    do {
				received_char = ReadData();
				//	received_char = data.buffer[i];
        if (received_char == '$') {
            buffer_index = 0;
            is_VTG = 0;
            CommaCounter = 0;
        }
        else if (is_VTG == 1)
        {
            if (received_char == ',')
						{
                data.data_start_speed[CommaCounter++] = buffer_index;
						}
            data.buffer_speed[buffer_index++] = received_char;
        }
        else if (VTG[0] == 'V' && VTG[1] == 'T' && VTG[2] == 'G')
        {
            is_VTG = 1;
            VTG[0] = 0;
            VTG[1] = 0;
            VTG[2] = 0;
        }
        else
        {
            VTG[0] = VTG[1];
            VTG[1] = VTG[2];
            VTG[2] = received_char;
        }
				i++;
    } while (CommaCounter != 7);
				
		compute_lat_lon();
		sprintf(total_distance_in_string, "%Lf", data.total_distance);
		LCD_WriteCommand(1);
		LCD_DisplayString(total_distance_in_string);
		if (data.total_distance > 100) {
			Portf_output(0x02);
			return;
		}
		//LCD_WriteCommand(1);
}

//****************** compute lat and lon from gps *********
void compute_lat_lon() {
	int temp;
	long double temp_2;
	long double distance;
	char valid_bit_index;
	char valid_bit;
	long double speed;
	 char total_distance_in_string[6];
 	unsigned char data_begin = data.data_start[0];
	valid_bit_index = data.data_start[4];
	valid_bit_index++;
	valid_bit = data.buffer[valid_bit_index];
	//valid_bit = '1';
	if (valid_bit == '1') {
		speed = get_speed(data.data_start_speed[5]);
		//sprintf(total_distance_in_string, "%0.2Lf", speed);
		//LCD_WriteCommand(1);
		//LCD_DisplayString(total_distance_in_string);
		//LCD_DisplayString("-");
		//if (speed > 1.5){
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

			if (speed > 1.5){
				distance = distanceBetween();
				data.total_distance += distance;
				senddouble_Uart2(data.current_lat);
				SendData_UART2(',');
				senddouble_Uart2(data.current_lon);
				SendData_UART2(',');
			}
			data.prev_lat = data.current_lat;
			data.prev_lon = data.current_lon;
		//}
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
    long double longitude;
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

//****************** get speed ************************
long double get_speed(unsigned char speed_pointer)
{
		char *ptr;
    unsigned char speed_index = speed_pointer + 1;
    unsigned char index = 0;
    char speed_buffer[15];
    long double speed;
    for (; data.buffer_speed[speed_index] != ','; speed_index++) {
        speed_buffer[index] = data.buffer_speed[speed_index];
        index++;
    }
    speed_index++;
    speed = strtold(speed_buffer, &ptr);
	return speed;
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
