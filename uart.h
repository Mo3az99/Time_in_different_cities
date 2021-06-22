#ifndef UART_H_
#define UART_H_

void printChar(char c);   					//print character
char readChar(void);								//read character
void printString(char * string);		//print string
void UART0_Trans(char * data);			//send to uart0
void UART0_Init(void);							//init uart0
char UART0_Read(void);							//recieve from uart0
void UART0_Write_Text(char* txt);		//print text diffrent implemntation
#endif /* UART_H_ */
