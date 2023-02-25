/*
 * Pwm.h
 *
 *  Created on: Feb 25, 2023
 *      Author: ahmad
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "Types.h"
#include "Dio.h"

#define PWM_PIN_OC0     DIO_PORTB,DIO_PIN3
#define PWM_PIN_OC1A    DIO_PORTD,DIO_PIN5
#define PWM_PIN_OC1B    DIO_PORTD,DIO_PIN4
#define PWM_PIN_OC2     DIO_PORTD,DIO_PIN7

typedef enum {
    PWM_CHANNEL_OC0,
    PWM_CHANNEL_OC1A,
    PWM_CHANNEL_OC1B,
    PWM_CHANNEL_OC2
} Pwm_ChannelType;

typedef enum {
    PWM_PRESCALER_1,
    PWM_PRESCALER_8,
    PWM_PRESCALER_64,
    PWM_PRESCALER_256,
    PWM_PRESCALER_1024,
    PWM_PRESCALER_EXT_FALLING,
    PWM_PRESCALER_EXT_RISING,
} Pwm_PrescalerType;

typedef enum {
    PWM_MODE_FAST,
    PWM_MODE_PHASE_CORRECT
} Pwm_ModeType;

void Pwm_Init(Pwm_ChannelType channel, Pwm_ModeType mode);
void Pwm_Start(Pwm_ChannelType channel, Pwm_PrescalerType prescaler);
void Pwm_Stop(Pwm_ChannelType channel);
void Pwm_SetDutyCycle(Pwm_ChannelType channel, u8 value);

#endif /* INC_PWM_H_ */
