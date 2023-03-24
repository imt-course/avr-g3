/*
 * Eeprom.c
 *
 *  Created on: Mar 24, 2023
 *      Author: ahmad
 */

#include "Types.h"
#include "Macros.h"
#include "I2c.h"
#include "Eeprom_Cfg.h"
#include "Eeprom.h"

void Eeprom_Init(void) {
    I2c_MasterInit(0);
}

Eeprom_StateType Eeprom_WriteByte(u16 address, u8 data) {
    I2c_StatusType state;
    u8 slave_address;
    slave_address = (0b1010000 | (EEPROM_PIN_A2<<2) | (address>>8));

    /* Send Start Condition */
    state = I2c_SendStart();
    if (state != I2C_STATUS_MASTER_START_SENT) {
        return EEPROM_FAIL;
    }

    /* Send Slave Address (Device Address [0b1010 + A2/A1/A0 + PageNumber]) */
    state = I2c_SendSlaveAddress(slave_address, I2C_REQUEST_WRITE);
    if (state != I2C_STATUS_MASTER_SA_W_ACK) {
        I2c_SendStop();
        return EEPROM_FAIL;
    }

    /* Send Address in Memory Page [0 .. 255] */
    state = I2c_WriteData((u8)address);
    if (state != I2C_STATUS_MASTER_DATA_SENT_ACK) {
        I2c_SendStop();
        return EEPROM_FAIL;
    }

    /* Send Data to be written */
    state = I2c_WriteData(data);
    if (state != I2C_STATUS_MASTER_DATA_SENT_ACK) {
        I2c_SendStop();
        return EEPROM_FAIL;
    }

    /* Send Stop Condition */
    I2c_SendStop();
    return EEPROM_SUCCESS;
}

Eeprom_StateType Eeprom_ReadByte(u16 address, u8* data) {
    I2c_StatusType state;
    u8 slave_address;
    slave_address = (0b1010000 | (EEPROM_PIN_A2<<2) | (address>>8));

    /* Send Start Condition */
    state = I2c_SendStart();
    if (state != I2C_STATUS_MASTER_START_SENT) {
        return EEPROM_FAIL;
    }

    /* Send Slave Address (Device Address [0b1010 + A2/A1/A0 + PageNumber]) */
    state = I2c_SendSlaveAddress(slave_address, I2C_REQUEST_WRITE);
    if (state != I2C_STATUS_MASTER_SA_W_ACK) {
        I2c_SendStop();
        return EEPROM_FAIL;
    }

    /* Send Address in Memory Page [0 .. 255] */
    state = I2c_WriteData((u8)address);
    if (state != I2C_STATUS_MASTER_DATA_SENT_ACK) {
        I2c_SendStop();
        return EEPROM_FAIL;
    }

    /* Send Repeated Start */
    state = I2c_SendStart();
    if (state != I2C_STATUS_MASTER_REP_START_SENT) {
        return EEPROM_FAIL;
    }

    /* Send Slave Address (Device Address [0b1010 + A2/A1/A0 + PageNumber]) */
    state = I2c_SendSlaveAddress(slave_address, I2C_REQUEST_READ);
    if (state != I2C_STATUS_MASTER_SA_R_ACK) {
        I2c_SendStop();
        return EEPROM_FAIL;
    }

    I2c_EnableAck();

    /* Read Data */
    state = I2c_ReadData(&data);
    if (state != I2C_STATUS_MASTER_DATA_RECEIVED_ACK) {
        I2c_SendStop();
        return EEPROM_FAIL;
    }

    I2c_DisableAck();

    /* Send Stop Condition */
    I2c_SendStop();
    return EEPROM_SUCCESS;
}
