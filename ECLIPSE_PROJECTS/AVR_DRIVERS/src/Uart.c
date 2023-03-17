/*
 * Uart.c
 *
 *  Created on: Mar 10, 2023
 *      Author: ahmad
 */


#include "Types.h"
#include "Macros.h"
#include "Registers.h"
#include "Interrupts.h"
#include "Dio.h"
#include "Uart_Cfg.h"
#include "Uart.h"


void (*Uart_RxCallback) (u8 data) = NULL_PTR;
void (*Uart_TxCallback) (void   ) = NULL_PTR;
void (*Uart_RegEmptyCallback) (void) = NULL_PTR;

ISR(VECTOR_UART_RX) {
    if(NULL_PTR != Uart_RxCallback) {
        Uart_RxCallback(UDR);
    }
}

ISR(VECTOR_UART_TX) {
    if(NULL_PTR != Uart_TxCallback) {
        Uart_TxCallback();
    }
}

ISR(VECTOR_UART_REG_EMPTY) {
    if(NULL_PTR != Uart_RegEmptyCallback) {
        Uart_RegEmptyCallback();
    }
}


void Uart_Init(void) {
    u8 temp = 0;
#if (UART_RX_STATE == UART_ENABLED)
    /* Receiver Enable */
    Dio_SetPinMode(DIO_PORTD, DIO_PIN0, DIO_MODE_INPUT_FLOATING);
    SET_BIT(UCSRB, 4);
#endif
#if (UART_TX_STATE == UART_ENABLED)
    /* Transmitter Enable */
    Dio_SetPinMode(DIO_PORTD, DIO_PIN1, DIO_MODE_OUTPUT);
    SET_BIT(UCSRB, 3);
#endif
    /* Register Select (UCSRC) */
    SET_BIT(temp, 7);
    /* Character Size */
#if (UART_CHAR_SIZE == 8)
    CLR_BIT(UCSRB, 2);
    SET_BIT(temp , 2);
    SET_BIT(temp , 1);
#elif (UART_CHAR_SIZE == 7)
    CLR_BIT(UCSRB, 2);
    SET_BIT(temp , 2);
    CLR_BIT(temp , 1);
#elif (UART_CHAR_SIZE == 6)
    CLR_BIT(UCSRB, 2);
    CLR_BIT(temp , 2);
    SET_BIT(temp , 1);
#elif (UART_CHAR_SIZE == 5)
    CLR_BIT(UCSRB, 2);
    CLR_BIT(temp , 2);
    CLR_BIT(temp , 1);
#endif

#if (UART_PARITY_BIT == UART_PARITY_ODD)
    SET_BIT(temp, 4);
    SET_BIT(temp, 5);
#elif (UART_PARITY_BIT == UART_PARITY_EVEN)
    CLR_BIT(temp, 4);
    SET_BIT(temp, 5);
#endif

#if (UART_STOP_BITS == 2)
    SET_BIT(temp, 3);
#endif

    UCSRC = temp;
    Uart_SetBaudRate(UART_BAUDRATE);
}

void Uart_SetBaudRate(u16 value) {
    u16 baud_register_val = 0;
    /* Baud Rate Registers */
    if (UART_BAUDRATE > UART_FREQ_OSC/16) {
        /* Double the USART Transmission Speed */
        SET_BIT(UCSRA, 1);
        baud_register_val = (UART_FREQ_OSC/((u32)8*UART_BAUDRATE)) - 1;
    }
    else {
        CLR_BIT(UCSRA, 1);
        baud_register_val = (UART_FREQ_OSC/((u32)16*UART_BAUDRATE)) - 1;
    }
    UBRRL = (u8) baud_register_val;
    UBRRH = (u8) ((baud_register_val>>8)&0x0F);
}

void Uart_Transmit(u8 data) {
    /* Wait for USART Data Register Empty */
    while (GET_BIT(UCSRA, 5) == 0);
    /* Write Data Register */
    UDR = data;
    /* Wait for USART Transmit Complete */
    while (GET_BIT(UCSRA, 6) == 0);
    /* Clear USART Transmit Complete Flag */
    SET_BIT(UCSRA, 6);
}

u8 Uart_Receive(void) {
    /* Wait for USART Receive Complete */
    while (GET_BIT(UCSRA, 7) == 0);
    return UDR;
}


void Uart_EnableNotification(Uart_InterruptSourceType source) {
    switch (source)
    {
    case UART_INT_SOURCE_RX:
        SET_BIT(UCSRB, 7);
        break;
    case UART_INT_SOURCE_TX:
        SET_BIT(UCSRB, 6);
        break;
    case UART_INT_SOURCE_DATA_REG_EMPTY:
        SET_BIT(UCSRB, 5);
        break;
    default:
        break;
    }
}

void Uart_DisableNotification(Uart_InterruptSourceType source) {
    switch (source)
    {
    case UART_INT_SOURCE_RX:
        CLR_BIT(UCSRB, 7);
        break;
    case UART_INT_SOURCE_TX:
        CLR_BIT(UCSRB, 6);
        break;
    case UART_INT_SOURCE_DATA_REG_EMPTY:
        CLR_BIT(UCSRB, 5);
        break;
    default:
        break;
    }
}

void Uart_SetTransmitCallback (void (*funcPtr) (void)) {
    Uart_TxCallback = funcPtr;
}

void Uart_SetDataEmptyCallback(void (*funcPtr) (void)) {
	Uart_RegEmptyCallback = funcPtr;
}

void Uart_SetReceiveCallback  (void (*funcPtr) (u8)) {
	Uart_RxCallback = funcPtr;
}
