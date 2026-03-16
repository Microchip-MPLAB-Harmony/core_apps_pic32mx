/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

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

#include <string.h>
#include "bsp/bsp.h"
#include "app.h"
#include "library/emulated_eeprom/emulated_eeprom.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

#define OFFSETOF(s, m) ((size_t)&(((s *)0)->m))
#define SIZEOF(s, m) ((size_t) sizeof(((s *)0)->m))

#define EMU_EEPROM_READ(MEM, DEST) EMU_EEPROM_BufferRead(OFFSETOF(EEPROM_DATA, MEM), (uint8_t*)DEST, SIZEOF(EEPROM_DATA, MEM))

#define EMU_EEPROM_WRITE(MEM, DATA) EMU_EEPROM_BufferWrite(OFFSETOF(EEPROM_DATA, MEM), (const uint8_t*)DATA, SIZEOF(EEPROM_DATA, MEM))

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;
EEPROM_DATA CACHE_ALIGN appTestData ;
EEPROM_DATA appRAMCopy = {0};


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


void APP_BufferFill(uint8_t* buffer, uint32_t nBytes)
{
    uint32_t i;
    
    for (i = 0; i < nBytes; i++)
    {
        buffer[i] = i;
    }
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    EMU_EEPROM_STATUS libStatus;
    
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
            
            libStatus = EMU_EEPROM_StatusGet();
            
            if (libStatus == EMU_EEPROM_STATUS_OK)
            {
                appData.state = APP_STATE_WRITE_DATA;
            }            
            else if ((libStatus == EMU_EEPROM_STATUS_ERR_BAD_FORMAT) || (libStatus == EMU_EEPROM_STATUS_ERR_NOT_INITIALIZED))
            {      
                /* Format EEPROM memory space */
                EMU_EEPROM_FormatMemory();
                appData.state = APP_STATE_LIB_STATUS_VERIFY;
            }
            else
            {
                appData.state = APP_STATE_ERROR;
            }            
        
            break;        

        case APP_STATE_LIB_STATUS_VERIFY:
            
            /* Make sure the EEPROM Emulator is initialized successfully after it was formatted */
            libStatus = EMU_EEPROM_StatusGet();
            
            if (libStatus == EMU_EEPROM_STATUS_OK)
            {
                appData.state = APP_STATE_WRITE_DATA;
            }  
            else
            {
                appData.state = APP_STATE_ERROR;
            } 
            break;
            
        case APP_STATE_WRITE_DATA:
            
            /* For demonstration purpose, write some random values to EEPROM memory region */
            appTestData.var_1 = 0x0A;
    
            EMU_EEPROM_WRITE(var_1, &appTestData.var_1);

            appTestData.var_2 = 0x1234;

            EMU_EEPROM_WRITE(var_2, &appTestData.var_2);

            appTestData.var_3 = 0x33445566;

            EMU_EEPROM_WRITE(var_3, &appTestData.var_3);

            appTestData.var_7 = 0x3189AB1C;

            EMU_EEPROM_WRITE(var_7, &appTestData.var_7);

            appTestData.var_7 = 0x9A7BC123;

            EMU_EEPROM_WRITE(var_7, &appTestData.var_7);

            appTestData.var_2 = 0x1256;

            EMU_EEPROM_WRITE(var_2, &appTestData.var_2);

            appTestData.var_7 = 0x882B7C9A;

            EMU_EEPROM_WRITE(var_7, &appTestData.var_7);

            appTestData.var_2 = 0x7788;

            EMU_EEPROM_WRITE(var_2, &appTestData.var_2);
            
            APP_BufferFill(appTestData.buffer_1, sizeof (appTestData.buffer_1));
              
            EMU_EEPROM_WRITE(buffer_1, &appTestData.buffer_1);
            
            appTestData.var_11 = 0x7498AFDD;

            EMU_EEPROM_WRITE(var_11, &appTestData.var_11);

            appTestData.var_7 = 0x1788BB8D;

            EMU_EEPROM_WRITE(var_7, &appTestData.var_7);

            appTestData.var_10 = 0x7744AABB;

            EMU_EEPROM_WRITE(var_10, &appTestData.var_10);

            appTestData.var_2 = 0x9922;
            
            EMU_EEPROM_WRITE(var_2, &appTestData.var_2);
            
            appTestData.var_5 = 0x59AF;

            EMU_EEPROM_WRITE(var_5, &appTestData.var_5);
            
            appTestData.var_9 = 0x99AA;
            
            EMU_EEPROM_WRITE(var_9, &appTestData.var_9); 

            appTestData.var_10 = 0x88888888;

            EMU_EEPROM_WRITE(var_10, &appTestData.var_10);
              
            appTestData.var_12 = 0x5577;

            EMU_EEPROM_WRITE(var_12, &appTestData.var_12); 

            appTestData.var_10 = 0x1AC87439;

            EMU_EEPROM_WRITE(var_10, &appTestData.var_10);
            
            appTestData.var_8 = 0x752B9ACE;

            EMU_EEPROM_WRITE(var_8, &appTestData.var_8);
            
            appTestData.var_2 = 0xA765;

            EMU_EEPROM_WRITE(var_2, &appTestData.var_2);
            
            appTestData.var_4 = 0xA7;

            EMU_EEPROM_WRITE(var_4, &appTestData.var_4);
            
            appTestData.var_9 = 0xEEF1;
            
            EMU_EEPROM_WRITE(var_9, &appTestData.var_9); 
            
            appTestData.var_6 = 0xF497;
            
            EMU_EEPROM_WRITE(var_6, &appTestData.var_6); 
            
            appData.state = APP_STATE_READ_DATA;
            
            break;
          
        case APP_STATE_READ_DATA:       
                     
            /* Randomly read back the written values */
            EMU_EEPROM_READ(var_2, &appRAMCopy.var_2);
            
            EMU_EEPROM_READ(var_3, &appRAMCopy.var_3);
                                   
            EMU_EEPROM_READ(var_7, &appRAMCopy.var_7);
            
            EMU_EEPROM_READ(var_9, &appRAMCopy.var_9);
            
            EMU_EEPROM_READ(var_10, &appRAMCopy.var_10);
            
            EMU_EEPROM_READ(var_12, &appRAMCopy.var_12);
            
            EMU_EEPROM_READ(var_1, &appRAMCopy.var_1);
            
            EMU_EEPROM_READ(var_6, &appRAMCopy.var_6);
            
            EMU_EEPROM_READ(var_8, &appRAMCopy.var_8);
            
            EMU_EEPROM_READ(var_11, &appRAMCopy.var_11);                        
            
            EMU_EEPROM_READ(buffer_1, &appRAMCopy.buffer_1);
            
            EMU_EEPROM_READ(var_4, &appRAMCopy.var_4);
            
            EMU_EEPROM_READ(var_5, &appRAMCopy.var_5);
                        
            appData.state = APP_STATE_VERIFY;
                        
            break;

        case APP_STATE_VERIFY:
            if (memcmp((void const*)&appRAMCopy, (void const*)&appTestData, sizeof (EEPROM_DATA)) == 0)
            {
                LED1_On();
            }
            else
            {
                LED1_Off();
            }
            
            appData.state = APP_STATE_IDLE;
            break;
            
        case APP_STATE_IDLE:
            break;
            
        case APP_STATE_ERROR:
            break;

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
