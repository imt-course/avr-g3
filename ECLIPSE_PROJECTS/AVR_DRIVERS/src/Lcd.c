/*
 * Lcd.c
 *
 *  Created on: Feb 3, 2023
 *      Author: ahmad
 */

#include <stdarg.h>
#include "Types.h"
#include "Dio.h"
#include "Macros.h"
#include "Delay.h"
#include "Lcd_Cfg.h"
#include "Lcd.h"

static void Lcd_SendCommand(u8 command);
static void Lcd_SendData(u8 data);
#if LCD_MODE == LCD_MODE_4_BIT
static void Lcd_Enter_4Bit_Mode(void);
#endif

void Lcd_Init(const Lcd_DisplayControlType* control) {
    Dio_SetPinMode(LCD_PIN_RS, DIO_MODE_OUTPUT);
    Dio_SetPinMode(LCD_PIN_RW, DIO_MODE_OUTPUT);
    Dio_SetPinMode(LCD_PIN_EN, DIO_MODE_OUTPUT);
#if LCD_MODE == LCD_MODE_8_BIT
    Dio_SetPinMode(LCD_PIN_D0, DIO_MODE_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D1, DIO_MODE_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D2, DIO_MODE_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D3, DIO_MODE_OUTPUT);
#endif
    Dio_SetPinMode(LCD_PIN_D4, DIO_MODE_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D5, DIO_MODE_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D6, DIO_MODE_OUTPUT);
    Dio_SetPinMode(LCD_PIN_D7, DIO_MODE_OUTPUT);

#if LCD_MODE == LCD_MODE_4_BIT
    Lcd_Enter_4Bit_Mode();
#endif

    Lcd_ControlDisplay(control);

   /* Display Clear */
   Lcd_SendCommand(0b00000001);
}

void Lcd_DisplayCharcter(char data) {
    Lcd_SendData(data);
}

void Lcd_DisplayString(const char* str) {
    while (*str != '\0') {
        Lcd_SendData(*str);
        str++;
    }
}

void Lcd_DisplayNumber(s32 number) {
    u64 reversed = 0;
    u8 digitsCounter = 0;
    if (number < 0) {
        number = number * -1;
        Lcd_SendData('-');
    }
    do {
        reversed = (reversed*10) + (number%10);
        number /= 10;
        digitsCounter++;
    } while (number > 0);
    while (digitsCounter > 0) {
        Lcd_SendData(reversed%10 + '0');
        reversed /= 10;
        digitsCounter--;
    }
}

void Lcd_ClearDisplay(void) {
    Lcd_SendCommand(1);
}
// 1, 39 -> 1*0x40 + 39 = 0x40 + 0x27 = 0x67
void Lcd_SetCursorPosition(u8 row, u8 column) {
    u8 address = row*0x40 + column;
    SET_BIT(address, 7);
    Lcd_SendCommand(address);
}

void Lcd_ShiftDisplayLeft(u8 count) {
    while (count > 0) {
        Lcd_SendCommand(0b00011000);
        count--;
    }
}

void Lcd_ShiftDisplayRight(u8 count) {
    while (count > 0) {
        Lcd_SendCommand(0b00011100);
        count--;
    }
}

void Lcd_ReturnHome(void) {
    Lcd_SendCommand(0b00000010);
}

void Lcd_ShiftCursorRight(u8 count) {
    while (count > 0) {
        Lcd_SendCommand(0b00010100);
        count--;
    }
}

void Lcd_ShiftCursorLeft(u8 count) {
    while (count > 0) {
        Lcd_SendCommand(0b00010000);
        count--;
    }
}

void Lcd_ControlDisplay(const Lcd_DisplayControlType* control) {
    u8 command;
    /* Display ON/OFF Control */
    command = 0b00001000;
    if (control->display == LCD_STATE_ON) {
        SET_BIT(command, 2);
        if (control->cursor == LCD_STATE_ON) {
            SET_BIT(command, 1);
            if (control->cursorBlink == LCD_STATE_ON) {
                SET_BIT(command, 0);
            }
        }
    } 
    Lcd_SendCommand(command);
    /* Function Set */
#if LCD_MODE == LCD_MODE_8_BIT
    command = 0b00110000;
#elif LCD_MODE == LCD_MODE_4_BIT
    command = 0b00100000;
#endif
    if (control->lines == LCD_LINES_2) {
        SET_BIT(command, 3);
    }
    if (control->font == LCD_FONT_5X10) {
        SET_BIT(command, 2);
    }
    Lcd_SendCommand(command);
}

void Lcd_SaveSpecialCharacter(u8 location, u8* pattern) {
    u8 i;
    if (location < 8) {
        location *= 8;
        SET_BIT(location, 6);
        Lcd_SendCommand(location);
        for (i=0; i<8; i++) {
            Lcd_SendData(pattern[i]);
        }
    }
}

void Lcd_Print(char* str, ...) {
	va_list var_list;
	va_start(var_list, str);
	while(*str != '\0') {
		if (*str == '%') {
			str++;
			switch(*str) {
				case 'c':
                    Lcd_DisplayCharcter((char)va_arg(var_list, int));
					break;
				case 'd':
                    Lcd_DisplayNumber((int)va_arg(var_list, int));
					break;
				case 'u':
                    Lcd_DisplayNumber((unsigned int)va_arg(var_list, unsigned int));
					break;
				case 'l':
                    Lcd_DisplayNumber((long int)va_arg(var_list, long int));
					break;
				default:
					Lcd_DisplayCharcter(*str);
					break;
			}
		}
		else {
			Lcd_DisplayCharcter(*str);
		}
		str++;
	}
}



