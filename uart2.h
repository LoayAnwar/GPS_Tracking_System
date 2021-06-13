#ifndef UART_H_
#define UART2_H_
#include "stdint.h"

void UART2_Init(void);
uint8_t ReadData_uart2(void);
void SendData_UART2(char data);
void senddouble_Uart2(long double num);
#endif