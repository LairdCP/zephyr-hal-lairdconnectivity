/******************************************************************************
**              Copyright (C) 2020 Laird Connectivity
**
** Project:     Zephyr
**
** Module:      UwgPublic.h
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
#if !defined(_UWGPUBLIC_H)     /* prevent multiple inclusions */
#define _UWGPUBLIC_H

/******************************************************************************/
/* Include Files*/
/******************************************************************************/
#include "UwgResultCodesMapping.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/* Defines*/
/******************************************************************************/

#define UWRESULTCODE_SUCCESS                0x0000
#define UWRESULTCODE_LOWEST_FAIL_VALUE      0x0100

/* Add more above as TOK needs 32 for the moment so positioned at the */
/* upper end */
#define UWRESULTCODE_OKSTART_TOK_MODULE     0x00E0  /* reserving 32 for TOK */

#define UWG_UUID_SIZE_UI8                   (16)
#define UWG_UUID_SIZE_UI16                  (8)
#define UWG_UUID_SIZE_UI32                  (4)

/******************************************************************************/
/* Macros*/
/******************************************************************************/

#define UWSUCCESS(r)            ( (r)==UWRESULTCODE_SUCCESS)
#define UWCONTINUE(r)           ( (r)==UWRESULTCODE_CONTINUE)
#define UWFAIL(r)               ( (r)>=UWRESULTCODE_LOWEST_FAIL_VALUE)

/******************************************************************************/
/* Enum Typedefs*/
/******************************************************************************/

/*============================================================================*/
/* This enum collects all generic success result codes */
/*============================================================================*/
enum
{
    UWRESULTCODE_OK                     = UWRESULTCODE_SUCCESS
   ,UWRESULTCODE_CONTINUE

   /*
   ,UWRESULTCODE_
   */
};

/******************************************************************************/
/* Simple (non struct/union) Typedefs*/
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
