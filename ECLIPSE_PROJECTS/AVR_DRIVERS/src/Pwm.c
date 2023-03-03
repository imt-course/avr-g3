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
    case PWM_CHANNEL_OC1A:
    case PWM_CHANNEL_OC1B:
    {
        if (channel == PWM_CHANNEL_OC1A) {
            /* Set Pin as Output */
            Dio_SetPinMode(PWM_PIN_OC1A, DIO_MODE_OUTPUT);
            /**
             * Compare Output Mode for Channel A
             * Clear OC1A then Set OC1A
            */
            CLR_BIT(TCCR1A, 6);
            SET_BIT(TCCR1A, 7);
        }
        else {
            /* Set Pin as Output */
            Dio_SetPinMode(PWM_PIN_OC1B, DIO_MODE_OUTPUT);
            /**
             * Compare Output Mode for Channel B
             * Clear OC1B then Set OC1B
            */
            CLR_BIT(TCCR1A, 4);
            SET_BIT(TCCR1A, 5);
        }
        switch (mode)
        {
        case PWM_MODE_PHASE_CORRECT:
                SET_BIT(TCCR1A, 0);
                SET_BIT(TCCR1A, 1);
                CLR_BIT(TCCR1B, 3);
                SET_BIT(TCCR1B, 4);
            break;
        case PWM_MODE_FAST:
                SET_BIT(TCCR1A, 0);
                SET_BIT(TCCR1A, 1);
                SET_BIT(TCCR1B, 3);
                SET_BIT(TCCR1B, 4);
            break;
        case PWM_MODE_FAST_ICR1:
                CLR_BIT(TCCR1A, 0);
                SET_BIT(TCCR1A, 1);
                SET_BIT(TCCR1B, 3);
                SET_BIT(TCCR1B, 4);
            break;
        default:
            break;
        }
        break;
    }
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
    case PWM_CHANNEL_OC1A:
    case PWM_CHANNEL_OC1B:
    {
        switch (prescaler)
        {
        case PWM_PRESCALER_1:
            SET_BIT(TCCR1B,0);
            CLR_BIT(TCCR1B,1);
            CLR_BIT(TCCR1B,2);
            break;
        case PWM_PRESCALER_8:
            CLR_BIT(TCCR1B,0);
            SET_BIT(TCCR1B,1);
            CLR_BIT(TCCR1B,2);
            break;
        case PWM_PRESCALER_64:
            SET_BIT(TCCR1B,0);
            SET_BIT(TCCR1B,1);
            CLR_BIT(TCCR1B,2);
            break;
        case PWM_PRESCALER_256:
            CLR_BIT(TCCR1B,0);
            CLR_BIT(TCCR1B,1);
            SET_BIT(TCCR1B,2);
            break;
        case PWM_PRESCALER_1024:
            SET_BIT(TCCR1B,0);
            CLR_BIT(TCCR1B,1);
            SET_BIT(TCCR1B,2);
            break;
        case PWM_PRESCALER_EXT_FALLING:
            CLR_BIT(TCCR1B,0);
            SET_BIT(TCCR1B,1);
            SET_BIT(TCCR1B,2);
            break;
        case PWM_PRESCALER_EXT_RISING:
            SET_BIT(TCCR1B,0);
            SET_BIT(TCCR1B,1);
            SET_BIT(TCCR1B,2);
            break;
        default:
            break;
        }
        TCNT1 = 0;
        break;
    }
    /** TODO: Complete (OC2)*/
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
    case PWM_CHANNEL_OC1A:
    case PWM_CHANNEL_OC1B:
        CLR_BIT(TCCR1B, 2);
        CLR_BIT(TCCR1B, 1);
        CLR_BIT(TCCR1B, 0);
        break;
    case PWM_CHANNEL_OC2:
        CLR_BIT(TCCR2, 2);
        CLR_BIT(TCCR2, 1);
        CLR_BIT(TCCR2, 0);
        break;
    default:
        break;
    }
}

void Pwm_SetDutyCycle(Pwm_ChannelType channel, u8 value) {
    switch (channel)
    {
    case PWM_CHANNEL_OC0:
        OCR0 = ((u16)value*0xFF) / 100;
        break;
    case PWM_CHANNEL_OC1A:
        OCR1A = ((u16)value*0xFFFF) / 100;
        break;
    case PWM_CHANNEL_OC1B:
        OCR1B = ((u16)value*0xFFFF) / 100;
        break;
    case PWM_CHANNEL_OC2:
        OCR2 = ((u16)value*0xFF) / 100;
        break;
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
    case PWM_CHANNEL_OC1A:
        OCR1A = value;
        break;
    case PWM_CHANNEL_OC1B:
        OCR1B = value;
        break;
    case PWM_CHANNEL_OC2:
        OCR2 = value;
        break;
    default:
        break;
    }
}

void Pwm_SetICR(u16 value) {
    ICR1 = value;
}