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
#include "Gpt.h"
#include "Pwm.h"
#include "Icu.h"
#include "Wdt.h"
#include "Uart.h"
#include "Eeprom.h"
#include "Delay.h"




int main (void) {
	u8 value = 0;
	Eeprom_Init();
	Uart_Init();
	Uart_Transmit('*');
	_delay_ms(1000);
	Eeprom_ReadByte(10, &value);
	Uart_Transmit(value);
	while (1)
	{
		value = Uart_Receive();
		Uart_Transmit(value);
		Eeprom_WriteByte(10, value);
		_delay_ms(500);
		Eeprom_ReadByte(10, &value);
		Uart_Transmit(value);
	}
}


#if 0
//#define ICU_HW
volatile u16 T_on;
volatile u16 T_total;
volatile u8 overflow_counter = 0;

#ifdef ICU_HW

void Handler_Icu (u16 value) {
	static u8 state = 1;
	static u16 offset = 0;
	switch (state)
	{
	case 1:
		offset = value;
		overflow_counter = 0;
		state = 2;
		break;
	case 2:
		T_total = 0x100*overflow_counter + value - offset;
		Icu_SetTriggerEdge(ICU_EDGE_FALLING);
		state = 3;
		break;
	case 3:
		T_on = 0x100*overflow_counter + value - T_total - offset;
		Icu_SetTriggerEdge(ICU_EDGE_RISING);
		state = 1;
		break;
	default:
		break;
	}
}

void Handler_Tim1_OVF (void) {
	overflow_counter++;
}

#endif 



#ifdef ICU_SW

void Handler_Int0 (void) {
	static u8 state = 1;
	static u16 offset = 0;
	switch (state)
	{
	case 1:
		offset = Gpt_GetElapsedTime(GPT_CHANNEL_TIM0);
		overflow_counter = 0;
		state = 2;
		break;
	case 2:
		T_total = 0x100*overflow_counter + Gpt_GetElapsedTime(GPT_CHANNEL_TIM0) - offset;
		ExtInt_SetTriggerEdge(EXTINT_CHANNEL_INT0, EXTINT_TRIGGER_FALLING_EDGE);
		state = 3;
		break;
	case 3:
		T_on = 0x100*overflow_counter + Gpt_GetElapsedTime(GPT_CHANNEL_TIM0) - T_total - offset;
		ExtInt_SetTriggerEdge(EXTINT_CHANNEL_INT0, EXTINT_TRIGGER_RISING_EDGE);
		state = 1;
		break;
	default:
		break;
	}
}

void Handler_Tim0_OVF (void) {
	overflow_counter++;
}

#endif 

volatile u8 receivedChar;
volatile u8 receivedFlag = 0;

void Handler_UartRx (u8 data) {
	receivedChar = data;
	receivedFlag = 1;
}

