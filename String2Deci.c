/*
 * This is a program to convert string to number without using atoi
 *
/*===============INCLUDES============*/

#include "types.h"
/*==============INLINE===============*/

CPCHAR cpCFileName = "STR2DEC.C";
/*==========MACROS====================*/

#define TST_NUMERIC_ASCII_START '0'
#define TST_NUMERIC_ASCII_END   '9'
/*==========PROTOTYPES================*/

TST_ERROR_CODE TST_ConvertStrint2Deci ( CPCHAR cpcDecimalStrint );
UINT32  TST_NthRootOfBase ( UINT32 ui32Base, UINT32 ui32Pow );
/*==========DEFENITIONS===============*/

/*
 * API NAME: main
 * DES: main
 */
INT32 main (INT32 argc, PCHAR argv[])
{
    TST_RETURN  stGenericVar        = {0};
    CHAR        acInputInteger[20];
    UINT32      ui32Integior        = 0;
    UINT8       ui8LocLoooping      = 0;
    
    printf("ENTER THE INPUT NUMARIC STRING:");
    scanf("%s",acInputInteger);

    if ( TST_NO_ERROR != TST_ConvertStrint2Deci ( acInputInteger , &stGenericVar ))

    if ( stOriginalRet.enReturnType = TST_FLOAT )
    {
        printf ("FLT[%f]",stOriginalRet.genDatatype.vfReturn );
    }
    else if ( stOriginalRet.enReturnType = TST_INT )
    {
        printf ("UINT[%u]",stOriginalRet.genDatatype.ui32Return );
    }
    else if ( stOriginalRet.enReturnType = TST_UNSIGNED_INT )
    {
        printf ("INT[%d]",stOriginalRet.genDatatype.i32Return );        
    }
    
    getchar();
    return 0;
}

/*
 * API NAME: TST_ConvertStrint2Deci
 * DES: To find the numarical value from the given strint input
 */
TST_ERROR_CODE TST_ConvertStrint2Deci ( CPCHAR cpcDecimalStrint, TST_RETURN* pstOriginalRet )
{
    UINT32  ui32Integior    = 0;
    UINT8   ui8LocLoooping  = 0;
    UINT8   ui8DotCount     = 0;
    TST_RETURN stOriginalRet;

    /* Validate weather the given string is negative or not*/
    if ( '-' == cpcDecimalStrint [ ui8LocLoooping ] )
    {
        pstOriginalRet->enReturnType = TST_INT;
        ++ui8LocLoooping;
    }
    else
    {
        pstOriginalRet->enReturnType = TST_UNSIGNED_INT;
    }

    while ( '\0' != cpcDecimalStrint [ ui8LocLoooping ] )
    {
        if (( TST_NUMERIC_ASCII_START <=acInputInteger[ ui8LocLoooping ] ) &&\
            ( TST_NUMERIC_ASCII_END >= cpcDecimalStrint [ ui8LocLoooping ] ))
        {
            UINT8 ui8CurrDecVal = cpcDecimalStrint [ ui8LocLoooping ] - TST_NUMERIC_ASCII_START;
            
            ( TST_INT == pstOriginalRet->enReturnType ? pstOriginalRet->genDatatype.i32Return :\
                TST_UNSIGNED_INT == pstOriginalRet->enReturnType ? pstOriginalRet->genDatatype.ui32Return :\
                pstOriginalRet->genDatatype.fvReturn ) *= 10;

            ( TST_INT == pstOriginalRet->enReturnType ? pstOriginalRet->genDatatype.i32Return :\
                TST_UNSIGNED_INT == pstOriginalRet->enReturnType ? pstOriginalRet->genDatatype.ui32Return :\
                pstOriginalRet->genDatatype.fvReturn ) += ui8CurrDecVal;
        }
        else if ( '.' == cpcDecimalStrint [ ui8LocLoooping ] )
        {
            pstOriginalRet->enReturnType = TST_FLOAT;
            ui8DotCount = ui8LocLoooping;
        }
        ++ui8LocLoooping; 
    }

    if ( pstOriginalRet->enReturnType = TST_FLOAT )
    {
        pstOriginalRet->genDatatype.vfReturn /= (FLOATV)TST_NthRootOfBase( 10, ui8DotCount );        
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
            ui32LocLp      = ( ui32Base > ui32Pow ) ? ui32Pow : ui32Base,
            ui32LocBase    = ui32LocMul;

    while ( 0 < ui32LocLp )
    {
        ui32LocBase *= ui32LocMul;
        --ui32LocLp;
    }
    return ui32LocBase;
}



