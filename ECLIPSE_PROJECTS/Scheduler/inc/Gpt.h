/*
 * Gpt.h
 *
 *  Created on: Feb 24, 2023
 *      Author: ahmad
 */

#ifndef INC_GPT_H_
#define INC_GPT_H_

#include "Types.h"

typedef enum {
    GPT_INT_SOURCE_TIM0_COMP,
    GPT_INT_SOURCE_TIM0_OVF,
    GPT_INT_SOURCE_TIM1_COMPA,
    GPT_INT_SOURCE_TIM1_COMPB,
    GPT_INT_SOURCE_TIM1_OVF,
    GPT_INT_SOURCE_TIM1_CAPT,
    GPT_INT_SOURCE_TIM2_COMP,
    GPT_INT_SOURCE_TIM2_OVF
} Gpt_InterruptSourceType;

typedef enum {
    GPT_CHANNEL_TIM0,
    GPT_CHANNEL_TIM1,
    GPT_CHANNEL_TIM2
} Gpt_ChannelType;

typedef enum {
    GPT_COMP_REG_TIM0,
    GPT_COMP_REG_TIM1A,
    GPT_COMP_REG_TIM1B,
    GPT_COMP_REG_TIM2
} Gpt_CompareRegType;

typedef enum {
    GPT_PRESCALER_1,
    GPT_PRESCALER_8,
    GPT_PRESCALER_64,
    GPT_PRESCALER_256,
    GPT_PRESCALER_1024,
    GPT_PRESCALER_EXT_FALLING,
    GPT_PRESCALER_EXT_RISING,
} Gpt_PrescalerType;

typedef enum {
    GPT_MODE_NORMAL,
    GPT_MODE_CTC
} Gpt_ModeType;

typedef enum {
    GPT_COMP_OUT_MODE_DISCONNECTED,
    GPT_COMP_OUT_MODE_TOGGLE,
    GPT_COMP_OUT_MODE_CLEAR,
    GPT_COMP_OUT_MODE_SET
} Gpt_CompareOutModeType;

typedef struct {
    Gpt_ModeType mode;
    Gpt_CompareOutModeType compareMode;
} Gpt_ConfigType;

extern Gpt_ConfigType Gpt_Configuration[3];

void Gpt_Init(Gpt_ChannelType channel, const Gpt_ConfigType* config);
void Gpt_Start(Gpt_ChannelType channel, Gpt_PrescalerType prescaler);
void Gpt_Stop(Gpt_ChannelType channel);
void Gpt_Reset (Gpt_ChannelType channel);
void Gpt_SetCounterValue (Gpt_ChannelType channel, u16 value);
void Gpt_SetCompareValue (Gpt_CompareRegType reg, u16 value);
void Gpt_EnableNotification(Gpt_InterruptSourceType source);
void Gpt_DisableNotification(Gpt_InterruptSourceType source);
void Gpt_SetCallback(Gpt_InterruptSourceType source, void (*funcPtr) (void));
u16  Gpt_GetElapsedTime(Gpt_ChannelType channel);

#endif /* INC_GPT_H_ */
