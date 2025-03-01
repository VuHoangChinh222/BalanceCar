#ifndef ENCODER_H
#define ENCODER_H

#include "stm32f1xx_hal.h"

typedef struct {
    TIM_HandleTypeDef *htim;  // Con tro toi Timer (TIM2, TIM3,...)
    int16_t lastCount;        // Giá tri counter lan doc truoc
    int16_t speed;            // Toc do tính toán
} Encoder;

void Encoder_Init(Encoder *encoder, TIM_HandleTypeDef *htim);
int16_t Encoder_GetSpeed(Encoder *encoder);

#endif
