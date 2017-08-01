#ifndef _PIDCONTROL_H
#define _PIDCONTROL_H
#include "sys.h"
#include "robot_action.h"
#include "sensor_driver.h"

typedef struct {
	float kp;
	float ki;
	float kd;
	float integral_interval;
	float differential_interval;
	float set_angle;
}pid_value;
	
extern u8 pid_running;
void pid_control_init(pid_value *pidv);
void pid_control_setvalue(pid_value *pidv);
void pid_control_suspend(void);
void pid_control_start(void);
float pid_control_refresh(void);
#endif
