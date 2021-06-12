#ifndef EEPROM_H_
#define EEPROM_H_
void EEPROM_Init();
void Erase();
void writeData(long double data);
void set_block_and_offset(int block ,int offset);
long double readData();
#endif