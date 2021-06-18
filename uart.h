#ifndef UART_H_
#define UART_H_

void uart_init(void);
void printChar(char c);
char readChar(void);
void printString(char * string);


char UART0_Receiver(void);
char UART0_Receive(void);
void UART0_Trans(char * data);

void UART0_Init(void);
char UART0_Read(void);
void UART0_Write_Text(char* txt);
#endif /* UART_H_ */
