
#define NVIC_ST_CTRL_R (*( (volatile int *) 0xE000E010))
#define NVIC_ST_RELOAD_R ( *((volatile int *) 0xE000E014))
#define NVIC_ST_CURRENT_R (*((volatile int *) 0xE000E018))

void sysTickInit(void)
{
	NVIC_ST_CTRL_R =0;
	NVIC_ST_CURRENT_R =0 ;
	NVIC_ST_CTRL_R = 0x00000005;
	
}

void sysTickWait(int delay)
{
	NVIC_ST_RELOAD_R =delay-1;
	while((NVIC_ST_CTRL_R & 0x00010000)==0) ;
	
}

void sysTickWait1Ms(unsigned long  delay)
{
	unsigned long i;
	for( i=0 ;i<delay ;i++)
	{
		sysTickWait(16000);
	}
}