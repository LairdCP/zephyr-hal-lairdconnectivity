/******************************************************************************
**              Copyright (C) 2020 Laird Connectivity
**
** Project:     Zephyr
**
** Module:      BlrPublic.c
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

/******************************************************************************/
/* CONDITIONAL COMPILE DEFINES*/
/******************************************************************************/

/******************************************************************************/
/* Include Files*/
/******************************************************************************/
#include <string.h>
#include "BlrPublic.h"
#include "MscCRC32.h"

/******************************************************************************/
/* Local Defines*/
/******************************************************************************/

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

static uint32_t nExternalFunctionAddress = 0;
static uint16_t nExternalFunctionVersion = 0;

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

/*============================================================================*/
/* Used to set the values of the bootloader function address and version      */
/*============================================================================*/
bool
BlrPubSetup(
    )
{
    //Get data from external bootloader structure
    BootloaderExternalSettingsInfoStruct *pBLInfo;
    pBLInfo = (void*)BOOTLOADER_EXTERNAL_STRUCT_ADDR;

    //Check if values seem sane
#ifndef BLR_SKIP_CHECKSUM_VERIFY
    if (pBLInfo->Checksum == BLR_STRUCT_INVALID_CHECKSUM_MIN || pBLInfo->Checksum == BLR_STRUCT_INVALID_CHECKSUM_MAX)
    {
        //checksum is very likely invalid
        return false;
    }
    else
#endif
    if (pBLInfo->HeaderSize < BLR_STRUCT_MINIMUM_HEADER_SIZE || pBLInfo->HeaderSize > sizeof(BootloaderExternalSettingsInfoStruct))
    {
        //Header size is invalid
        return false;
    }
    else if (pBLInfo->Areas > BLR_STRUCT_MAXIMUM_AREAS)
    {
        //Too many areas
        return false;
    }
    else if (pBLInfo->ExternalFunctionVersion == BLR_STRUCT_INVALID_FUNCTION_VERSION_MIN || pBLInfo->ExternalFunctionVersion == BLR_STRUCT_INVALID_FUNCTION_VERSION_MAX)
    {
        //No external bootloader function version
        return false;
    }
    else if (pBLInfo->ExternalFunctionAddress == BLR_STRUCT_INVALID_FUNCTION_ADDRESS_MIN || pBLInfo->ExternalFunctionAddress == BLR_STRUCT_INVALID_FUNCTION_ADDRESS_MAX)
    {
        //No external bootloader function address
        return false;
    }

#ifndef CONFIG_LAIRDCONNECTIVITY_BLR_SKIP_CHECKSUM_VERIFY
    //Check that the header checksum is valid
    if (MscPubCalc32bitCrcNonTableMethod(0, (uint8_t *)(BOOTLOADER_EXTERNAL_STRUCT_ADDR + sizeof(pBLInfo->Checksum)), (sizeof(BootloaderExternalSettingsInfoStruct) - sizeof(pBLInfo->Checksum))) != pBLInfo->Checksum)
    {
        //Checksum mismatch
        return false;
    }
#endif

    //Header verified, update parameters
    nExternalFunctionAddress = pBLInfo->ExternalFunctionAddress;
    nExternalFunctionVersion = pBLInfo->ExternalFunctionVersion;

    return true;
}

