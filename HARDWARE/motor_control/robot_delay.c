#include "robot_delay.h"

//���ڵ��������ͨ����ʱ��ms delay
void robot_delay_ms(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=10300;
 		while(a--);
	}
}

//���ڵ��������ͨ����ʱ��us delay
void robot_delay_us(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=9;
		while(a--);
	}
}
