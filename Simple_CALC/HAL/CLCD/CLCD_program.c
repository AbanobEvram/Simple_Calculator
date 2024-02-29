/*********************************************************************/
/*********************************************************************/
/*++++++++++++++++++  AUTHOR : ABANOB EVRAM   +++++++++++++++++++++++*/  
/*++++++++++++++++++  LAYER:HAL               +++++++++++++++++++++++*/  
/*++++++++++++++++++  SWC:CLCD                +++++++++++++++++++++++*/  
/*++++++++++++++++++  VERSION:1.00            +++++++++++++++++++++++*/  
/*********************************************************************/ 
/*********************************************************************/
#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"DIO_interface.h"
#include"CLCD_config.h"
#include"CLCD_interface.h"
#include"CLCD_private.h"
#include<util/delay.h>
#if CLCD_MODE == CLCD_FOUR_BIT
static void CLCD_voidSetDataPins(u8 Copy_u8Data)
{
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_u8PIN4,GET_BIT(Copy_u8Data,0));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_u8PIN5,GET_BIT(Copy_u8Data,1));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_u8PIN6,GET_BIT(Copy_u8Data,2));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_u8PIN7,GET_BIT(Copy_u8Data,3));
}
#endif
void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_CTR_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);
	/*set RW pin to low for rite*/
	DIO_u8SetPinValue(CLCD_CTR_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
#if CLCD_MODE == CLCD_EIGHT_BIT
	/*SET command to data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);
	/*send enable puls*/
	CLCD_voidSendEnablePulse();
#elif CLCD_MODE==CLCD_FOUR_BIT

	CLCD_voidSetDataPins(Copy_u8Command>>4);
	CLCD_voidSendEnablePulse();
	CLCD_voidSetDataPins(Copy_u8Command);
	CLCD_voidSendEnablePulse();

#endif

}


void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*set RS pin to high for data*/
	DIO_u8SetPinValue(CLCD_CTR_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);
	/*set RW pin to low for rite*/
	DIO_u8SetPinValue(CLCD_CTR_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
#if CLCD_MODE == CLCD_EIGHT_BIT
	/*SET DATA to data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	/*send enable puls*/
	CLCD_voidSendEnablePulse();
#elif CLCD_FOUR_BIT== CLCD_FOUR_BIT
	CLCD_voidSetDataPins((Copy_u8Data)>>4);
	CLCD_voidSendEnablePulse();
	CLCD_voidSetDataPins(Copy_u8Data);
	CLCD_voidSendEnablePulse();
#endif
}



void CLCD_voidInit(void)
{
	/*wait for more than 30 ms after VDD rises to 4.5 V */
	_delay_ms(40);
#if CLCD_MODE==CLCD_EIGHT_BIT
	/*Function set command :-
	                  no.of lines(N):  0  for 1 line   Font size(F):  0  for 5*8
	                                   1  for 2 line                  1  for 5*11            */
	CLCD_voidSendCommand(0b00111000);/*m4 bn3ml delay 3l4an al function a5rha delay */

#elif CLCD_MODE == CLCD_FOUR_BIT
	CLCD_voidSetDataPins(0b0010);
	CLCD_voidSendEnablePulse();
	CLCD_voidSetDataPins(0b0010);
	CLCD_voidSendEnablePulse();
	CLCD_voidSetDataPins(0b1000);
	CLCD_voidSendEnablePulse();
#endif
	/*Display on/off control : display enable(D) , disable cursor(C) , no blink cursor(B) */
	CLCD_voidSendCommand(0b00001110);
	/*clear display*/
	CLCD_voidSendCommand(1);

}


void CLCD_voidSendString(const char* Copy_pcString)
{
	u8 Local_u8Counter=0;
	/*Unless the character is not \0 */
	while(Copy_pcString[Local_u8Counter]!='\0')
	{
		/*Send character to display*/
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}


void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	/*Local variable for the addres after calculate */
	u8 Local_u8Address=0;
	/*in case we need to write in first row*/
	if(Copy_u8XPos==0)
	{
		/*Location at first line*/
		Local_u8Address=Copy_u8YPos;
	}
	/*in case we need to write in second row*/
	else if (Copy_u8XPos==1)
	{
		/*Location at second line*/
		Local_u8Address=0x40+Copy_u8YPos;
	}
	//mn saf7t al command l2yt an el bit 7==1 fa gam3t 128 (Set DDRAM Address)
	CLCD_voidSendCommand(Local_u8Address+128);
}
void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern ,u8 Copy_u8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos)
{
   u8 Local_u8CGRAMAddress=0,Local_u8Iterator;
	/*Calculat The CGRAM Address whose each block is 8 bytes*/
	Local_u8CGRAMAddress=Copy_u8PatternNumber*8;
	/*send CGRAM address comand to lcd, with setting bit 6 , clearing bit 7*/
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);
	/*	write the pattern into CG RAM*/
	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}
	/*GO back to DDRAM to display the pattern*/
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);
	/*display the pattern written in the CG RAM*/
	CLCD_voidSendData(Copy_u8PatternNumber);
}
void CLCD_voidWriteNumber(u32 Copy_u32Number)
{
	u8 Local_u8arr[9],Local_u8Iterator1=0;

if(Copy_u32Number==0)
CLCD_voidSendData('0');
else
{

while(Copy_u32Number!=0)
{
	Local_u8arr[Local_u8Iterator1]=Copy_u32Number % 10;
 Copy_u32Number /=10;
 Local_u8Iterator1++;
}
while(Local_u8Iterator1!=0)
{

	CLCD_voidSendData(Local_u8arr[Local_u8Iterator1-1]+48);
	Local_u8Iterator1--;
}
}
}
static void CLCD_voidSendEnablePulse(void)
{
	DIO_u8SetPinValue(CLCD_CTR_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTR_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}
void CLCD_voidWriteFloatOnLCD(f32 number) {
    int integerPart = (int)number;
    int decimalPart = (number - integerPart) * 1000;
    if(integerPart >= 100)
    {
    	integerPart /= 10;
    }
    CLCD_voidWriteNumber(integerPart);
    CLCD_voidSendData('.');
    CLCD_voidWriteNumber(decimalPart);

}
void CLCD_voidCleatTheScreen()
{
	CLCD_voidSendCommand(1);
}






