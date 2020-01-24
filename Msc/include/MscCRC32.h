/******************************************************************************
**              Copyright (C) 2020 Laird Connectivity
**
** Project:     Zephyr
**
** Module:      MscCRC32.h
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
#ifndef MSCCRC32_H__
#define MSCCRC32_H__

/******************************************************************************/
/* Include Files*/
/******************************************************************************/
#include <stdlib.h>
#include <stdint.h>

/******************************************************************************/
/* Local Functions or Private Members*/
/******************************************************************************/

/*============================================================================*/
/*============================================================================*/
uint32_t
MscPubCalc32bitCrcNonTableMethod(
    uint32_t nCrc32,
    const uint8_t *pSrcStr,
    uint32_t nSrcLen /* in bytes */
    );

#endif
/******************************************************************************/
/* END OF FILE*/
/******************************************************************************/
