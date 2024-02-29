/*********************************************************************/
/*********************************************************************/
/*++++++++++++++++++  AUTHOR : ABANOB EVRAM   +++++++++++++++++++++++*/  
/*++++++++++++++++++  LAYER:HAL               +++++++++++++++++++++++*/  
/*++++++++++++++++++  SWC:KPD                 +++++++++++++++++++++++*/  
/*++++++++++++++++++  VERSION:1.00            +++++++++++++++++++++++*/  
/*********************************************************************/ 
/*********************************************************************/
#include"STD_TYPES.h"
#include"DIO_interface.h"
#include"KPD_config.h"
#include"KPD_private.h"
#include"KPD_interface.h"

u8 KPD_u8GetPressedKeyPad(void)
{
	u8 Local_u8PressedKey=KPD_NO_PRESSED_KEY;//local variable to store value of pressed key
	u8 Local_u8ColumnnIdx; //a local variable for column iterator
	u8 Local_u8RowIdx;//a local variable for rows iterator
	u8 Local_u8PinState;//a local variable for reading current row
	static u8 Local_u8KPDArr[ROW_NUM][COLUMN_NUM] = KPD_ARR_VAL;//an array of buttons values
	static u8 Local_u8KPDColumnArr[COLUMN_NUM]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
	static u8 Local_u8KPDROWArr[ROW_NUM]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};


	/*looping over columns*/
	for(Local_u8ColumnnIdx=0;Local_u8ColumnnIdx<COLUMN_NUM;Local_u8ColumnnIdx++)
	{
		/*Activate current column*/
		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnnIdx],DIO_u8PIN_LOW);
		/*looping over rows to search for pressed key*/
		for(Local_u8RowIdx=0;Local_u8RowIdx<ROW_NUM;Local_u8RowIdx++)
		{
			/*READ THE CURRENT ROW*/
			DIO_u8GetPinValue(KPD_PORT,Local_u8KPDROWArr[Local_u8RowIdx],&Local_u8PinState);
			/*Check is switch is pressed*/
			if(Local_u8PinState==DIO_u8PIN_LOW)
			{
				Local_u8PressedKey=Local_u8KPDArr[Local_u8RowIdx][Local_u8ColumnnIdx];
				/*polling(busy waiting) until the key is relased*/
				while(Local_u8PinState==DIO_u8PIN_LOW)
				{
					DIO_u8GetPinValue(KPD_PORT,Local_u8KPDROWArr[Local_u8RowIdx],&Local_u8PinState);
				}

				return Local_u8PressedKey;
			}
		}
		/*deactivate the current column*/
		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnnIdx],DIO_u8PIN_HIGH);

	}






	return Local_u8PressedKey;
}
