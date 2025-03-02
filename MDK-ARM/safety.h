#ifndef SAFETY_H
#define SAFETY_H

#include <stdbool.h>


void Safety_Init(void);
/**
 * @brief Kiem tra xem góc nghiêng hien tai có vuot nguong không.
 * @param angle Góc hien tai.
 * @param maxAngle Nguong gioi han an toàn .
 * @return true neu vuot quá nguong => Không an toàn.
 */
bool Safety_CheckTiltAngle(float angle, float maxAngle);

void Safety_TimerCheck(void);
/**
 * @brief Cap nhat trang thái an toàn.
 * @param isSafe Trang thái an toàn hien tai (true = an toàn, false = khong giòn).
 */
void Safety_UpdateStatus(bool isSafe);

/**
 * @brief Lay trang thái an toàn hien tai.
 * @return true neu dang trong trang thái an toàn, false neu dang khong giòn ahihi.
 */
bool Safety_IsSafe(void);

/**
 * @brief Canh báo khi mat an toàn
 */
void Safety_TriggerWarning(void);

#endif // SAFETY_H
