/*
 * Adc.h
 *
 *  Created on: Feb 18, 2023
 *      Author: ahmad
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "Types.h"


typedef enum
{
    ADC_CHANNEL_ADC0,
    ADC_CHANNEL_ADC1,
    ADC_CHANNEL_ADC2,
    ADC_CHANNEL_ADC3,
    ADC_CHANNEL_ADC4,
    ADC_CHANNEL_ADC5,
    ADC_CHANNEL_ADC6,
    ADC_CHANNEL_ADC7,
    ADC_CHANNEL_ADC0_ADC0_10X,
    ADC_CHANNEL_ADC1_ADC0_10X,
    ADC_CHANNEL_ADC0_ADC0_200X,
    ADC_CHANNEL_ADC1_ADC0_200X,
    ADC_CHANNEL_ADC2_ADC2_10X,
    ADC_CHANNEL_ADC3_ADC2_10X,
    ADC_CHANNEL_ADC2_ADC2_200X,
    ADC_CHANNEL_ADC3_ADC2_200X,
    ADC_CHANNEL_ADC0_ADC1_1X,
    ADC_CHANNEL_ADC1_ADC1_1X,
    ADC_CHANNEL_ADC2_ADC1_1X,
    ADC_CHANNEL_ADC3_ADC1_1X,
    ADC_CHANNEL_ADC4_ADC1_1X,
    ADC_CHANNEL_ADC5_ADC1_1X,
    ADC_CHANNEL_ADC6_ADC1_1X,
    ADC_CHANNEL_ADC7_ADC1_1X,
    ADC_CHANNEL_ADC0_ADC2_1X,
    ADC_CHANNEL_ADC1_ADC2_1X,
    ADC_CHANNEL_ADC2_ADC2_1X,
    ADC_CHANNEL_ADC3_ADC2_1X,
    ADC_CHANNEL_ADC4_ADC2_1X,
    ADC_CHANNEL_ADC5_ADC2_1X,
    ADC_CHANNEL_1_22_V,
    ADC_CHANNEL_GND
} Adc_ChannelType;


typedef enum {
    ADC_REF_AREF,
    ADC_REF_AVCC,
    ADC_REF_INTERNAL
} Adc_referenceType;

typedef enum {
    ADC_AUTO_TRIGGER_OFF,
    ADC_AUTO_TRIGGER_FREE_RUNNING,
    ADC_AUTO_TRIGGER_ANAL_COMP,
    ADC_AUTO_TRIGGER_EXTI0,
    ADC_AUTO_TRIGGER_TIM0_COMP,
    ADC_AUTO_TRIGGER_TIM0_OVF,
    ADC_AUTO_TRIGGER_TIMB_COMP,
    ADC_AUTO_TRIGGER_TIM1_OVF,
    ADC_AUTO_TRIGGER_TIM1_CAP
} Adc_TriggerSourceType;

typedef enum {
    ADC_PRESCALER_2,
    ADC_PRESCALER_4,
    ADC_PRESCALER_8,
    ADC_PRESCALER_16,
    ADC_PRESCALER_32,
    ADC_PRESCALER_64,
    ADC_PRESCALER_128
} Adc_PrescalerType;

typedef struct {
    Adc_referenceType reference;
    Adc_TriggerSourceType trigger;
    Adc_PrescalerType prescaler;
} Adc_ConfigurationType;

typedef enum {
    ADC_NOT_COMPLETE,
    ADC_COMPLETE
} Adc_StateType;

extern Adc_ConfigurationType Adc_Configuration;

void Adc_Init(const Adc_ConfigurationType* config);
void Adc_StartConversion(Adc_ChannelType channel);
u16 Adc_GetResultSync(void);
Adc_StateType Adc_GetResultAsync(u16* result_ref);
void Adc_EnableNotification(void);
void Adc_DisableNotification(void);
void Adc_SetCallback(void (*funcPtr) (u16 data));
#endif /* INC_ADC_H_ */
