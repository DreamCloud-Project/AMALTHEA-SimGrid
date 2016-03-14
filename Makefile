#===========================================================================#
#===========================================================================#
##################### DREAMCLOUD APPLICATION MAKE FILE#######################
#===========================================================================#
#===========================================================================#

# The linker options.
#SC_DIR = /usr/local/systemc231
#SC_LIBS := -L$(SC_DIR)/lib-linux64

#Link to Xerces lib use for parsing amalthea xml file
XERCES_DIR = /usr/local/xercesc311
XERCES_LIBS := -L$(XERCES_DIR)/lib/ -lxerces-c

#MY_LIBS   = -I$(SC_LIBS) -I$(XERCES_LIBS)
MY_LIBS   = -I$(XERCES_LIBS)

## SIMGRID
##==========================================================================
INSTALL_PATH = /usr/local/simgrid_dev
INCLUDES = -I$(INSTALL_PATH)/include
LIBS = -L$(INSTALL_PATH)/lib/
SG_CFLAGS = -g -std=gnu99
LDADD = -lm -lsimgrid
BIN_DIR := $(TOP_DIR)/obj/bin





# The pre-processor options used by the cpp (man cpp for more).
CPPFLAGS  = -Wall

# The directories in which source files reside.
SRCDIRS   = $(CURDIR)/Parser

# The executable file name.
# If not specified, current directory name or `a.out' will be used.
PROGRAM   = main

## Implicit Section: change the following only when necessary.
##==========================================================================

# The source file types (headers excluded).
# .c indicates C source files, and others C++ ones.
SRCEXTS = .cpp 

# The header file types.
HDREXTS = .h

# The pre-processor and compiler options.
# Users can override those variables from the command line.
CFLAGS  = -g -O2 $(SG_CFLAGS)
CXXFLAGS	= -g -std=c++11 -Wall -pedantic $(SG_CFLAGS)

# The C program compiler.
CC     = gcc

# The C++ program compiler.
CXX    = g++



## Stable Section: usually no need to be changed. But you can add more.
##==========================================================================
SHELL   = /bin/sh
EMPTY   =
SPACE   = $(EMPTY) $(EMPTY)
ifeq ($(PROGRAM),)
	CUR_PATH_NAMES = $(subst /,$(SPACE),$(subst $(SPACE),_,$(CURDIR)))
	PROGRAM = $(word $(words $(CUR_PATH_NAMES)),$(CUR_PATH_NAMES))
	ifeq ($(PROGRAM),)
		PROGRAM = a.out
	endif
endif
ifeq ($(SRCDIRS),)
	SRCDIRS = .
endif
SOURCES = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(SRCEXTS))))
HEADERS = $(foreach d,$(SRCDIRS),$(wildcard $(addprefix $(d)/*,$(HDREXTS))))
SRC_CXX = $(filter-out %.c,$(SOURCES))
OBJS    = $(addsuffix .o, $(basename $(SOURCES)))
DEPS    = $(OBJS:.o=.d)

## Define some useful variables.
DEP_OPT = $(shell if `$(CC) --version | grep "GCC" >/dev/null`; then \
				echo "-MM -MP"; else echo "-M"; fi )
DEPEND      = $(CC)  $(DEP_OPT)  $(MY_CFLAGS) $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $(LIBS) $(LDADD)
DEPEND.d    = $(subst -g ,,$(DEPEND))
COMPILE.cxx = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) $(LIBS) $(LDADD) -c

LINK.cxx    = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(INCLUDES) $(LIBS) $(LDADD)

.PHONY: all objs tags ctags clean distclean help show

# Delete the default suffixes
.SUFFIXES:

all: $(PROGRAM)

# Rules for creating dependency files (.d).
#------------------------------------------

%.d:%.cpp
	@echo -n $(dir $<) > $@
	@$(DEPEND.d) $< >> $@

# Rules for generating object files (.o).
#----------------------------------------
objs:$(OBJS)

%.o:%.cpp
	$(COMPILE.cxx) $< -o $@


# Rules for generating the executable.
#-------------------------------------
$(PROGRAM):$(OBJS)
ifeq ($(SRC_CXX),)              # C program
	$(LINK.c)   $(OBJS) $(MY_LIBS) -o $@
	@echo Type ./$@ to execute the program.
else                            # C++ program
	$(LINK.cxx) $(OBJS) $(MY_LIBS) -o $@
	@echo Type ./$@ to execute the program.
endif



ifndef NODEP
ifneq ($(DEPS),)
	#sinclude $(DEPS)
endif
endif

clean:
	$(RM) $(OBJS) $(PROGRAM) $(PROGRAM).exe

run:
	./$(PROGRAM)
## End of the Makefile ##  Suggestions are welcome  ## All rights reserved ##
#############################################################################
