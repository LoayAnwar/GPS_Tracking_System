#ifndef gps_H_
#define gps_H_


void read_gps_data();
float get_latitude(unsigned char lat_pointer);
float get_longitude(unsigned char lon_pointer);
double get_distance(double current_lat, double current_lon, double prev_lat, double prev_lon);

#endif