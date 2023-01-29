/*
 * Led.h
 *
 *  Created on: Jan 28, 2023
 *      Author: ahmad
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "Dio.h"
#include "Led_Cfg.h"

typedef enum {
    LED_OFF,
    LED_ON
} Led_StateType;

void Led_Init (Dio_PortType port, Dio_PinType pin);
void Led_TurnOn (Dio_PortType port, Dio_PinType pin);
void Led_TurnOff (Dio_PortType port, Dio_PinType pin);
#define Led_Flip        Dio_FlipPinLevel
#define Led_ReadState   Dio_ReadPinLevel


#endif /* INC_LED_H_ */
