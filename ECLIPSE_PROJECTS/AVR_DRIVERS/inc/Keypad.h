/*
 * Keypad.h
 *
 *  Created on: Feb 4, 2023
 *      Author: ahmad
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

/***********************************************
*   B00   *   B01   *   B02   *   B03   *  ROW1*
*   B04   *   B05   *   B06   *   B07   *  ROW2*
*   B08   *   B09   *   B10   *   B11   *  ROW3*
*   B12   *   B13   *   B14   *   B15   *  ROW4*
* COLOMN1   COLUMN2   COLUMN3   COLUMN4 *      *
***********************************************/


typedef enum {
    KEYPAD_NOT_PRESSED,
    KEYPAD_PRESSED,
} Keypad_ButtonStateType;

typedef enum {
    KEYPAD_BUTTON_00,
    KEYPAD_BUTTON_01,
    KEYPAD_BUTTON_02,
    KEYPAD_BUTTON_03,
    KEYPAD_BUTTON_04,
    KEYPAD_BUTTON_05,
    KEYPAD_BUTTON_06,
    KEYPAD_BUTTON_07,
    KEYPAD_BUTTON_08,
    KEYPAD_BUTTON_09,
    KEYPAD_BUTTON_10,
    KEYPAD_BUTTON_11,
    KEYPAD_BUTTON_12,
    KEYPAD_BUTTON_13,
    KEYPAD_BUTTON_14,
    KEYPAD_BUTTON_15
} Keypad_ButtonType;

void Keypad_Init(void);
Keypad_ButtonStateType Keypad_GetButtonState(Keypad_ButtonType button);

#endif /* INC_KEYPAD_H_ */
