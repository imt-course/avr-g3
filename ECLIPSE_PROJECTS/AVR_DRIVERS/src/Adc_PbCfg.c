/*
 * Adc_PbCfg.c
 *
 *  Created on: Feb 18, 2023
 *      Author: ahmad
 */

#include "Adc.h"

Adc_ConfigurationType Adc_Configuration = {
	ADC_REF_AVCC,
	ADC_AUTO_TRIGGER_OFF,
	ADC_PRESCALER_128
};
