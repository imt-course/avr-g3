/*
 * main.c
 *
 *  Created on: Jan 27, 2023
 *      Author: ahmad
 */


#include "Types.h"
#include "Macros.h"
#include "Registers.h"
#include "Dio.h"
#include "Led.h"
#include "Button.h"
#include "Delay.h"

int main (void) {

#if 0
	/* LED is connected to A4 */

	/* Set Pin as Output */
	SET_BIT(DDRA,4);

	while (1) {
		/* Set Pin to high */
		SET_BIT(PORTA, 4);
		_delay_ms(500);
		/* Set Pin to low */
		CLR_BIT(PORTA, 4);
		_delay_ms(500);
	}
#endif

#if 0

	/*
	 *  LED:    PIN_A0
	 *  SWITCH: PIN_A1
	 */

	/* Set LED pin as output */
	SET_BIT(DDRA, 0);
	/* Set SWITCH pin as input */
	CLR_BIT(DDRA, 1);
	/* Enable Pull up resistor */
	SET_BIT(PORTA, 1);
	for (;;) {
		/* Check if SWITCH is pressed */
		if (GET_BIT(PINA, 1) == 0) {
			/*Turn LED on*/
			SET_BIT(PORTA, 0);
		}
		else {
			/* Turn LED off*/
			CLR_BIT(PORTA, 0);
		}
	}

#endif

#if 1
	Led_Init(LED_PIN);
	Button_Init(BUTTON_PIN);
	while (1)
	{
		if (Button_GetState(BUTTON_PIN) == BUTTON_PRESSED) {
			Led_TurnOn(LED_PIN);
		}
		else {
			Led_TurnOff(LED_PIN);
		}
	}
#endif


}
