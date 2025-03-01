#include "motor_control.h"

// Gia su tin hieu dao chieu (motor trái) - GPIOA_PIN11
// Gia su tin hieu dao chieu (motor phai) - GPIOA_PIN10

#define LEFT_PIN   GPIO_PIN_11
#define RIGHT_PIN   GPIO_PIN_10
#define GPIO_PORT_MT GPIOA

extern TIM_HandleTypeDef htim1;  // PWM dùng TIM1_CH1 & TIM1_CH2

void Motor_Init(void) {
    // Cau hình GPIO
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = LEFT_PIN |  RIGHT_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    StopMotors();
}

void Motor_SetSpeed(float speedLeft, float speedRight) {
    uint16_t pwmLeft = (uint16_t) (__fabs(speedLeft) * 999);   // Ti le 0 - 100% tuong ung 0 - 999
    uint16_t pwmRight = (uint16_t) (__fabs(speedRight) * 999);

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwmLeft);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwmRight);

    MotorDirection dirLeft = (speedLeft >= 0) ? MOTOR_FORWARD : MOTOR_BACKWARD;
    MotorDirection dirRight = (speedRight >= 0) ? MOTOR_FORWARD : MOTOR_BACKWARD;

    Motor_SetDirection(dirLeft, dirRight);
}

void Motor_SetDirection(MotorDirection dirLeft, MotorDirection dirRight) {
    // Motor trái
    switch (dirLeft) {
        case MOTOR_FORWARD:
            HAL_GPIO_WritePin(GPIO_PORT_MT, LEFT_PIN, GPIO_PIN_RESET);
            break;
        case MOTOR_BACKWARD:
            HAL_GPIO_WritePin(GPIO_PORT_MT, LEFT_PIN, GPIO_PIN_SET);
            break;
        case MOTOR_STOP:
        default:
            HAL_GPIO_WritePin(GPIO_PORT_MT, LEFT_PIN, GPIO_PIN_RESET);
            break;
    }
    // Motor phai
    switch (dirRight) {
        case MOTOR_FORWARD:
            HAL_GPIO_WritePin(GPIO_PORT_MT, RIGHT_PIN, GPIO_PIN_RESET);
            break;
        case MOTOR_BACKWARD:
            HAL_GPIO_WritePin(GPIO_PORT_MT, RIGHT_PIN, GPIO_PIN_SET);
            break;
        case MOTOR_STOP:
        default:
            HAL_GPIO_WritePin(GPIO_PORT_MT, RIGHT_PIN, GPIO_PIN_RESET);
            break;
    }
}

void StopMotors(void) {
    Motor_SetSpeed(0, 0);
    Motor_SetDirection(MOTOR_STOP, MOTOR_STOP);
}