static void Lcd_SendCommand(u8 command) {
    Dio_SetPinLevel(LCD_PIN_RS, DIO_LEVEL_LOW);
    Dio_SetPinLevel(LCD_PIN_RW, DIO_LEVEL_LOW);
#if LCD_MODE == LCD_MODE_8_BIT
    Dio_SetPinLevel(LCD_PIN_D0, GET_BIT(command, 0));
    Dio_SetPinLevel(LCD_PIN_D1, GET_BIT(command, 1));
    Dio_SetPinLevel(LCD_PIN_D2, GET_BIT(command, 2));
    Dio_SetPinLevel(LCD_PIN_D3, GET_BIT(command, 3));
#endif
    Dio_SetPinLevel(LCD_PIN_D4, GET_BIT(command, 4));
    Dio_SetPinLevel(LCD_PIN_D5, GET_BIT(command, 5));
    Dio_SetPinLevel(LCD_PIN_D6, GET_BIT(command, 6));
    Dio_SetPinLevel(LCD_PIN_D7, GET_BIT(command, 7));
    Dio_SetPinLevel(LCD_PIN_EN, DIO_LEVEL_HIGH);
    _delay_ms(2);
    Dio_SetPinLevel(LCD_PIN_EN, DIO_LEVEL_LOW);
#if LCD_MODE == LCD_MODE_4_BIT
    Dio_SetPinLevel(LCD_PIN_D4, GET_BIT(command, 0));
    Dio_SetPinLevel(LCD_PIN_D5, GET_BIT(command, 1));
    Dio_SetPinLevel(LCD_PIN_D6, GET_BIT(command, 2));
    Dio_SetPinLevel(LCD_PIN_D7, GET_BIT(command, 3));
    Dio_SetPinLevel(LCD_PIN_EN, DIO_LEVEL_HIGH);
    _delay_ms(2);
    Dio_SetPinLevel(LCD_PIN_EN, DIO_LEVEL_LOW);
#endif
}

static void Lcd_SendData(u8 data) {
    Dio_SetPinLevel(LCD_PIN_RS, DIO_LEVEL_HIGH);
    Dio_SetPinLevel(LCD_PIN_RW, DIO_LEVEL_LOW);
#if LCD_MODE == LCD_MODE_8_BIT
    Dio_SetPinLevel(LCD_PIN_D0, GET_BIT(data, 0));
    Dio_SetPinLevel(LCD_PIN_D1, GET_BIT(data, 1));
    Dio_SetPinLevel(LCD_PIN_D2, GET_BIT(data, 2));
    Dio_SetPinLevel(LCD_PIN_D3, GET_BIT(data, 3));
#endif
    Dio_SetPinLevel(LCD_PIN_D4, GET_BIT(data, 4));
    Dio_SetPinLevel(LCD_PIN_D5, GET_BIT(data, 5));
    Dio_SetPinLevel(LCD_PIN_D6, GET_BIT(data, 6));
    Dio_SetPinLevel(LCD_PIN_D7, GET_BIT(data, 7));
    Dio_SetPinLevel(LCD_PIN_EN, DIO_LEVEL_HIGH);
    _delay_ms(2);
    Dio_SetPinLevel(LCD_PIN_EN, DIO_LEVEL_LOW);
#if LCD_MODE == LCD_MODE_4_BIT
    Dio_SetPinLevel(LCD_PIN_D4, GET_BIT(data, 0));
    Dio_SetPinLevel(LCD_PIN_D5, GET_BIT(data, 1));
    Dio_SetPinLevel(LCD_PIN_D6, GET_BIT(data, 2));
    Dio_SetPinLevel(LCD_PIN_D7, GET_BIT(data, 3));
    Dio_SetPinLevel(LCD_PIN_EN, DIO_LEVEL_HIGH);
    _delay_ms(2);
    Dio_SetPinLevel(LCD_PIN_EN, DIO_LEVEL_LOW);
#endif
}

#if LCD_MODE == LCD_MODE_4_BIT
static void Lcd_Enter_4Bit_Mode(void) {
    Dio_SetPinLevel(LCD_PIN_RS, DIO_LEVEL_LOW);
    Dio_SetPinLevel(LCD_PIN_RW, DIO_LEVEL_LOW);
    Dio_SetPinLevel(LCD_PIN_D4, DIO_LEVEL_LOW);
    Dio_SetPinLevel(LCD_PIN_D5, DIO_LEVEL_HIGH);
    Dio_SetPinLevel(LCD_PIN_D6, DIO_LEVEL_LOW);
    Dio_SetPinLevel(LCD_PIN_D7, DIO_LEVEL_LOW);
    Dio_SetPinLevel(LCD_PIN_EN, DIO_LEVEL_HIGH);
    _delay_ms(2);
    Dio_SetPinLevel(LCD_PIN_EN, DIO_LEVEL_LOW);
}
#endif