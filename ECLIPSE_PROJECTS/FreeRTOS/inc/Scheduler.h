/*
 * Scheduler.h
 *
 *  Created on: Mar 31, 2023
 *      Author: ahmad
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "Types.h"

void Scheduler_Init        (void);
u8   Scheduler_CreateTask  (void (*funcPtr) (void), u16 delay, u16 periodicity);
void Scheduler_DeleteTask  (u8 index);
void Scheduler_SuspendTask (u8 index);
void Scheduler_ResumeTask  (u8 index);
void Scheduler_Start       (void);
void Scheduler_Dispath     (void);

#endif /* INC_SCHEDULER_H_ */
