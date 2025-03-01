#ifndef FLASH_STORAGE_H
#define FLASH_STORAGE_H

#include "stm32f1xx_hal.h"

#define FLASH_STORAGE_ADDRESS 0x0800FC00  // Ðia chi page cuoi cua F103C8T6 (64KB Flash)
//Link tài lieu giai thich: https://khuenguyencreator.com/lap-trinh-stm32-flash-doc-ghi-va-xoa-du-lieu/

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    uint32_t crc;  // CRC de kiem tra du lieu hop le
} PID_Parameters;

void Flash_SavePID(float Kp, float Ki, float Kd);
int Flash_LoadPID(float *Kp, float *Ki, float *Kd);
uint32_t CalculateCRC32(const uint8_t *data, uint32_t length);

#endif
