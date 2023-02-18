/*
 * Adc.c
 *
 *  Created on: Feb 18, 2023
 *      Author: ahmad
 */
#include "Types.h"
#include "Macros.h"
#include "Registers.h"
#include "Adc.h"




void Adc_Init(const Adc_ConfigurationType* config) {

    /****************** Reference Selection Bits */
    switch (config->reference)
    {
    case ADC_REF_AREF:
        /** TODO: */
        break;
    case ADC_REF_AVCC:
        CLR_BIT(ADMUX, 7);
        SET_BIT(ADMUX, 6);
        break;
    case ADC_REF_INTERNAL:
        /** TODO: */
        break;
    default:
        break;
    }

    /****************** ADC Left Adjust Result */
    CLR_BIT(ADMUX, 5); // Right

    /****************** ADC Auto Trigger Enable */
    switch (config->trigger)
    {
    case ADC_AUTO_TRIGGER_OFF:
        CLR_BIT(ADCSRA, 5);
        break;
    case ADC_AUTO_TRIGGER_FREE_RUNNING:
        SET_BIT(ADCSRA, 5);
        CLR_BIT(SFIOR, 5);
        CLR_BIT(SFIOR, 6);
        CLR_BIT(SFIOR, 7);
        break;
    case ADC_AUTO_TRIGGER_ANAL_COMP:
        /** TODO: */
        break;
    case ADC_AUTO_TRIGGER_EXTI0:
        /** TODO: */
        break;
    case ADC_AUTO_TRIGGER_TIM0_COMP:
        /** TODO: */
        break;
    case ADC_AUTO_TRIGGER_TIM0_OVF:
        /** TODO: */
        break;
    case ADC_AUTO_TRIGGER_TIMB_COMP:
        /** TODO: */
        break;
    case ADC_AUTO_TRIGGER_TIM1_OVF:
        /** TODO: */
        break;
    case ADC_AUTO_TRIGGER_TIM1_CAP:
        /** TODO: */
        break;
    
    default:
        break;
    }

    /****************** ADC Prescaler Select Bits */
    switch (config->prescaler)
    {
    case ADC_PRESCALER_2:
        /** TODO: */
        break;
    case ADC_PRESCALER_4:
        /** TODO: */
        break;
    case ADC_PRESCALER_8:
        /** TODO: */
        break;
    case ADC_PRESCALER_16:
        /** TODO: */
        break;
    case ADC_PRESCALER_32:
        /** TODO: */
        break;
    case ADC_PRESCALER_64:
        /** TODO: */
        break;
    case ADC_PRESCALER_128:
        SET_BIT(ADCSRA, 2);
        SET_BIT(ADCSRA, 1);
        SET_BIT(ADCSRA, 0);
        break;    
    default:
        break;
    }

    /****************** ADC Enable */
    SET_BIT(ADCSRA,7);
}



void Adc_StartConversion(Adc_ChannelType channel) {
    /* Wait until current conversion finishes */
    while (GET_BIT(ADCSRA, 6) == 1);
    
    /* Analog Channel and Gain Selection Bits */
    ADMUX &= 0b11100000;
    ADMUX |= channel;

    /* ADC Start Conversion */
    SET_BIT(ADCSRA, 6);
}

u16 Adc_GetResultSync(void) {
    /* Wait until conversion completes */
    while(GET_BIT(ADCSRA, 4) == 0);
    /* Clear flag */
    SET_BIT(ADCSRA, 4);
    /* Return result */
    return (ADCDATA&0x3FF);
}

Adc_StateType Adc_GetResultAsync(u16* result_ref) {
    if (GET_BIT(ADCSRA, 4) == 0) {
        return ADC_NOT_COMPLETE;
    }
    else {
        /* Clear flag */
        SET_BIT(ADCSRA, 4);
        /* Write result in pointer */
        *result_ref = (ADCDATA&0x3FF);
        /* Return result */
        return ADC_COMPLETE;
    }
}

void Adc_EnableNotification(void) {
    /** TODO: */
}
void Adc_DisableNotification(void) {
    /** TODO: */
}
void Adc_SetCallback(void (*funcPtr) (u16 data)) {
    /** TODO: */
}
