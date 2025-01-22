/*
 * FILE NAME : condition variable
 * DEC       : This is a sample to demonstrate a condition variable.
 *
 */
/*==============INCLUDES=============*/
#include "types.h"
#include "comfun.h"
#include <pthread.h>
/*==============INTERNAL=============*/
static const char const* gsCpCcFileName = "CONDVAR.C";

/*=============Defines============*/

#define TNG_PRODUCTION_MAX_LIMIT 10
#define TNG_PRODUCTION_MIN_LIMIT 0
/*===============MACROS==============*/

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

/*=============GLOBAL============*/
pthread_mutex_t mtxConsumerRecvSync;
pthread_cond_t  cndConsumer;
pthread_cond_t  cndProducer;
UINT32 gui32Resource;
/*=============PROTOTYPES============*/

PVOID COND_ConsumerTask ( PVOID pvArgs );
PVOID COND_ProducerTask ( PVOID pvArgs );
/*=============DEFINITIONS===========*/

/*
 * API NAME: Main entery.
 * DES: The entry point of the program.
 */
INT32 main ( INT32 argc, PCHAR argv[])
{
    /* Loc variables to hold two task's objects */
    pthread_t   hThread1,
                hThread2;
    PVOID       pvReturn;
    
    /* creating a common mutex to sync both consumer and producer */
    CHECK_RETURN(pthread_mutex_init(&mtxConsumerRecvSync, OS_NULL));

    /* Two condition variables to ensure data consistency. */
    CHECK_RETURN(pthread_cond_init(&cndConsumer, OS_NULL));
    CHECK_RETURN(pthread_cond_init(&cndProducer, OS_NULL));

    /* Creating two threads */
    CHECK_RETURN(pthread_create(&hThread1, OS_NULL, COND_ConsumerTask, OS_NULL ));
    CHECK_RETURN(pthread_create(&hThread2, OS_NULL, COND_ProducerTask, OS_NULL ));

    /* waiting till the two threads self destruct and clear their resources. */
    CHECK_RETURN(pthread_join(hThread1, &pvReturn));
    CHECK_RETURN(pthread_join(hThread2, &pvReturn));

    /* Cleaning the sync variables */
    CHECK_RETURN(pthread_mutex_destroy ( &mtxConsumerRecvSync ));
    CHECK_RETURN(pthread_cond_destroy ( &cndConsumer ));
    CHECK_RETURN(pthread_cond_destroy ( &cndProducer ));

    return OS_NO_ERROR;
}

/*
 * API NAME: Condition consumer task.
 * DES: Task to consume a resource with sync.
 */
PVOID COND_ConsumerTask ( PVOID pvArgs )
{
    /* Infinite loop which consumes "gui32Resource" global resource */    
    while ( 1 )
    {
        /* To synchronize the "gui32Resource" access between created two threads */    
        pthread_mutex_lock(&mtxConsumerRecvSync);

        /* Wait infinity till the "gui32Resource" is available to access */
        while ( TNG_PRODUCTION_MIN_LIMIT >= gui32Resource)
        {
            OS_MessageLogging("%s %d>$TNG$<WT-C{CL[%d]ML[%d]}>",
                                gsCpCcFileName,
                                __LINE__,
                                gui32Resource,
                                TNG_PRODUCTION_MIN_LIMIT );

            /* Condition variable wait. Unlocks "mtxConsumerRecvSync" variable to do the 
             *  producing work as there is no resource to consume.
             */
            pthread_cond_wait( &cndProducer , &mtxConsumerRecvSync );
        }

        /* Simple resource consumption */    
        --gui32Resource;

        OS_MessageLogging("%s %d>$TNG-%s$<CNS[%d]>"
                            , gsCpCcFileName
                            , __LINE__
                            , __FUNCTION__
                            , gui32Resource );

        pthread_mutex_unlock(&mtxConsumerRecvSync);
        /* Signaling the condition variable which might be waiting in other thread to resume it. */
        pthread_cond_signal( &cndConsumer );
    }

    return OS_NULL;
}

/*
 * API NAME: Condition producer task
 * DES: Task to produce a resource with sync.
 */
PVOID COND_ProducerTask ( PVOID pvArgs )
{
    /* Infinite loop which produces "gui32Resource" global resource */ 
    while ( 1 )
    {
        /* To synchronize the "gui32Resource" access between created two threads */  
        pthread_mutex_lock(&mtxConsumerRecvSync);

        /* Wait infinity till the "gui32Resource" is available to put */
        while ( TNG_PRODUCTION_MAX_LIMIT <= gui32Resource )
        {
           OS_MessageLogging("%s %d>$TNG$<WT-P{CL[%d]ML[%d]}>",
                                gsCpCcFileName,
                                __LINE__,
                                gui32Resource,
                                TNG_PRODUCTION_MAX_LIMIT );

            /* Condition variable wait. Unlocks "mtxConsumerRecvSync" variable to do the 
             *  consuming work as there is no space to put the resource. 
             */
           pthread_cond_wait ( &cndConsumer ,&mtxConsumerRecvSync );
        }

        /* Simple resource Production */
        ++gui32Resource;

        OS_MessageLogging("%s %d>$TNG-%s$<PROD[%d]>"
                            , gsCpCcFileName
                            , __LINE__
                            , __FUNCTION__
                            , gui32Resource );

        /* Signaling the condition variable which might be waiting in other thread to resume it. */
        pthread_cond_signal( &cndProducer );
        pthread_mutex_unlock(&mtxConsumerRecvSync);
    }

    return OS_NULL;
}

