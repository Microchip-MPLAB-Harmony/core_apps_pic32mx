/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app1.c

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
// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app1.h"
#include "user.h"
#include <stdio.h>

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
    This structure should be initialized by the APP1_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP1_DATA app1Data;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

void Timer1_Callback ( uintptr_t context )
{
    app1Data.tmr1Expired = true;
}

void Timer2_Callback ( uintptr_t context )
{
    app1Data.tmr2Expired = true;
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
    void APP1_Initialize ( void )

  Remarks:
    See prototype in app1.h.
 */

void APP1_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app1Data.state = APP1_STATE_INIT;

    app1Data.tmr1Handle = SYS_TIME_HANDLE_INVALID;
    app1Data.tmr2Handle = SYS_TIME_HANDLE_INVALID;
    app1Data.tmr3Handle = SYS_TIME_HANDLE_INVALID;

    app1Data.tmr1Expired = false;
    app1Data.tmr2Expired = false;
}


/******************************************************************************
  Function:
    void APP1_Tasks ( void )

  Remarks:
    See prototype in app1.h.
 */

void APP1_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app1Data.state )
    {
        /* Application's initial state. */
        case APP1_STATE_INIT:
            
            app1Data.tmr1Handle = SYS_TIME_CallbackRegisterMS(Timer1_Callback, 0, LED1_BLINK_RATE_MS, SYS_TIME_PERIODIC);
            app1Data.tmr2Handle = SYS_TIME_CallbackRegisterMS(Timer2_Callback, 0, LED2_BLINK_RATE_MS, SYS_TIME_PERIODIC);

            if ((app1Data.tmr1Handle != SYS_TIME_HANDLE_INVALID) && (app1Data.tmr2Handle != SYS_TIME_HANDLE_INVALID))
            {

                app1Data.state = APP1_STATE_SERVICE_TASKS;
            }
            break;

        case APP1_STATE_SERVICE_TASKS:

            if(app1Data.tmr1Expired == true)
            {
                /* Toggle LED1 periodically */
                app1Data.tmr1Expired = false;
                LED1_Toggle();
            }
            if(app1Data.tmr2Expired == true)
            {   
                /* Toggle LED2 periodically */
                app1Data.tmr2Expired = false;
                LED2_Toggle();
            }
            if(SWITCH_GET() == SWITCH_STATUS_PRESSED)
            {
                /* Toggle LED3 periodically when switch is pressed */
                if (app1Data.tmr3Handle == SYS_TIME_HANDLE_INVALID)
                {
                    SYS_TIME_DelayMS(SWITCH_DELAY_MS, &app1Data.tmr3Handle);
                }
            }
            if (app1Data.tmr3Handle != SYS_TIME_HANDLE_INVALID)
            {
                if (SYS_TIME_DelayIsComplete(app1Data.tmr3Handle))
                {
                    app1Data.tmr3Handle = SYS_TIME_HANDLE_INVALID;
                    LED3_Toggle();
                } 
            }
            break;

        /* The default state should never be executed. */
        default:
        {
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
