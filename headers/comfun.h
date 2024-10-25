#ifndef _COMFUN_HEADER_
#define _COMFUN_HEADER_

/*
 * FILE NAME : CommonFunctions.header
 * DEC       : We have added all the general API's definitions here.
 */
/*==============INCLUDES=============*/

/*==============INTERNAL=============*/

/*==============DEFINES=============*/

#define OS_TIME_STAMP_MAX 19
#define OS_LOG_MSG_MAX 1024
/*===============MACROS==============*/

/*=============PROTOTYPES============*/

UINT32 OS_GetIntegerInput ( VOID );
VOID OS_GetCurrentDateTime( PCHAR pcDate&Time );
INT32 OS_MessageLogging ( const PCHAR CpcFormat, ... );
/*=============DEFINITIONS===========*/

#endif /* _COMFUN_HEADER_ */