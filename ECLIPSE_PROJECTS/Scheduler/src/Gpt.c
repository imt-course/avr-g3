/*
 * Gpt.c
 *
 *  Created on: Feb 24, 2023
 *      Author: ahmad
 */


#include "Types.h"
#include "Registers.h"
#include "Macros.h"
#include "Interrupts.h"
#include "Gpt.h"

void (*Gpt_Callback_TIM0_COMP ) (void) = NULL_PTR;
void (*Gpt_Callback_TIM0_OVF  ) (void) = NULL_PTR;
void (*Gpt_Callback_TIM1A_COMP) (void) = NULL_PTR;
void (*Gpt_Callback_TIM1B_COMP) (void) = NULL_PTR;
void (*Gpt_Callback_TIM1_OVF  ) (void) = NULL_PTR;
void (*Gpt_Callback_TIM1_CAPT ) (void) = NULL_PTR;
void (*Gpt_Callback_TIM2_OVF  ) (void) = NULL_PTR;
void (*Gpt_Callback_TIM2_COMP ) (void) = NULL_PTR;

ISR(VECTOR_TIM0_COMP) {
    if (NULL_PTR != Gpt_Callback_TIM0_COMP) {
        Gpt_Callback_TIM0_COMP();
    }
}

ISR(VECTOR_TIM0_OVF) {
    if (NULL_PTR != Gpt_Callback_TIM0_OVF) {
        Gpt_Callback_TIM0_OVF();
    }
}

/** TODO: Complete all ISRs (4 ISRs for Timer 1, 2 ISRs for Tomer 2)*/


void Gpt_Init(Gpt_ChannelType channel, const Gpt_ConfigType* config) {
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
    {
        switch (config->mode)
        {
        case GPT_MODE_NORMAL:
            CLR_BIT(TCCR0, 3);
            CLR_BIT(TCCR0, 6);
            break;
        case GPT_MODE_CTC:
            SET_BIT(TCCR0, 3);
            CLR_BIT(TCCR0, 6);
            break;
        default:
            break;
        }
        switch (config->compareMode)
        {
        case GPT_COMP_OUT_MODE_DISCONNECTED:
            CLR_BIT(TCCR0, 4);
            CLR_BIT(TCCR0, 5);
            break;
        case GPT_COMP_OUT_MODE_TOGGLE:
            SET_BIT(TCCR0, 4);
            CLR_BIT(TCCR0, 5);
            break;
        case GPT_COMP_OUT_MODE_CLEAR:
            CLR_BIT(TCCR0, 4);
            SET_BIT(TCCR0, 5);
            break;
        case GPT_COMP_OUT_MODE_SET:
            SET_BIT(TCCR0, 4);
            SET_BIT(TCCR0, 5);
            break;
        default:
            break;
        }
        break;
    }
    /** TODO: Complete all cases (TIM1, TIM2) */
    default:
        break;
    }
}

void Gpt_Start(Gpt_ChannelType channel, Gpt_PrescalerType prescaler) {
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
    {
        switch (prescaler)
        {
        case GPT_PRESCALER_1:
            SET_BIT(TCCR0,0);
            CLR_BIT(TCCR0,1);
            CLR_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_8:
            CLR_BIT(TCCR0,0);
            SET_BIT(TCCR0,1);
            CLR_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_64:
            SET_BIT(TCCR0,0);
            SET_BIT(TCCR0,1);
            CLR_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_256:
            CLR_BIT(TCCR0,0);
            CLR_BIT(TCCR0,1);
            SET_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_1024:
            SET_BIT(TCCR0,0);
            CLR_BIT(TCCR0,1);
            SET_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_EXT_FALLING:
            CLR_BIT(TCCR0,0);
            SET_BIT(TCCR0,1);
            SET_BIT(TCCR0,2);
            break;
        case GPT_PRESCALER_EXT_RISING:
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
    default:
        break;
    }
}
void Gpt_Stop(Gpt_ChannelType channel) {
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        CLR_BIT(TCCR0, 2);
        CLR_BIT(TCCR0, 1);
        CLR_BIT(TCCR0, 0);
        break;
    /** TODO: Complete all Cases (TIM1, TIM2)*/
    default:
        break;
    }
}

void Gpt_Reset (Gpt_ChannelType channel) {
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        TCNT0 = 0;
        break;
    /** TODO: Complete all Cases (TIM1, TIM2)*/
    default:
        break;
    }
}

void Gpt_SetCounterValue (Gpt_ChannelType channel, u16 value) {
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        TCNT0 = value;
        break;
    /** TODO: Complete all Cases (TIM1, TIM2)*/
    default:
        break;
    }
}

void Gpt_SetCompareValue (Gpt_CompareRegType reg, u16 value) {
    switch (reg)
    {
    case GPT_COMP_REG_TIM0:
        OCR0 = value;
        break;
    /** TODO: Complete all Cases (TIM1A, TIM1B, TIM2)*/
    default:
        break;
    }
}

void Gpt_EnableNotification(Gpt_InterruptSourceType source) {
    switch (source)
    {
    case GPT_INT_SOURCE_TIM0_COMP:
        SET_BIT(TIMSK, 1);
        break;
    case GPT_INT_SOURCE_TIM0_OVF:
        SET_BIT(TIMSK, 0);
        break;
    /** TODO: Complete all Cases (4 ISRs for Timer 1, 2 ISRs for Tomer 2)*/
    default:
        break;
    }
}

void Gpt_DisableNotification(Gpt_InterruptSourceType source) {
    switch (source)
    {
    case GPT_INT_SOURCE_TIM0_COMP:
        CLR_BIT(TIMSK, 1);
        break;
    case GPT_INT_SOURCE_TIM0_OVF:
        CLR_BIT(TIMSK, 0);
        break;
    /** TODO: Complete all Cases (4 ISRs for Timer 1, 2 ISRs for Tomer 2)*/
    default:
        break;
    }
}

void Gpt_SetCallback(Gpt_InterruptSourceType source, void (*funcPtr) (void)) {
    switch (source)
    {
    case GPT_INT_SOURCE_TIM0_COMP:
        Gpt_Callback_TIM0_COMP = funcPtr;
        break;
    case GPT_INT_SOURCE_TIM0_OVF:
        Gpt_Callback_TIM0_OVF = funcPtr;
        break;
    /** TODO: Complete all Cases (4 ISRs for Timer 1, 2 ISRs for Tomer 2)*/
    default:
        break;
    }
}


u16  Gpt_GetElapsedTime(Gpt_ChannelType channel) {
    u16 ret_value = 0;
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        ret_value = TCNT0;
        break;
    case GPT_CHANNEL_TIM1:
        /** TODO: */
        break;
    case GPT_CHANNEL_TIM2:
        /** TODO: */
        break;
    default:
        break;
    }
    return ret_value;
}
