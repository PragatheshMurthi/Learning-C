/*
 * FILE NAME : STACK.C
 * DEC       : Implement the stack operation using array and linked list.
 */
/*==============INCLUDES=============*/
#include "types.h"
#include "comfun.h"
/*==============INTERNAL=============*/
static const char const* gsCpCcFileName = "STATIC.C";
static OS_INSTANCE gshStackInstance;
/*===============MACROS==============*/
#define OS_STACK_MAX_SIZE 20
#define OS_STACK_DATA_TYPE UINT32

/*============= ENUM  ===========*/

typedef enum tagstackstateenum
{
    /* 0x00 */      OS_STACK_STATE_INVALID      
    /* 0x01 */  ,   OS_STACK_STATE_FULL
    /* 0x02 */  ,   OS_STACK_STATE_EMPTY
    /* 0x03 */  ,   OS_STACK_STATE_FREE
    /* 0x04 */  ,   OS_STACK_STATE_MAX
}OS_STACK_STATE_ENUM;

/*=============STRUCTURES===========*/
typedef struct tagInternalStackDataStruct
{
    PVOID pvDataStackBaseAdd;
    UINT32 ui32TopPointer;

    UINT16  ui16DataSize;
    UINT16  ui16DataDepth;

}OS_INTERN_STACK_DATA_STRUCT;

/*=============PROTOTYPES============*/

OS_INSTANCE OS_CreateStackInstance ( UINT32 ui32StackDataSize, UINT32 ui32StackMaxDepth );
OS_ERROR_CODE OS_DeleteStackInstance ( OS_INSTANCE hStackInstance );
OS_ERROR_CODE OS_PushToStack ( OS_INSTANCE hStackInstance, PVOID pvValue );
OS_ERROR_CODE OS_PopFromStack ( OS_INSTANCE hStackInstance, PVOID pvValue );
OS_STACK_STATE_ENUM OS_GetStackState ( OS_INSTANCE hStackInstance );
OS_INSTANCE OS_MakeAsCurrentInstance ( OS_INSTANCE hCurrentStackInstance );

/*=============DEFINITIONS===========*/

INT32 main ( INT32 argc, PCHAR argv[])
{
    OS_INSTANCE hStackInstance      = OS_CreateStackInstance( sizeof(OS_STACK_DATA_TYPE), OS_STACK_MAX_SIZE );
    UINT32      ui32SampleData[20]  = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    if ( OS_INVALID_INSTANCE != hStackInstance )
    {
        UINT8 ui8LocLp = 0;

        OS_MessageLogging("%s %d>$TNG$<INSERTION START>",gsCpCcFileName,__LINE__);
        
        while ( ui8LocLp < OS_STACK_MAX_SIZE )
        {
            OS_PushToStack ( hStackInstance, &( ui32SampleData[ui8LocLp] ));
            printf("%u ", ui32SampleData[ui8LocLp] );
            ++ui8LocLp;
        }

        printf("\n");
        OS_MessageLogging("%s %d>$TNG$<EXTRACTION START>",gsCpCcFileName,__LINE__);
        
        ui8LocLp = 0;

        while ( ui8LocLp < OS_STACK_MAX_SIZE )
        {
            OS_PopFromStack ( hStackInstance, &( ui32SampleData[ui8LocLp] ));
            printf("%u ", ui32SampleData[ui8LocLp] );
            ++ui8LocLp;
        }

        getch();
        return OS_TRUE;
    }

    return OS_FALSE;
}

/*
 * API NAME: OS_CreateInstance()
 * DES: We can separately create instance to create and maintain multiple stack containers.
 */
