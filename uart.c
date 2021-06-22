#include "uart.h"
#include "main.h"

void printChar(char c){

  UARTCharPut(UART0_BASE,c);	
} 

char readChar(void){
  char c;
  while((UART_FR_RXFF  & (1<<4) )!= 0 ){}; //checking untill its not empty, something to read
  c = UARTCharGet(UART0_BASE);
	//printf(c);
  return c;
}




void printString(char* string)
{
    while(*string)
    {
        UARTCharPut(UART0_BASE, *(string++));
    }
}




void UART0_Init(void){

		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    // Configure GPIO Pins for UART mode.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    //Use the internal 16MHz oscillator as the UART clock source
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTDisable(UART0_BASE);
    UARTConfigSetExpClk(UART0_BASE, 16000000, 9600,(UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |UART_CONFIG_WLEN_8));//SysCtlClockGet() -> 16000000 //parity none, one stop bit, 8 bits   
    //Enable FIFO
    UARTFIFOEnable(UART0_BASE);
    //Enable the UART
    UARTEnable(UART0_BASE);
}

char UART0_Read(void)
{
//	while((UART0_FR_R & 0x10) != 0);
  return (char)UARTCharGet(UART0_BASE);
}

void UART0_Write_Text(char* txt)
{
	while(*txt){
    printChar(*(txt++)); //increment the address where pointer is pointing at, while loop stops when it reaches character 0

  }
}