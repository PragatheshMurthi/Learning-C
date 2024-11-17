/*
 * This is a program to convert string to number without using atoi
 */
/*===============INCLUDES============*/

#include "types.h"

/* including c source file is not advisable. But since I dont have a make 
 * system, anyway it sucks in windows 32bit environment, Iam including c file.
 */
#ifndef TNG_OWN_MAKE_SUPPORTED
//#include <comfun.c>
#else
#include <comfun.h> 
#endif /* #ifndef TNG_OWN_MAKE_SUPPORTED */

/*==============INLINE===============*/

CPCHAR gsCpcFileName = "STR2DEC.C";
/*==========MACROS====================*/

#define TST_NUMERIC_ASCII_START '0'
#define TST_NUMERIC_ASCII_END   '9'
/*==========PROTOTYPES================*/

TST_ERROR_CODE TST_ConvertString2Deci ( CPCHAR cpcDecimalString, TST_RETURN* pstOriginalRet );
UINT32  TST_NthRootOfBase ( UINT32 ui32Base, UINT32 ui32Pow );
/*==========DEFINITIONS===============*/

/*
 * API NAME: main
 * DES: main
 */
INT32 main (INT32 argc, PCHAR argv[])
{
    TST_RETURN  stGenericVar        = {0};
    CHAR        acInputInteger[20];
    UINT32      ui32Integer        = 12;
    UINT8       ui8LocLooping      = 0;
     
    OS_MessageLogging("%s %d>$TNG$<ENTER THE INPUT NUMERIC STRING>",gsCpcFileName, __LINE__ );

    while ( 1 )
    {
        scanf("%s",acInputInteger); 
        if ( TST_NO_ERROR == TST_ConvertString2Deci ( acInputInteger , &stGenericVar ))
        {
            break;
        }
        memset (&stGenericVar, 0, sizeof(stGenericVar));
        printf("BAD PARAM ENTERED: RE-ENTER \n");
    }

    if ( stGenericVar.enReturnType == TST_FLOAT )
    {
        printf ("FLT[%f]",stGenericVar.genDatatype.vfReturn );
    }
    else if ( stGenericVar.enReturnType == TST_UNSIGNED_INT )
    {
        printf ("UINT[%u]",stGenericVar.genDatatype.ui32Return );
    }
    else if ( stGenericVar.enReturnType == TST_INT )
    {
        printf ("INT[%d]",stGenericVar.genDatatype.i32Return );        
    }
    
    getchar();
    getchar();
    return 0;
}

/*
 * API NAME: TST_ConvertString2Deci
 * DES: To find the numerical value from the given string input
 */
TST_ERROR_CODE TST_ConvertString2Deci ( CPCHAR cpcDecimalString, TST_RETURN* pstOriginalRet )
{
    UINT32  ui32Integer    = 0;
    UINT8   ui8LocLooping  = 0;
    UINT8   ui8DotCount     = 0;
    TST_RETURN stOriginalRet;

    /* Validate weather the given string is negative or not*/
    if ( '-' == cpcDecimalString [ ui8LocLooping ] )
    {
        pstOriginalRet->enReturnType = TST_INT;
        ++ui8LocLooping;
    }
    else
    {
        pstOriginalRet->enReturnType = TST_UNSIGNED_INT;
    }

    while ( '\0' != cpcDecimalString [ ui8LocLooping ] )
    {
        if (( TST_NUMERIC_ASCII_START <= cpcDecimalString [ ui8LocLooping ] ) &&\
            ( TST_NUMERIC_ASCII_END >= cpcDecimalString [ ui8LocLooping ] ))
        {
            UINT8 ui8CurrDecVal = cpcDecimalString [ ui8LocLooping ] - TST_NUMERIC_ASCII_START;
            
/* Faced lvalue required compilation error ( Need to debug ) - 20/10/2024 - 17:56 */
#if 0
            ( TST_INT == pstOriginalRet->enReturnType ) ? pstOriginalRet->genDatatype.i32Return :\
                TST_UNSIGNED_INT == pstOriginalRet->enReturnType ? pstOriginalRet->genDatatype.ui32Return :\
                pstOriginalRet->genDatatype.vfReturn ) *= 10;

            ( TST_INT == pstOriginalRet->enReturnType ? pstOriginalRet->genDatatype.i32Return :\
                TST_UNSIGNED_INT == pstOriginalRet->enReturnType ? pstOriginalRet->genDatatype.ui32Return :\
                pstOriginalRet->genDatatype.vfReturn ) += ui8CurrDecVal;
#else
            if ( TST_INT == pstOriginalRet->enReturnType ) 
            {
                pstOriginalRet->genDatatype.i32Return *= 10;        
                pstOriginalRet->genDatatype.i32Return += ui8CurrDecVal;
            }
            else if (( TST_UNSIGNED_INT == pstOriginalRet->enReturnType ) ||\
                    ( TST_FLOAT == pstOriginalRet->enReturnType ))
            {
                pstOriginalRet->genDatatype.ui32Return *= 10;
                pstOriginalRet->genDatatype.ui32Return += ui8CurrDecVal;
            }
#endif
        }
        else if ( '.' == cpcDecimalString [ ui8LocLooping ] )
        {
            if ( TST_INT == pstOriginalRet->enReturnType )
            {
                return TST_ERROR_BAD_PARAMETER;
            }
            
            pstOriginalRet->enReturnType = TST_FLOAT;
            ui8DotCount = ui8LocLooping;
        }
        else
        {
            return TST_ERROR_BAD_PARAMETER;
        }
        ++ui8LocLooping; 
    }

    if ( ui8DotCount )
    {
        ui8DotCount = ( ui8LocLooping - 1 ) - ui8DotCount ;
        pstOriginalRet->genDatatype.vfReturn = (FLOATV)pstOriginalRet->genDatatype.ui32Return / (FLOATV)TST_NthRootOfBase( 10, ui8DotCount );        
    }

    if ( TST_INT == pstOriginalRet->enReturnType )
    {
        pstOriginalRet->genDatatype.i32Return *= -1;
    }

    return TST_NO_ERROR;
}

/*
 * API NAME: TST_NthRootOfBase
 * DES: To find the n pow m value for given inputs
 */
UINT32  TST_NthRootOfBase ( UINT32 ui32Base, UINT32 ui32Pow )
{
    UINT32  ui32LocMul     = ( ui32Base > ui32Pow ) ? ui32Base : ui32Pow ,
            ui32LocLp      = (( ui32Base > ui32Pow ) ? ui32Pow : ui32Base) - 1,
            ui32LocBase    = ui32LocMul;

    while ( 0 < ui32LocLp )
    {
        ui32LocBase *= ui32LocMul;
        --ui32LocLp;
    }
    return ui32LocBase;
}

