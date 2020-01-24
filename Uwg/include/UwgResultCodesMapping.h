/******************************************************************************
**              Copyright (C) 2020 Laird Connectivity
**
** Project:     Zephyr
**
** Module:      UwgResultCodesMapping.h
**
** Mnemonic:    Uwg
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
#if !defined(_UWGRESULTCODESMAPPING_H)     /* prevent multiple inclusions */
#define _UWGRESULTCODESMAPPING_H

/******************************************************************************/
/* Include Files*/
/******************************************************************************/

/******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/* Defines*/
/******************************************************************************/

/* ERROR resultcode start value - where MSB != 0 */
#define UWRESULTCODE_START_UWG_MODULE       0x0200
#define UWRESULTCODE_START_MSC_MODULE       0x2400
#define UWRESULTCODE_START_BLR_MODULE       0x3800

/*
** Add more UWRESULTCODE_START_mmm_MODULE above
**
** DO NOT USE 0xFF00 as a start value
**
** ---------------------------------------------------------
** WARNING - DANGER  || WARNING - DANGER || WARNING - DANGER
** ---------------------------------------------------------
**
** Do NOT assign a start value in the range FF00 to FFFF inclusive
** as that range is used as a special value
**
*/

/******************************************************************************/
/* Macros*/
/******************************************************************************/

/******************************************************************************/
/* Simple (non struct/union) Typedefs*/
/******************************************************************************/

/******************************************************************************/
/* Enum Typedefs*/
/******************************************************************************/

/******************************************************************************/
/* Forward declaration of Class, Struct & Unions*/
/******************************************************************************/

/******************************************************************************/
/* Class definitions*/
/******************************************************************************/

/******************************************************************************/
/* Struct definitions*/
/******************************************************************************/

/******************************************************************************/
/* Union definitions*/
/******************************************************************************/

/******************************************************************************/
/* Global Variables exported for other modules*/
/******************************************************************************/

/******************************************************************************/
/* Global Functions (API etc) exported for other modules*/
/******************************************************************************/

/******************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* Prevention of multiple inclusion */
/******************************************************************************/
/* END OF FILE*/
/******************************************************************************/
