/******************************************************************************
**              Copyright (C) 2020 Laird Connectivity
**
** Project:     Zephyr
**
** Module:      BlrPublic.h
**
** Mnemonic:    Blr
**
** Notes:       
**
** License:     This code is for use only in projects based around the Laird
**              Connectivity Pinnacle 100 module (including PC or embedded
**              device applications). All other use of this code is prohibited.
**
**              All rights reserved.
**
**              It is provided "as is", without warranty/guarantee of any kind,
**              express of implied, including but not limited to the warranties
**              of merchantability, fitness for a particular purpose and
**              non-infringement.
**
*******************************************************************************/
#if !defined(_BLRPUBLIC_H)     /* prevent multiple inclusions */
#define _BLRPUBLIC_H

/******************************************************************************/
/* CONDITIONAL COMPILE DEFINES*/
/******************************************************************************/

/******************************************************************************/
/* Include Files*/
/******************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "UwgPublic.h"
#include "Bootloader_External_Settings.h"

/*=============================================================================*/
/* The enum in the following included file collects all module Blr specific    */
/* result codes                                                                */
/*=============================================================================*/
#include "BlrResultCodes.h"

//Commented lines are for possible future use
enum BLR_TYPES
{
    BLR_TYPE_UNKNOWN                                  = 0,
    BLR_TYPE_NUMERIC,
    BLR_TYPE_BYTE_ARRAY,
    BLR_TYPE_STRING,

    BLR_TYPE_MAX
};

//Commented lines are for possible future use
enum BLR_EXTENDED_TYPES
{
    BLR_EXTENDED_TYPE_UNKNOWN                         = 0,
    BLR_EXTENDED_TYPE_NUMERIC_LITTLE_ENDIAN,
    BLR_EXTENDED_TYPE_NUMERIC_BIG_ENDIAN,
    BLR_EXTENDED_TYPE_BYTE_ARRAY,
    BLR_EXTENDED_TYPE_BYTE_ARRAY_FLIP,

    BLR_EXTENDED_TYPE_MAX
};

enum BLR_INFO_TYPES
{
    BLR_INFO_TYPE_HEADER_CHECKSUM                     = 0,
    BLR_INFO_TYPE_HEADER_VERSION,
    BLR_INFO_TYPE_HEADER_SIZE,
    BLR_INFO_TYPE_EXTERNAL_FUNCTION_ADDRESS,
    BLR_INFO_TYPE_EXTERNAL_FUNCTION_VERSION,
    BLR_INFO_TYPE_CHECKSUM_TYPE,
    BLR_INFO_TYPE_AREAS,
    BLR_INFO_TYPE_BUILD_DATE,

    BLR_INFO_TYPE_AREA_START_ADDRESS                  = 0x40,
    BLR_INFO_TYPE_AREA_SIZE,
    BLR_INFO_TYPE_AREA_CHECKSUM,
    BLR_INFO_TYPE_AREA_VERSION,
    BLR_INFO_TYPE_AREA_TYPE,
    BLR_INFO_TYPE_AREA_ACCESS_RIGHTS,
    BLR_INFO_TYPE_AREA_SIGNATURE_TYPE,
    BLR_INFO_TYPE_AREA_SIGNATURE
};

enum BLE_FUNCTION_VERSIONS
{
    BLR_FUNCTION_VERSION_1                            = 1,          //First version of bootloader function
    BLR_FUNCTION_VERSION_2,

    BLR_FUNCTION_VERSION_MAX
};

enum BOOTLOADER_INIT_STATES
{
    BOOTLOADER_INIT_STATE_UNINITIALISED               = 0,
    BOOTLOADER_INIT_STATE_INITIALISED,
    BOOTLOADER_INIT_STATE_ERROR_CHECKSUM_INVALID,
    BOOTLOADER_INIT_STATE_ERROR_SIZE,
    BOOTLOADER_INIT_STATE_ERROR_TOO_MANY_AREAS,
    BOOTLOADER_INIT_STATE_ERROR_NO_FUNCTION_VERSION,
    BOOTLOADER_INIT_STATE_ERROR_NO_FUNCTION_ADDRESS,
    BOOTLOADER_INIT_STATE_CHECKSUM_MISMATCH
};

