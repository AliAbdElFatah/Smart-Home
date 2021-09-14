/*
 * SHS.c
 *
 * Created: 9/11/2021 9:06:36 PM
 * Author : Ali
 */ 
/*******************LIBERARIES INCLUDING***************************************/
#define  F_CPU      16000000UL                                      //Define Crystal Speed Is 16 MHZ
#include <util/delay.h>                                             //Including Delay Liberary                            
#include "STD_TYPES.h"                                              //Including Standerd Types Liberary
#include "BIT_MATH.h"                                               //Including Bit Math Liberary
#include "DIO_interface.h"                                          //Including Data Direction Driver
#include "SPI_interface.h"                                          //Including SPI Driver
#include "LCD_Int.h"                                                //Including LCD Driver
/*******************SETTING DATA DIRECTION REGISTERS***************************/
int main(void)
{
	DIO_voidSetPinDirection(PORTC , PIN2 , OUTPUT);                 //Set PIN2 On PORTC as Output Pin - LED 0    --> Output
	DIO_voidSetPinDirection(PORTC , PIN7 , OUTPUT);                 //Set PIN7 On PORTC as Output Pin - LED 1    --> Output
	DIO_voidSetPinDirection(PORTD , PIN3 , OUTPUT);                 //Set PIN3 On PORTD as Output Pin - LED 2    --> Output
	DIO_voidSetPinDirection(PORTA , PIN2 , OUTPUT);                 //Set PIN2 On PORTA as Output Pin - Relay    --> Output
	DIO_voidSetPinDirection(PORTB , PIN1 , OUTPUT);                 //Set PIN1 On PORTB as Output Pin - LCD_RS   --> Output
	DIO_voidSetPinDirection(PORTB , PIN2 , OUTPUT);                 //Set PIN2 On PORTB as Output Pin - LCD_RW   --> Output
	DIO_voidSetPinDirection(PORTB , PIN3 , OUTPUT);                 //Set PIN3 On PORTB as Output Pin - LCD_EN   --> Output
	DIO_voidSetPinDirection(PORTA , PIN4 , OUTPUT);                 //Set PIN4 On PORTA as Output Pin - LCD_Pin  --> Output
	DIO_voidSetPinDirection(PORTA , PIN5 , OUTPUT);                 //Set PIN5 On PORTA as Output Pin - LCD_Pin  --> Output
	DIO_voidSetPinDirection(PORTA , PIN6 , OUTPUT);                 //Set PIN6 On PORTA as Output Pin - LCD_Pin  --> Output
	DIO_voidSetPinDirection(PORTA , PIN7 , OUTPUT);                 //Set PIN7 On PORTA as Output Pin - LCD_Pin  --> Output
/*******************INITIALIZATION FUNCTIONS***********************************/	
	SPI_SlaveInit();                                                //Initalize SPI In Slave Mode
	LCD_voidInit4Bit();                                             //Initalize LCD In 4Bits Mode
/*******************VARIABLE DECLERATION***************************************/	
	u8 Order = 0;                                                   //Declaration Of a U8 Variable With Initial Value = 0
/*******************CODE*******************************************************/
    while (1) 
    {
		Order = SPI_u8SlaveTransmitRecive('1');                     //Store Recived Data From Master MC In Variable 'Order'
		/************Turn Light ON**************************/
		if (Order == '1')                                           //If Recived DATA Is = 1
		{
			LCD_voidWriteString4Bit("Light: ON" , 0 , 0);           //LCD Write "Light : ON" Started From First Row And First Column When Send 1
			DIO_voidSetPinValue(PORTC , PIN2 , HIGH);               //Write Logic 1 On PORTC - PIN2 --> Turn LED0 on
		}
		/************Turn Light OFF*************************/
		else if (Order == '2')                                      //If Recived DATA Is = 2
		{
			LCD_voidSendCMD4Bit(0x01);                              //Send Command To LCD --> Clear Display      
			_delay_ms(10);                                          //Wait For 10 MiliSeconds
			LCD_voidWriteString4Bit("Light: OFF" , 0 , 0);          //LCD Write "Light : OFF" Started From First Row And First Column When Send 2
			DIO_voidSetPinValue(PORTC , PIN2 , LOW);                //Write Logic 0 On PORTC - PIN2 --> Turn LED0 Off
		}
		/************Turn TV ON****************************/
		else if (Order == '3')                                      //If Recived DATA Is = 3
		{
			LCD_voidSendCMD4Bit(0x01);                              //Send Command To LCD --> Clear Display 
			_delay_ms(10);                                          //Wait For 10 MiliSeconds
			LCD_voidWriteString4Bit("TV: ON" , 0 , 0);              //LCD Write "TV : ON" Started From First Row And First Column When Send 3
			DIO_voidSetPinValue(PORTC , PIN7 , HIGH);               //Write Logic 1 On PORTC - PIN7 --> Turn LED1 on       
		}
		/************Turn TV OFF***************************/
		else if (Order == '4')                                      //If Recived DATA Is = 4
		{
			LCD_voidSendCMD4Bit(0x01);                              //Send Command To LCD --> Clear Display
			_delay_ms(10);                                          //Wait For 10 MiliSeconds
			LCD_voidWriteString4Bit("TV: OFF" , 0 , 0);             //LCD Write "TV : OFF" Started From First Row And First Column When Send 4
			DIO_voidSetPinValue(PORTC , PIN7 , LOW);                //Write Logic 0 On PORTC - PIN7 --> Turn LED1 off
		}
		/************Turn AC ON****************************/
		else if (Order == '5')                                      //If Recived DATA Is = 5
		{
			LCD_voidSendCMD4Bit(0x01);                              //Send Command To LCD --> Clear Display
			_delay_ms(10);                                          //Wait For 10 MiliSeconds
			LCD_voidWriteString4Bit("AC: ON" , 0 , 0);              //LCD Write "AC : ON" Started From First Row And First Column When Send 5
			DIO_voidSetPinValue(PORTA , PIN2 , HIGH);               //Write Logic 1 On PORTA - PIN2 --> Turn Relay on
			DIO_voidSetPinValue(PORTD , PIN3 , HIGH);               //Write Logic 1 On PORTD - PIN3 --> Turn LED2 on
		}
		/************Turn AC OFF***************************/
		else if (Order == '6')                                      //If Recived DATA Is = 6
		{
			LCD_voidSendCMD4Bit(0x01);                              //Send Command To LCD --> Clear Display
			_delay_ms(10);                                          //Wait For 10 MiliSeconds
			LCD_voidWriteString4Bit("AC: OFF" , 0 , 0);             //LCD Write "AC : OFF" Started From First Row And First Column When Send 6
			DIO_voidSetPinValue(PORTA , PIN2 , LOW);                //Write Logic 0 On PORTA - PIN2 --> Turn Relay off
			DIO_voidSetPinValue(PORTD , PIN3 , LOW);                //Write Logic 0 On PORTD - PIN3 --> Turn LED2 off
		}
		/************Turn ALL OFF*************************/
		else if (Order == '7')                                      //If Recived DATA Is = 7
		{
			LCD_voidSendCMD4Bit(0x01);                              //Send Command To LCD --> Clear Display
			_delay_ms(10);                                          //Wait For 10 MiliSeconds
			LCD_voidWriteString4Bit("ALL  OFF" , 0 , 0);            //LCD Write "ALL OFF" Started From First Row And First Column When Send 7
			DIO_voidSetPinValue(PORTC , PIN2 , LOW);                //Write Logic 0 On PORTC - PIN2 --> Turn LED0 Off
			DIO_voidSetPinValue(PORTC , PIN7 , LOW);                //Write Logic 0 On PORTC - PIN2 --> Turn LED1 Off
			DIO_voidSetPinValue(PORTA , PIN2 , LOW);                //Write Logic 0 On PORTA - PIN2 --> Turn Relay off
			DIO_voidSetPinValue(PORTD , PIN3 , LOW);                //Write Logic 0 On PORTD - PIN3 --> Turn LED2 off
		}		
    }
	return 0;
}

