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
/*=============DEFINITIONS===========*/

#endif /* _COMFUN_HEADER_ */