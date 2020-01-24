/******************************************************************************
**              Copyright (C) 2020 Laird Connectivity
**
** Project:     Zephyr
**
** Module:      MscCRC32.c
**
** Mnemonic:    Msc
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
/* Include Files*/
/******************************************************************************/
#include "MscCRC32.h"

/******************************************************************************/
/* Local Functions or Private Members*/
/******************************************************************************/

/*============================================================================*/
#define CRC32_POLYNOMIAL 0xEDB88320
/*============================================================================*/
static uint32_t
MscPubCalc32bitForByte(
    uint8_t nByte
    )
{
    uint8_t nBitCount=8;
    uint32_t nCrc32 = nByte;
    while(nBitCount--)
    {
        if(nCrc32 & 1)
        {
            nCrc32 = (nCrc32 >> 1)^CRC32_POLYNOMIAL;
        }
        else
        {
            nCrc32 >>= 1;
        }
    }
    return nCrc32;
}

/*============================================================================*/
/* Given an array of bytes, a new 32 bit CRC is calculated.                   */
/*============================================================================*/
uint32_t
MscPubCalc32bitCrcNonTableMethod(
    uint32_t nCrc32,
    const uint8_t *pSrcStr,
    uint32_t nSrcLen /* in bytes */
    )
{
    uint32_t nTemp1,nTemp2;
    while(nSrcLen--)
    {
        nTemp1 = (nCrc32 >> 8) & 0x00FFFFFFL;
        nTemp2 = MscPubCalc32bitForByte( (uint8_t)((nCrc32 ^ *pSrcStr++) & 
                     0xFF) );
        nCrc32 = nTemp1 ^ nTemp2;
    }
    return nCrc32;
}

/******************************************************************************/
/* END OF FILE*/
/******************************************************************************/
