/*
 * FILE NAME : BITWISE OPERATIONS
 * DEC       : This file contains the shortcut bitwise operations which might be 
 * performed during the actual code writing.
 */
/*==============INCLUDES=============*/
#include <types.h>

#ifdef TNG_OWN_MAKE_SUPPORTED
#include <comfun.h>
#else
#include <comfun.c>
#endif

/*==============INTERNAL=============*/
static CPCCHAR gsCpCcFileName = "BITWSE.C";
/*===============MACROS==============*/

/* Gives the size of given variable */
//#define eTNG_SIZE_OF(VAR) ((((PCHAR)(&VAR + 1)) - ((PCHAR)(&VAR))) * 8 )
#define eTNG_SIZE_OF(VAR) (sizeof(VAR) * 8 )

#define eTNG_SIZE_OF_IN_BYTES(VAR) ((((PCHAR)(&VAR + 1)) - ((PCHAR)(&VAR))))

/* Define to set a series of bits for given position and count */
#define eTNG_SET_BIT_SERIES( VAR, POS, CNT )    (( eTNG_SIZE_OF( VAR )) > ( POS + CNT ) ) ?\
                                                ( VAR | ((( 1 << CNT ) - 1 ) << POS ))  : VAR

/* Decides weather the given value is negative or positive */
#define eTNG_NEGATIVE_OR_POSITIVE( VAR )  (( VAR >> (( eTNG_SIZE_OF(VAR)) - 1 )) & ( 1 ))

/* Toggling a given bit. Making a mask value with only toggle bit set and performing xor with it.
 *  As the mask value is always 1, resultant bit will be toggled  */
#define eTNG_TOGGLE_NTH_BIT(VAR,POS) ((( eTNG_SIZE_OF( VAR )) > POS ) ? ( VAR ^ ( 1 << POS )) : VAR )

#define eTNG_REVERSE_BITS(VAR,SIZ)  UINT32  ui32SzOfVar = SIZ,\
                                            ui32LocLp;\
                                    PCHAR  pui8TemPlaceHolder = OS_Allocate ( ui32SzOfVar );\
                                    for ( ui32LocLp = 0 ; (( ui32SzOfVar > ui32LocLp ) && ( OS_NULL != pui8TemPlaceHolder )) ; ++ui32LocLp )\
                                    {\
                                        if( VAR & ( 1 << ui32LocLp ) )\
                                        {\
                                            UINT8   ui8Block = ((( ui32SzOfVar - 1 ) - ui32LocLp ) / 8 ),\
                                                    ui8Bit   = ((( ui32SzOfVar - 1 ) - ui32LocLp ) % 8 );\
                                            pui8TemPlaceHolder[ui8Block] |= ( 1 << ui8Bit );\
                                        }\
                                    }\
                                    memcpy ( &VAR, pui8TemPlaceHolder, (ui32SzOfVar/8) );\
                                    OS_Free( pui8TemPlaceHolder );

#define eTNG_SET_RESET_BIT_CNT(VAR, SET_RESET, CNT)  {  UINT16  ui16LocLp,\
                                                        ui16SetResetCnt = 0;\
                                                        for ( ui16LocLp = 0 ; ( ( eTNG_SIZE_OF(VAR)) > ui16LocLp ); ++ui16LocLp )\
                                                        {\
                                                            if (( VAR & ( 1 << ui16LocLp )) && ( OS_TRUE == SET_RESET) )\
                                                            {\
                                                                ++CNT;\
                                                            }\
                                                            else if ((!( VAR & ( 1 << ui16LocLp ))) && ( OS_FALSE == SET_RESET) )\
                                                            {\
                                                                ++CNT;\
                                                            }\
                                                        }\
                                                    }
/* This macro prints the bit value of the given variable from LSB to MSB*/
#define eTNG_PRINT_BITS(VAL)    UINT8 ui8LocLp = 0; \
                                while( eTNG_SIZE_OF(VAL) > ui8LocLp ) \
                                { \
                                    OS_MessageLogging("%s %d>$TNG-PB$<BIT{POS[%d]VAL[%c]}>" \
                                                                        ,   gsCpCcFileName \
                                                                        ,   __LINE__ \
                                                                        ,   ui8LocLp \
                                                                        ,   (( VAL & ( 1 << ui8LocLp )) ? '1' : '0')); \
                                    ++ui8LocLp; \
                                }                                                    
//#pragma warn -incompatible-pointer-types
#define eTNG_DECIDE_ENDIAN(__X__)  UINT32 ui32Sample = 1;\
                            PUINT8 pui8Host = &ui32Sample;\
                            __X__ = ((*pui8Host == 1) ? "LITTLE" : "BIG")
//#pragma warn +incompatible-pointer-types

/* If the last bit is set, then the variable is odd and if ti is not then it is even. */
#define eTNG_IS_EVEN(__X__) (__X__ & 1)

/* For all the POW 2 subtracting 1 from the number would result in setting of all the binary digits
 * before the number and reset of the curent set digit. If & operations is performed
 * it would fail if pow(2) except for one.
 */
#define eTNG_IS_POW_2(__X__) (( __X__ & ( __X__ - 1 )) || (__X__ == 1)) ? "FALSE" : "TRUE"

/* General calculation for the swap. */
#define eTNG_SWAP(__A__,__B__);  __A__ = __A__ ^ __B__;\
                                __B__ = __A__ ^ __B__;\
                                __A__ = __A__ ^ __B__;\

#define eTNG_FIND_RIGHT_MOST_SET_BIT(__VAR__,__POS__);  eTNG_SET_RESET_BIT_CNT((UINT32)((__VAR__ & ((~__VAR__) + 1)) - 1), OS_TRUE, __POS__ ) \
                                                        ++__POS__;

