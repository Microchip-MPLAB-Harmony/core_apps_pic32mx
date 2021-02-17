/*******************************************************************************
* Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    task4.c

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

#include "task4.h"
#include "definitions.h"
#include <string.h>
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

TASK4_DATA task4Data;
static SemaphoreHandle_t switchPressSemaphore;
extern SemaphoreHandle_t uartMutexLock;
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the TASK4_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

static void SwitchPress_Handler( GPIO_PIN pin, uintptr_t context)
{
    BaseType_t xHigherPriorityTaskWoken;

    /* Unblock the task by releasing the semaphore. */
    xSemaphoreGiveFromISR( switchPressSemaphore, &xHigherPriorityTaskWoken );

    /* If xHigherPriorityTaskWoken was set to true you
    we should yield */

    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
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
    void TASK4_Initialize ( void )

  Remarks:
    See prototype in task4.h.
 */

void TASK4_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    task4Data.state = TASK4_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void TASK4_Tasks ( void )

  Remarks:
    See prototype in task4.h.
 */

void TASK4_Tasks ( void )
{
    bool status = false;
    TickType_t timeNow;
    
    switchPressSemaphore = xSemaphoreCreateBinary();

    if (switchPressSemaphore != NULL)
    {
        status = true;
    }

    GPIO_PinInterruptCallbackRegister(SWITCH1_PIN, SwitchPress_Handler, (uintptr_t)NULL);
    GPIO_PinInterruptEnable(SWITCH1_PIN);

    while (status == true)
    {
        /* Block until user presses the switch */
        if( xSemaphoreTake( switchPressSemaphore, portMAX_DELAY ) == pdTRUE )
        {
            /* Task4 is running (<-) now */
            xSemaphoreTake(uartMutexLock, portMAX_DELAY);
            UART1_Write((uint8_t*)"                                Tsk4-P4 <-\r\n", 44);
            xSemaphoreGive(uartMutexLock);

            /* Work done by task3 for 10 ticks */
            timeNow = xTaskGetTickCount();
            while ((xTaskGetTickCount() - timeNow) < 10);

            /* Task4 is exiting (->) now */
            xSemaphoreTake(uartMutexLock, portMAX_DELAY);
            UART1_Write((uint8_t*)"                                Tsk4-P4 ->\r\n", 44);
            xSemaphoreGive(uartMutexLock);
        }
    }
}


/*******************************************************************************
 End of File
 */
