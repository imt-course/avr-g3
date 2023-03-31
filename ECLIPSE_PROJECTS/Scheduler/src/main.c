/*
 * main.c
 *
 *  Created on: Mar 31, 2023
 *      Author: ahmad
 */
#include "Types.h"
#include "Dio.h"
#include "Gie.h"
#include "Scheduler.h"

#define LED1 DIO_PORTA, DIO_PIN0
#define LED2 DIO_PORTA, DIO_PIN1

void InitTask(void);
void Task1(void);
void Task2(void);

int main(void)
{
    Scheduler_Init();
    Scheduler_CreateTask(InitTask, 0, 0);
    Scheduler_CreateTask(Task1, 0, 1000);
    Scheduler_CreateTask(Task2, 1000, 1000);
    Scheduler_Start();
    Gie_Enable();
    Scheduler_Dispath();
}

void InitTask(void)
{
    Dio_SetPinMode(LED1, DIO_MODE_OUTPUT);
    Dio_SetPinMode(LED2, DIO_MODE_OUTPUT);
}

void Task1(void)
{
    Dio_FlipPinLevel(LED1);
}

void Task2(void)
{
    Dio_FlipPinLevel(LED2);
}
