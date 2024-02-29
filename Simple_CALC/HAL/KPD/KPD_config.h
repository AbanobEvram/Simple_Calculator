/*********************************************************************/
/*********************************************************************/
/*++++++++++++++++++  AUTHOR : ABANOB EVRAM   +++++++++++++++++++++++*/  
/*++++++++++++++++++  LAYER:HAL               +++++++++++++++++++++++*/  
/*++++++++++++++++++  SWC:KPD                 +++++++++++++++++++++++*/  
/*++++++++++++++++++  VERSION:1.00            +++++++++++++++++++++++*/  
/*********************************************************************/ 
/*********************************************************************/
//preprocessor file guard
#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_PORT           DIO_u8PORTD
/*Output pins high value*/
#define KPD_COLUMN0_PIN    DIO_u8PIN3
#define KPD_COLUMN1_PIN    DIO_u8PIN2
#define KPD_COLUMN2_PIN    DIO_u8PIN1
#define KPD_COLUMN3_PIN    DIO_u8PIN0
/*Input pins pullup*/
#define KPD_ROW0_PIN       DIO_u8PIN4
#define KPD_ROW1_PIN       DIO_u8PIN5
#define KPD_ROW2_PIN       DIO_u8PIN6
#define KPD_ROW3_PIN       DIO_u8PIN7
/*set a value to return in case of no pressed keys , out of range of[0-15]*/

#define KPD_NO_PRESSED_KEY   0xFF

/*a configurable array to set values of button*/
#define    KPD_ARR_VAL     {{7,8,9,'+'},{4,5,6,'-'},{1,2,3,'*'},{'C',0,'=','/'}}



#endif
