#ifndef _TYPES_HEADER_
#define _TYPES_HEADER_

#include <stdio.h>
#include <conio.h>
#include <string.h>

#define OS_TIME_STAMP_MAX 
#define OS_LOG_MSG_MAX 1024

/* Basic data types */
typedef int             INT32;
typedef unsigned int    UINT32;

typedef float           FLOATV;
typedef char            INT8;

typedef unsigned char   UINT8;
typedef char            CHAR;

/*Pointers*/
typedef char* PCHAR;

/*Constatnt materiels*/
typedef const char* CPCHAR;

/* Union for desired datatype return */
typedef union tstdatatypes
{
    INT32 i32Return; /* data */
    UINT32  ui32Return;
    FLOATV  vfReturn;    
}TST_DATA_TYPES;

typedef enum tstreturntype
{
    /* 0X1 */       TST_INT
    /* 0X2 */   ,   TST_FLOAT
    /* 0X3 */   ,   TST_UNSIGNED_INT
}TST_RETURN_TYPE;

/* This sturcture can be used for returning either float ,signed int or unsigned int */
typedef struct tstReturn
{
    TST_DATA_TYPES  genDatatype;
    TST_RETURN_TYPE enReturnType;
}TST_RETURN;

typedef enum tsterrorcode
{
    /* 0X00000000 */        TST_NO_ERROR
    /* 0X00000001 */    ,   TST_ERROR_BAD_PARAMETER
}TST_ERROR_CODE;

#endif /* #ifdef _TYPES_HEADER_ */