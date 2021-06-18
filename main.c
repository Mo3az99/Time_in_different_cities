
#include "main.h"

/* Dimension of the buffer */
#define mainMAX_MSG_LEN	( 80 )

/* The tasks to be created */
static void Task1(void *pvParameters);
static void Task2(void *pvParameters);
static void Task3(void *pvParameters);



// Cities and their time differences from London
static char cities[][10] = {"London", "Paris", "Madrid", "Rome", "Athens", "Ankara", "Istanbul", "Cairo", "Moscow", "Tehran"};
static char timediff[] = {0, 1, 1, 1, 2, 2, 2, 2, 3, 4};

static char cBuffer[ mainMAX_MSG_LEN ];
unsigned int selection;

/* Declare variables of type xQueueHandle. */
xQueueHandle xQueue1;
xQueueHandle xQueue2;


int main( void )
{	
	// Create the queues
	xQueue1 = xQueueCreate(1, 8);
  xQueue2 = xQueueCreate(1, 8);
	
	// Create the tasks
	xTaskCreate(Task1, "Time Controller", 100, NULL, 1, NULL);
	//xTaskCreate(Task2, "LCD Controller", 100, NULL, 1, NULL);
	xTaskCreate(Task3, "UART Controller", 100, NULL, 1, NULL);
	
	vTaskStartScheduler();
}

// Time Controller
static void Task1(void *pvParameters)
{
	typedef struct Message
	{
		unsigned char hours;
		unsigned char minutes;
		unsigned char seconds;
	} AMessage;

	AMessage Tim;
	
	xQueueReceive(xQueue2, &Tim, portMAX_DELAY);	// Receive initial time from Task 3

	for( ;; )
	{
		vTaskDelay(pdMS_TO_TICKS(1000)); // Wait for 1 second
		Tim.seconds ++; 								 // Increment seconds
		
		if(Tim.seconds == 60) 	// If 60
		{
			Tim.seconds = 0; 			// Reset to 0
			Tim.minutes ++; 			// Increment minutes
			if(Tim.minutes == 60) // If 60
			{
				Tim.minutes = 0; 		// Reset to 0
				Tim.hours ++; 			// Increment hours
				if(Tim.hours == 24) // If 24
					Tim.hours = 0; 		// Reset to 0
			}
		}
		
		xQueueSendToBack(xQueue1, &Tim, 0);	// Send to Task 2
	}
}

// This function is used to read the selection of the city from the user
// Read an integer number from the keyboard and return to the calling program
// It reads the integer as char and returns the corresponding number
unsigned int Read_From_Keyboard()
{
	unsigned int Total;
	unsigned char N;
	Total = 0;
	
	while(1)
	{
		N = UART0_Read();					// Read a char
		if (N == '\r') break;			// If enter
		N = N - '0';							// Pure number (corresponding number of the char)
		Total = 10 * Total + N;		// Total number
	}
	
	return Total;
}

// This function is used to read the time in London from the user
// Read time from the keyboard. The time is entered as hh:mm:ss
void Read_Time(char buf[])
{
	unsigned char c, k = 0;
	
	while(1)
	{
		c = UART0_Read();				// Read a char
		if (c == '\r') break;		// If Enter
		buf[k] = c;							// Save char
		k++;										// Increment pointer
	}
	buf[k] = '\0';						// NULL terminator
}

// LCD controller
static void Task2(void *pvParameters)
{
	
}

// UART controller
static void Task3(void *pvParameters)
{
	char k, Buffer[10];
	typedef struct Message
	{
		unsigned char hh;
		unsigned char mm;
		unsigned char ss;
	} AMessage;

	AMessage Tim;
	
	UART0_Init();
	
	UART0_Write_Text("Time in Different Countries\n\r");
	UART0_Write_Text("===========================\n\r");
	UART0_Write_Text("Enter the time in London (hh::mm::ss): ");
	
	Read_Time(Buffer);
	Tim.hh = 10 * (Buffer[0] - '0') + Buffer[1] - '0';	// Convert to number
	Tim.mm = 10 * (Buffer[3] - '0') + Buffer[4] - '0';	// Convert to number
	Tim.ss = 10 * (Buffer[6] - '0') + Buffer[7] - '0';	// Convert to number
	
	xQueueSendToBack( xQueue2, &Tim, 0 );								// Send to task 1
	
	for(;;)
	{
			//take semaphore here
		UART0_Write_Text("\n\r\n\rSelect a City:");
		for(k = 0; k < 10; k++)
		{
			sprintf(cBuffer, "\n\r%c. %s", k + '0', cities[k]);
			UART0_Write_Text(cBuffer);
		}
		UART0_Write_Text("\n\rSelection: ");
	 
		selection = Read_From_Keyboard();
		UART0_Write_Text("\r\n");
	
	}
}

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining - and
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation and will only be performed if configCHECK_FOR_STACK_OVERFLOW
	is set to either 1 or 2 in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/
/*
void vApplicationIdleHook( void )
{*/
	/* This example does not use the idle hook to perform any processing.  The
	idle hook will only be called if configUSE_IDLE_HOOK is set to 1 in 
	FreeRTOSConfig.h. */
//}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing.   The
	tick hook will only be called if configUSE_TICK_HOOK is set to 1 in
	FreeRTOSConfig.h. */
}
