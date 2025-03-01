#ifndef PID_H
#define PID_H

#include <stdint.h>

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float prevError;
    float integral;
} PID_Controller;

/* Khoi tao PID voi tham so ban dau */
void PID_Init(PID_Controller *pid, float Kp, float Ki, float Kd);

/* Tính dau ra tu PID */
float PID_Compute(PID_Controller *pid, float currentAngle, float targetAngle);

/* Ðoc thông so PID tu Flash */
void PID_LoadFromFlash(PID_Controller *pid);

/* Luu thông so PID vào Flash */
void PID_SaveToFlash(PID_Controller *pid);

/* Tu dong cân chinh PID dùng Ziegler-Nichols */
/*Ziegler-Nichols la gi thi tu di mà tra gg :)))*/
void PID_AutoTune(PID_Controller *pid, float getAngle, void (*setMotorSpeed)(float));

#endif

