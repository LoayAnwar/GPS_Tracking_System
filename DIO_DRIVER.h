#ifndef DIO_DRIVER_H_
#define DIO_DRIVER_H_

void Portf_Init_input_Output(void);
int Portf_input(void);
void Portf_output(int data);
void Portb_Init_output(void);
void 	portE_init_output();

void Portb_output(char data);
void PortE_output(char data);
void Portd_Init_output(void);
void Portd_output(char data);
#endif