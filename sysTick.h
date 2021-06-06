#ifndef sysTick_H_
#define sysTick_H_

void sysTickInit(void);

void sysTickWait(int delay) ;
void sysTickWait1Ms(unsigned long  delay);

#endif