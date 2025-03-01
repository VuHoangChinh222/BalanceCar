//#ifndef MOTOR_CONTROL_H
//#define MOTOR_CONTROL_H

//void Motor_SetSpeed(float speed1, float speed2);
//void StopMotors(void);

//#endif
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include "stm32f1xx_hal.h"

typedef enum {
    MOTOR_STOP = 0,
    MOTOR_FORWARD,
    MOTOR_BACKWARD
} MotorDirection;

void Motor_Init(void);
void Motor_SetSpeed(float speedLeft, float speedRight);
void Motor_SetDirection(MotorDirection dirLeft, MotorDirection dirRight);
void StopMotors(void);

#endif
