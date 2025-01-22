/*
 * FILE NAME : STACK.C
 * DEC       : Implement the stack operation using array and linked list.
 */
/*==============INCLUDES=============*/
#include "types.h"
#include "comfun.h"
#include <pthread.h>
/*==============INTERNAL=============*/

static const char const* gsCpCcFileName = "ostask.C";

/*===============MACROS==============*/

#define OS_STACK_MAX_SIZE 20
#define OS_STACK_DATA_TYPE UINT32

/*============= ENUM  ===========*/


/*=============Macros===========*/
#define CHECK_RETURN(FUN)   {\
                                int ret = FUN;\
                                if ( ret != 0 )\
                                {\
                                    OS_MessageLogging("%s %d>$TNG-PTHREAD$<F[%s]ERROR{RET[%d]PES[%s]}>"\
                                                    ,   gsCpCcFileName\
                                                    ,   __LINE__\
                                                    ,   #FUN\
                                                    ,   ret\
                                                    ,   strerror(errno));\
                                    return ret;\                
                                }\
                            }
/*=============STRUCTURES===========*/

/*=============PROTOTYPES============*/

OS_ERROR_CODE OS_CreateThread ( VOID );
PVOID OS_TaskCallback ( PVOID );
OS_ERROR_CODE OS_CreateThread ( VOID );
/*=============DEFINITIONS===========*/

/*
 * API NAME: main entry
 * DES: Main entry for the pthread hanson program
 */
INT32 main ( INT32 argc, PCHAR argv[])
{

    OS_CreateThread ( );
}

/*
 * API NAME: OS_CreateThread
 * DES: 
 */
OS_ERROR_CODE OS_CreateThread ( VOID )
{
    pthread_t hThreadID;
    PVOID   pvRetrun;
    pthread_attr_t stAtrribute;

    CHECK_RETURN(pthread_attr_init(&stAtrribute));

    CHECK_RETURN(pthread_attr_setstacksize( &stAtrribute, 500 ));

    CHECK_RETURN(pthread_create(&hThreadID, &stAtrribute, OS_TaskCallback, OS_NULL ));

    CHECK_RETURN(pthread_join ( hThreadID ,&pvRetrun ));
}

/*
 * API NAME: 
 * DES: 
 */
PVOID OS_TaskCallback ( PVOID )
{
    while ( 1 )
    {
        OS_MessageLogging("%s %d>$TNG$<print>",gsCpCcFileName,__LINE__);
        sleep(1);
    }
}