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

ifeq "$(TNG_STACK_TEST)" "$(ENABLE)"
SOURCES +=stack.c
endif

ifeq "$(TNG_ARR_SORT_TEST)" "$(ENABLE)" 
SOURCES +=mrgsrt.c
endif

ifeq "$(TNG_PTHREAD_TEST)" "$(ENABLE)" 
SOURCES +=ostask.c
DEP_LIBS += -lpthread
endif

ifeq "$(TNG_PTHREAD_COND_TEST)" "$(ENABLE)" 
SOURCES +=condvar.c
DEP_LIBS += -lpthread
endif

## Add the compiler flags  here
CFLAGS:=-DTNG_OWN_MAKE_SUPPORTED -g -O3

$(EXECUTABLE):$(SOURCES)
	$(MAKE_DIRECTORY) .\Out
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o .\Out\$(EXECUTABLE) $(DEP_LIBS)

clean:
	$(REMOVE) .\Out\$(EXECUTABLE)