OS_INSTANCE OS_CreateStackInstance ( UINT32 ui32StackDataSize, UINT32 ui32StackMaxDepth )
{
    if ( !gshStackInstance )
    {
        OS_INTERN_STACK_DATA_STRUCT* pstLocIntStackPtr = OS_NULL;
        pstLocIntStackPtr = OS_Allocate ( sizeof( OS_INTERN_STACK_DATA_STRUCT ));

        if ( OS_NULL == pstLocIntStackPtr )
        {
            OS_MessageLogging("%s %d>$TNG-STK-CRE$<KO-ALLOC-SID{SZ[%u]}}>"
                                ,   gsCpCcFileName
                                ,   __LINE__
                                ,   sizeof( OS_INTERN_STACK_DATA_STRUCT ));
            return OS_INVALID_INSTANCE;
        }
        pstLocIntStackPtr->pvDataStackBaseAdd   =   OS_Allocate ( ui32StackMaxDepth * ui32StackDataSize );
        
        if ( OS_NULL == pstLocIntStackPtr->pvDataStackBaseAdd )
        {
            OS_Free( pstLocIntStackPtr->pvDataStackBaseAdd );

            OS_MessageLogging("%s %d>$TNG-STK-CRE$<KO-ALLOC-SDP{SZ[%u]}}>"
                                ,   gsCpCcFileName
                                ,   __LINE__
                                ,   ( ui32StackMaxDepth * ui32StackDataSize ));
            return OS_INVALID_INSTANCE;
        }

        pstLocIntStackPtr->ui16DataSize         =   ui32StackDataSize;
        pstLocIntStackPtr->ui16DataDepth        =   ui32StackMaxDepth;
        /* pstLocIntStackPtr->ui32TopPointer       =   0; */ //OS_ALLOCATE returns memset value

        gshStackInstance = (PVOID)pstLocIntStackPtr;
    }
    else
    {
        OS_MessageLogging("%s %d>$TNG$<KO-ALREADY-INITIALIZED>",gsCpCcFileName,__LINE__);
    }

    return gshStackInstance;
}

/*
 * API NAME: OS_DeleteInstance()
 * DES: Deallocating the instance data.
 */
OS_ERROR_CODE OS_DeleteStackInstance ( OS_INSTANCE hStackInstance )
{
    if ( !hStackInstance )
    {
        OS_INTERN_STACK_DATA_STRUCT* pstLocIntStackPtr = (OS_INTERN_STACK_DATA_STRUCT*)hStackInstance;

        OS_Free ( pstLocIntStackPtr->pvDataStackBaseAdd );
        OS_Free( pstLocIntStackPtr );
    }
    else
    {
        OS_MessageLogging("%s %d>$TNG$<KO-NOT-INITIALIZED>",gsCpCcFileName,__LINE__);
        return OS_ERROR_MODULE_NOT_INITIALIZED;
    }

    return OS_NO_ERROR;
}
/*
 * API NAME: eOS_PushToStack()
 * DES: Inserting an element to data structure.
 */
OS_ERROR_CODE OS_PushToStack ( OS_INSTANCE hStackInstance, PVOID pvValue )
{
    OS_INTERN_STACK_DATA_STRUCT*    pstLocStackInternal = (OS_INTERN_STACK_DATA_STRUCT*)hStackInstance;
    PUINT8                          pui8StackBaseAdd    = pstLocStackInternal ?\
                                                          pstLocStackInternal->pvDataStackBaseAdd :\
                                                          OS_NULL;
    UINT16                          ui16MaxDepth        = pstLocStackInternal ?\
                                                          pstLocStackInternal->ui16DataDepth :\
                                                          0;                    
    UINT32                          ui32TopPos          = pstLocStackInternal ?\
                                                          pstLocStackInternal->ui32TopPointer :\
                                                          ui16MaxDepth;
    
    if (( OS_NULL == pstLocStackInternal ) || ( ui16MaxDepth <= ui32TopPos ))
    {
        OS_MessageLogging("%s %d>$TNG-PtS$<KO{LSI[%lX]TP[%d]MAX[%d]}>"
                            ,   gsCpCcFileName
                            ,   __LINE__
                            ,   pstLocStackInternal 
                            ,   ui32TopPos
                            ,   ui16MaxDepth );
        return OS_ERROR_BAD_PARAMETER;
    }
    
    memcpy (( pui8StackBaseAdd + ( ui32TopPos * pstLocStackInternal->ui16DataSize )), pvValue,  pstLocStackInternal->ui16DataSize );
    
    ++pstLocStackInternal->ui32TopPointer;

    return OS_NO_ERROR;
}

