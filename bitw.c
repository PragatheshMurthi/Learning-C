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
#define eTNG_SIZE_OF(VAR) (((PCHAR)(&VAR + 1)) - ((PCHAR)(&VAR)))

/* Define to set a series of bits for given position and count */
#define eTNG_SET_BIT_SERIES( VAR, POS, CNT )    (( eTNG_SIZE_OF( VAR ) * 8 ) > ( POS + CNT ) ) ?\
                                                ( VAR | ((( 1 << CNT ) - 1 ) << POS ))  : VAR

/* Decides weather the given value is negative or positive */
#define eTNG_NEGATIVE_OR_POSITIVE( VAR )  (( VAR >> (( eTNG_SIZE_OF(VAR) * 8 ) - 1 )) & ( 1 ))

/* Is given variable is pow or 2 */
#define eTNG_IS_POW_OF_2(VAR) VAR ? !( VAR & ( VAR - 1 ) ) : 0

/* Toggling a given bit. Making a mask value with only toggle bit set and performing xor with it.
 *  As the mask value is always 1, resultant bit will be toggled  */
#define eTNG_TOGGLE_NTH_BIT(VAR,POS) ((( eTNG_SIZE_OF( VAR ) * 8 ) > POS ) ? ( VAR ^ ( 1 << POS )) : VAR )

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
                                                        for ( ui16LocLp = 0 ; ( ( eTNG_SIZE_OF(VAR) * 8 ) > ui16LocLp ); ++ui16LocLp )\
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
                                                                
/*=============PROTOTYPES============*/

/*=============DEFINITIONS===========*/

/*
 * API NAME: Main entry
 * DES: Main entry
 */
INT32 main ( INT32 argc, PCHAR argv[])
{
    UINT32  ui32BitManipVar = 1,
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

    OS_MessageLogging("%s %d>$TNG-ISPOW2$<IP[%u]IP2[%u]>",
                                            gsCpCcFileName,
                                            __LINE__,
                                            ui32BitManipVar,
                                            eTNG_IS_POW_OF_2(ui32BitManipVar)
                                            );

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

    eTNG_REVERSE_BITS( ui32BitManipVar, (eTNG_SIZE_OF( ui32BitManipVar ) * 8 ));
    OS_MessageLogging("%s %d>$TNG-REV$<OP[%d:%X]>",
                                                gsCpCcFileName,
                                                __LINE__,
                                                ui32BitManipVar,
                                                ui32BitManipVar);
    getch();                            
    return (INT32)OS_NO_ERROR;                            
}