/*============================================================================*/
/* Convert flags to type                                                      */
/*============================================================================*/
uint8_t
BlrPubConvertFlagToType(
    uint16_t nFlags
    )
{
    if ((nFlags & BOOTLOADER_STORAGE_FLAG_NUMERIC_LITTLE_ENDIAN))
    {
        //Numeric
        return BLR_TYPE_NUMERIC;
    }
    else if ((nFlags & BOOTLOADER_STORAGE_FLAG_BYTE_ARRAY) || (nFlags & BOOTLOADER_STORAGE_FLAG_BYTE_ARRAY_16))
    {
        //Byte array
        return BLR_TYPE_BYTE_ARRAY;
    }
    else if ((nFlags & BOOTLOADER_STORAGE_FLAG_STRING_NOT_TERMINATED) || (nFlags & BOOTLOADER_STORAGE_FLAG_STRING_NULL_TERMINATED))
    {
        //String
        return BLR_TYPE_STRING;
    }

    //Unknown
    return BLR_TYPE_UNKNOWN;
}

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
    )
{
    uint8_t nTmpVal;
    uint32_t nDataSize;
    void *pDataPos;

    if (!nExternalFunctionAddress)
    {
        //Bootloader external settings function not available
        return UWRESULTCODE_BLR_FUNCTION_UNAVAILABLE;
    }

    //Get data from external bootloader structure
    BootloaderExternalSettingsInfoStruct *pBLInfo;
    pBLInfo = (void*)BOOTLOADER_EXTERNAL_STRUCT_ADDR;

    if (
            (nType == BLR_INFO_TYPE_HEADER_CHECKSUM) || 
            (nType == BLR_INFO_TYPE_HEADER_VERSION) || 
            (nType == BLR_INFO_TYPE_HEADER_SIZE) || 
            (nType == BLR_INFO_TYPE_EXTERNAL_FUNCTION_ADDRESS) || 
            (nType == BLR_INFO_TYPE_EXTERNAL_FUNCTION_VERSION) || 
            (nType == BLR_INFO_TYPE_CHECKSUM_TYPE) || 
            (nType == BLR_INFO_TYPE_AREAS) || 
            (nType == BLR_INFO_TYPE_AREA_START_ADDRESS) || 
            (nType == BLR_INFO_TYPE_AREA_SIZE) || 
            (nType == BLR_INFO_TYPE_AREA_CHECKSUM) || 
            (nType == BLR_INFO_TYPE_AREA_VERSION) || 
            (nType == BLR_INFO_TYPE_AREA_TYPE) || 
            (nType == BLR_INFO_TYPE_AREA_ACCESS_RIGHTS) || 
            (nType == BLR_INFO_TYPE_AREA_SIGNATURE_TYPE)
        )
    {
        //Numeric
        if (pDataType)
        {
            //Update data type
            *pDataType = BLR_TYPE_NUMERIC;
        }

        if (nType == BLR_INFO_TYPE_HEADER_CHECKSUM)
        {
            //Header checksum
            nDataSize = sizeof(pBLInfo->Checksum);
            pDataPos = &pBLInfo->Checksum;
        }
        else if (nType == BLR_INFO_TYPE_HEADER_VERSION)
        {
            //Header version
            nDataSize = sizeof(pBLInfo->HeaderVersion);
            pDataPos = &pBLInfo->HeaderVersion;
        }
        else if (nType == BLR_INFO_TYPE_HEADER_SIZE)
        {
            //Header size
            nDataSize = sizeof(pBLInfo->HeaderSize);
            pDataPos = &pBLInfo->HeaderSize;
        }
        else if (nType == BLR_INFO_TYPE_EXTERNAL_FUNCTION_ADDRESS)
        {
            //External function address
            nDataSize = sizeof(pBLInfo->ExternalFunctionAddress);
            pDataPos = &pBLInfo->ExternalFunctionAddress;
        }
        else if (nType == BLR_INFO_TYPE_EXTERNAL_FUNCTION_VERSION)
        {
            //External function version
            nDataSize = sizeof(pBLInfo->ExternalFunctionVersion);
            pDataPos = &pBLInfo->ExternalFunctionVersion;
        }
        else if (nType == BLR_INFO_TYPE_CHECKSUM_TYPE)
        {
            //Checksum type
            nDataSize = sizeof(pBLInfo->ChecksumType);
            pDataPos = &pBLInfo->ChecksumType;
        }
        else if (nType == BLR_INFO_TYPE_AREAS)
        {
            //Number of areas
            nDataSize = sizeof(pBLInfo->Areas);
            pDataPos = &pBLInfo->Areas;
        }
        else if (
                (nType == BLR_INFO_TYPE_AREA_START_ADDRESS) || 
                (nType == BLR_INFO_TYPE_AREA_SIZE) || 
                (nType == BLR_INFO_TYPE_AREA_CHECKSUM) || 
                (nType == BLR_INFO_TYPE_AREA_VERSION) || 
                (nType == BLR_INFO_TYPE_AREA_TYPE) || 
                (nType == BLR_INFO_TYPE_AREA_ACCESS_RIGHTS) || 
                (nType == BLR_INFO_TYPE_AREA_SIGNATURE_TYPE)
            )
        {
            //Area information - check that the area is valid
            if (nArea > pBLInfo->Areas)
            {
                //Area is not valid
                return UWRESULTCODE_BLR_INVALID_AREA;
            }
            else if (nType == BLR_INFO_TYPE_AREA_START_ADDRESS)
            {
                //Area: Start address
                nDataSize = sizeof(pBLInfo->AreaInfo[0].StartAddress);
                pDataPos = &pBLInfo->AreaInfo[nArea].StartAddress;
            }
            else if (nType == BLR_INFO_TYPE_AREA_SIZE)
            {
                //Area: Size
                nDataSize = sizeof(pBLInfo->AreaInfo[0].Size);
                pDataPos = &pBLInfo->AreaInfo[nArea].Size;
            }
            else if (nType == BLR_INFO_TYPE_AREA_CHECKSUM)
            {
                //Area: Checksum
                nDataSize = sizeof(pBLInfo->AreaInfo[0].Checksum);
                pDataPos = &pBLInfo->AreaInfo[nArea].Checksum;
            }
            else if (nType == BLR_INFO_TYPE_AREA_VERSION)
            {
                //Area: Version
                nDataSize = sizeof(pBLInfo->AreaInfo[0].Version);
                pDataPos = &pBLInfo->AreaInfo[nArea].Version;
            }
            else if (nType == BLR_INFO_TYPE_AREA_TYPE)
            {
                //Area: Type
                nTmpVal = pBLInfo->AreaInfo[nArea].Type;
                nDataSize = sizeof(nTmpVal);
                pDataPos = &nTmpVal;
            }
            else if (nType == BLR_INFO_TYPE_AREA_ACCESS_RIGHTS)
            {
                //Area: Access rights
                nTmpVal = pBLInfo->AreaInfo[nArea].Access;
                nDataSize = sizeof(nTmpVal);
                pDataPos = &nTmpVal;
            }
            else if (nType == BLR_INFO_TYPE_AREA_SIGNATURE_TYPE)
            {
                //Area: signature type
                nTmpVal = pBLInfo->AreaInfo[nArea].SignatureType;
                nDataSize = sizeof(nTmpVal);
                pDataPos = &nTmpVal;
            }
        }
    }
    else if (
            (nType == BLR_INFO_TYPE_BUILD_DATE)
        )
    {
        //String
        if (pDataType)
        {
            //Update data type
            *pDataType = BLR_TYPE_STRING;
        }

        nDataSize = sizeof(pBLInfo->BuildDate);
        pDataPos = pBLInfo->BuildDate;
    }
    else if (
            (nType == BLR_INFO_TYPE_AREA_SIGNATURE)
        )
    {
        if (nArea > pBLInfo->Areas)
        {
            //Area is not valid
            return UWRESULTCODE_BLR_INVALID_AREA;
        }

        //Byte array
        if (pDataType)
        {
            //Update data type
            *pDataType = BLR_TYPE_BYTE_ARRAY;
        }

        //Area: signature type
        nDataSize = SIGNATURE_SIZE;
        pDataPos = pBLInfo->AreaInfo[nArea].Signature;
    }
    else
    {
        //Invalid
        return UWRESULTCODE_BLR_INVALID_TYPE;
    }

    if (pDataSize != NULL)
    {
        *pDataSize = nDataSize;
    }

    if (pBuffer && nBufferSize > 0)
    {
        //Copy some/all the data over
        memcpy(pBuffer, pDataPos, (nBufferSize > nDataSize ? nDataSize : nBufferSize));
    }

    //Complete
    return UWRESULTCODE_SUCCESS;
}

