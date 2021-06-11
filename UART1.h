#ifndef UART_H_
#define UART1_H_

void UART_Init(void);
void UART0_Init(void);
char ReadData(void);
char ReadData_UART0(void);
void SendData_UART0(char data);
void sendString_Uart0(char* string);
#endif