int main (void) {
	Uart_Init();
	Uart_SetReceiveCallback(Handler_UartRx);
	Uart_EnableNotification(UART_INT_SOURCE_RX);
	Gie_Enable();
	while (1)
	{
		if (receivedFlag) {
			Uart_Transmit(receivedChar);
			receivedFlag = 0;
		}
	}
	


#if 0
	Dio_SetPinMode(DIO_PORTA, DIO_PIN0, DIO_MODE_OUTPUT);
	Wdt_SetTimeOut(WDT_TIMEOUT_2100_MS);
	Wdt_Enable();
	Dio_SetPinLevel(DIO_PORTA, DIO_PIN0, DIO_LEVEL_HIGH);
	_delay_ms(1000);
	Dio_SetPinLevel(DIO_PORTA, DIO_PIN0, DIO_LEVEL_LOW);
	while (1)
	{
		_delay_ms(800);
		Wdt_Refresh();
	}
#endif

#ifdef ICU_HW
	u8 i = 0;
	Lcd_Init(&Lcd_Configuration);

	Dio_SetPinMode(ICU_PIN, DIO_MODE_INPUT_FLOATING);

	Icu_SetTriggerEdge(ICU_EDGE_RISING);
	Icu_SetCallback(Handler_Icu);
	Icu_EnableNotification();

	Gpt_Init(GPT_CHANNEL_TIM1, &Gpt_Configuration[1]);
	Gpt_Start(GPT_CHANNEL_TIM1, GPT_PRESCALER_8);
	Gpt_SetCallback(GPT_INT_SOURCE_TIM1_OVF, Handler_Tim1_OVF);
	Gpt_EnableNotification(GPT_INT_SOURCE_TIM1_OVF);

	Pwm_Init(PWM_CHANNEL_OC0, PWM_MODE_FAST);
	Pwm_Start(PWM_CHANNEL_OC0, PWM_PRESCALER_8);

	Gie_Enable();

	Lcd_DisplayString(" ** ");
	_delay_ms(1000);

	while (1)
	{
		Pwm_SetTimeOn(PWM_CHANNEL_OC0, i);
		_delay_ms(20);
		Lcd_Print("T_total = %d", T_total);
		Lcd_SetCursorPosition(1,0);
		Lcd_Print("T_on = %d", T_on);
		_delay_ms(500);
		Lcd_ClearDisplay();
		i += 50;
	}
#endif 

#ifdef ICU_SW

	Lcd_Init(&Lcd_Configuration);

	Dio_SetPinMode(EXTINT_PIN_INT0, DIO_MODE_INPUT_FLOATING);

	ExtInt_SetTriggerEdge(EXTINT_CHANNEL_INT0, EXTINT_TRIGGER_RISING_EDGE);
	ExInt_SetCallback(EXTINT_CHANNEL_INT0, Handler_Int0);
	ExtInt_EnableNotification(EXTINT_CHANNEL_INT0);

	Gpt_Init(GPT_CHANNEL_TIM0, &Gpt_Configuration[0]);
	Gpt_Start(GPT_CHANNEL_TIM0, GPT_PRESCALER_8);
	Gpt_SetCallback(GPT_INT_SOURCE_TIM0_OVF, Handler_Tim0_OVF);
	Gpt_EnableNotification(GPT_INT_SOURCE_TIM0_OVF);

	Gie_Enable();

	Lcd_DisplayString(" ** ");
	_delay_ms(1000);

	while (1)
	{
		Lcd_Print("T_total = %d", T_total);
		Lcd_SetCursorPosition(1,0);
		Lcd_Print("T_on = %d", T_on);
		_delay_ms(100);
		Lcd_ClearDisplay();
	}

#endif 

#if 0
	u16 i;
	Pwm_Init(PWM_CHANNEL_OC1A, PWM_MODE_FAST_ICR1);
	Pwm_SetICR(20000);
	Pwm_Start(PWM_CHANNEL_OC1A, PWM_PRESCALER_8);
	while (1)
	{
		for (i = 500; i<2500; i+=100) {
			Pwm_SetTimeOn(PWM_CHANNEL_OC1A, i);
			_delay_ms(1500);
		}
	}
#endif 

#if 0
	u8 last_value = 1;
	Pwm_Init(PWM_CHANNEL_OC0, PWM_MODE_FAST);
	Gpt_Init(GPT_CHANNEL_TIM2, &Gpt_Configuration[2]);
	Gpt_SetCompareValue(GPT_COMP_REG_TIM2, 250);
	Gpt_SetCallback(GPT_INT_SOURCE_TIM2_COMP, Handler_Tim2_COMP);
	Gpt_EnableNotification(GPT_INT_SOURCE_TIM2_COMP);
	Pwm_Start(PWM_CHANNEL_OC0, PWM_PRESCALER_8);
	Gie_Enable();
	while (1)
	{
		// countUp = (i == 100)? 0 : (i == 0)? 1 : countUp;
		if (i == 100) {
			countUp = 0;
		}
		else if (i == 0) {
			countUp = 1;
		}
		if (last_value != i) {
			last_value = i;
			Pwm_SetDutyCycle(PWM_CHANNEL_OC0, i);
		}

	}
#endif 

#if 0
	u8 i;
	Pwm_Init(PWM_CHANNEL_OC0, PWM_MODE_FAST);
	Pwm_Start(PWM_CHANNEL_OC0, PWM_PRESCALER_8);
	while (1)
	{
		for (i=0; i<=100; i++) {
			Pwm_SetDutyCycle(PWM_CHANNEL_OC0, i);
			_delay_ms(10);
		}
		for (i=100; i>0; i--) {
			Pwm_SetDutyCycle(PWM_CHANNEL_OC0, i);
			_delay_ms(10);
		}
	}
#endif

#if 0
	Dio_SetPinMode(DIO_PORTA, DIO_PIN0, DIO_MODE_OUTPUT);
	Gpt_Init(GPT_CHANNEL_TIM0, &Gpt_Configuration[0]);
	Gpt_SetCompareValue(GPT_COMP_REG_TIM0, 125);
	Gpt_SetCallback(GPT_INT_SOURCE_TIM0_COMP, Handler_Tim0_COMP);
	Gpt_EnableNotification(GPT_INT_SOURCE_TIM0_COMP);
	Gpt_Start(GPT_CHANNEL_TIM0, GPT_PRESCALER_256);
	Gie_Enable();
	while (1)
	{
		
	}
#endif

#if 0
	Dio_SetPinMode(DIO_PORTA, DIO_PIN0, DIO_MODE_OUTPUT);
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
#endif


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
#endif
