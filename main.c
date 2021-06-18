

#include "LCD/lcd.h"
#include "main.h"

int main(void) {

        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

        LCD_init();

        while (1) {
            LCD_Print("Hello World!", "...................."); //Print 2 lines

            SysCtlDelay(80000000/3); //Delay
            LCD_Clear();

      	}

}