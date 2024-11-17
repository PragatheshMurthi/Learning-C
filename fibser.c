/*
 * FILE NAME : FIBONACCI SERIES.C
 * DEC       : To find the fibonacci series of the given number which is obtained from user.
 *
 */
/*==============INCLUDES=============*/
#include "types.h"

#ifdef TNG_OWN_MAKE_SUPPORTED
#include "comfun.h"
#else
#include "comfun.c" 
#endif

/*==============INTERNAL=============*/

static CPCCHAR gsCpCcFileName = "FIBSER.C";

/*===============MACROS==============*/

/*=============PROTOTYPES============*/

OS_ERROR_CODE TNG_PrintFibonacciNumber ( UINT32 ui32FibNumLoc );
/*=============DEFINITIONS===========*/
/*
 * API NAME: main entry
 * DES: main entry
 */
int main ( int argc, char* argv[])
{
    UINT32 ui32FibNNumb;

    /* Get the integer to print the fibonacci series */
    OS_MessageLogging("%s %d>$TNG$<ENTER THE FIBONACCI INPUT : >",gsCpCcFileName,__LINE__);
    ui32FibNNumb = OS_GetIntegerInput();

    EXAMINE_ERROR( TNG_PrintFibonacciNumber( ui32FibNNumb ));
    getch();
    return ((INT32) OS_NO_ERROR);
}

/*
 * API NAME: Fibonacci number calculation fuction.
 * DES: We print the output of the obtain fibonacci function..
 */
OS_ERROR_CODE TNG_PrintFibonacciNumber ( UINT32 ui32FibNumLoc )
{
    if ( ui32FibNumLoc )
    {
        UINT32  ui32FibNoIncLp          = 3;
        UINT16  u16SecondInstanceFib    = 1,
                u16ThirdInstanceFib     = 0,
                ui16CurrFibNum          = 1;

        OS_MessageLogging("%s %d>$TNG$<THE FIBONACCI SERIES IS AS FOLLOWS:>",gsCpCcFileName,__LINE__);
        printf("%u %u", 0, 1);

        while ( ui32FibNoIncLp < ui32FibNumLoc )
        {
            /* Calculating  the current fibonacci number with the last two numbers */
            ui16CurrFibNum = u16SecondInstanceFib + u16ThirdInstanceFib;

            /* Printing the fibonacci series number */
            printf(" %d", ui16CurrFibNum );

            /* Maintaining the last twe numbers for calculation */
            u16ThirdInstanceFib = u16SecondInstanceFib;
            u16SecondInstanceFib = ui16CurrFibNum;

            ++ui32FibNoIncLp;
        }
    return OS_NO_ERROR;
    }    
}
