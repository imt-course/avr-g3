/*
 * Uart_Cfg.h
 *
 *  Created on: Mar 10, 2023
 *      Author: ahmad
 */

#ifndef INC_UART_CFG_H_
#define INC_UART_CFG_H_

#define UART_PARITY_DISABLED    0
#define UART_PARITY_ODD         1
#define UART_PARITY_EVEN        2

#define UART_DISBLED            0
#define UART_ENABLED            1


/********************* USER CONFIGURATIONS *********************/

#define UART_RX_STATE       UART_ENABLED
#define UART_TX_STATE       UART_ENABLED
#define UART_FREQ_OSC       8000000UL
#define UART_BAUDRATE       9600UL
#define UART_CHAR_SIZE      8
#define UART_STOP_BITS      1
#define UART_PARITY_BIT     UART_PARITY_DISABLED


#endif /* INC_UART_CFG_H_ */
