/*
 * ExtInt.c
 *
 *  Created on: Feb 11, 2023
 *      Author: ahmad
 */
#include "Types.h"
#include "Registers.h"
#include "Macros.h"
#include "Interrupts.h"
#include "ExtInt.h"

void (*Callback_Int0) (void) = NULL_PTR;
void (*Callback_Int1) (void) = NULL_PTR;
void (*Callback_Int2) (void) = NULL_PTR;

ISR(VECTOR_INT0)
{
	if (NULL_PTR != Callback_Int0) {
        Callback_Int0();
    }
}

ISR(VECTOR_INT1)
{
	if (NULL_PTR != Callback_Int1) {
        Callback_Int1();
    }
}

ISR(VECTOR_INT2)
{
	if (NULL_PTR != Callback_Int2) {
        Callback_Int2();
    }
}

void ExInt_SetCallback(ExtInt_ChannelType channel, void (*funcPtr) (void)) {
    switch (channel)
    {
    case EXTINT_CHANNEL_INT0:
        Callback_Int0 = funcPtr;
        break;
    case EXTINT_CHANNEL_INT1:
        Callback_Int1 = funcPtr;
        break;
    case EXTINT_CHANNEL_INT2:
        Callback_Int2 = funcPtr;
        break;
    default:
        break;
    }
}

void ExtInt_SetTriggerEdge(ExtInt_ChannelType channel, ExtInt_TriggerEdgeType edge) {
    switch (channel)
    {
    case EXTINT_CHANNEL_INT0:
    {
        switch (edge)
        {
        case EXTINT_TRIGGER_LOW_LEVEL:
            CLR_BIT(MCUCR, MCUCR_ISC00);
            CLR_BIT(MCUCR, MCUCR_ISC01);
            break;
        case EXTINT_TRIGGER_ON_CHANGE:
            SET_BIT(MCUCR, MCUCR_ISC00);
            CLR_BIT(MCUCR, MCUCR_ISC01);
            break;
        case EXTINT_TRIGGER_FALLING_EDGE:
            CLR_BIT(MCUCR, MCUCR_ISC00);
            SET_BIT(MCUCR, MCUCR_ISC01);
            break;
        case EXTINT_TRIGGER_RISING_EDGE:
            SET_BIT(MCUCR, MCUCR_ISC00);
            SET_BIT(MCUCR, MCUCR_ISC01);
            break;
        default:
            break;
        }
        break;
    }
    case EXTINT_CHANNEL_INT1:
    {
        switch (edge)
        {
        case EXTINT_TRIGGER_LOW_LEVEL:
            CLR_BIT(MCUCR, MCUCR_ISC10);
            CLR_BIT(MCUCR, MCUCR_ISC11);
            break;
        case EXTINT_TRIGGER_ON_CHANGE:
            SET_BIT(MCUCR, MCUCR_ISC10);
            CLR_BIT(MCUCR, MCUCR_ISC11);
            break;
        case EXTINT_TRIGGER_FALLING_EDGE:
            CLR_BIT(MCUCR, MCUCR_ISC10);
            SET_BIT(MCUCR, MCUCR_ISC11);
            break;
        case EXTINT_TRIGGER_RISING_EDGE:
            SET_BIT(MCUCR, MCUCR_ISC10);
            SET_BIT(MCUCR, MCUCR_ISC11);
            break;
        default:
            break;
        }
        break;
    }
    case EXTINT_CHANNEL_INT2:
    {
        switch (edge)
        {
        case EXTINT_TRIGGER_FALLING_EDGE:
            CLR_BIT(MCUCSR, MCUCSR_ISC2);
            break;
        case EXTINT_TRIGGER_RISING_EDGE:
            SET_BIT(MCUCSR, MCUCSR_ISC2);
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void ExtInt_EnableNotification(ExtInt_ChannelType channel) {
    switch (channel)
    {
    case EXTINT_CHANNEL_INT0:
        SET_BIT(GICR, GICR_INT0);
        break;
    case EXTINT_CHANNEL_INT1:
        SET_BIT(GICR, GICR_INT1);
        break;
    case EXTINT_CHANNEL_INT2:
        SET_BIT(GICR, GICR_INT2);
        break;
    default:
        break;
    }
}

void ExtInt_DisableNotification(ExtInt_ChannelType channel) {
    switch (channel)
    {
    case EXTINT_CHANNEL_INT0:
        CLR_BIT(GICR, GICR_INT0);
        break;
    case EXTINT_CHANNEL_INT1:
        CLR_BIT(GICR, GICR_INT1);
        break;
    case EXTINT_CHANNEL_INT2:
        CLR_BIT(GICR, GICR_INT2);
        break;
    default:
        break;
    }

}

void ExtInt_ClearFlag(ExtInt_ChannelType channel) {
    switch (channel)
    {
    case EXTINT_CHANNEL_INT0:
        SET_BIT(GIFR, GIFR_INTF0);
        break;
    case EXTINT_CHANNEL_INT1:
        SET_BIT(GIFR, GIFR_INTF1);
        break;
    case EXTINT_CHANNEL_INT2:
        SET_BIT(GIFR, GIFR_INTF2);
        break;
    default:
        break;
    }
}

u8 ExtInt_ReadFlag(ExtInt_ChannelType channel) {
    u8 flag = 0;
    switch (channel)
    {
    case EXTINT_CHANNEL_INT0:
        flag = GET_BIT(GIFR, GIFR_INTF0);
        break;
    case EXTINT_CHANNEL_INT1:
        flag = GET_BIT(GIFR, GIFR_INTF1);
        break;
    case EXTINT_CHANNEL_INT2:
        flag = GET_BIT(GIFR, GIFR_INTF2);
        break;
    default:
        break;
    }
    return flag;
}
