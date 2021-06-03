#ifndef DIO_DRIVER_H_
#define DIO_DRIVER_H_

char ReadData(void);
void read_gps_data();
float get_latitude(unsigned char lat_pointer);
float get_longitude(unsigned char lon_pointer);
double degree_to_rad(double degree);

#endif