/*
 * Wdt.c
 *
 *  Created on: Mar 4, 2023
 *      Author: ahmad
 */
#include "Types.h"
#include "Registers.h"
#include "Macros.h"
#include "Wdt.h"

void Wdt_Enable(void) {
    SET_BIT(WDTCR, 3);
}

void Wdt_Disable(void) {
    /* In the same operation, write a logic one to WDTOE and WDE. */
    WDTCR |= (1<<3) | (1<<4);
    /*  Within the next four clock cycles, write a logic 0 to WDE */
    WDTCR &= 0xF7; //0b11110111
}

void Wdt_Refresh(void) {
    Wdt_Disable();
    Wdt_Enable();
}

void Wdt_SetTimeOut(Wdt_TimeoutType time) {
    if (time <= WDT_TIMEOUT_2100_MS) {
        WDTCR &= 0xF8; //0b11111000
        WDTCR |= time;
    }
}
