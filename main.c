#include "tm4c123gh6pm.h"
#include "DIO_DRIVER.h"
#include "gps.h"
//#include "sysTick.h"

void SystemInit()
{
	
}
int __main (void)
{
 
	if(total_distance > =100){
	    Portf_output(0x02);
   }
	
}
