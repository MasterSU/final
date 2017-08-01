#include "robot_delay.h"

//用于电机驱动器通信延时的ms delay
void robot_delay_ms(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=10300;
 		while(a--);
	}
}

//用于电机驱动器通信延时的us delay
void robot_delay_us(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=9;
		while(a--);
	}
}
