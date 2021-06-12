#include "tm4c123gh6pm.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"

void EEPROM_Init()
{
	SYSCTL_RCGCEEPROM_R |=0x01;
	EEPROM_EEBLOCK_R = 0;
	EEPROM_EEOFFSET_R =0 ;
}
void Erase()
{
	EEPROM_EEDBGME_R  = 0xE37B0001;
	while(EEPROM_EEDBGME_R&1);
}
void writeData(long double data)
{
	int i=0;
		char data_as_string[10];
	sprintf(data_as_string, "%Lf", data);
	for(i=0 ; data_as_string[i]!='\0';i++)
	{
		EEPROM_EERDWRINC_R =data_as_string[i];
		while(EEPROM_EEDONE_R & (1<<3));
	}
		EEPROM_EERDWRINC_R =data_as_string[i];
		while(EEPROM_EEDONE_R & (1<<3));
}


void set_block_and_offset(int block ,int offset)
{
	EEPROM_EEBLOCK_R = block;
	EEPROM_EEOFFSET_R =offset ;
}
long double readData()
{
	int index =0;
	char data_as_string[50];
	char data;
	long double d ;
	while(1)
	{
		data = EEPROM_EERDWRINC_R;
		while(EEPROM_EEDONE_R & (1<<0));
		if(data!= '\0')
		{
			data_as_string[index] =data ;
			index++;
		}
		else
		{
			data_as_string[index] =data ;
			index++;	
			d= strtold(data_as_string, NULL);
			return d;
		}
}
}