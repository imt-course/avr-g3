/*
 * Pwm.c
 *
 *  Created on: Feb 25, 2023
 *      Author: ahmad
 */

#include "Types.h"
#include "Macros.h"
#include "Registers.h"
#include "Dio.h"
#include "Pwm.h"

void Pwm_Init(Pwm_ChannelType channel, Pwm_ModeType mode) {
    switch (channel)
    {
    case PWM_CHANNEL_OC0:
    {
        Dio_SetPinMode(PWM_PIN_OC0, DIO_MODE_OUTPUT);
        CLR_BIT(TCCR0, 4);
        SET_BIT(TCCR0, 5);
        switch (mode)
        {
        case PWM_MODE_PHASE_CORRECT:
            SET_BIT(TCCR0, 3);
            CLR_BIT(TCCR0, 6);
            break;
        case PWM_MODE_FAST:
            SET_BIT(TCCR0, 3);
            SET_BIT(TCCR0, 6);
            break;
        default:
            break;
        }
        break;
    }
    /** TODO: Complete all cases (OC1A, OC1B), (OC2)*/
    default:
        break;
    }
}

void Pwm_Start(Pwm_ChannelType channel, Pwm_PrescalerType prescaler) {
    switch (channel)
    {
    case PWM_CHANNEL_OC0:
    {
        switch (prescaler)
        {
        case PWM_PRESCALER_1:
            SET_BIT(TCCR0,0);
            CLR_BIT(TCCR0,1);
            CLR_BIT(TCCR0,2);
            break;
        case PWM_PRESCALER_8:
            CLR_BIT(TCCR0,0);
            SET_BIT(TCCR0,1);
            CLR_BIT(TCCR0,2);
            break;
        case PWM_PRESCALER_64:
            SET_BIT(TCCR0,0);
            SET_BIT(TCCR0,1);
            CLR_BIT(TCCR0,2);
            break;
        case PWM_PRESCALER_256:
            CLR_BIT(TCCR0,0);
            CLR_BIT(TCCR0,1);
            SET_BIT(TCCR0,2);
            break;
        case PWM_PRESCALER_1024:
            SET_BIT(TCCR0,0);
            CLR_BIT(TCCR0,1);
            SET_BIT(TCCR0,2);
            break;
        case PWM_PRESCALER_EXT_FALLING:
            CLR_BIT(TCCR0,0);
            SET_BIT(TCCR0,1);
            SET_BIT(TCCR0,2);
            break;
        case PWM_PRESCALER_EXT_RISING:
            SET_BIT(TCCR0,0);
            SET_BIT(TCCR0,1);
            SET_BIT(TCCR0,2);
            break;
        default:
            break;
        }
        TCNT0 = 0;
        break;
    }
    /** TODO: Complete all cases (OC1A, OC1B), (OC2)*/
    default:
        break;
    }
}

void Pwm_Stop(Pwm_ChannelType channel) {
    switch (channel)
    {
    case PWM_CHANNEL_OC0:
        CLR_BIT(TCCR0, 2);
        CLR_BIT(TCCR0, 1);
        CLR_BIT(TCCR0, 0);
        break;
    /** TODO: Complete all cases (OC1A, OC1B), (OC2)*/
    default:
        break;
    }
}

void Pwm_SetDutyCycle(Pwm_ChannelType channel, u8 value) {
    switch (channel)
    {
    case PWM_CHANNEL_OC0:
        OCR0 = ((u16)value*255) / 100;
        break;
    /** TODO: Complete all cases (OC1A, OC1B, OC2) */
    default:
        break;
    }
}

void Pwm_SetTimeOn(Pwm_ChannelType channel, u8 value) {
    switch (channel)
    {
    case PWM_CHANNEL_OC0:
        OCR0 = value;
        break;
    /** TODO: Complete all cases (OC1A, OC1B, OC2) */
    default:
        break;
    }
}
void Pwm_SetICR(u16 value) {
    /** TODO: */
}