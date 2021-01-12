/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_task2.c

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

#include "app_task2.h"
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
    This structure should be initialized by the APP_TASK2_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_TASK2_DATA app_task2Data;

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
    void APP_TASK2_Initialize ( void )

  Remarks:
    See prototype in app_task2.h.
 */

void APP_TASK2_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_task2Data.state = APP_TASK2_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_TASK2_Tasks ( void )

  Remarks:
    This task periodically polls for switch press every 250 milliseconds
 */

void APP_TASK2_Tasks ( void )
{
    while (1)
    {
        if (SWITCH2_Get() == SWITCH2_STATE_PRESSED)
        {
            LED2_Toggle();
        }
        
        /* Poll for switch press every 250 ms */
        vTaskDelay(250 / portTICK_PERIOD_MS );
    }
}


/*******************************************************************************
 End of File
 */