/******************************************************************************/
/* Local Defines*/
/******************************************************************************/

#define BLR_STRUCT_INVALID_CHECKSUM_MIN         0                   //Invalid checksum value
#define BLR_STRUCT_INVALID_CHECKSUM_MAX         0xffffffff          //Invalid checksum value
#define BLR_STRUCT_MINIMUM_HEADER_SIZE          10                  //Minimum header size
#define BLR_STRUCT_MAXIMUM_AREAS                8                   //Maximum areas
#define BLR_STRUCT_INVALID_FUNCTION_VERSION_MIN 0                   //Invalid function version value
#define BLR_STRUCT_INVALID_FUNCTION_VERSION_MAX 0xffffffff          //Invalid function version value
#define BLR_STRUCT_INVALID_FUNCTION_ADDRESS_MIN 0                   //Invalid function address value
#define BLR_STRUCT_INVALID_FUNCTION_ADDRESS_MAX 0xffffffff          //Invalid function address value

/******************************************************************************/
/* Local Macros*/
/******************************************************************************/

/******************************************************************************/
/* Local Forward Class,Struct & Union Declarations*/
/******************************************************************************/

/******************************************************************************/
/* Local Class,Struct,Union Typedefs*/
/******************************************************************************/

/******************************************************************************/
/* External Variable Declarations*/
/******************************************************************************/

/******************************************************************************/
/* Global/Static Variable Declarations*/
/******************************************************************************/

/******************************************************************************/
/* External Function Declarations*/
/******************************************************************************/

/******************************************************************************/
/* Local Forward Function Declarations*/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/* Local Functions or Private Members*/
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/******************************************************************************/
/* Global Functions or Public Members*/
/******************************************************************************/
/******************************************************************************/

/*=============================================================================*/
/* Used to set the values of the bootloader function address and version       */
/*=============================================================================*/
bool
BlrPubSetup(
    );

/*============================================================================*/
/* Return information on external bootloader function                         */
/*============================================================================*/
uint8_t
BlrPubGetInfo(
    uint16_t *pExternalFunctionVersion,
    uint16_t *pHeaderVersion,
    uint8_t *pFirmwareBuildDate
    );

/*=============================================================================*/
/* Convert flags to type                                                       */
/*=============================================================================*/
uint8_t
BlrPubConvertFlagToType(
    uint16_t nFlags
    );

/*=============================================================================*/
/* Return infoformation on item in bootloader struct                           */
/*=============================================================================*/
uint32_t
BlrPubInfo(
    uint8_t nType,
    uint8_t nArea,
    uint8_t *pBuffer,
    uint32_t nBufferSize,
    uint8_t *pDataType,
    uint32_t *pDataSize
    );

/*=============================================================================*/
/* Interacts with the bootloader query function                                */
/*=============================================================================*/
uint32_t
BlrPubQuery(
    uint32_t nIndex,
    uint8_t nPartition,
    uint8_t nSubKey,
    uint8_t* pDataBuffer,
    uint32_t nDataBufferSize,
    uint32_t* pDataSize,
    uint8_t* pSBFlags,
    uint16_t* pBootloaderFlags
    );

/*=============================================================================*/
/* Returns the type of the data                                                */
/*=============================================================================*/
uint32_t
BlrPubCheckType(
    uint32_t nIndex,
    uint8_t nPartition,
    uint8_t nSubKey,
    uint8_t* pType,
    uint8_t* pExtendedType
    );

#endif

/******************************************************************************/
/* END OF FILE*/
/******************************************************************************/
