#include "robot_action.h"

u8 runtime_mode;   //我也不知道是啥
u8 robot_state;    //机器人行走方向
u16 global_speed;  //机器人移动速度


u8 stop_action()
{
    //对驱动器进行复位
    CAN_RoboModule_DRV_Reset(0,1);
    CAN_RoboModule_DRV_Reset(0,2);
    CAN_RoboModule_DRV_Reset(0,3);
    CAN_RoboModule_DRV_Reset(0,4);
    robot_delay_ms(1000);
}

void stop_move()
{
	CAN_RoboModule_DRV_OpenLoop_Mode(0,1,0);
	CAN_RoboModule_DRV_OpenLoop_Mode(0,2,0);
  CAN_RoboModule_DRV_OpenLoop_Mode(0,3,0);
  CAN_RoboModule_DRV_OpenLoop_Mode(0,4,0);
}
u8 move_init(unsigned char Mode)
{
    runtime_mode=Mode;
    //CAN1初始化
    CAN1_Configuration();
    robot_delay_ms(100);
    //对驱动器进行复位
    CAN_RoboModule_DRV_Reset(0,1);
    CAN_RoboModule_DRV_Reset(0,2);
    CAN_RoboModule_DRV_Reset(0,3);
    CAN_RoboModule_DRV_Reset(0,4);
	  CAN_RoboModule_DRV_Reset(1,1);
	  CAN_RoboModule_DRV_Reset(1,2);
    //发送复位指令后的延时必须要有，等待驱动器复位完毕。
    robot_delay_ms(1000);
    //配置为1s传回一次数据
    CAN_RoboModule_DRV_Config(0,1,100,0);
    CAN_RoboModule_DRV_Config(0,2,100,0);
    CAN_RoboModule_DRV_Config(0,3,100,0);
    CAN_RoboModule_DRV_Config(0,4,100,0);
	  CAN_RoboModule_DRV_Config(1,1,100,0);
    CAN_RoboModule_DRV_Config(1,2,100,0);
	  robot_delay_ms(1);
    //进入选择的模式
    CAN_RoboModule_DRV_Mode_Choice(0,1,Mode);
    CAN_RoboModule_DRV_Mode_Choice(0,2,Mode);
    CAN_RoboModule_DRV_Mode_Choice(0,3,Mode);
    CAN_RoboModule_DRV_Mode_Choice(0,4,Mode);
		CAN_RoboModule_DRV_Mode_Choice(1,1,Mode);
		CAN_RoboModule_DRV_Mode_Choice(1,2,Mode);
    //发送模式选择指令后，要等待驱动器进入模式就绪。所以延时也不可以去掉。
    robot_delay_ms(500);
    //检测驱动器是否掉线
    return motor_online_check();
}

u8 motor_online_check()
{
    //以广播发送形式检测四个电机是否在线
    CAN_RoboModule_DRV_Online_Check(0,0);
    robot_delay_ms(10);
    //如果在线返回1
    if(Real_Online[0]&&Real_Online[1]&&Real_Online[2]&&Real_Online[3])
        return 1;
    else return 0;
}

u8 move_forward(u16 speed)
{
	  CAN_RoboModule_DRV_OpenLoop_Mode(0,1,speed);
	  CAN_RoboModule_DRV_OpenLoop_Mode(0,2,0-speed);
	  CAN_RoboModule_DRV_OpenLoop_Mode(0,3,0-speed);
	  CAN_RoboModule_DRV_OpenLoop_Mode(0,4,speed);
}

u8 move_backword(u16 speed)
{
    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,0-speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,2,speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,3,speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,4,0-speed);
}

//u8 move_rurn_right(u16 speed,float angle,u16 correct_accuracy)
//{
//    move_turn_right_place(speed);
//    while(/*此处填写是否平移到指定位置的判断语句*/1)
//    {
//        //每次按指定精度平移
//        move_right_translation(speed,correct_accuracy);
//        //官方建议指令发送间隔10ms
//        robot_delay_ms(10);
//    }
//}

//u8 move_rurn_letf(u16 speed,float angle,u16 correct_accuracy)
//{
//    //move_turn_letf_place(speed,angle);
//    while(/*此处填写是否平移到指定位置的判断语句*/1)
//    {
//        //每次按指定精度平移
//        move_left_translation(speed,correct_accuracy);
//        //官方建议指令发送间隔10ms
//        robot_delay_ms(10);
//    }
//}

void move_left_translation(short speed)
{
    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,-speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,2,-speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,3,speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,4,speed);
}

void move_right_translation(short speed)
{
    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,2,speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,3,-speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,4,-speed);
}

void move_turn_place_pid(short speed)
{
	  CAN_RoboModule_DRV_OpenLoop_Mode(0,1,speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,2,speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,3,speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,4,speed);
}

void move_turn_right_place(short speed)
{
    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,2,speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,3,speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,4,speed);
}

void move_turn_left_place(short speed)
{
    CAN_RoboModule_DRV_OpenLoop_Mode(0,1,-speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,2,-speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,3,-speed);
    CAN_RoboModule_DRV_OpenLoop_Mode(0,4,-speed);
}
void emission_quickly(short speed)
{
	CAN_RoboModule_DRV_OpenLoop_Mode(1,1,-speed);
}
void emission_slow(short speed)
{
	CAN_RoboModule_DRV_OpenLoop_Mode(1,2,-speed);

}