#define eTNG_SWAP_TWO_BITS( VAL, POS_A, POS_B )     if(VAL & (1 << POS_A)) 
                                                    {\
                                                        if (VAL & (1 << POS_B))\
                                                            VAL |= 1 << POS_A;\
                                                        else\
                                                            VAL &= (~(1 << POS_A)); \
                                                        VAL |= 1 << POS_B;\
                                                    }\
                                                    else\
                                                    {\
                                                        if (VAL & (1 << POS_B)) \
                                                            VAL |= 1 << POS_A;\
                                                        else\
                                                            VAL &= (~(1 << POS_A)); \
                                                        VAL &= ~(1 << POS_B);\
                                                    }
/*=============PROTOTYPES============*/

/*=============DEFINITIONS===========*/

/*
 * API NAME: Main entry
 * DES: Main entry
 */
INT32 main ( INT32 argc, PCHAR argv[])
{
    UINT32  ui32BitManipVar = 2,
            ui32BitPosition = 1,
            ui32BitCnt;

    OS_MessageLogging("%s %d>$TNG-SETBITSER$<MAN[%X]-DBG{MSK[%X]SZ[%u]}>",
                                gsCpCcFileName,
                                __LINE__,
                                eTNG_SET_BIT_SERIES(ui32BitManipVar, 5, 4 ),
                                (( 1 << 4 ) - 1 ),
                                eTNG_SIZE_OF( ui32BitManipVar ));

    OS_MessageLogging("%s %d>$TNG-SIGN$<IP[%X]OP[%u]>",
                                gsCpCcFileName,
                                __LINE__,                                
                                ui32BitManipVar,
                                eTNG_NEGATIVE_OR_POSITIVE(ui32BitManipVar));

    OS_MessageLogging("%s %d>$TNG-TGL$<IP[V{%d:%X}POS{%d:%X}]TR[%X]>",
                                            gsCpCcFileName,
                                            __LINE__,
                                            ui32BitManipVar,
                                            ui32BitManipVar,
                                            ui32BitPosition,
                                            ui32BitPosition,
                                            eTNG_TOGGLE_NTH_BIT(ui32BitManipVar, ui32BitPosition)); 

    eTNG_SET_RESET_BIT_CNT (ui32BitManipVar, 1, ui32BitCnt);
    OS_MessageLogging("%s %d>$TNG-SRC$<C[%u]>",gsCpCcFileName,__LINE__, ui32BitCnt);

    /* Prints the each bit of the variable from LSB to MSB */
    eTNG_PRINT_BITS(ui32BitManipVar);

    OS_MessageLogging("%s %d>$TNG-EVN/ODD$<IP[%X]OP[%s]>",gsCpCcFileName,__LINE__, ui32BitManipVar, eTNG_IS_EVEN(ui32BitManipVar) ? "ODD" : "EVEN");
  
    OS_MessageLogging("%s %d>$TNG-ISPOW2$<IP[%X]OP[%s]>",gsCpCcFileName,__LINE__, ui32BitManipVar, eTNG_IS_POW_2(ui32BitManipVar));

    {
        CPCHAR pCcEndian;
        
        eTNG_DECIDE_ENDIAN(pCcEndian);
        OS_MessageLogging("%s %d>$TNG-DEND$<IP[%u]ENDI[%s]>"
                                                    ,   gsCpCcFileName
                                                    ,   __LINE__
                                                    ,   pCcEndian );
    }
    

    /* This define modifies the bit value of source. So keep it as last always or make additional variable to store the result */
    eTNG_REVERSE_BITS( ui32BitManipVar, (eTNG_SIZE_OF( ui32BitManipVar )));
    OS_MessageLogging("%s %d>$TNG-REV$<OP[%d:%X]>",
                                                gsCpCcFileName,
                                                __LINE__,
                                                ui32BitManipVar,
                                                ui32BitManipVar);

    {
        UINT32 ui32VarA = 10, ui32TempVarA, ui32VarB = 20, ui32TempVarB;
        ui32TempVarA = ui32VarA;
        ui32TempVarB = ui32VarB;
        eTNG_SWAP(ui32VarA, ui32VarB);
        OS_MessageLogging("%s %d>$TNG-SWP$<BS{A[%u]B[%u]}AS{A[%u]B[%u]}>"
                                                ,   gsCpCcFileName
                                                ,   __LINE__

                                                ,   ui32TempVarA
                                                ,   ui32TempVarB
                                                
                                                ,   ui32VarA
                                                ,   ui32VarB
                                                );
    }

    {
        UINT32 ui32SampleNum = 8;
        UINT32 ui32Position;
        eTNG_FIND_RIGHT_MOST_SET_BIT(ui32SampleNum, ui32Position );
        OS_MessageLogging("%s %d>$TNG-RMB$<IP[%u]OP[%u]>",gsCpCcFileName,__LINE__, ui32SampleNum, ui32Position );
    }
    {
        UINT32 ui32SwapBitsVal  = 4;
        UINT32 ui32SwapBitsOrig = ui32SwapBitsVal;
        UINT32 POS_A = 4, POS_B = 3, VAL = 4;

       // eTNG_SWAP_TWO_BITS(ui32SwapBitsVal, 4, 3 );

        OS_MessageLogging("%s %d>$TNG-SWPB$<ORG[%X]SWP[%X]-DBG{[VAL[%X]}>"
                                            ,   gsCpCcFileName
                                            ,   __LINE__
                                            ,   ui32SwapBitsOrig
                                            ,   ui32SwapBitsVal
                                            ,   VAL    
                                            );
    }                     
    getch();                            
    return (INT32)OS_NO_ERROR;                            
}

