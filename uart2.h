#ifndef UART2_H_
#define UART2_H_

void UART2_Init(void);
char ReadData_uart2(void);
void SendData_UART2(char data);
void senddouble_Uart2(long double num);
#endif