/*
 * Gpt_PbCfg.c
 *
 *  Created on: Feb 25, 2023
 *      Author: ahmad
 */

#include "Gpt.h"

Gpt_ConfigType Gpt_Configuration [3] = {
    /* Configuration for TIM0 */
    {
        GPT_MODE_NORMAL,
        GPT_COMP_OUT_MODE_DISCONNECTED
    },
    /* Configuration for TIM1 */
    {
        GPT_MODE_NORMAL,
        GPT_COMP_OUT_MODE_DISCONNECTED
    },
    /* Configuration for TIM2 */
    {
        GPT_MODE_CTC,
        GPT_COMP_OUT_MODE_DISCONNECTED
    }
};
