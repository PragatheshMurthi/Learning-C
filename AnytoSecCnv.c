/*
 * FILE NAME : AnyToSecondsConvertor.C
 * DEC       : This program converts any time unit given to the sec.
 *              Version 1 - supported inputs :: minutes,Hours and days
 */
/*==============INCLUDES=============*/
#include <types.h>

/* including c source file is not advisable. But since I dont have a make 
 * system, anyway it sucks in windows 32bit environment, Iam including c file.  
 */
#ifndef TNG_OWN_MAKE_SUPPORTED
#include <comfun.c>
#else
#include <comfun.h>
#endif /* #ifndef TNG_OWN_MAKE_SUPPORTED */

/*==============INTERNAL=============*/
static CPCHAR gsCpcFileName = "ANYTOSECCNV.C"
/*===============MACROS==============*/

/*=============PROTOTYPES============*/

/*=============DEFINITIONS===========*/

/*
 * API NAME: MAIN
 * DES: Entry api
 */
int main ( int argc, char argv[])
{
    OS_GetDecimalInput();
}