/*=============================================================================*/
/* Interacts with the bootloader query function                                */
/*=============================================================================*/
uint32_t
BlrPubQuery(
    uint32_t nIndex,
    uint8_t nPartition,
    uint8_t nSubKey,
    uint8_t * pDataBuffer,
    uint32_t nDataBufferSize,
    uint32_t * pDataSize,
    uint8_t * pSBFlags,
    uint16_t * pBootloaderFlags
    )
{
    uint32_t resCode = UWRESULTCODE_BLR_UNKNOWN_RESPONSE;
    uint8_t nBLResCode;
    uint16_t nBootloaderFlags = 0;

    if (!nExternalFunctionAddress)
    {
        //Bootloader external settings function not available
        return UWRESULTCODE_BLR_FUNCTION_UNAVAILABLE;
    }

    //Check which bootloader function version this is
    if (nExternalFunctionVersion != BLR_FUNCTION_VERSION_1 && nExternalFunctionVersion != BLR_FUNCTION_VERSION_2)
    {
        //Version is not supported
        return UWRESULTCODE_BLR_FUNCTION_NOT_SUPPORTED;
    }

    //Query
    bootloader_function_setting_t bldrload = (bootloader_function_setting_t)nExternalFunctionAddress;
    nBLResCode = bldrload(nIndex, nPartition, nSubKey, pDataBuffer, nDataBufferSize, pDataSize, &nBootloaderFlags);

    if (nBLResCode == BOOTLOADER_STORAGE_CODE_SUCCESS)
    {
        //Completed
        resCode = UWRESULTCODE_SUCCESS;

        if (pSBFlags)
        {
            //Update sB flags
            *pSBFlags = BlrPubConvertFlagToType(nBootloaderFlags);
        }

        if (pBootloaderFlags)
        {
            //Update Bootloader flags
            *pBootloaderFlags = nBootloaderFlags;
        }

        if ((pDataBuffer) && (nBootloaderFlags & BOOTLOADER_STORAGE_FLAG_BYTE_ARRAY_16))
        {
            //Endian flip requested
            if ((nDataBufferSize%2))
            {
                //The buffer size is odd, this means the data cannot be successfully flipped
                resCode = UWRESULTCODE_BLR_CANNOT_FLIP_UNEVEN_BYTES;
            }
            else
            {
                //Flip the bytes
                uint32_t nPos = 0;
                uint8_t nTmp;
                while (nPos < nDataBufferSize)
                {
                    nTmp = pDataBuffer[nPos];
                    pDataBuffer[nPos] = pDataBuffer[nPos+1];
                    pDataBuffer[nPos+1] = nTmp;
                    nPos += 2;
                }
            }
        }
    }
    else if (nBLResCode == BOOTLOADER_STORAGE_CODE_INVALID_ID)
    {
        //Invalid ID supplied
        resCode = UWRESULTCODE_BLR_INVALID_ID;
    }
    else if (nBLResCode == BOOTLOADER_STORAGE_CODE_NOT_PRESENT)
    {
        //Item not present/set
        resCode = UWRESULTCODE_BLR_NOT_SET;
    }
    else if (nBLResCode == BOOTLOADER_STORAGE_CODE_DISCREPANCY_DETECTED)
    {
        //Discrepancy detected
        resCode = UWRESULTCODE_BLR_DISCREPANCY_DETECTED;
    }
    else if (nBLResCode == BOOTLOADER_STORAGE_CODE_INVALID_PARTITION)
    {
        //Invalid partition
        resCode = UWRESULTCODE_BLR_INVALID_PARTITION;
    }
    else if (nBLResCode == BOOTLOADER_STORAGE_CODE_INVALID_SUB_ID)
    {
        //Invalid Sub-ID
        resCode = UWRESULTCODE_BLR_INVALID_SUB_ID;
    }

    //Return result code
    return resCode;
}

