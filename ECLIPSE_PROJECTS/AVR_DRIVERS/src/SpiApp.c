/*
 * SpiApp.c
 *
 *  Created on: Mar 17, 2023
 *      Author: ahmad
 */


#include "Types.h"
#include "Uart.h"
#include "Spi.h"
#include "Gie.h"

#define APP_MODE_MASTER 1
#define APP_MODE_SLAVE  2

#define APP_MODE        3


#if (APP_MODE == APP_MODE_MASTER)

int main (void) {
    u8 data;
    Uart_Init();
    Spi_Init();
    while (1)
    {
        data = Uart_Receive();
        Spi_Transfer(data);
    }
}

#elif (APP_MODE == APP_MODE_SLAVE)

volatile u8 receivedFlag = 0;
volatile u8 receivetData;

void Handler_Spi (u8 data) {
    receivedFlag = 1;
    receivetData = data;
}

int main (void) {
    Uart_Init();
    Spi_Init();
    Spi_SetCallbak(Handler_Spi);
    Spi_EnableNotification();
    Gie_Enable();
    while (1)
    {
        if(receivedFlag) {
            Uart_Transmit(receivetData);
            receivedFlag = 0;
        }
    }
    
}

#endif