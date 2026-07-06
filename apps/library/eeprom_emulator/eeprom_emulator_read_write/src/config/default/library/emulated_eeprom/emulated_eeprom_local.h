/*******************************************************************************
  EEPROM Emulator Local definitions and data structures

  Company:
    Microchip Technology Inc.

  File Name:
    emulated_eeprom_local.h

  Summary:
    EEPROM Emulator Library local definitions and data structures

  Description:
    This file defines data structures used internally by the EEPROM Emulator library.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries.
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
//DOM-IGNORE-END

#ifndef EEPROM_EMULATOR_LOCAL_H
#define EEPROM_EMULATOR_LOCAL_H

#include "emulated_eeprom_definitions.h"
#include "osal/osal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* MISRA C-2023 Rule 5.4 deviated:2 Deviation record ID -  H3_MISRAC_2023_R_5_4_DR_1 */
#define EEPROM_EMULATOR_ROW_SIZE                                4096
#define EEPROM_EMULATOR_PAGES_PER_ROW                           8U
#define EEPROM_EMULATOR_PAGE_SIZE                               512U
#define EEPROM_EMULATOR_INVALID_PAGE_NUMBER                     0xFFFFU
#define EEPROM_EMULATOR_INVALID_ROW_NUMBER                      0xFFFFU
#define EEPROM_EMULATOR_HEADER_SIZE                             4U
#define EEPROM_EMULATOR_NUM_PHYSICAL_PAGES                      32U
#define EEPROM_EMULATOR_NUM_LOGICAL_PAGES                       12U
#define EEPROM_EMULATOR_LOGICAL_SIZE_BYTES                      6096
#define EEPROM_EMULATOR_NUM_LOGICAL_PAGES_PER_ROW               (EEPROM_EMULATOR_PAGES_PER_ROW>>1)

/* MISRAC 2012 deviation block end */

#define EEPROM_EMULATOR_EEPROM_START_ADDRESS                   0x9D07C000

/** Size of the user data portion of each logical EEPROM page, in bytes. */
#define EEPROM_EMULATOR_PAGE_DATA_SIZE                         (EEPROM_EMULATOR_PAGE_SIZE - EEPROM_EMULATOR_HEADER_SIZE)

/**
 * \internal
 * \brief Structure describing emulated pages of EEPROM data.
 */
typedef struct __attribute__((packed, aligned(4)))
{
    /** Header information of the EEPROM page. */
    struct
    {
        uint16_t logical_page;

        /* The final version string is of 4 bytes.
         * 2 bytes are stored in page 0 header and remaining 2 bytes in page 1 header of each row. */
        uint8_t version;
        
        uint8_t checksum;
    } header;

    /** Data content of the EEPROM page. */
    uint8_t data[EEPROM_EMULATOR_PAGE_DATA_SIZE];
}EEPROM_PAGE;

/**
 * \internal
 * \brief Internal device instance struct.
 */
typedef struct
{
    /** Initialization state of the EEPROM emulator. */
    bool initialized;

    /** Absolute byte pointer to the first byte of FLASH where the emulated EEPROM is stored. */
    EEPROM_PAGE* main_array;

    /** Mapping array from logical EEPROM pages to physical FLASH pages. */
    uint8_t page_map[EEPROM_EMULATOR_NUM_LOGICAL_PAGES];

    /** Row number for the spare row (used by next write). */
    uint16_t spare_row;

    /** Buffer to hold the currently cached page. */
    EEPROM_PAGE cache;

    /** Indicates library status */
    EMU_EEPROM_STATUS status;

    /* Mutex to synchronize multiple simultaneous access */
    OSAL_MUTEX_DECLARE (EmulatedEEPROMAccessLock);

}EEPROM_MODULE CACHE_ALIGN;

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* EEPROM_EMULATOR_LOCAL_H */
