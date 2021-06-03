#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define buffer_size 80
#define data_no 20
#define pi 3.14159265358979323846
                      
unsigned char data_start[data_no]; 
char CommaCounter;
volatile unsigned int buffer_index;
volatile unsigned char  is_GGA = 0;
char buffer[buffer_size];              
char GGA[3];

char ReadData(void){

    while(UART1_FR_R & 0x0010 != 0);
    return ((char)(UART1_DR_R& 0xFF));
}



void  read_gps_data()
{
    unsigned char received_char;
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