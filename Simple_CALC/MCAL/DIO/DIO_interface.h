/*********************************************************************/
/*********************************************************************/
/*++++++++++++++++++  AUTHOR : ABANOB EVRAM   +++++++++++++++++++++++*/  
/*++++++++++++++++++  LAYER:MCAL              +++++++++++++++++++++++*/  
/*++++++++++++++++++  SWC:DIO                 +++++++++++++++++++++++*/  
/*++++++++++++++++++  VERSION:1.00            +++++++++++++++++++++++*/  
/*********************************************************************/ 
/*********************************************************************/ 

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/*Macros for PIN HIGH/LOW*/
#define DIO_u8PIN_LOW        0
#define DIO_u8PIN_HIGH       1
/*Macros for PORT HIGH/LOW*/
#define  DIO_u8PORT_LOW      0
#define  DIO_u8PORT_HIGH     0xff
/*Macros for define the value of PORTS*/
#define DIO_u8PORTA          0
#define DIO_u8PORTB          1
#define DIO_u8PORTC          2
#define DIO_u8PORTD          3
/*Macros for define the value of PINS*/
#define DIO_u8PIN0           0
#define DIO_u8PIN1           1
#define DIO_u8PIN2           2
#define DIO_u8PIN3           3
#define DIO_u8PIN4           4
#define DIO_u8PIN5           5
#define DIO_u8PIN6           6
#define DIO_u8PIN7           7

/*Function for set the value of PIN : high/low*/
u8 DIO_u8SetPinValue(u8 Copy_u8Port , u8 Copy_u8Pin ,u8 Copy_u8value);
/*Function for set the value of PPRT : high/low*/
u8 DIO_u8SetPortValue(u8 Copy_u8Port ,u8 Copy_u8value);
/*Function for read the pin : high/low*/
u8 DIO_u8GetPinValue(u8 Copy_u8Port,u8 Copy_u8Pin,u8* Copy_pu8Value);

#endif
