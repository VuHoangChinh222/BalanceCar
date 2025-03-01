#include "safety.h"
#include "motor_control.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"

// Bien trang thái an toàn cuc (static gia giá tri giua các lan gui)
static bool systemIsSafe = true;

void Safety_Init(void) {
    // Neu có LED canh báo thì cau hình GPIO o dây
    systemIsSafe = true; // Mac dinh an toàn lúc khoi dong
}

bool Safety_CheckTiltAngle(float angle, float maxAngle) {
    if (angle > maxAngle || angle < -maxAngle) {
        Safety_UpdateStatus(false);
        return true;
    } else {
        Safety_UpdateStatus(true);
        return false;
    }
}

void Safety_UpdateStatus(bool isSafe) {
    systemIsSafe = isSafe;

    if (!isSafe) {
        Safety_TriggerWarning();
    }
}

bool Safety_IsSafe(void) {
    return systemIsSafe;
}

void Safety_TriggerWarning(void) {
    // Ví du: tat dong co khi mat an toàn
    StopMotors();

    // Hien thi den canh bao
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET); // Bat LED canh báo

//    printf("Warning: Tilt angle exceeded safety limit!\n");
}
