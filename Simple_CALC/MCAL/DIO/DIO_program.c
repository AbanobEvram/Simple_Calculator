/*********************************************************************/
/*********************************************************************/
/*++++++++++++++++++  AUTHOR : ABANOB EVRAM   +++++++++++++++++++++++*/  
/*++++++++++++++++++  LAYER:MCAL              +++++++++++++++++++++++*/  
/*++++++++++++++++++  SWC:DIO                 +++++++++++++++++++++++*/  
/*++++++++++++++++++  VERSION:1.00            +++++++++++++++++++++++*/  
/*********************************************************************/ 
/*********************************************************************/ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_register.h"
#include "DIO_interface.h"
#include "DIO_private.h"


/*****************************************************************************************/
u8 DIO_u8SetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin ,u8 Copy_u8value)
{
	/*Local variable for checking the errors*/
	u8 Local_ErrorState=0;
	/*Check the value of the pin if it correct */
	if(Copy_u8Pin<=DIO_u8PIN7)
	{
		/*in case the value is low*/
		if(Copy_u8value==DIO_u8PIN_LOW)
		{
			// Check on the Required PORT Number
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA : CLR_BIT(PORTA,Copy_u8Pin);    break;
			case DIO_u8PORTB : CLR_BIT(PORTB,Copy_u8Pin);    break;
			case DIO_u8PORTC : CLR_BIT(PORTC,Copy_u8Pin);    break;
			case DIO_u8PORTD : CLR_BIT(PORTD,Copy_u8Pin);    break;
			default: Local_ErrorState=1 ;                    break;
			}
		}
		/*in case the value is high*/
		else if(Copy_u8value==DIO_u8PIN_HIGH)
		{
			// Check on the Required PORT Number
			switch(Copy_u8Port)
			{
			case DIO_u8PORTA : SET_BIT(PORTA,Copy_u8Pin);    break;
			case DIO_u8PORTB : SET_BIT(PORTB,Copy_u8Pin);    break;
			case DIO_u8PORTC : SET_BIT(PORTC,Copy_u8Pin);    break;
			case DIO_u8PORTD : SET_BIT(PORTD,Copy_u8Pin);    break;
			default: Local_ErrorState=1 ;                    break;
			}
		}
		/*in case the value is error*/
		else
		{
			Local_ErrorState =1;
		}
	}
	/*in case the PIN error*/
	else
	{
		Local_ErrorState =1;
	}
	return Local_ErrorState;
}
/*****************************************************************************************/
u8 DIO_u8SetPortValue(u8 Copy_u8Port ,u8 Copy_u8value)
{
	/*Local variable for checking the errors*/
	u8 Local_ErrorState=0;
	// Check on the Required PORT Number
	switch(Copy_u8Port)
	{
	case DIO_u8PORTA : PORTA = Copy_u8value;    break;
	case DIO_u8PORTB : PORTB = Copy_u8value;    break;
	case DIO_u8PORTC : PORTC = Copy_u8value;    break;
	case DIO_u8PORTD : PORTD = Copy_u8value;    break;
	default :	Local_ErrorState=1;             break;
	}
	return Local_ErrorState;
}
/*****************************************************************************************/
u8 DIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8* Copy_pu8Value)
{
	/*Local variable for checking the errors*/
	u8 Local_ErrorState=0;
	if((Copy_pu8Value!=NULL)&&(Copy_u8Pin<=DIO_u8PIN7))
	{
		// Check on the Required PORT Number
		switch(Copy_u8Port)
		{
		case DIO_u8PORTA :* Copy_pu8Value =GET_BIT(PINA,Copy_u8Pin);   break;
		case DIO_u8PORTB :* Copy_pu8Value =GET_BIT(PINB,Copy_u8Pin);   break;
		case DIO_u8PORTC :* Copy_pu8Value =GET_BIT(PINC,Copy_u8Pin);   break;
		case DIO_u8PORTD :* Copy_pu8Value =GET_BIT(PIND,Copy_u8Pin);   break;
		default :	Local_ErrorState=1;             break;
		}
	}
	else
	{
		Local_ErrorState=1;
	}
	return Local_ErrorState;
}
/*****************************************************************************************/
