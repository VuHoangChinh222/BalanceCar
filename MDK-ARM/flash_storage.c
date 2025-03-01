#include "flash_storage.h"
#include <string.h>

// Tính CRC32 don gian
uint32_t CalculateCRC32(const uint8_t *data, uint32_t length) {
    uint32_t crc = 0xFFFFFFFF;
    for (uint32_t i = 0; i < length; i++) {
			//Toan tu "^" là toan tu XOR
			// 1^1 =0; 0^0=0; 1^0=1
			//Vi du: len vietjack doc :)))
			//https://vietjack.com/lap_trinh_c/toan_tu_trong_c.jsp
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
							//Toan tu ">>" dich phai
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    return ~crc;
}

// Ghi PID vào flash
void Flash_SavePID(float Kp, float Ki, float Kd) {
    HAL_FLASH_Unlock();

    // Xóa page flash truoc khi ghi
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t pageError = 0;
    eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInit.PageAddress = FLASH_STORAGE_ADDRESS;
    eraseInit.NbPages = 1;

    HAL_FLASHEx_Erase(&eraseInit, &pageError);

    // Tao cau trúc du lieu can luu
    PID_Parameters pidParams;
    pidParams.Kp = Kp;
    pidParams.Ki = Ki;
    pidParams.Kd = Kd;

    // Tính CRC
    pidParams.crc = CalculateCRC32((uint8_t*)&pidParams, sizeof(PID_Parameters) - sizeof(uint32_t));

    // Ghi tung 32-bit vào flash
    uint32_t *data = (uint32_t*)&pidParams;
    for (uint32_t i = 0; i < sizeof(PID_Parameters) / 4; i++) {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_STORAGE_ADDRESS + i * 4, data[i]);
    }

    HAL_FLASH_Lock();
}

// Ðoc PID tu flash
int Flash_LoadPID(float *Kp, float *Ki, float *Kd) {
    PID_Parameters pidParams;
    memcpy(&pidParams, (void*)FLASH_STORAGE_ADDRESS, sizeof(PID_Parameters));

    // Kiem tra CRC de xác nhan du lieu hop le
    uint32_t calculatedCRC = CalculateCRC32((uint8_t*)&pidParams, sizeof(PID_Parameters) - sizeof(uint32_t));

    if (calculatedCRC != pidParams.crc) {
        // CRC không dúng
        return 0;  // Loi
    }

    *Kp = pidParams.Kp;
    *Ki = pidParams.Ki;
    *Kd = pidParams.Kd;

    return 1;  // Thành công
}
