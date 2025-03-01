#include "encoder.h"

/**
 * @brief Khoi tao encoder v� start timer.
 * @param encoder: Con tro tai struct encoder.
 * @param htim: Con tro tai timer handle (v� du: &htim2).
 */
void Encoder_Init(Encoder *encoder, TIM_HandleTypeDef *htim) {
    encoder->htim = htim;
    encoder->lastCount = __HAL_TIM_GET_COUNTER(htim);
    encoder->speed = 0;

    // Bat dau Timer che do Encoder
    HAL_TIM_Encoder_Start(encoder->htim, TIM_CHANNEL_ALL);
}

/**
 * @brief �oc v� t�nh toc do.
 * @param encoder: Con tro tai struct encoder.
 * @return Toc do.
 */
int16_t Encoder_GetSpeed(Encoder *encoder) {
    int16_t currentCount = (int16_t)__HAL_TIM_GET_COUNTER(encoder->htim);  // �p kieu ve signed 16-bit
    int16_t delta = currentCount - encoder->lastCount;

    // Update last count de lan sau t�nh tiep
    encoder->lastCount = currentCount;

    // Handle overflow v� underflow
    if (delta > 32767) {
        delta -= 65536;  // Tr�n nguoc (forward overflow)
    } else if (delta < -32767) {
        delta += 65536;  // Tr�n xu�i (backward overflow)
    }

    encoder->speed = delta;
    return encoder->speed;
}
