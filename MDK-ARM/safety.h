#ifndef SAFETY_H
#define SAFETY_H

#include <stdbool.h>


void Safety_Init(void);
/**
 * @brief Kiem tra xem g�c nghi�ng hien tai c� vuot nguong kh�ng.
 * @param angle G�c hien tai.
 * @param maxAngle Nguong gioi han an to�n .
 * @return true neu vuot qu� nguong => Kh�ng an to�n.
 */
bool Safety_CheckTiltAngle(float angle, float maxAngle);

void Safety_TimerCheck(void);
/**
 * @brief Cap nhat trang th�i an to�n.
 * @param isSafe Trang th�i an to�n hien tai (true = an to�n, false = khong gi�n).
 */
void Safety_UpdateStatus(bool isSafe);

/**
 * @brief Lay trang th�i an to�n hien tai.
 * @return true neu dang trong trang th�i an to�n, false neu dang khong gi�n ahihi.
 */
bool Safety_IsSafe(void);

/**
 * @brief Canh b�o khi mat an to�n
 */
void Safety_TriggerWarning(void);

#endif // SAFETY_H
