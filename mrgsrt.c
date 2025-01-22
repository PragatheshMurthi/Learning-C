/*
 * FILE NAME : MRGSRT.C
 * DEC       : sorts a given array using merge sort algorithm.
 */
/*==============INCLUDES=============*/
#include "types.h"
#include "comfun.h"
/*==============INTERNAL=============*/
static const char const* gsCpCcFileName = "MRGSRT.C";

/*===============MACROS==============*/

#define OS_ENABLE_TRACE_PRINTS
/*============= ENUM  ===========*/

typedef enum tagsorttype
{
    /* 0x01 */      OS_SORT_TYPE_MERGE
    /* 0x01 */  ,   OS_SORT_TYPE_QUICK      
}OS_SORT_TYPE_ENUM;

/*=============STRUCTURES===========*/

/*=============PROTOTYPES============*/

OS_ERROR_CODE OS_SortArray ( PUINT32 paui32Array, UINT8 ui8ASize, OS_SORT_TYPE_ENUM enSortType );

/* APIs related to merge sort. */
OS_ERROR_CODE OS_MergeSortArray( PUINT32 paui32Array, UINT8 ui8ASize );
OS_ERROR_CODE OS_Merge ( PUINT32 paui32DestArr, UINT32 ui32DestSZ,\
                         PUINT32 paui32LeftArr, UINT32 ui32LeftSZ, \
                         PUINT32 paui32RightArr, UINT32 ui32RightSZ  );

/* APIs related to Quick sort */
OS_ERROR_CODE OS_QuickSort ( PUINT32 paui32Array, UINT8 ui8Start, UINT8 ui8ASize );
UINT16 OS_ArrangePivot ( PUINT32 paui32Array, UINT8 ui8Start, UINT8 ui8ASize );

/*=============DEFINITIONS===========*/

INT32 main ( INT32 argc, PCHAR argv[])
{
    UINT32  aui32NSarray[21] = { 10, 12, 9 , 7 , 20, 22, 21, 23, 0, 10, 12, 4, 1, 30, 5, 8, 31, 3, 90, 1, 3};
    UINT8   ui8PrintLp = 0,
            ui8SizeOfA = sizeof(aui32NSarray)/sizeof(aui32NSarray[0]);

    OS_SortArray( aui32NSarray, ui8SizeOfA, OS_SORT_TYPE_QUICK );
    
    while ( ui8PrintLp < ui8SizeOfA )
    {
        printf("%d ", aui32NSarray[ui8PrintLp] );
        ++ui8PrintLp;
    }

    return 0;
}

/*
 * API NAME: OS_SortArray
 * DES: To sort the given array in different sorting algorithms.
 */
OS_ERROR_CODE OS_SortArray ( PUINT32 paui32Array, UINT8 ui8ASize, OS_SORT_TYPE_ENUM enSortType )
{

    if ( OS_SORT_TYPE_MERGE == enSortType )
    {
        OS_MergeSortArray ( paui32Array, ui8ASize );
    }
    else if ( OS_SORT_TYPE_QUICK == enSortType )
    {
        OS_QuickSort ( paui32Array, 0, ui8ASize );
    }

    return OS_NO_ERROR;
}

/*
 * API NAME: OS_MergeSortArray
 * DES: To Sort two given arrays using merge sort algorithm
 */
