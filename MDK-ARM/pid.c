#include "pid.h"
#include "flash_storage.h"
#include <math.h>
#include <stdio.h>

/* Khoi tao PID */
void PID_Init(PID_Controller *pid, float Kp, float Ki, float Kd) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->prevError = 0.0f;
    pid->integral = 0.0f;
}

/* T�nh to�n dau ra PID */
float PID_Compute(PID_Controller *pid, float currentAngle, float targetAngle) {
    float error = targetAngle - currentAngle;

    pid->integral += error;
    float derivative = error - pid->prevError;

    pid->prevError = error;

    float output = pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;
		if(output<-1000)
			return -1000;
		else if(output>1000)
			return 1000;
		else
			return output;
}

/* �oc th�ng so PID tu Flash */
void PID_LoadFromFlash(PID_Controller *pid) {
    float Kp, Ki, Kd;
    Flash_LoadPID(&Kp, &Ki, &Kd);
    PID_Init(pid, Kp, Ki, Kd);
}

/* Luu th�ng so PID v�o Flash */
void PID_SaveToFlash(PID_Controller *pid) {
    Flash_SavePID(pid->Kp, pid->Ki, pid->Kd);
}

/* Tu dong c�n chinh PID - Ziegler-Nichols */
void PID_AutoTune(PID_Controller *pid, float getAngle, void (*setMotorSpeed)(float)) {
    float Ku = 0.0f;  // Ultimate Gain (Gain l�m he dao dong li�n tuc)
    float Tu = 0.0f;  // Ultimate Period (chu ky dao dong)

    // �at motor speed nhu thang bang ban dau
    setMotorSpeed(0.0f);

    float lastAngle = getAngle;
    float maxAngle = -999.0f, minAngle = 999.0f;
    int oscillationCount = 0;

    uint32_t startTime = HAL_GetTick();
//    uint32_t lastTime = startTime;

    // Tang dan de gain toi khi xe dao dong li�n tuc
    float testKp = 1.0f;  // Start tu gi� tri Kp nho
    pid->Kp = testKp;
    pid->Ki = 0;  // Tat t�ch ph�n
    pid->Kd = 0;  // Tat vi ph�n

    setMotorSpeed(0.0f);
    HAL_Delay(500);

    while (oscillationCount < 10) {
        float angle = getAngle;
        float output = PID_Compute(pid, angle, 0.0f);
        setMotorSpeed(output);

        if (angle > maxAngle) maxAngle = angle;
        if (angle < minAngle) minAngle = angle;

        if ((lastAngle < 0 && angle > 0) || (lastAngle > 0 && angle < 0)) {
            oscillationCount++;
            if (oscillationCount == 1) {
                startTime = HAL_GetTick();
            } else if (oscillationCount == 3) {
                uint32_t now = HAL_GetTick();
                Tu = (now - startTime) / 2.0f;  // Chu ky dao dong
                break;
            }
        }
        lastAngle = angle;

        HAL_Delay(20);
    }

    Ku = testKp;  // Ku = Kp tai nguong dao dong li�n tuc

    // �p dung c�ng thuc Ziegler-Nichols
    pid->Kp = 0.6f * Ku;
    pid->Ki = 1.2f * Ku / Tu;
    pid->Kd = 0.075f * Ku * Tu;

    // In debug th�ng so
    printf("Auto-tuned PID: Kp = %.3f, Ki = %.3f, Kd = %.3f\n", pid->Kp, pid->Ki, pid->Kd);

    // Luu loi v�o Flash de d�ng sau
    PID_SaveToFlash(pid);
}
