/******************************************************************************
**              Copyright (C) 2020 Laird Connectivity
**
** Project:     Zephyr
**
** Module:      BlrResultCodes.h
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
#if !defined(_BLRRESULTCODES_H)     /* prevent multiple inclusions */
#define _BLRRESULTCODES_H

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

/******************************************************************************/
/* Macros*/
/******************************************************************************/

/******************************************************************************/
/* Simple (non struct/union) Typedefs*/
/******************************************************************************/

/******************************************************************************/
/* Enum Typedefs*/
/******************************************************************************/

/*=============================================================================*/
/* This enum collects all module BLR specific result codes */
/*=============================================================================*/
#define UWRESULTCODE_START_BLR_MODULE 0x3800

enum
{
    UWRESULTCODE_BLR_FUNCTION_UNAVAILABLE   =   /* 3800 */ UWRESULTCODE_START_BLR_MODULE
    ,UWRESULTCODE_BLR_FUNCTION_NOT_SUPPORTED    /* 3801 */
    ,UWRESULTCODE_BLR_UNKNOWN_RESPONSE          /* 3802 */
    ,UWRESULTCODE_BLR_NOT_SET                   /* 3803 */
    ,UWRESULTCODE_BLR_INVALID_ID                /* 3804 */
    ,UWRESULTCODE_BLR_INVALID_PARTITION         /* 3805 */
    ,UWRESULTCODE_BLR_INVALID_SUB_ID            /* 3806 */
    ,UWRESULTCODE_BLR_INVALID_AREA              /* 3807 */
    ,UWRESULTCODE_BLR_DISCREPANCY_DETECTED      /* 3808 */
    ,UWRESULTCODE_BLR_INVALID_TYPE              /* 3809 */
    ,UWRESULTCODE_BLR_TYPE_NOT_KNOWN            /* 380A */
    ,UWRESULTCODE_BLR_INTEGER_OVERFLOW          /* 380B */
    ,UWRESULTCODE_BLR_CANNOT_FLIP_UNEVEN_BYTES  /* 380C */

   /*
   ************ ADD A NEW RESULTCODE ABOVE HERE ***********

   Looks like you have added an error code.
   Remember to update XY01 so you can grep for the error value if a customer ever
   reports an error number. It will help you trace the error path.

   NOW PLEASE GO AND DO ....
   Open BlrResultCodes.c and add the CASE(UWRESULTCODE_,BLR_someError ); macro.

   NEVER change its position in this email once allocated, because you will
   just be creating grief for yourself. Once a resultCode value gets out
   it SHOULD NEVER be changed.
   */


   /*
   ,UWRESULTCODE_BLR_
   */
};

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
