#ifndef MAIN_H_
#define MAIN_H_

#define PART_TM4C123GH6PM
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "inc\hw_gpio.h"
#include "inc/hw_uart.h"
#include "inc/hw_ints.h"
#include "inc\hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "tm4c123gh6pm.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "lcd.h"
#include "uart.h"

// Function prototypes
void Read_Time(char buf[]);
unsigned int Read_From_Keyboard(void);

#endif /* MAIN_H_ */
