#include "pid_control.h"
//定义PID控制器内部结构体
typedef struct {
  float kp;
	float ki;
	float kd;
	float last_error;
	float now_error;
	float integral_sum;
	float differential;
	float integral_interval;
	float differential_interval;
	float set_angle;
}pid_typedef;

u8 pid_running; //是否打开PID标志

pid_typedef *mypid_typedef;  //初始化PID内部结构体

//初始化PID控制器
//pidv：外部定义的pid参数
void pid_control_init(pid_value *pidv)
{
	mypid_typedef=(pid_typedef *)malloc(sizeof(pid_typedef));
	//timer config
	//
	//set pid data
	mypid_typedef->kd = pidv->kd;
	mypid_typedef->ki = pidv->ki;
	mypid_typedef->kp = pidv->kp;
	mypid_typedef->integral_interval = pidv->integral_interval;
	mypid_typedef->differential_interval = pidv->differential_interval;
	mypid_typedef->set_angle = pidv->set_angle;
	mypid_typedef->last_error = 0;
	mypid_typedef->now_error = 0;
	mypid_typedef->integral_sum = 0;
	mypid_typedef->differential = 0;
	//pid_control_start();
}

//在运行时修改pid的参数
void pid_control_setvalue(pid_value *pidv)
{
	pid_control_suspend();
	mypid_typedef->kd = pidv->kd;
	mypid_typedef->ki = pidv->ki;
	mypid_typedef->kp = pidv->kp;
	mypid_typedef->integral_interval = pidv->integral_interval;
	mypid_typedef->differential_interval = pidv->differential_interval;
	pid_control_start();
}

//挂起pid
void pid_control_suspend()
{
	pid_running = 0;
}

//开始pid
void pid_control_start()
{
	pid_running = 1;
}

//pid
float pid_control_refresh()
{
	//如果是向前或者后退才执行pid
	if(robot_state==forward||robot_state==back)
	{
		float Output=0;
		//get error
		mypid_typedef->now_error = mypid_typedef->set_angle - (float)stcAngle.Angle[2]/32768*180;
		printf("Angle: %.1f\r\n",(float)stcAngle.Angle[2]/32768*180);
		printf("mypid_typedef->now_error: %.1f\r\n",mypid_typedef->now_error);
		//wu cha dai      ----ZhengHao Xu
		if(mypid_typedef->now_error <= 5.0f && mypid_typedef->now_error >= -5.0f) 
		{
			mypid_typedef->last_error = mypid_typedef->now_error;
			//判断是前进还是后退
			if(robot_state==forward) move_forward(global_speed);
			else if(robot_state==back) move_backword(global_speed);
			return Output;
		}
		else
		{
			//integral
			mypid_typedef->integral_sum += (mypid_typedef->now_error * mypid_typedef->integral_interval);   
			//differential
			mypid_typedef->differential = (mypid_typedef->now_error - mypid_typedef->last_error) / mypid_typedef->differential_interval;      
			//get pid value
			Output = mypid_typedef->kp * mypid_typedef->now_error + mypid_typedef->ki * mypid_typedef->integral_sum + mypid_typedef->kd * mypid_typedef->differential; 
			//refresh last error	
			mypid_typedef->last_error = mypid_typedef->now_error;     
			//return pid value
			//stop_move();
			/*if(mypid_typedef->now_error < 0)
			{
				//global_speed += (int)Output;
				//move_turn_right_place((int)Output,2);
				move_turn_left_place((int)Output,2);
			}
			else
			{
				move_turn_right_place((int)Output,2);
				//move_turn_left_place(0-(int)Output,2);
			}*/
			//将pid结果传入电机控制函数
			move_turn_place_pid(0-(int)Output);
			//printf("Output: %d\r\n",(int)Output);
			return Output;
		}
	}
}
