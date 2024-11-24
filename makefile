#####################################
##	MAKEFILE TO COMPILE TESTCODES  ##
#####################################

## Compiler options decide
include .\opt\compiler.inc

##Basic variables
ENABLE=1
DISABLE=0
SOURCES:=

## repository options
include .\opt\repopt.opt

## Add the include options here
INCLUDES:=-I./headers -I./

SOURCES+=comfun.c

ifeq "$(TNG_COMPILE_FIBONACCI_SERIES)" "$(ENABLE)"
SOURCES +=fibser.c
endif

ifeq "$(TNG_BIT_MANIPULATION_TEST)" "$(ENABLE)"
SOURCES +=bitw.c
endif

## Add the compiler flags  here
CFLAGS:=-DTNG_OWN_MAKE_SUPPORTED

$(EXECUTABLE):$(SOURCES)
	$(MAKE_DIRECTORY) .\Out
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o .\Out\$(EXECUTABLE)

clean:
	$(REMOVE) .\Out\$(EXECUTABLE)