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


void Uart_Init(void) {
    u8 temp = 0;
    u16 baud_register_val = 0;
    /* Receiver Enable */
    Dio_SetPinMode(DIO_PORTD, DIO_PIN0, DIO_MODE_INPUT_FLOATING);
    SET_BIT(UCSRB, 4);
    /* Transmitter Enable */
    Dio_SetPinMode(DIO_PORTD, DIO_PIN1, DIO_MODE_OUTPUT);
    SET_BIT(UCSRB, 3);
    /* Register Select (UCSRC) */
    SET_BIT(temp, 7);
    /* Character Size (8 bit) */
    CLR_BIT(UCSRB, 2);
    SET_BIT(temp , 2);
    SET_BIT(temp , 1);
    UCSRC = temp;
    /* Baud Rate Registers */
    baud_register_val = (UART_FREQ_OSC/(16*UART_BAUDRATE)) - 1;
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
