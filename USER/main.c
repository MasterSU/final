#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "my_usart.h"
#include "sensor_driver.h"
#include "pid_control.h"
#include "timer.h"
#include "robot_action.h"
#include "beep.h"
#include "motor_ps2.h"
#include "24l01.h"
u8 rxbuff[32]={0};
short button1=0;
short button2=0;
void send(void);
int main(void)
{
	u8 key;
	//u8 tmp_buf[32];
	static u8 key_up=1;
	pid_value pid; //定义pid参数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168); //初始化滴答定时器
	//蜂鸣器初始化
	BEEP_Init();
	//初始化电机控制器 ---位置模式
	move_init(OpenLoop_Mode);
	//检测电机控制器是否在线
//	if(!motor_online_check())
//	{
//		while(1)
//			GPIO_SetBits(GPIOF,GPIO_Pin_8);
//	}
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);
	uart_init(115200); //上位机通信串口初始化
	usart2_init(115200); //陀螺仪通信串口初始化
	usart3_init(115200);
	NRF24L01_Init(); 
	while(NRF24L01_Check())
	{
		GPIO_SetBits(GPIOF,GPIO_Pin_8);
	}
	GPIO_ResetBits(GPIOF,GPIO_Pin_8);
	NRF24L01_TX_Mode();
	PS2_Init();	
	PS2_SetInit();
	pid_control_suspend(); //挂起pid
	timer2_init(1000-1,8400-1);  //打开pid定时器2 100ms
	//timer3_init(1000-1,8400-1);
	//设置pid参数
	pid.kp = 25.0f;
	pid.ki = 0.0f;
	pid.kd = 0.0f;
	pid.set_angle = 13.0f;
	pid.integral_interval = 50.0f;
	pid.differential_interval = 50.0f;
	//初始化pid控制器
	pid_control_init(&pid);
	delay_ms(800);
	//打开pid
	//pid_control_start();
	//设置机器人移动速度为500 前进后退
	global_speed = 1300;
	//停止移动等待遥控指令
	stop_move();
  while(1)
	{
		//按钮上 前进，按钮下 后退，按钮左 原地左转，按钮右 原地右转
		//三角 button1加速，方块 button2加速，X 停止机器人移动
		//R2 击发舵机，L1 左平移，R1 右平移，L2+三角 button1减速
		//L2+方块 button2减速，L2+圆 向上抬升，圆 向下抬升
    key=PS2_DataKey();
		if(key_up&&key!=0)                   //有按键按下
    {
			key_up=0;
			
			if(key==5)  //前进
			{
				robot_state=forward;
				move_forward(global_speed);
			}
				//delay_ms(500);
			else if(key==6)  //原地右转
			{
				robot_state=right_place;
				move_turn_right_place(global_speed);
			}
			  //delay_ms(500);
			else if(key==7)  //后退
			{
				robot_state=back;
				move_backword(global_speed);
			}
			  //delay_ms(500);
			else if(key==8)  //原地左转
			{
				robot_state=left_place;
				move_turn_left_place(global_speed);
			}
			  // delay_ms(500); 
	
			else if(key==9)   
			{
				/*button2=button2-500;
				if(button2<=0)
					button2=0;
				emission_slow(button2);*/
				
			}
			else if(key==11)
			{
				move_left_translation(global_speed);
			}
			else if(key==12)
			{
				move_right_translation(global_speed);
			}
			else if(key==13) 
			{
				//TODO
				button1=button1+500;
				if(button1>=5000)
					button1=5000;
				emission_quickly(button1);
				
			}
			  // delay_ms(500); 
			else if(key==14)  //原地左转
			{
				//TODO
				/*button1=button1-500;
				if(button1<=0)
					button1=0;
				emission_quickly(button1);*/
				
			}
			  // delay_ms(500); 
			else if(key==15)  //原地左转
			{
				robot_state=stop;
				stop_move();
			}
			  // delay_ms(500); 
			else if(key==16)  //原地左转
			{
				//TODO
				button2=button2+500;
				if(button2>=5000)
					button2=5000;
				emission_slow(button2);
				
			}
			  // delay_ms(500); 
    }
		else if(!key)
			key_up=1;
		
		send();
		//delay_ms(50);
	}	 
}

void send(void)
{
	sprintf((char*)rxbuff+0,"%d",button1);
	sprintf((char*)rxbuff+4,"%d",button2);
	sprintf((char*)rxbuff+8,"%.1f",(float)stcAngle1.Angle[0]/32768*180);
	sprintf((char*)rxbuff+13,"%.1f",(float)stcAngle.Angle[1]/32768*180);
	sprintf((char*)rxbuff+18,"%.1f",(float)stcAngle.Angle[2]/32768*180);
	while(NRF24L01_TxPacket(rxbuff)!=TX_OK);
	memset(rxbuff,0,32);
	/*rxbuff[12]=(u8)(temp);
	rxbuff[11]=(u8)(((int)(temp))>>8);
	rxbuff[10]=(u8)(((int)(temp))>>16);
	rxbuff[9]=(u8)(((int)(temp))>>24);*/
	//temp=(float)stcAngle.Angle[1]/32768*180;
	/*rxbuff[17]=(u8)(temp);
	rxbuff[16]=(u8)(((int)(temp))>>8);
	rxbuff[15]=(u8)(((int)(temp))>>16);
	rxbuff[14]=(u8)(((int)(temp))>>24);*/
	//temp=(float)stcAngle.Angle[2]/32768*180;
	/*rxbuff[22]=(u8)(temp);
	rxbuff[21]=(u8)(((int)(temp))>>8);
	rxbuff[20]=(u8)(((int)(temp))>>16);
	rxbuff[19]=(u8)(((int)(temp))>>24);*/
	
}

