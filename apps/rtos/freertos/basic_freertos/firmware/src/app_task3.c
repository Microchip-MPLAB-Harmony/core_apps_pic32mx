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
    app_task3.c

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

#include "app_task3.h"
#include "definitions.h"
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
    This structure should be initialized by the APP_TASK3_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_TASK3_DATA app_task3Data;
static SemaphoreHandle_t switchPressSemaphore;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

static void SwitchPress_Handler( CN_PIN cnPin, uintptr_t context)
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
    void APP_TASK3_Initialize ( void )

  Remarks:
    See prototype in app_task3.h.
 */

void APP_TASK3_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_task3Data.state = APP_TASK3_STATE_INIT;

    GPIO_PinInterruptCallbackRegister(CN19_PIN, SwitchPress_Handler, (uintptr_t)NULL);
    GPIO_PinInterruptEnable(CN19_PIN);
}


/******************************************************************************
  Function:
    void APP_TASK3_Tasks ( void )

  Remarks:
    This task blocks on switch press. It unblocks when switch is pressed/released, toggles LED and
    again blocks on switch press event.
 */

void APP_TASK3_Tasks ( void )
{
    bool status = false;
    
    switchPressSemaphore = xSemaphoreCreateBinary();

    if (switchPressSemaphore != NULL)
    {
        status = true;
    }

    while (status == true)
    {
        /* Block until user presses the switch */
        if( xSemaphoreTake( switchPressSemaphore, portMAX_DELAY ) == pdTRUE )
        {
            LED3_Toggle();
        }
    }
}


/*******************************************************************************
 End of File
 */