/*
 * API NAME: eOS_PopFromStack()
 * DES: Recovering an element from stack data structure.
 */
OS_ERROR_CODE OS_PopFromStack ( OS_INSTANCE hStackInstance, PVOID pvValue )
{
    OS_INTERN_STACK_DATA_STRUCT*    pstLocStackInternal = (OS_INTERN_STACK_DATA_STRUCT*)hStackInstance;
    PUINT8                          pui8StackBaseAdd    = pstLocStackInternal ?\
                                                          pstLocStackInternal->pvDataStackBaseAdd :\
                                                          OS_NULL;
    UINT16                          ui16MaxDepth        = pstLocStackInternal ?\
                                                          pstLocStackInternal->ui16DataDepth :\
                                                          0;                    
    UINT32                          ui32TopPos          = pstLocStackInternal ?\
                                                          pstLocStackInternal->ui32TopPointer :\
                                                          0;
    
    if (( OS_NULL == pstLocStackInternal ) || ( 0 == ui32TopPos ))
    {
        OS_MessageLogging("%s %d>$TNG-PfS$<KO{LSI[%lX]TP[%d]MAX[%d]}>"
                            ,   gsCpCcFileName
                            ,   __LINE__
                            ,   pstLocStackInternal 
                            ,   ui32TopPos
                            ,   ui16MaxDepth );
        return OS_ERROR_BAD_PARAMETER;
    }
    
    --pstLocStackInternal->ui32TopPointer;
    --ui32TopPos;

    memcpy ( pvValue, ( pui8StackBaseAdd + ( ui32TopPos * pstLocStackInternal->ui16DataSize )),  pstLocStackInternal->ui16DataSize );
    
    return OS_NO_ERROR;
}

/*
 * API NAME: OS_GetStackState (  )
 * DES: To validate the stack is filled or free or have space?
 */
OS_STACK_STATE_ENUM OS_GetStackState ( OS_INSTANCE hStackInstance )
{
    OS_INTERN_STACK_DATA_STRUCT*    pstLocStackInternal = (OS_INTERN_STACK_DATA_STRUCT*)hStackInstance;
    UINT16                          ui16MaxDepth        = pstLocStackInternal ? pstLocStackInternal->ui16DataDepth : 0;
    UINT32                          ui32LocTopPointer   = pstLocStackInternal ? pstLocStackInternal->ui32TopPointer : 0;
    if (( OS_NULL == pstLocStackInternal ) || ( 0 == ui16MaxDepth ))
    {
        OS_MessageLogging("%s %d>$TNG-PSS$<KO{LSI[%lX]MAX[%d]}>"
                            ,   gsCpCcFileName
                            ,   __LINE__
                            ,   pstLocStackInternal 
                            ,   ui16MaxDepth );

        return OS_STACK_STATE_INVALID;                    
    }

    if ( 0 == ui32LocTopPointer )
    {
        return OS_STACK_STATE_EMPTY;
    }
    else if ( ui16MaxDepth <= ui32LocTopPointer )
    {
        return OS_STACK_STATE_FULL;
    }
    else 
    {
        return OS_STACK_STATE_FREE;
    }

    return OS_STACK_STATE_INVALID;
}

/*
 * API NAME: OS_MakeAsCurrentInstance()
 * DES: To make the given instance as the current instance.
 */
OS_INSTANCE OS_MakeAsCurrentInstance ( OS_INSTANCE hCurrentStackInstance )
{
    OS_INSTANCE hPreviousStackInstance = OS_INVALID_INSTANCE;

    if ( gshStackInstance )
    {
        hPreviousStackInstance = gshStackInstance;
    }

    gshStackInstance = hCurrentStackInstance;

    return hPreviousStackInstance;
}