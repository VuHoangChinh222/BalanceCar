#include "mpu6050.h"
#include <math.h>

// Các thanh ghi MPU6050
#define MPU6050_REG_PWR_MGMT_1    0x6B
#define MPU6050_REG_ACCEL_XOUT_H  0x3B
#define MPU6050_REG_GYRO_XOUT_H   0x43

uint8_t MPU6050_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t check, data;

    // Ki?m tra WHO_AM_I
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, 0x75, 1, &check, 1, HAL_MAX_DELAY);
    if (check != 0x68) return 1;  // Không tìm th?y MPU6050

    // Ðánh th?c MPU6050
    data = 0x00;
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_REG_PWR_MGMT_1, 1, &data, 1, HAL_MAX_DELAY);

    // C?u hình Gyro và Accel
    data = 0x08;  // ±4g
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, 0x1C, 1, &data, 1, HAL_MAX_DELAY);

    data = 0x18;  // ±2000 °/s
    HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, 0x1B, 1, &data, 1, HAL_MAX_DELAY);

    return 0;  // Thành công
}

void MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_Data *data) {
    uint8_t buffer[14];

    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_REG_ACCEL_XOUT_H, 1, buffer, 14, HAL_MAX_DELAY);

    int16_t accelX = (buffer[0] << 8) | buffer[1];
    int16_t accelY = (buffer[2] << 8) | buffer[3];
    int16_t accelZ = (buffer[4] << 8) | buffer[5];
    int16_t gyroX = (buffer[8] << 8) | buffer[9];
    int16_t gyroY = (buffer[10] << 8) | buffer[11];
    int16_t gyroZ = (buffer[12] << 8) | buffer[13];

    data->accelX = accelX / 8192.0f;  // ±4g
    data->accelY = accelY / 8192.0f;
    data->accelZ = accelZ / 8192.0f;
    data->gyroX = gyroX / 16.4f;  // ±2000°/s
    data->gyroY = gyroY / 16.4f;
    data->gyroZ = gyroZ / 16.4f;

    // Tính góc don gi?n t? gia t?c k? (d? so sánh v?i Kalman)
    data->angleX = atan2f(data->accelY, data->accelZ) * 180.0f / 3.141592653589793 ;
    data->angleY = atan2f(-data->accelX, sqrtf(data->accelY * data->accelY + data->accelZ * data->accelZ)) * 180.0f / 3.141592653589793;
}

float MPU6050_GetPitch(MPU6050_Data *data) {
    return data->angleX;
}

float MPU6050_GetRoll(MPU6050_Data *data) {
    return data->angleY;
}
