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

//复位控制器
u8 stop_action(void);
//停止当前动作
void stop_move(void);
//行走电机初始化
u8 move_init(unsigned char Mode);
//向前移动
u8 move_forward(u16 speed);
//向后移动
u8 move_backword(u16 speed);
//
//u8 move_rurn_right(u16 speed,float angle,u16 correct_accuracy);

//u8 move_rurn_letf(u16 speed,float angle,u16 correct_accuracy);
//左平移
void move_left_translation(short speed);
//右平移
void move_right_translation(short speed);

void move_turn_place_pid(short speed);
//原地右转
void move_turn_right_place(short speed);
//原地左转
void move_turn_left_place(short speed);

u8 motor_online_check(void);
void emission_quickly(short speed);
void emission_slow(short speed);
#endif // _ROBOTACTION_
