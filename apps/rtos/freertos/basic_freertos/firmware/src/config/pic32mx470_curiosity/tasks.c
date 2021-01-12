/*******************************************************************************
 System Tasks File

  File Name:
    tasks.c

  Summary:
    This file contains source code necessary to maintain system's polled tasks.

  Description:
    This file contains source code necessary to maintain system's polled tasks.
    It implements the "SYS_Tasks" function that calls the individual "Tasks"
    functions for all polled MPLAB Harmony modules in the system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    polled in the system.  These handles are passed into the individual module
    "Tasks" functions to identify the instance of the module to maintain.
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

#include "configuration.h"
#include "definitions.h"


// *****************************************************************************
// *****************************************************************************
// Section: RTOS "Tasks" Routine
// *****************************************************************************
// *****************************************************************************
/* Handle for the TASK1_Tasks. */
TaskHandle_t xTASK1_Tasks;

void _TASK1_Tasks(  void *pvParameters  )
{   
    while(1)
    {
        TASK1_Tasks();
    }
}
/* Handle for the TASK2_Tasks. */
TaskHandle_t xTASK2_Tasks;

void _TASK2_Tasks(  void *pvParameters  )
{   
    while(1)
    {
        TASK2_Tasks();
    }
}
/* Handle for the TASK3_Tasks. */
TaskHandle_t xTASK3_Tasks;

void _TASK3_Tasks(  void *pvParameters  )
{   
    while(1)
    {
        TASK3_Tasks();
    }
}
/* Handle for the TASK4_Tasks. */
TaskHandle_t xTASK4_Tasks;

void _TASK4_Tasks(  void *pvParameters  )
{   
    while(1)
    {
        TASK4_Tasks();
    }
}




// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Remarks:
    See prototype in system/common/sys_module.h.
*/
void SYS_Tasks ( void )
{
    /* Maintain system services */
    

    /* Maintain Device Drivers */
    

    /* Maintain Middleware & Other Libraries */
    

    /* Maintain the application's state machine. */
        /* Create OS Thread for TASK1_Tasks. */
    xTaskCreate((TaskFunction_t) _TASK1_Tasks,
                "TASK1_Tasks",
                1024,
                NULL,
                1,
                &xTASK1_Tasks);

    /* Create OS Thread for TASK2_Tasks. */
    xTaskCreate((TaskFunction_t) _TASK2_Tasks,
                "TASK2_Tasks",
                1024,
                NULL,
                2,
                &xTASK2_Tasks);

    /* Create OS Thread for TASK3_Tasks. */
    xTaskCreate((TaskFunction_t) _TASK3_Tasks,
                "TASK3_Tasks",
                1024,
                NULL,
                3,
                &xTASK3_Tasks);

    /* Create OS Thread for TASK4_Tasks. */
    xTaskCreate((TaskFunction_t) _TASK4_Tasks,
                "TASK4_Tasks",
                1024,
                NULL,
                4,
                &xTASK4_Tasks);




    /* Start RTOS Scheduler. */
    
     /**********************************************************************
     * Create all Threads for APP Tasks before starting FreeRTOS Scheduler *
     ***********************************************************************/
    vTaskStartScheduler(); /* This function never returns. */

}

/*******************************************************************************
 End of File
 */

