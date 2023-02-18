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




void Adc_Init(void) {
    /* Reference Selection Bits */
    CLR_BIT(ADMUX, 7);
    SET_BIT(ADMUX, 6);
    /* ADC Left Adjust Result */
    CLR_BIT(ADMUX, 5); // Right
    /* ADC Auto Trigger Enable */
    CLR_BIT(ADCSRA, 5);
    /* ADC Prescaler Select Bits */
    SET_BIT(ADCSRA, 2);
    SET_BIT(ADCSRA, 1);
    SET_BIT(ADCSRA, 0);
    /* ADC Enable */
    SET_BIT(ADCSRA,7);
}
void Adc_StartConversion(Adc_ChannelType channel) {
    /* Wait until current conversion finishes */
    while (GET_BIT(ADCSRA, 6) == 1);
    
    /* Analog Channel and Gain Selection Bits */
    switch (channel)
    {
    case ADC_CHANNEL_ADC0:
        CLR_BIT(ADMUX, 0);
        CLR_BIT(ADMUX, 1);
        CLR_BIT(ADMUX, 2);
        CLR_BIT(ADMUX, 3);
        CLR_BIT(ADMUX, 4);
        break;
    
    default:
        break;
    }
    /* ADC Start Conversion */
    SET_BIT(ADCSRA, 6);
}

u16 Adc_GetResult(void) {
    /* Wait until conversion completes */
    while(GET_BIT(ADCSRA, 4) == 0);
    /* Clear flag */
    SET_BIT(ADCSRA, 4);
    /* Return result */
    return (ADCDATA&0x3FF);
}
