/*
 * ExtInt.h
 *
 *  Created on: Feb 11, 2023
 *      Author: ahmad
 */

#ifndef INC_EXTINT_H_
#define INC_EXTINT_H_

#include "Dio.h"

#define EXTINT_PIN_INT0     DIO_PORTD,DIO_PIN2
#define EXTINT_PIN_INT1     DIO_PORTD,DIO_PIN3
#define EXTINT_PIN_INT2     DIO_PORTB,DIO_PIN2


typedef enum {
    EXTINT_TRIGGER_LOW_LEVEL,
    EXTINT_TRIGGER_ON_CHANGE,
    EXTINT_TRIGGER_FALLING_EDGE,
    EXTINT_TRIGGER_RISING_EDGE
} ExtInt_TriggerEdgeType;

typedef enum {
    EXTINT_CHANNEL_INT0,
    EXTINT_CHANNEL_INT1,
    EXTINT_CHANNEL_INT2
} ExtInt_ChannelType;

void ExtInt_SetTriggerEdge(ExtInt_ChannelType channel, ExtInt_TriggerEdgeType edge);
void ExtInt_EnableNotification(ExtInt_ChannelType channel);
void ExtInt_DisableNotification(ExtInt_ChannelType channel);
void ExtInt_ClearFlag(ExtInt_ChannelType channel);
u8 ExtInt_ReadFlag(ExtInt_ChannelType channel);
void ExInt_SetCallback(ExtInt_ChannelType channel, void (*funcPtr) (void));
#endif /* INC_EXTINT_H_ */
