/*********************************************************************/
/*********************************************************************/
/*++++++++++++++++++  AUTHOR : ABANOB EVRAM   +++++++++++++++++++++++*/  
/*++++++++++++++++++  LAYER:HAL               +++++++++++++++++++++++*/  
/*++++++++++++++++++  SWC:CLCD                +++++++++++++++++++++++*/  
/*++++++++++++++++++  VERSION:1.00            +++++++++++++++++++++++*/  
/*********************************************************************/ 
/*********************************************************************/ 
//preprocessor file guard
#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

#define  CLCD_DATA_PORT   DIO_u8PORTA

/*Choose your connection mode : 1-CLCD_EIGHT_BIT
 *                              2-CLCD_FOUR_BIT  */

#define CLCD_MODE         CLCD_FOUR_BIT


#if CLCD_MODE == CLCD_FOUR_BIT
#define CLCD_u8PIN4       DIO_u8PIN4
#define CLCD_u8PIN5       DIO_u8PIN5
#define CLCD_u8PIN6       DIO_u8PIN6
#define CLCD_u8PIN7       DIO_u8PIN7
#endif


#define CLCD_CTR_PORT     DIO_u8PORTC
#define CLCD_RS_PIN       DIO_u8PIN0
#define CLCD_RW_PIN       DIO_u8PIN1
#define CLCD_E_PIN        DIO_u8PIN2



#endif