OS_ERROR_CODE OS_MergeSortArray( PUINT32 paui32Array, UINT8 ui8ASize )
{
    /* Dividing the two arrays equally with their size */    
    UINT32  ui32LeftArraySz = ui8ASize / 2;
    UINT32  ui32RightArraySz = ( ui8ASize - ui32LeftArraySz );

#ifdef OS_ENABLE_TRACE_PRINTS
    OS_MessageLogging("%s %d>$TNG-SA$<AAS[%d]LAS[%d]RAS[%d]>",gsCpCcFileName,__LINE__,ui8ASize,ui32LeftArraySz, ui32RightArraySz);
#endif

    /* If the given actual array size is 1 then there is array to divide. In the recursion next the array will be sorted and merged. */
    if ( 1 >= ui8ASize  )
    {
        return OS_NO_ERROR;
    }
    else
    {
        /* Allocating new array for storing the divided array */ 
        PUINT32 paui32LeftArray = OS_Allocate ( ui32LeftArraySz * sizeof(paui32Array[0])),
                paui32RightArray = OS_Allocate ( ui32RightArraySz * sizeof(paui32Array[0]));

        memcpy ( paui32LeftArray, paui32Array, (ui32LeftArraySz * sizeof(paui32Array[0])));
        memcpy ( paui32RightArray, &(paui32Array[ ui32LeftArraySz ]), ( ui32RightArraySz * sizeof(paui32Array[0])));

        /* Calling the function */
        OS_MergeSortArray( paui32LeftArray,  ui32LeftArraySz );
        OS_MergeSortArray( paui32RightArray, ui32RightArraySz );

        OS_Merge ( paui32Array, ui8ASize, paui32LeftArray, ui32LeftArraySz, paui32RightArray, ui32RightArraySz );

        OS_Free( paui32LeftArray );
        OS_Free( paui32RightArray );

        return OS_NO_ERROR;
    }

    return OS_ERROR_BAD_PARAMETER;
}

OS_ERROR_CODE OS_Merge ( PUINT32 paui32DestArr, UINT32 ui32DestSZ,\
                         PUINT32 paui32LeftArr, UINT32 ui32LeftSZ, \
                         PUINT32 paui32RightArr, UINT32 ui32RightSZ  )
{
    UINT32  ui32DestLp  = 0,
            ui32RtLp    = 0,
            ui32LftLp   = 0;

    while (( ui32LftLp < ui32LeftSZ ) && ( ui32RtLp < ui32RightSZ ))
    {

#ifdef OS_ENABLE_TRACE_PRINTS        
        OS_MessageLogging("%s %d>$TNG$<AS{%d:%d:%d}-LT{%d:%d}-RT{%d:%d}-D{%d:%d}>"
                                ,   gsCpCcFileName
                                ,   __LINE__
                                ,   ui32LeftSZ
                                ,   ui32RightSZ
                                ,   ui32DestSZ    

                                ,   paui32LeftArr[ui32LftLp]
                                ,   ui32LftLp
                                ,   paui32RightArr[ui32RtLp]
                                ,   ui32RtLp
                                ,   paui32DestArr[ui32DestLp]
                                ,   ui32DestLp);
#endif                                

        if ( paui32LeftArr[ui32LftLp] < paui32RightArr[ui32RtLp] )
        {
            paui32DestArr[ui32DestLp] = paui32LeftArr[ui32LftLp];
            ++ui32LftLp;
        }
        else
        {
            paui32DestArr[ui32DestLp] = paui32RightArr[ui32RtLp];
            ++ui32RtLp;
        }
        ++ui32DestLp;
    }

    while ( ( ui32LftLp < ui32LeftSZ ) )
    {

#ifdef OS_ENABLE_TRACE_PRINTS
        OS_MessageLogging("%s %d>$TNG$<ASL{%d:%d}-LT{%d:%d}-D{%d:%d}>"
                                ,   gsCpCcFileName
                                ,   __LINE__
                                ,   ui32LeftSZ
                                ,   ui32DestSZ    

                                ,   paui32LeftArr[ui32LftLp]
                                ,   ui32LftLp
                                ,   paui32DestArr[ui32DestLp]
                                ,   ui32DestLp);
#endif                                

        paui32DestArr[ui32DestLp] = paui32LeftArr[ui32LftLp];
        ++ui32LftLp;
        ++ui32DestLp;
    }

    while ( ( ui32RtLp < ui32RightSZ ) )
    {

#ifdef OS_ENABLE_TRACE_PRINTS
        OS_MessageLogging("%s %d>$TNG$<ASR{%d:%d}-RT{%d:%d}-D{%d:%d}>"
                        ,   gsCpCcFileName
                        ,   __LINE__
                        ,   ui32RightSZ
                        ,   ui32DestSZ    

                        ,   paui32RightArr[ui32RtLp]
                        ,   ui32RtLp
                        ,   paui32DestArr[ui32DestLp]
                        ,   ui32DestLp);
#endif                        

        paui32DestArr[ui32DestLp] = paui32RightArr[ui32RtLp];
        ++ui32RtLp;
        ++ui32DestLp;
    }
    
    ui32DestLp = 0;

#ifdef OS_ENABLE_TRACE_PRINTS
    while ( ui32DestLp < ui32DestSZ )
    {
        OS_MessageLogging("%s %d>$TNG$< FA [%d] >",gsCpCcFileName,__LINE__, paui32DestArr[ui32DestLp] );
        ++ui32DestLp;
    }
#endif

    return OS_NO_ERROR;
}

