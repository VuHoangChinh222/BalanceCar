#ifndef KALMAN_H
#define KALMAN_H

typedef struct {
    float Q_angle;
    float Q_bias;
    float R_measure;
    float angle;
    float bias;
    float rate;
    float P[2][2];
} KalmanFilter;

void Kalman_Init(KalmanFilter *kf, float initialAngle);
float Kalman_Update(KalmanFilter *kf, float newAngle, float newRate, float dt);

#endif