/*=============================================================================*/
/* Returns the type of the data                                                */
/*=============================================================================*/
uint32_t
BlrPubCheckType(
    uint32_t nIndex,
    uint8_t nPartition,
    uint8_t nSubKey,
    uint8_t * pType,
    uint8_t * pExtendedType
    )
{
    uint32_t resCode;
    uint16_t nFlags = 0;
    resCode = BlrPubQuery(nIndex, nPartition, nSubKey, NULL, 0, 0, NULL, &nFlags);

    if (UWSUCCESS(resCode))
    {
        //Check which type this is
        if (nFlags & BOOTLOADER_STORAGE_FLAG_NUMERIC_LITTLE_ENDIAN)
        {
            //Numeric (little endian)
            if (pType != NULL)
            {
                *pType = BLR_TYPE_NUMERIC;
            }

            if (pExtendedType != NULL)
            {
                *pExtendedType = BLR_EXTENDED_TYPE_NUMERIC_LITTLE_ENDIAN;
            }
        }
        else if ((nFlags & BOOTLOADER_STORAGE_FLAG_BYTE_ARRAY) || (nFlags & BOOTLOADER_STORAGE_FLAG_BYTE_ARRAY_16))
        {
            //Byte array
            if (pType != NULL)
            {
                *pType = BLR_TYPE_BYTE_ARRAY;
            }

            if (pExtendedType != NULL)
            {
                *pExtendedType = (nFlags & BOOTLOADER_STORAGE_FLAG_BYTE_ARRAY_16) ? BLR_EXTENDED_TYPE_BYTE_ARRAY_FLIP : BLR_EXTENDED_TYPE_BYTE_ARRAY;
            }
        }
        else
        {
            //Unknown
            if (pType != NULL)
            {
                *pType = BLR_TYPE_UNKNOWN;
            }

            if (pExtendedType != NULL)
            {
                *pExtendedType = BLR_EXTENDED_TYPE_UNKNOWN;
            }
        }
    }

    //Return result code
    return resCode;
}

/******************************************************************************/
/* END OF FILE*/
/******************************************************************************/
