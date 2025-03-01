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

/* T�nh dau ra tu PID */
float PID_Compute(PID_Controller *pid, float currentAngle, float targetAngle);

/* �oc th�ng so PID tu Flash */
void PID_LoadFromFlash(PID_Controller *pid);

/* Luu th�ng so PID v�o Flash */
void PID_SaveToFlash(PID_Controller *pid);

/* Tu dong c�n chinh PID d�ng Ziegler-Nichols */
/*Ziegler-Nichols la gi thi tu di m� tra gg :)))*/
void PID_AutoTune(PID_Controller *pid, float getAngle, void (*setMotorSpeed)(float));

#endif

