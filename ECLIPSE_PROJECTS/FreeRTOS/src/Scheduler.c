/*
 * Scheduler.c
 *
 *  Created on: Mar 31, 2023
 *      Author: ahmad
 */

#include "Types.h"
#include "Gpt.h"
#include "Scheduler.h"

#define SCHED_MAX_TASKS 10

static void Scheduler_UpdateTasks(void);

typedef enum
{
    SCHED_TASK_SUSPENDED,
    SCHED_TASK_RESUMED
} Scheduler_TaskStateType;

typedef struct
{
    void (*funcPtr)(void);
    u16 delay;
    u16 periodicity;
    Scheduler_TaskStateType state;
    BooleanType readyFlag;
} Scheduler_TaskType;

Scheduler_TaskType Tasks[SCHED_MAX_TASKS];

void Scheduler_Start(void)
{
    /* Initialize Timer 0 With CTC Mode */
    Gpt_Init(GPT_CHANNEL_TIM0, &Gpt_Configuration[0]);
    /* Set Compare Value with 125 and Prescaler with 64, so Tick Time = OCR*(pre/Freq) = 125*(64/8M) = 1ms */
    Gpt_SetCompareValue(GPT_COMP_REG_TIM0, 125);
    /* Set Callback Function and Enable Interrupt */
    Gpt_SetCallback(GPT_INT_SOURCE_TIM0_COMP, Scheduler_UpdateTasks);
    Gpt_EnableNotification(GPT_INT_SOURCE_TIM0_COMP);
    Gpt_Start(GPT_CHANNEL_TIM0, GPT_PRESCALER_64);
}

void Scheduler_Init(void)
{
    u8 i;
    for (i = 0; i < SCHED_MAX_TASKS; i++)
    {
        Scheduler_DeleteTask(i);
    }
}

u8 Scheduler_CreateTask(void (*funcPtr)(void), u16 delay, u16 periodicity)
{
    u8 i;
    for (i = 0; i < SCHED_MAX_TASKS; i++)
    {
        if (NULL_PTR == Tasks[i].funcPtr)
        {
            Tasks[i].funcPtr = funcPtr;
            Tasks[i].delay = delay;
            Tasks[i].periodicity = periodicity;
            Tasks[i].state = SCHED_TASK_RESUMED;
            Tasks[i].readyFlag = FALSE;
            break;
        }
    }
    return i;
}

void Scheduler_DeleteTask(u8 index)
{
    if (index < SCHED_MAX_TASKS)
    {
        Tasks[index].funcPtr = NULL_PTR;
        Tasks[index].delay = 0;
        Tasks[index].periodicity = 0;
        Tasks[index].state = SCHED_TASK_SUSPENDED;
        Tasks[index].readyFlag = FALSE;
    }
}

void Scheduler_SuspendTask(u8 index)
{
    if (index < SCHED_MAX_TASKS)
    {
        Tasks[index].state = SCHED_TASK_SUSPENDED;
    }
}

void Scheduler_ResumeTask(u8 index)
{
    if (index < SCHED_MAX_TASKS)
    {
        Tasks[index].state = SCHED_TASK_RESUMED;
    }
}

void Scheduler_Dispath(void)
{
    u8 i;
    while (1)
    {
        for (i = 0; i < SCHED_MAX_TASKS; i++)
        {
            if ((Tasks[i].readyFlag == TRUE) && (Tasks[i].state != SCHED_TASK_SUSPENDED))
            {
                Tasks[i].readyFlag = FALSE;
                Tasks[i].funcPtr();
                if (Tasks[i].periodicity == 0)
                {
                    /* One Shot Task */
                    Scheduler_DeleteTask(i);
                }
            }
        }
    }
}

static void Scheduler_UpdateTasks(void)
{
    u8 i;
    for (i = 0; i < SCHED_MAX_TASKS; i++)
    {
        if (NULL_PTR != Tasks[i].funcPtr)
        {
            if (Tasks[i].delay == 0)
            {
                Tasks[i].delay = Tasks[i].periodicity;
                Tasks[i].readyFlag = TRUE;
            }
            Tasks[i].delay--;
        }
    }
}
