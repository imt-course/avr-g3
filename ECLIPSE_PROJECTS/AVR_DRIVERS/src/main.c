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
#include "Ssd.h"
#include "Lcd.h"
#include "Keypad.h"
#include "ExtInt.h"
#include "Gie.h"
#include "Adc.h"
#include "Interrupts.h"
#include "Delay.h"

void Handler_Int0 (void) {
	Dio_FlipPinLevel(DIO_PORTA, DIO_PIN0);
}

ISR(VECTOR_TIM0_COMP) {
	static u16 counter = 0;
	counter++;
	if (counter == 4000) {
		counter = 0;
		Dio_FlipPinLevel(DIO_PORTA, DIO_PIN0);
	}
}

int main (void) {
	/* Waveform Generation Mode (CTC) */
	SET_BIT(TCCR0, 3);
	CLR_BIT(TCCR0, 6);
	/* Output Compare Register */
	OCR0 = 250;
	/* Output Compare Match Interrupt Enable */
	SET_BIT(TIMSK, 1);
	/* Clock Select (prescaler 8)*/
	CLR_BIT(TCCR0, 2);
	SET_BIT(TCCR0, 1);
	CLR_BIT(TCCR0, 0);

	/* Glopal Interrupt Enable */
	Gie_Enable();

	while (1)
	{
		
	}
	


#if 0
	u16 result = 0;
	Adc_Init(&Adc_Configuration);
	Lcd_Init(&Lcd_Configuration);
	Adc_StartConversion(ADC_CHANNEL_ADC0);
	while (1)
	{
		Lcd_ClearDisplay();
		if (Adc_GetResultAsync(&result) == ADC_COMPLETE) {
			Lcd_Print("Adc = %d", (((u32)result*5000)/1024));
			Adc_StartConversion(ADC_CHANNEL_ADC0);
		}

		_delay_ms(500);
	}
#endif 


#if 0
	u16 result = 0;
	u8 i;
	Adc_Init(&Adc_Configuration);
	Lcd_Init(&Lcd_Configuration);
	Lcd_DisplayNumber(100);
	_delay_ms(500);
	while (1)
	{
		Lcd_ClearDisplay();
		result = 0;
		for (i=0; i<20; i++) {
			Adc_StartConversion(ADC_CHANNEL_ADC0);
			result += Adc_GetResultSync();
			_delay_ms(15);
		}
		result /= 20;
		Lcd_Print("Adc = %d", (((u32)result*5000)/1024));
		_delay_ms(500);
	}

#endif 
#if 0
	/* LED Pin */
	Dio_SetPinMode(DIO_PORTA, DIO_PIN0, DIO_MODE_OUTPUT);
	/* Button Pin */
	Dio_SetPinMode(EXTINT_PIN_INT0, DIO_MODE_INPUT_PULLUP);
	ExtInt_SetTriggerEdge(EXTINT_CHANNEL_INT0, EXTINT_TRIGGER_FALLING_EDGE);
	ExInt_SetCallback(EXTINT_CHANNEL_INT0, Handler_Int0);
	ExtInt_EnableNotification(EXTINT_CHANNEL_INT0);
	Gie_Enable();
	while (1)
	{
		
	}
#endif 

#if 0
	u16 x = 15;
	u8 pattern[] {
		0b00110,
		0b01100,
		0b00000,
		0b00100,
		0b00100,
		0b00100,
		0b00100,
		0b00000
	};
	Lcd_Init(&Lcd_Configuration);
	Lcd_SaveSpecialCharacter(0, pattern);
	Lcd_SetCursorPosition(1,0);
	Lcd_DisplayCharcter(0);	
#endif


#if 0
	Keypad_ButtonType i;
	u8 flag[16] = {0};
	Keypad_Init();
	Lcd_Init();
	Lcd_DisplayCharcter('*');
	while (1) {
		for (i=KEYPAD_BUTTON_00; i<=KEYPAD_BUTTON_15; i++) {
			if (Keypad_GetButtonState(i) == KEYPAD_PRESSED) {
				if (flag[i] == 0) {
				flag[i] = 1;
				Lcd_DisplayNumber(i);
				Lcd_DisplayCharcter('-');
				}
			}
			else {
				flag[i] = 0;
			}
		}
	}
#endif

#if 0
	Lcd_Init();
	Lcd_DisplayString("My name is Hassan");
	Lcd_DisplayCharcter('-');
	Lcd_DisplayNumber(2147483647);
#endif

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

#if 0
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

#if 0
	u8 i;
	Ssd_Init();
	for (i=0; i<9; i++) {
		Ssd_DisplayNumber(i);
		_delay_ms(1000);
	}
	for (i=9; i>0; i--) {
		Ssd_DisplayNumber(i);
		_delay_ms(1000);
	}
#endif 

}
