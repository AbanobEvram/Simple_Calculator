#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"PORT_interface.h"
#include"DIO_interface.h"
#include"KPD_interface.h"
#include"CLCD_interface.h"
#include"util/delay.h"
void main(void)
{
	f32 Local_f32FirstNum=0                        //for saving the first number
	,Local_f32SecondNum=0                          // for saving the second number
	,Local_f32Result=0;                            //for saving the Local_f32Result

	u8 Local_variable,                           //temp variable to save the temp pressed key
	Local_u8Itrator,                             //itrator for save digits of the number
	Local_u8Operation,                           //for save the operation
	Local_u8TempPressedKey;                      //for save the num return from the KPD




	/*Intilize the PORTS and CLCD*/
	PORT_voidInit();
	CLCD_voidInit();

	/*For writing my name*/
	CLCD_voidSendString("Simple ");
	_delay_ms(500);
	CLCD_voidSendString("Calc");
	_delay_ms(500);
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("BY: ");
	_delay_ms(500);
	CLCD_voidSendString("ABANOB ");
	_delay_ms(500);
	CLCD_voidSendString("EVRAM");
	_delay_ms(1300);
	CLCD_voidCleatTheScreen();


	while (1)
	{
		/*Save the value of the switch which pressed*/
		do
		{
			Local_variable=KPD_u8GetPressedKeyPad();
		}
		while(Local_variable==0xff);


		/*Save the digits in the second num*/
		if(Local_variable>=0&&Local_variable<=9)
		{
			Local_u8TempPressedKey=Local_variable;
			CLCD_voidWriteNumber(Local_variable);
			Local_u8Itrator++;
			switch(Local_u8Itrator)
			{
			case 1 : Local_f32SecondNum= Local_u8TempPressedKey ; break;
			case 2 : Local_f32SecondNum= (Local_f32SecondNum*10)+Local_u8TempPressedKey ; break;
			case 3 : Local_f32SecondNum= (Local_f32SecondNum*10)+Local_u8TempPressedKey ; break;
			case 4 :Local_f32SecondNum= (Local_f32SecondNum*10)+Local_u8TempPressedKey ; break;
			}

		}


		switch (Local_variable)
		{
		case '+' :
			Local_u8Itrator=0;
			CLCD_voidSendData('+');
			Local_f32FirstNum=Local_f32SecondNum;
			Local_u8Operation = Local_variable;
			break;

		case '-' :
			Local_u8Itrator=0;
			CLCD_voidSendData('-');
			Local_f32FirstNum=Local_f32SecondNum;
			Local_u8Operation = Local_variable;
			break;

		case '*' :
			Local_u8Itrator=0;
			CLCD_voidSendData('*');
			Local_f32FirstNum=Local_f32SecondNum;
			Local_u8Operation = Local_variable;
			break;

		case '/' :
			Local_u8Itrator=0;
			CLCD_voidSendData('/');
			Local_f32FirstNum=Local_f32SecondNum;
			Local_u8Operation = Local_variable;
			break;
/************************************************************************************/
/************************************************************************************/
		case '=' :
			if(Local_u8Operation=='+')
			{
				Local_f32Result=Local_f32FirstNum+Local_f32SecondNum;
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendString("Result: ");
				CLCD_voidWriteNumber(Local_f32Result);
			}

/************************************************************************************/
			else if(Local_u8Operation=='-')
			{
				if(Local_f32FirstNum>=Local_f32SecondNum)
				{
					Local_f32Result=Local_f32FirstNum-Local_f32SecondNum;
					CLCD_voidGoToXY(1,0);
					CLCD_voidSendString("Result: ");
					CLCD_voidWriteNumber(Local_f32Result);
				}
				else if(Local_f32FirstNum<Local_f32SecondNum)
				{
					Local_f32Result=Local_f32SecondNum-Local_f32FirstNum;
					CLCD_voidGoToXY(1,0);
					CLCD_voidSendString("Result: ");
					CLCD_voidSendData('-');
					CLCD_voidWriteNumber(Local_f32Result);
				}
			}

/************************************************************************************/
			else if (Local_u8Operation=='*')
			{
				Local_f32Result=Local_f32FirstNum*Local_f32SecondNum;
				CLCD_voidGoToXY(1,0);
				CLCD_voidSendString("Result: ");
				CLCD_voidWriteNumber(Local_f32Result);
			}

/************************************************************************************/
			else if (Local_u8Operation=='/')
			{
				if(Local_f32SecondNum==0)
				{
					CLCD_voidGoToXY(1,0);
					CLCD_voidSendString("Result: Infinite");

				}
				else
				{
					Local_f32Result=Local_f32FirstNum/Local_f32SecondNum;
					CLCD_voidGoToXY(1,0);
					CLCD_voidSendString("Result: ");
					CLCD_voidWriteFloatOnLCD(Local_f32Result);
				}
			}

/************************************************************************************/
			Local_f32FirstNum=0;
			Local_f32SecondNum=0;
			Local_u8Operation=0;
			break;
		case 'C' :
			Local_u8Itrator=0;

			CLCD_voidCleatTheScreen();
			break;
		}
	}
}