/*
 * API NAME: OS_QuickSort
 * DES: To sort the given array with quick sort algorithm
 */
OS_ERROR_CODE OS_QuickSort ( PUINT32 paui32Array, UINT8 ui8Start, UINT8 ui8ASize )
{
    UINT16  ui16CurrPivotPos;

    if ( ui8Start >=  ( ui8ASize - 1 ))
    {
        return OS_NO_ERROR;
    }

    ui16CurrPivotPos = OS_ArrangePivot ( paui32Array, ui8Start, ui8ASize );

#ifdef OS_ENABLE_TRACE_PRINTS
    OS_MessageLogging("%s %d>$TNG$<I{ST[%d]E[%d]}-CPP[%d]>"
                            ,   gsCpCcFileName
                            ,   __LINE__
                            ,   ui8Start 
                            ,   ui8ASize
                            ,   ui16CurrPivotPos );
#endif

    OS_QuickSort ( paui32Array, ui8Start, ui16CurrPivotPos );
    OS_QuickSort ( paui32Array, ( ui16CurrPivotPos + 1 ) , ui8ASize );

    return OS_NO_ERROR;

}

/*
 * API NAME: OS_ArrangePivot
 * DES: To find the pivot and arrange the elements to right and left side of pivot.
 */
UINT16 OS_ArrangePivot ( PUINT32 paui32Array, UINT8 ui8Start, UINT8 ui8ASize )
{

    UINT16  ui16Destination = 0,
            ui16CheckSource = 0;
    UINT32  ui32PivotVal    = paui32Array [ ( ui8ASize - 1 ) ];

    while ( ui16CheckSource < ( ui8ASize - 1 ))
    {

#ifdef OS_ENABLE_TRACE_PRINTS        
        OS_MessageLogging("%s %d>$TNG$<IV{CS[%d:%d]D[%d]}-VAL{S[%d]P[%d]D[%d]}>"
                                    ,   gsCpCcFileName
                                    ,   __LINE__

                                    ,   ui16CheckSource 
                                    ,   ( ui8ASize - 1 )
                                    ,   ui16Destination

                                    ,   paui32Array [ ui16CheckSource ]
                                    ,   ui32PivotVal         
                                    ,   paui32Array [ ui16Destination ] );
#endif                                    

        if ( paui32Array [ ui16CheckSource ] <= ui32PivotVal )
        { 
            OS_Swap( &paui32Array [ ui16Destination ], &paui32Array [ ui16CheckSource ] );
            ++ui16Destination;
        }
        ++ui16CheckSource;
    }

    OS_Swap ( &paui32Array [ ui16Destination ] , &paui32Array [ ( ui8ASize - 1 ) ] );
    
#ifdef OS_ENABLE_TRACE_PRINTS
    ui16CheckSource = ui8Start;
    while ( ui16CheckSource < ui8ASize )
    {
        OS_MessageLogging("%s %d>$TNG$< FA [%d] >",gsCpCcFileName,__LINE__, paui32Array [ ui16CheckSource ] );
        ++ui16CheckSource;
    }
#endif
    return ui16Destination;
}