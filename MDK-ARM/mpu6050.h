#ifndef MPU6050_H
#define MPU6050_H

#include "stm32f1xx_hal.h"

#define MPU6050_ADDR (0x68 << 1)  // Ð?a ch? I2C (shifted 1 bit)

typedef struct {
    float accelX;
    float accelY;
    float accelZ;
    float gyroX;
    float gyroY;
    float gyroZ;
    float angleX;
    float angleY;
} MPU6050_Data;

uint8_t MPU6050_Init(I2C_HandleTypeDef *hi2c);
void MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_Data *data);
float MPU6050_GetPitch(MPU6050_Data *data);
float MPU6050_GetRoll(MPU6050_Data *data);

#endif
