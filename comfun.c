/*
 * FILE NAME : comfun.c
 * DEC       : This file contains all the most used fuction definitions.
 */
/*==============INCLUDES=============*/
#include <types.h>
/*==============INTERNAL=============*/
#ifndef TNG_OWN_MAKE_SUPPORTED
static CPCHAR gscpCFileName = "COMFUN.C"
#endif /* #ifndef TNG_OWN_MAKE_SUPPORTED */

/*===============MACROS==============*/

/*=============PROTOTYPES============*/

/*=============DEFINITIONS===========*/
/*
 * API NAME: GetIntegerAsInput 
 * DES: If user gives even sting as input avoid those chars and stores only integer.
 * Confession : This code is taken from other sources and not written on own.
 */
UINT32 TNG_GetIntegerInput ( VOID )
{
    char input[20]; // Buffer to hold input
    int index = 0;
    char ch;

    while (1) 
    {
        ch = getch(); // Get a character
        // Enter key
        if ('\r' == ch ) 
        { 
            break;
        }
        else if (ch == 8) 
        { // Backspace key
            if (index > 0) {
                index--;
                printf("\b \b"); // Erase character on console
            }
        } 
        else if ((ch >= '0' && ch <= '9') && index < 19) 
        { // Check if character is a digit
            input[index++] = ch; // Store character
            putchar(ch); // Echo the character
        }
    }
    
    input[index] = '\0'; // Null-terminate the string
    return atoi(input); // Convert string to integer
}

/*
 * API NAME: Logging the prints
 * DES: Common interface API to log the prints to console, file and IP.
 *      Version 1 :: only routes to console.
 */
INT32 OS_MessageLogging ( const PCHAR CpcFormat, ... )
{
    CHAR    acLogBuffer[ 1024/* For log message of 1kb */ + 1 /* For null */ ];
    INT32   i32InLength;

    va_list args;
    va_start ( args, CpcFormat );
    
    vsnprinf ( acLogBuffer, sizeof ( acLogBuffer ), CpcFormat, args );
    
    va_end ( args );
    return i32InLength;
}