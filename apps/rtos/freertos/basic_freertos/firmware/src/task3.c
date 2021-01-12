/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    task3.c

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

#include "task3.h"
#include "definitions.h"
#include "portmacro.h"
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
    This structure should be initialized by the TASK3_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

TASK3_DATA task3Data;
static SemaphoreHandle_t dataRxSemaphore;
extern SemaphoreHandle_t uartMutexLock;
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************
void uartReadEventHandler(UART_EVENT event, uintptr_t context )
{
    if (event == UART_EVENT_READ_THRESHOLD_REACHED)
    {
        BaseType_t xHigherPriorityTaskWoken;

        /* Unblock the task by releasing the semaphore. */
        xSemaphoreGiveFromISR( dataRxSemaphore, &xHigherPriorityTaskWoken );

        /* If xHigherPriorityTaskWoken was set to true you
        we should yield */

        portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
    }
}
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
    void TASK3_Initialize ( void )

  Remarks:
    See prototype in task3.h.
 */

void TASK3_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    task3Data.state = TASK3_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void TASK3_Tasks ( void )

  Remarks:
    See prototype in task3.h.
 */

void TASK3_Tasks ( void )
{
    uint8_t readByte;
    bool status = false;
    TickType_t timeNow;

    UART1_ReadCallbackRegister(uartReadEventHandler, 0);
    UART1_ReadThresholdSet(1);
    UART1_ReadNotificationEnable(true, false);

    dataRxSemaphore = xSemaphoreCreateBinary();

    if (dataRxSemaphore != NULL)
    {
        status = true;
    }

    while (status == true)
    {
        /* Block until a character is received on the terminal */
        if( xSemaphoreTake( dataRxSemaphore, portMAX_DELAY ) == pdTRUE )
        {
            /* Task3 is running (<-) now */
            xSemaphoreTake(uartMutexLock, portMAX_DELAY);
            UART1_Write((uint8_t*)"                      Tsk3-P3 <-\r\n", 34);
            xSemaphoreGive(uartMutexLock);

            /* Toggle an LED if character received is 'L' or 'l' */
            while (UART1_Read(&readByte, 1) == true)
            {
                if (readByte == 'L' || readByte == 'l')
                {
                    LED_TOGGLE();
                }
            }

            /* Work done by task3 for 50 ticks */
            timeNow = xTaskGetTickCount();
            while ((xTaskGetTickCount() - timeNow) < 50);

            /* Task3 is exiting (->) now */
            xSemaphoreTake(uartMutexLock, portMAX_DELAY);
            UART1_Write((uint8_t*)"                      Tsk3-P3 ->\r\n", 34);
            xSemaphoreGive(uartMutexLock);
        }
    }
}


/*******************************************************************************
 End of File
 */
