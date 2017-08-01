#include "robot_action.h"

u8 runtime_mode;   //��Ҳ��֪����ɶ
u8 robot_state;    //���������߷���
u16 global_speed;  //�������ƶ��ٶ�


u8 stop_action()
{
    //�����������и�λ
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
    //CAN1��ʼ��
    CAN1_Configuration();
    robot_delay_ms(100);
    //�����������и�λ
    CAN_RoboModule_DRV_Reset(0,1);
    CAN_RoboModule_DRV_Reset(0,2);
    CAN_RoboModule_DRV_Reset(0,3);
    CAN_RoboModule_DRV_Reset(0,4);
	  CAN_RoboModule_DRV_Reset(1,1);
	  CAN_RoboModule_DRV_Reset(1,2);
    //���͸�λָ������ʱ����Ҫ�У��ȴ���������λ��ϡ�
    robot_delay_ms(1000);
    //����Ϊ1s����һ������
    CAN_RoboModule_DRV_Config(0,1,100,0);
    CAN_RoboModule_DRV_Config(0,2,100,0);
    CAN_RoboModule_DRV_Config(0,3,100,0);
    CAN_RoboModule_DRV_Config(0,4,100,0);
	  CAN_RoboModule_DRV_Config(1,1,100,0);
    CAN_RoboModule_DRV_Config(1,2,100,0);
	  robot_delay_ms(1);
    //����ѡ���ģʽ
    CAN_RoboModule_DRV_Mode_Choice(0,1,Mode);
    CAN_RoboModule_DRV_Mode_Choice(0,2,Mode);
    CAN_RoboModule_DRV_Mode_Choice(0,3,Mode);
    CAN_RoboModule_DRV_Mode_Choice(0,4,Mode);
		CAN_RoboModule_DRV_Mode_Choice(1,1,Mode);
		CAN_RoboModule_DRV_Mode_Choice(1,2,Mode);
    //����ģʽѡ��ָ���Ҫ�ȴ�����������ģʽ������������ʱҲ������ȥ����
    robot_delay_ms(500);
    //����������Ƿ����
    return motor_online_check();
}

u8 motor_online_check()
{
    //�Թ㲥������ʽ����ĸ�����Ƿ�����
    CAN_RoboModule_DRV_Online_Check(0,0);
    robot_delay_ms(10);
    //������߷���1
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
//    while(/*�˴���д�Ƿ�ƽ�Ƶ�ָ��λ�õ��ж����*/1)
//    {
//        //ÿ�ΰ�ָ������ƽ��
//        move_right_translation(speed,correct_accuracy);
//        //�ٷ�����ָ��ͼ��10ms
//        robot_delay_ms(10);
//    }
//}

//u8 move_rurn_letf(u16 speed,float angle,u16 correct_accuracy)
//{
//    //move_turn_letf_place(speed,angle);
//    while(/*�˴���д�Ƿ�ƽ�Ƶ�ָ��λ�õ��ж����*/1)
//    {
//        //ÿ�ΰ�ָ������ƽ��
//        move_left_translation(speed,correct_accuracy);
//        //�ٷ�����ָ��ͼ��10ms
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