/*
 * I2c.c
 *
 *  Created on: Mar 18, 2023
 *      Author: ahmad
 */

#include "Types.h"
#include "Macros.h"
#include "Registers.h"
#include "Interrupts.h"
#include "I2c.h"

#define I2C_GET_STATUS()    (TWSR&0xF8)

void I2c_MasterInit(u8 address) {
    /* Set Own Address */
    TWAR = address<<1;
    /* Setting SCL Bit Rate to 400kbps */
    TWBR = 4;
    CLR_BIT(TWSR, 0);
    CLR_BIT(TWSR, 1);
    /* Enable TWI */
    SET_BIT(TWCR, 2);
}

void I2c_SlaveInit(u8 address) {
    /* Set Own Address */
    TWAR = address<<1;
    /* Enable TWI */
    SET_BIT(TWCR, 2);
}

I2c_StatusType I2c_SendStart() {
    /* TWI START Condition Bit */
    SET_BIT(TWCR, 5);
    /* Wait for flag */
    while(GET_BIT(TWCR, 7) == 0);
    /* Return Status */
    return I2C_GET_STATUS();
}

I2c_StatusType I2c_SendSlaveAddress(u8 address, I2c_RequestType request) {
    /* Clear TWI START Condition Bit */
    CLR_BIT(TWCR, 5);
    /* Set SLA+R/W */
    TWDR = (address<<1) | request;
    /* Clear Flag */
    SET_BIT(TWCR, 7);
    /* Wait for flag */
    while(GET_BIT(TWCR, 7) == 0);
    /* Return Status */
    return I2C_GET_STATUS();
}

I2c_StatusType I2c_WriteData(u8 data) {
    /* Write Data */
    TWDR = data;
    /* Clear Flag */
    SET_BIT(TWCR, 7);
    /* Wait for flag */
    while(GET_BIT(TWCR, 7) == 0);
    /* Return Status */
    return I2C_GET_STATUS();
}

I2c_StatusType I2c_ReadData(u8* data) {
    /* Clear Flag */
    SET_BIT(TWCR, 7);
    /* Wait for flag */
    while(GET_BIT(TWCR, 7) == 0);
    /* Read Data */
    *data = TWDR;
    /* Return Status */
    return I2C_GET_STATUS();
}

void I2c_SendStop(void) {
    /* Clear Flag */
    SET_BIT(TWCR, 7);
    /* TWI STOP Condition Bit */
    SET_BIT(TWCR, 4);
}

void I2c_EnableAck(void) {
    SET_BIT(TWCR, 6);
}
void I2c_DisableAck(void) {
    CLR_BIT(TWCR, 6);
}

I2c_ErrorType I2c_MasterTransmit(u8 data[], u8 length, u8 address) {
    u8 i;
    I2c_StatusType state;
    state = I2c_SendStart();
    if (I2C_STATUS_MASTER_START_SENT != state) {
        return I2C_ERROR_START_NOT_SENT;
    }
    state = I2c_SendSlaveAddress(address, I2C_REQUEST_WRITE);
    if (I2C_STATUS_MASTER_SA_W_ACK != state) {
        return I2C_ERROR_SLA_NACK;
    }
    for (i=0; i<length; i++) {
        state = I2c_WriteData(data[i]);
        if (I2C_STATUS_MASTER_DATA_SENT_ACK != state) {
            return I2C_ERROR_DATA_NACK;
        }
    }
    I2c_SendStop();
    return I2C_NO_ERROR;
}
I2c_ErrorType I2c_MasterReceive(u8 data[], u8 length, u8 address) {
    /**
     * TODO: 
    */
}

I2c_ErrorType I2c_SlaveTransmit(u8 data[], u8 length, u8 address) {
    /**
     * TODO: 
    */
}

I2c_ErrorType I2c_SlaveReceive(u8 data[], u8 length, u8 address) {
    I2c_StatusType state;
    u8 i, tempBuffer;
    I2c_EnableAck();
    /* Wait for flag */
    while(GET_BIT(TWCR, 7) == 0);

    /* Check for status */
    if (I2C_GET_STATUS() != I2C_STATUS_SLAVE_SA_W_RECEIVED) {
        return I2C_ERROR_WRITE_REQUEST_NOT_RECEIVED;
    }

    for (i=0; i<length; i++) {
        /* Read Data */
        state = I2c_ReadData(&tempBuffer);
        if (I2C_STATUS_SLAVE_SA_DATA_RECEIVED_ACK != state) {
            return I2C_ERROR_DATA_NOT_RECEIVED;
        }
        data[i] = tempBuffer;
    }

    I2c_DisableAck();
    return I2C_NO_ERROR;
}

