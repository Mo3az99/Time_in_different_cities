
#ifndef LCD_H_
#define LCD_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "string.h"
#include "main.h"

#include <ctype.h>
#include <stdlib.h>

#define LCDPORT         GPIO_PORTB_BASE
#define LCDPORTENABLE   SYSCTL_PERIPH_GPIOB
#define RS              GPIO_PIN_0
#define E               GPIO_PIN_1
#define D4              GPIO_PIN_4
#define D5              GPIO_PIN_5
#define D6              GPIO_PIN_6
#define D7              GPIO_PIN_7


void LCD_init(void);                                //LCD initialization
void LCD_Command(unsigned char c);                  //Send command
void LCD_Show(unsigned char d);                     //Show a char

void LCD_Clear(void);                               //Clear the screen
void LCD_Print(char *s, char *d);                   //Print 2 lines
void LCD_PrintLn(char i, char *s);                  //Print specific line
void LCD_Cursor(char x, char y);                    //Set cursor
void LCD_PrintColumn(char i , char *s);							//Print in Specific Coloumn
void LCD_intgerToString(int data);									//conert integer to string
void LCD_print_Continous(char *s);									//continuo printing in the same line you are in
void ByteToStr (char a , char *s);									//convert to string
void trim( char *input);														//trim spaces

 void reverse(char s[]);														//reverse string
 void itoa(int n, char s[]);											 //integer to string
#endif /* LCD_H_ */
