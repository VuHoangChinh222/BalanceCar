#include "safety.h"
#include "motor_control.h"
#include "stm32f1xx_hal.h"
#include "stdio.h"

// Bien trang th�i an to�n cuc (static gia gi� tri giua c�c lan gui)
static bool systemIsSafe = true;

void Safety_Init(void) {
    // Neu c� LED canh b�o th� cau h�nh GPIO o d�y
    systemIsSafe = true; // Mac dinh an to�n l�c khoi dong
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
    // V� du: tat dong co khi mat an to�n
    StopMotors();

    // Hien thi den canh bao
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET); // Bat LED canh b�o

//    printf("Warning: Tilt angle exceeded safety limit!\n");
}
