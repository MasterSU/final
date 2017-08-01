#ifndef _SENSORDRIVER_H
#define _SENSORDRIVER_H
#include "JY901.h"
#include "string.h"

//extern struct STime		stcTime;
extern struct SAcc 		stcAcc;
extern struct SGyro 		stcGyro;
extern struct SAngle 	stcAngle;
extern struct SAngle 	stcAngle1;
//extern struct SMag 		stcMag;
//extern struct SDStatus stcDStatus;
//extern struct SPress 	stcPress;
//extern struct SLonLat 	stcLonLat;
//extern struct SGPSV 		stcGPSV;

void CopeSerialData(unsigned char ucData);
void CopeSerialData1(unsigned char ucData);
#endif
