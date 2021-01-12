/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    task1.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "task1.h"
#include "definitions.h"
#include <string.h>

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the TASK1_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

TASK1_DATA task1Data;

/* Mutex used to protect the shared resource - UART */
SemaphoreHandle_t uartMutexLock;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void TASK1_Initialize ( void )

  Remarks:
    See prototype in task1.h.
 */

void TASK1_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    task1Data.state = TASK1_STATE_INIT;

    /* Create a mutex type semaphore. */
    uartMutexLock = xSemaphoreCreateMutex();

    if( uartMutexLock == NULL)
    {
        /* There was insufficient FreeRTOS heap available for the semaphore to
        be created successfully. */
        UART1_Write((uint8_t*)"Could not create mutex lock\r\n", strlen("Could not create mutex lock\r\n"));
    }
}

/******************************************************************************
  Function:
    void TASK1_Tasks ( void )

  Remarks:
    See prototype in task1.h.
 */

void TASK1_Tasks ( void )
{
    TickType_t timeNow;

    while (1)
    {
        /* Task1 is running (<-) now */
        xSemaphoreTake(uartMutexLock, portMAX_DELAY);
        UART1_Write((uint8_t*)"Tsk1-P1 <-\r\n", 12);
        xSemaphoreGive(uartMutexLock);

        /* Work done by task1 for 100 ticks */
        timeNow = xTaskGetTickCount();
        while ((xTaskGetTickCount() - timeNow) < 100);

        /* Task1 is exiting (->) now */
        xSemaphoreTake(uartMutexLock, portMAX_DELAY);
        UART1_Write((uint8_t*)"Tsk1-P1 ->\r\n", 12);
        xSemaphoreGive(uartMutexLock);

        /* Let idle task run for some time*/
        vTaskDelay(10 / portTICK_PERIOD_MS );
    }
}


/*******************************************************************************
 End of File
 */
