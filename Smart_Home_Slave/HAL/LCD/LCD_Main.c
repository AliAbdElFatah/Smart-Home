#include "Std_Types.h"
#include "Bit_Math.h"
#include "DIO_interface.h"
#include "LCD_Int.h"
#include <util/delay.h>
/**************************************************************************************************/
void     LCD_voidInit4Bit        (void)
{
		_delay_ms(100);
	/*send commands to LCD for initializing as 4-bit mode*/
	LCD_voidSendCMD4Bit(0x33);
	LCD_voidSendCMD4Bit(0x32);
	LCD_voidSendCMD4Bit(0x28);
	LCD_voidSendCMD4Bit(0x0C);
	LCD_voidSendCMD4Bit(0x01);
	LCD_voidSendCMD4Bit(0x06);
	LCD_voidSendCMD4Bit(0x02);
	_delay_ms(1000);
}
/**************************************************************************************************/
void     LCD_voidInit            (void)
{
	/*		power ON wait 30 msec	*/
	_delay_ms(35);
	/*		Function Set	DL = 8 bit mode	 F = 5*7  N= 2 lines			*/
	LCD_voidSendCMD(0x38);
		_delay_ms(1);
	/*		Display ON/OFF Controll,	D = 1 Display ON	 Cursor OFF		*/
	LCD_voidSendCMD(0x0C);
		_delay_ms(1);
	/*		Clear Display													*/
	LCD_voidSendCMD(0x01);
		_delay_ms(2);
	/*		Entry Mode	I/D = 1 increase from the left to Right S = 0 No shifting		*/
	LCD_voidSendCMD(0x06);
		_delay_ms(1);
}
/**************************************************************************************************/
void     LCD_voidWriteCharacter  (u8 Data)
{
	/*		RS = 1		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RS,HIGH);
	/*		RW = 0		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RW,LOW);
	/*		Send CMD	*/
	DIO_voidSetPortValue(LCD_DATA_PORT, Data);
	/*		En = Latch	*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_EN,HIGH);
	_delay_ms(5);
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_EN,LOW);
	_delay_ms(5);
}
/**************************************************************************************************/
void     LCD_voidSendCMD        (u8 CMD)
{
	/*		RS = 0		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RS,LOW);
	/*		RW = 0		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RW,LOW);
	/*		Send CMD	*/
	DIO_voidSetPortValue(LCD_DATA_PORT,CMD);
	/*		En = Latch	*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_EN,HIGH);
	_delay_ms(5);
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_EN,LOW);
	_delay_ms(5);
}
/**************************************************************************************************/
void     LCD_voidWriteCharacter4Bit    (u8 Data)
{
	u8 Temp = 0;
	/*		RS = 1		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RS,HIGH);
	/*		RW = 0		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RW,LOW);
	/*		Send CMD	*/	
	
	Temp = ((Data & 0xf0) | ((DIO_u8GetPortValue(LCD_DATA_PORT)) & 0x0f));
	DIO_voidSetPortValue(LCD_DATA_PORT , Temp);
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT , LCD_EN , HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT , LCD_EN , LOW);
	
	Temp = (Data << 4) | ((DIO_u8GetPortValue(LCD_DATA_PORT))& 0x0f);
	DIO_voidSetPortValue(LCD_DATA_PORT , Temp);
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT , LCD_EN , HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT , LCD_EN , LOW);
	
	_delay_ms(5);
}
/**************************************************************************************************/
void     LCD_voidSendCMD4Bit       (u8 CMD)
{
	u8 Temp = 0;
	/*		RS = 0		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RS,LOW);
	/*		RW = 0		*/
	DIO_voidSetPinValue(LCD_CONTROL_PORT,LCD_RW,LOW);
	/*		Send CMD	*/	
	
	Temp = ((CMD & 0xf0) | ((DIO_u8GetPortValue(LCD_DATA_PORT)) & 0x0f));
	DIO_voidSetPortValue(LCD_DATA_PORT , Temp);
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT , LCD_EN , HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT , LCD_EN , LOW);
	
	Temp = (CMD << 4) | ((DIO_u8GetPortValue(LCD_DATA_PORT))& 0x0f);
	DIO_voidSetPortValue(LCD_DATA_PORT , Temp);
	
	DIO_voidSetPinValue(LCD_CONTROL_PORT , LCD_EN , HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_CONTROL_PORT , LCD_EN , LOW);
	
	_delay_ms(5);	
}
/**************************************************************************************************/
void     LCD_GoToPos       (u8 Row , u8 Col)
{
	u8 Address;
	if (Row < 2 && Col < 16)
	{
		Address = (Row * 0x40) + Col;
		Address = SET_BIT(Address , 7);
		LCD_voidSendCMD4Bit(Address);
	}
}
/**************************************************************************************************/
void     LCD_voidWriteString4Bit   (u8* Str , u8 Row , u8 Col)
{
	LCD_GoToPos(Row , Col);
	u8 index = 0;
	u8 line0 = 0;
	
	while (Str[index] != '\0' && ((Row * 16)+(index + Col)) < 32)
	{
		if (((Row * 16)+(index + Col)) < 16)
		{
		     LCD_voidWriteCharacter4Bit(Str[index]);
		     index++;
		}
		else if (((Row * 16)+(index + Col)) == 16 && line0 == 0)
		{
			 LCD_GoToPos(1 , 0);
			 line0++;
		}	
		else if (((Row * 16)+(index + Col)) < 32 && line0 == 1)
		{
			 LCD_voidWriteCharacter4Bit(Str[index]);
		     index++;
		}	
	}
}
/**************************************************************************************************/
void     LCD_voidWriteNumber           (u64  Number )
{
	u64 LOC_u64Reversed = 1 ;

	if( Number == 0 )
	{
		LCD_voidWriteCharacter4Bit('0');
	}
	while( Number != 0 )
	{
		LOC_u64Reversed = ( LOC_u64Reversed * 10 ) + ( Number % 10 ) ;
		Number  /= 10 ;
	}
	while( LOC_u64Reversed != 1 )
	{
		LCD_voidWriteCharacter4Bit( ( LOC_u64Reversed % 10 ) + 48 );
		LOC_u64Reversed  /= 10 ;
	}
}
/**************************************************************************************************/
void     LCD_StoreCustomChr         (u8* pattern , u8 CGRAM_index)
{
	u8 Address;
	u8 index;
	if (CGRAM_index < 8)
	{
		Address = CGRAM_index * 8;
		Address = SET_BIT(Address , 6);
		LCD_voidSendCMD4Bit(Address);
		for (index = 0 ; index < 8 ; index++)
		{
			LCD_voidWriteCharacter4Bit(pattern[index]);
		}
	}
	LCD_voidSendCMD4Bit(0x80);
}
/**************************************************************************************************/
void     LCD_DisplayCustomChr     (u8 CGRAM_index , u8 Row ,u8 Col)
{
	LCD_GoToPos(Row , Col);
	LCD_voidWriteCharacter4Bit(CGRAM_index);
}
