/*
 * Eeprom.h
 *
 *  Created on: Mar 24, 2023
 *      Author: ahmad
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "Types.h"

typedef enum {
    EEPROM_FAIL,
    EEPROM_SUCCESS,
} Eeprom_StateType;

void Eeprom_Init(void);
Eeprom_StateType Eeprom_WriteByte(u16 address, u8 data);
Eeprom_StateType Eeprom_ReadByte(u16 address, u8* data);



#endif /* INC_EEPROM_H_ */
