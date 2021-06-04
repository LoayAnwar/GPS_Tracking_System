#ifndef gps_H_
#define gps_H_

//unsigned char is_N_or_S, is_E_or_W;
//uint8_t data_start[20]; 
void read_gps_data();
float get_latitude(unsigned char lat_pointer);
float get_longitude(unsigned char lon_pointer);
double get_distance(double current_lat, double current_lon, double prev_lat, double prev_lon);

#endif