/*
 * SHM.c
 *
 * Created: 9/11/2021 5:55:09 PM
 * Author : Ali
 */ 
/*******************LIBERARIES INCLUDING***************************************/
#define    F_CPU          16000000UL                           //Define Crystal Speed Is 16 MHZ
#include <util/delay.h>                                        //Including Delay Liberary
#include "STD_TYPES.h"                                         //Including Standerd Types Liberary
#include "BIT_MATH.h"                                          //Including Bit Math Liberary
#include "DIO_interface.h"                                     //Including Data Direction Driver
#include "UART_interface.h"                                    //Including UART Driver
#include "SPI_interface.h"                                     //Including SPI Driver
#include "LCD_Int.h"                                           //Including LCD Driver
/*******************SETTING DATA DIRECTION REGISTERS***************************/
int main(void)
{
	DIO_voidSetPinDirection(PORTD , PIN0 , INPUT );            //Set PIN0 On PORTD as Input  Pin - UART RX  --> Input
	DIO_voidSetPinDirection(PORTD , PIN1 , OUTPUT);            //Set PIN1 On PORTD as Output Pin - UART TX  --> Output
	DIO_voidSetPinDirection(PORTC , PIN2 , OUTPUT);            //Set PIN2 On PORTC as Output Pin - LED 0    --> Output
	DIO_voidSetPinDirection(PORTC , PIN7 , OUTPUT);            //Set PIN7 On PORTC as Output Pin - LED 1    --> Output
	DIO_voidSetPinDirection(PORTD , PIN3 , OUTPUT);            //Set PIN3 On PORTD as Output Pin - LED 2    --> Output
	DIO_voidSetPinDirection(PORTA , PIN3 , OUTPUT);            //Set PIN3 On PORTA as Output Pin - Buzzer   --> Output
	DIO_voidSetPinDirection(PORTA , PIN4 , OUTPUT);            //Set PIN4 On PORTA as Output Pin - LCD_Pin  --> Output
	DIO_voidSetPinDirection(PORTA , PIN5 , OUTPUT);            //Set PIN5 On PORTA as Output Pin - LCD_Pin  --> Output
	DIO_voidSetPinDirection(PORTA , PIN6 , OUTPUT);            //Set PIN6 On PORTA as Output Pin - LCD_Pin  --> Output
	DIO_voidSetPinDirection(PORTA , PIN7 , OUTPUT);            //Set PIN7 On PORTA as Output Pin - LCD_Pin  --> Output
	DIO_voidSetPinDirection(PORTB , PIN1 , OUTPUT);            //Set PIN1 On PORTB as Output Pin - LCD_RS   --> Output
	DIO_voidSetPinDirection(PORTB , PIN2 , OUTPUT);            //Set PIN2 On PORTB as Output Pin - LCD_RW   --> Output
	DIO_voidSetPinDirection(PORTB , PIN3 , OUTPUT);	           //Set PIN3 On PORTB as Output Pin - LCD_EN   --> Output
/*******************INITIALIZATION FUNCTIONS***********************************/	
	LCD_voidInit4Bit();                                        //Initalize LCD In 4Bits Mode
	UART_VoidInit();                                           //Initalize UART
	SPI_MasterInit();                                          //Initalize SPI In Master Mode
/*******************LCD INTERFACING********************************************/	
	LCD_voidWriteString4Bit("WELCOME BACK" , 0 , 2);           //LCD Write "WELCOME BACK" Started From First Row And Second Column When Firstly Opened
/*******************VARIABLE DECLERATION***************************************/			
	u8 Status = 0;                                             //Declaration Of a U8 Variable With Initial Value = 0
/*******************CODE*******************************************************/
    while (1) 
    {
		_delay_ms(1000);                                       //Wait For 1 Second Before Sending Data To Prevent Data Collision
		Status = UART_VoidRecieve();                           //Store Recived Data From Bluetooth In Variable 'Status'
		SPI_u8MasterTransmitRecive(Status);                    //Transimmit Status From Master MC To Slave MC Through SPI
		/************Turn Light ON**************************/
		if (Status == '1')                                     //If Recived DATA Is = 1
		{                                                      
		 DIO_voidSetPinValue(PORTA , PIN3 , HIGH);             //Write Logic 1 On PORTA - PIN3 --> Turn Buzzer on
		 _delay_ms(500);                                       //Wait For 500 MiliSeconds
		 DIO_voidSetPinValue(PORTA , PIN3 , LOW);              //Write Logic 0 On PORTA - PIN3 --> Turn Buzzer off     
		 DIO_voidSetPinValue(PORTC , PIN2 , HIGH);             //Write Logic 1 On PORTC - PIN2 --> Turn LED0 on
		 LCD_voidSendCMD4Bit(0x01);                            //Send Command To LCD --> Clear Display
		 _delay_ms(10);                                        //Wait For 10 MiliSeconds
		 LCD_voidWriteString4Bit("Controlling" , 0 , 2);       //LCD Write "Controlling" Started From First Row And Second Column When Send 1
		 LCD_voidWriteString4Bit("     Light" , 1 , 0);	       //LCD Write "Light" Started From Second Row And Fifth Column When Send 1
		}
		/************Turn Light OFF*************************/
		else if (Status == '2')                                //If Recived DATA Is = 2
		{
		 DIO_voidSetPinValue(PORTA , PIN3 , HIGH);             //Write Logic 1 On PORTA - PIN3 --> Turn Buzzer on
		 _delay_ms(500);                                       //Wait For 500 MiliSeconds
		 DIO_voidSetPinValue(PORTA , PIN3 , LOW);              //Write Logic 0 On PORTA - PIN3 --> Turn Buzzer off
		 DIO_voidSetPinValue(PORTC , PIN2 , LOW);              //Write Logic 0 On PORTC - PIN2 --> Turn LED0 Off
		 LCD_voidSendCMD4Bit(0x01);                            //Send Command To LCD --> Clear Display
		 _delay_ms(10);                                        //Wait For 10 MiliSeconds
		 LCD_voidWriteString4Bit(" UnControlling" , 0 , 0);    //LCD Write "UnControlling" Started From First Row And Second Column When Send 2
		 LCD_voidWriteString4Bit("     Light" , 1 , 0);        //LCD Write "Controlling" Started From Second Row And Fifth Column When Send 2
		}
		/************Turn TV ON****************************/
        else if (Status == '3')                                //If Recived DATA Is = 3
		{
		 DIO_voidSetPinValue(PORTA , PIN3 , HIGH);             //Write Logic 1 On PORTA - PIN3 --> Turn Buzzer on
		 _delay_ms(500);                                       //Wait For 500 MiliSeconds
		 DIO_voidSetPinValue(PORTA , PIN3 , LOW);              //Write Logic 0 On PORTA - PIN3 --> Turn Buzzer off
		 DIO_voidSetPinValue(PORTC , PIN7 , HIGH);             //Write Logic 1 On PORTC - PIN7 --> Turn LED1 on
		 LCD_voidSendCMD4Bit(0x01);                            //Send Command To LCD --> Clear Display
		 _delay_ms(10);                                        //Wait For 10 MiliSeconds
		 LCD_voidWriteString4Bit("Controlling" , 0 , 2);       //LCD Write "Controlling" Started From First Row And Second Column When Send 3
		 LCD_voidWriteString4Bit("       TV" , 1 , 0);         //LCD Write "TV" Started From Second Row And Fifth Column When Send 3
		}
		/************Turn TV OFF***************************/
		else if (Status == '4')                                //If Recived DATA Is = 4           
		{
		 DIO_voidSetPinValue(PORTA , PIN3 , HIGH);             //Write Logic 1 On PORTA - PIN3 --> Turn Buzzer on       
		 _delay_ms(500);                                       //Wait For 500 MiliSeconds
		 DIO_voidSetPinValue(PORTA , PIN3 , LOW);              //Write Logic 0 On PORTA - PIN3 --> Turn Buzzer off
		 DIO_voidSetPinValue(PORTC , PIN7 , LOW);              //Write Logic 0 On PORTC - PIN7 --> Turn LED1 off
		 LCD_voidSendCMD4Bit(0x01);                            //Send Command To LCD --> Clear Display
		 _delay_ms(10);                                        //Wait For 10 MiliSeconds
		 LCD_voidWriteString4Bit(" UnControlling" , 0 , 0);    //LCD Write "Controlling" Started From First Row And Second Column When Send 4
		 LCD_voidWriteString4Bit("       TV" , 1 , 0);         //LCD Write "TV" Started From Second Row And Fifth Column When Send 4
		}
		/************Turn AC ON****************************/
		else if (Status == '5')                                //If Recived DATA Is = 5
        {
         DIO_voidSetPinValue(PORTA , PIN3 , HIGH);             //Write Logic 1 On PORTA - PIN3 --> Turn Buzzer on
         _delay_ms(500);                                       //Wait For 500 MiliSeconds
         DIO_voidSetPinValue(PORTA , PIN3 , LOW);              //Write Logic 0 On PORTA - PIN3 --> Turn Buzzer off
         DIO_voidSetPinValue(PORTD , PIN3 , HIGH);             //Write Logic 1 On PORTD - PIN3 --> Turn LED2 on
         LCD_voidSendCMD4Bit(0x01);                            //Send Command To LCD --> Clear Display
         _delay_ms(10);                                        //Wait For 10 MiliSeconds
         LCD_voidWriteString4Bit("Controlling" , 0 , 2);       //LCD Write "Controlling" Started From First Row And Second Column When Send 5
         LCD_voidWriteString4Bit("       AC" , 1 , 0);         //LCD Write "AC" Started From Second Row And Fifth Column When Send 5
        }
		/************Turn AC OFF***************************/
		else if (Status == '6')                                //If Recived DATA Is = 6
		{
		 DIO_voidSetPinValue(PORTA , PIN3 , HIGH);             //Write Logic 1 On PORTA - PIN3 --> Turn Buzzer on
		 _delay_ms(500);                                       //Wait For 500 MiliSeconds
		 DIO_voidSetPinValue(PORTA , PIN3 , LOW);              //Write Logic 0 On PORTA - PIN3 --> Turn Buzzer off
		 DIO_voidSetPinValue(PORTD , PIN3 , LOW);              //Write Logic 0 On PORTD - PIN3 --> Turn LED2 off
		 LCD_voidSendCMD4Bit(0x01);                            //Send Command To LCD --> Clear Display
		 _delay_ms(10);                                        //Wait For 10 MiliSeconds
		 LCD_voidWriteString4Bit(" UnControlling" , 0 , 0);    //LCD Write "UnControlling" Started From First Row And Second Column When Send 6
		 LCD_voidWriteString4Bit("       AC" , 1 , 0);         //LCD Write "AC" Started From Second Row And Fifth Column When Send 6
		}
		/************Turn ALL OFF*************************/
		else if (Status == '7')                                //If Recived DATA Is = 7
		{
		 DIO_voidSetPinValue(PORTA , PIN3 , HIGH);             //Write Logic 1 On PORTA - PIN3 --> Turn Buzzer on
		 _delay_ms(500);                                       //Wait For 500 MiliSeconds
		 DIO_voidSetPinValue(PORTA , PIN3 , LOW);              //Write Logic 0 On PORTA - PIN3 --> Turn Buzzer off
		 DIO_voidSetPinValue(PORTC , PIN2 , LOW);              //Write Logic 0 On PORTC - PIN2 --> Turn LED0 Off
		 DIO_voidSetPinValue(PORTC , PIN7 , LOW);              //Write Logic 0 On PORTC - PIN2 --> Turn LED1 Off
		 DIO_voidSetPinValue(PORTD , PIN3 , LOW);              //Write Logic 0 On PORTD - PIN3 --> Turn LED2 off
		 LCD_voidSendCMD4Bit(0x01);                            //Send Command To LCD --> Clear Display
		 _delay_ms(10);                                        //Wait For 10 MiliSeconds
		 LCD_voidWriteString4Bit("OUT OF Control" , 0 , 0);    //LCD Write "Out OF Control" Started From First Row And Second Column When Send 7
		}
    }
	return 0;
}

