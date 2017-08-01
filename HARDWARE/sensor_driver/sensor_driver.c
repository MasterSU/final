#include "sensor_driver.h"

//define data struct
//struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SAngle 	stcAngle1;
//struct SMag 		stcMag;
//struct SDStatus stcDStatus;
//struct SPress 	stcPress;
//struct SLonLat 	stcLonLat;
//struct SGPSV 		stcGPSV;

//得到传感器数据
void CopeSerialData(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;
	if (ucRxBuffer[0]!=0x55) 
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}
	else
	{
		switch(ucRxBuffer[1])
		{
			//case 0x50:	memcpy(&stcTime,&ucRxBuffer[2],8);break;
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
			//case 0x54:	memcpy(&stcMag,&ucRxBuffer[2],8);break;
			//case 0x55:	memcpy(&stcDStatus,&ucRxBuffer[2],8);break;
			//case 0x56:	memcpy(&stcPress,&ucRxBuffer[2],8);break;
			//case 0x57:	memcpy(&stcLonLat,&ucRxBuffer[2],8);break;
			//case 0x58:	memcpy(&stcGPSV,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;
	}
}
//得到传感器数据
void CopeSerialData1(unsigned char ucData)
{
	static unsigned char ucRxBuffer1[250];
	static unsigned char ucRxCnt1 = 0;	
	
	ucRxBuffer1[ucRxCnt1++]=ucData;
	if (ucRxBuffer1[0]!=0x55) 
	{
		ucRxCnt1=0;
		return;
	}
	if (ucRxCnt1<11) {return;}
	else
	{
		switch(ucRxBuffer1[1])
		{
			//case 0x50:	memcpy(&stcTime,&ucRxBuffer1[2],8);break;
			//case 0x51:	memcpy(&stcAcc,&ucRxBuffer1[2],8);break;
			//case 0x52:	memcpy(&stcGyro,&ucRxBuffer1[2],8);break;
			case 0x53:	memcpy(&stcAngle1,&ucRxBuffer1[2],8);break;
			//case 0x54:	memcpy(&stcMag,&ucRxBuffer1[2],8);break;
			//case 0x55:	memcpy(&stcDStatus,&ucRxBuffer1[2],8);break;
			//case 0x56:	memcpy(&stcPress,&ucRxBuffer1[2],8);break;
			//case 0x57:	memcpy(&stcLonLat,&ucRxBuffer1[2],8);break;
			//case 0x58:	memcpy(&stcGPSV,&ucRxBuffer1[2],8);break;
		}
		ucRxCnt1=0;
	}
}
