/*
 * Dio.h
 *
 *  Created on: Jan 28, 2023
 *      Author: ahmad
 */

#ifndef INC_DIO_H_
#define INC_DIO_H_

/******************* Types Definition *******************/

typedef enum {
    DIO_PORTA,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PORTD
} Dio_PortType;

typedef enum {
    DIO_PIN0,
    DIO_PIN1,
    DIO_PIN2,
    DIO_PIN3,
    DIO_PIN4,
    DIO_PIN5,
    DIO_PIN6,
    DIO_PIN7
} Dio_PinType;

typedef enum {
    DIO_MODE_INPUT_FLOATING,
    DIO_MODE_INPUT_PULLUP,
    DIO_MODE_OUTPUT
} Dio_ModeType;

typedef enum {
    DIO_LEVEL_LOW,
    DIO_LEVEL_HIGH
} Dio_LevelType;


/******************* Functions Prototype *******************/

/**
 * @brief The function sets the mode (direction) of pin
 * 
 * @param port  : The port of pin
 * @param pin   : The pin index
 * @param mode  : The mode to be set
 */
void Dio_SetPinMode(Dio_PortType port, Dio_PinType pin, Dio_ModeType mode);


/**
 * @brief The function sets the level (High/Low) of pin
 * 
 * @param port  : The port of pin
 * @param pin   : The pin index
 * @param level : The level to be set
 */
void Dio_SetPinLevel(Dio_PortType port, Dio_PinType pin, Dio_LevelType level);


/**
 * @brief The function toggle the level (High/Low) of pin
 * 
 * @param port  : The port of pin
 * @param pin   : The pin index
 * @return Dio_LevelType : New level of pin after flipping
 */
Dio_LevelType Dio_FlipPinLevel(Dio_PortType port, Dio_PinType pin);


/**
 * @brief The function reads pin level (High/Low)
 * 
 * @param port  : The port of pin
 * @param pin   : The pin index
 * @return Dio_LevelType : Level of pin (High/Low)
 */
Dio_LevelType Dio_ReadPinLevel (Dio_PortType port, Dio_PinType pin);


#endif /* INC_DIO_H_ */
