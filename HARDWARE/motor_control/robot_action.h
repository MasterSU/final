#ifndef _ROBOTACTION_
#define _ROBOTACTION_
#include "sys.h"
#include "motor_driver.h"
#include "robot_delay.h"
#include "sensor_driver.h"

#define stop         0x60
#define forward      0x61
#define back         0x62
#define left_remove  0x63
#define right_remove 0x64
#define left_place   0x65
#define right_place  0x66

extern u16 global_speed;
extern u8 robot_state;

//��λ������
u8 stop_action(void);
//ֹͣ��ǰ����
void stop_move(void);
//���ߵ����ʼ��
u8 move_init(unsigned char Mode);
//��ǰ�ƶ�
u8 move_forward(u16 speed);
//����ƶ�
u8 move_backword(u16 speed);
//
//u8 move_rurn_right(u16 speed,float angle,u16 correct_accuracy);

//u8 move_rurn_letf(u16 speed,float angle,u16 correct_accuracy);
//��ƽ��
void move_left_translation(short speed);
//��ƽ��
void move_right_translation(short speed);

void move_turn_place_pid(short speed);
//ԭ����ת
void move_turn_right_place(short speed);
//ԭ����ת
void move_turn_left_place(short speed);

u8 motor_online_check(void);
void emission_quickly(short speed);
void emission_slow(short speed);
#endif // _ROBOTACTION_
