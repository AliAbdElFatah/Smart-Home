#ifndef      LCD_INTERFACE_H
#define      LCD_INTERFACE_H
/**************************************************************************************************/
#define            LCD_DATA_PORT                    PORTA
#define            LCD_CONTROL_PORT                 PORTB
#define            LCD_RS                           PIN1
#define            LCD_RW                           PIN2
#define            LCD_EN                           PIN3
/**************************************************************************************************/
void     LCD_voidInit                          (void);
void     LCD_voidWriteCharacter                (u8 Data);
void     LCD_voidSendCMD                       (u8 CMD);
/**************************************************************************************************/
void     LCD_voidInit4Bit                      (void);
void     LCD_voidWriteCharacter4Bit            (u8 Data);
void     LCD_voidSendCMD4Bit                   (u8 CMD);
/**************************************************************************************************/
void     LCD_voidWriteString4Bit               (u8* Str , u8 Row , u8 Col);
void     LCD_GoToPos                           (u8 Row , u8 Col);
void     LCD_voidWriteNumber                   (u64  Number );
/**************************************************************************************************/
void     LCD_StoreCustomChr                    (u8* pattern , u8 CGRAM_index);
void     LCD_DisplayCustomChr                  (u8 CGRAM_index , u8 Row ,u8 Col);
#endif    