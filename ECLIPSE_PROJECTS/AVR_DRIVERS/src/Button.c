/*
 * Button.c
 *
 *  Created on: Jan 28, 2023
 *      Author: ahmad
 */

#include "Types.h"
#include "Dio.h"
#include "Button_Cfg.h"
#include "Button.h"



void Button_Init(Dio_PortType port, Dio_PinType pin) {
#if (BUTTON_CONNECTION == BUTTON_PULLUP)
    Dio_SetPinMode(port, pin, DIO_MODE_INPUT_PULLUP);
#elif (BUTTON_CONNECTION == BUTTON_PULLDOWN)
    Dio_SetPinMode(port, pin, DIO_MODE_INPUT_FLOATING);
    #warning "Input Pull Down not supported"
#else
    #error "Invalid Button Connection Type"
#endif
}


Button_StateType Button_GetState(Dio_PortType port, Dio_PinType pin) {
    Button_StateType ret_value = BUTTON_NOT_PRESSED;
#if (BUTTON_CONNECTION == BUTTON_PULLUP)
    if (Dio_ReadPinLevel(port, pin) == DIO_LEVEL_LOW)
#elif (BUTTON_CONNECTION == BUTTON_PULLDOWN)
    if (Dio_ReadPinLevel(port, pin) == DIO_LEVEL_HIGH)
#else
    if (0)
#endif
    {
        ret_value = BUTTON_PRESSED;
    }
    else {
        ret_value = BUTTON_NOT_PRESSED;
    }
    return ret_value;
}


