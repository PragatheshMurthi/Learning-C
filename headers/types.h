#ifndef _TYPES_HEADER_
#define _TYPES_HEADER_

/*
 * FILE NAME : AllTheTypes.header
 * DEC       : We have added all the root structures required for the repository is available here.
 */
/*==============INCLUDES=============*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

/*==============DEFINES=============*/

#define OS_TRUE     1
#define OS_FALSE    0
/*==============TYPEDEFS=============*/

/* Basic data types */
typedef float               FLOATV;

typedef int                 INT32;
typedef unsigned int        UINT32;

typedef short int           INT16;
typedef short unsigned int  UINT16;

typedef char                INT8;
typedef unsigned char       UINT8;

typedef char                CHAR;

typedef unsigned int        eBOOLEAN;
/*Pointers*/
typedef char*               PCHAR;

/*Constatnt materiels*/
typedef const char*         CPCHAR;
typedef const char const*   CPCCHAR;

typedef void                VOID;
typedef void*               PVOID;

/*==============UNIONS=============*/

/* Union for desired datatype return */
typedef union tstdatatypes
{
    INT32 i32Return; /* data */
    UINT32  ui32Return;
    FLOATV  vfReturn;    
}TST_DATA_TYPES;

/*==============ENUMERATIONS=============*/

typedef enum tstreturntype
{
    /* 0X1 */       TST_INT
    /* 0X2 */   ,   TST_FLOAT
    /* 0X3 */   ,   TST_UNSIGNED_INT
}TST_RETURN_TYPE;

typedef enum oserrorcode
{
    /* 0X00000000 */       OS_NO_ERROR
    /* 0X00000001 */    ,  OS_ERROR_BAD_PARAMETER
}OS_ERROR_CODE;

/*==============STRUCTURES=============*/

/* This structure can be used for returning either float ,signed int or unsigned int */
typedef struct tstReturn
{
    TST_DATA_TYPES  genDatatype;
    TST_RETURN_TYPE enReturnType;
}TST_RETURN;

#endif /* #ifdef _TYPES_HEADER_ */

