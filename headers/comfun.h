#ifndef _COMFUN_HEADER_
#define _COMFUN_HEADER_

/*
 * FILE NAME : CommonFunctions.header
 * DEC       : We have added all the general API's definitions here.
 */
/*==============INCLUDES=============*/

#include <stdarg.h>
#include <time.h>
/*==============INTERNAL=============*/

/*==============DEFINES=============*/

#define OS_TIME_STAMP_MAX 19
#define OS_LOG_MSG_MAX 1024

/*======== STRUCT AND UNION ==========*/

/* 
 * This structure is used to seperate the bits from the unsigned variable.
 * If this along with Union of integer used then the bits of the integer can be 
 * accessed using the bitfield variables of the structure after assigning the
 * whole value to the integer.
*/
typedef struct tagetngbits
{
    UINT32 ui32Bit0:1;
    UINT32 ui32Bit1:1;
    UINT32 ui32Bit2:1;
    UINT32 ui32Bit3:1;
    UINT32 ui32Bit4:1;
    UINT32 ui32Bit5:1;
    UINT32 ui32Bit6:1;
    UINT32 ui32Bit7:1;
    UINT32 ui32Bit8:1;
    UINT32 ui32Bit9:1;
    UINT32 ui32Bit10:1;
    UINT32 ui32Bit11:1;
    UINT32 ui32Bit12:1;
    UINT32 ui32Bit13:1;
    UINT32 ui32Bit14:1;
    UINT32 ui32Bit15:1;
    UINT32 ui32Bit16:1;
    UINT32 ui32Bit17:1;
    UINT32 ui32Bit18:1;
    UINT32 ui32Bit19:1;
    UINT32 ui32Bit20:1;
    UINT32 ui32Bit21:1;
    UINT32 ui32Bit22:1;
    UINT32 ui32Bit23:1;
    UINT32 ui32Bit24:1;
    UINT32 ui32Bit25:1;
    UINT32 ui32Bit26:1;
    UINT32 ui32Bit27:1;
    UINT32 ui32Bit28:1;
    UINT32 ui32Bit29:1;
    UINT32 ui32Bit30:1;
    UINT32 ui32Bit31:1;
}eTNG_BITS_STRUCT;

typedef union tagetngstorebit
{
    UINT32 ui32WholeBits;       
    eTNG_BITS_STRUCT stBits; 
}eTNG_STORE_BITS_UNION;

/*===============MACROS==============*/

/* macro for a safe validation */
#define EXAMINE_ERROR(x)    OS_ERROR_CODE enErrorCode = x;                             \
                            if ( enErrorCode != OS_NO_ERROR )                          \
                            {                                                           \
                                OS_MessageLogging("%s %d>$TNG-ERR$<KO{F[%s]ES[%s]}>",gsCpCcFileName,__LINE__,(#x),OS_Error2Str (enErrorCode)); \
                                if ( OS_TRUE ==  OS_IsFatal ( enErrorCode ))             \
                                { return enErrorCode; }                                 \
                            }

/*=============PROTOTYPES============*/

UINT32 OS_GetIntegerInput ( VOID );
VOID OS_GetCurrentDateTime( PCHAR pcDateTime );
INT32 OS_MessageLogging ( const PCHAR CpcFormat, ... );
CPCHAR OS_FindMonString ( UINT8 ui8Month );
eBOOLEAN OS_IsFatal( OS_ERROR_CODE enErrorCode );
CPCHAR OS_Error2Str ( OS_ERROR_CODE enErrorCode );
PVOID OS_Allocate ( UINT32 ui32Size );
VOID OS_Free ( PVOID pvAddress );
OS_ERROR_CODE OS_Swap ( PUINT32 pui32One, PUINT32 pui32Two );
/*=============DEFINITIONS===========*/

#endif /* _COMFUN_HEADER_ */