/*
 * Icu.h
 *
 *  Created on: Mar 3, 2023
 *      Author: ahmad
 */

#ifndef INC_ICU_H_
#define INC_ICU_H_

#include "Types.h"
#include "Dio.h"

#define ICU_PIN     DIO_PORTD,DIO_PIN6

typedef enum {
    ICU_EDGE_FALLING,
    ICU_EDGE_RISING
} Icu_TriggerEdgeType;

void Icu_SetTriggerEdge(Icu_TriggerEdgeType edge);
void Icu_EnableNoiseCanceller(void);
void Icu_DisbleNoiseCanceller(void);
void Icu_EnableNotification(void);
void Icu_DisableNotification(void);
void Icu_SetCallback(void (*funcPtr) (u16 value));

#endif /* INC_ICU_H_ */
