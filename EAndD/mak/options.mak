
DIR_PROJECT_HOME = .

COMPILER                = gcc -c
LINK                    = gcc
ARCHIVER                = ar
ASSEMBLER               = as


DIR_OBJ = $(DIR_PROJECT_HOME)/obj
DIR_SRC = $(DIR_PROJECT_HOME)/src 
DIR_INC = $(DIR_PROJECT_HOME)/inc 
DIR_CFG = $(DIR_PROJECT_HOME)/mak 
DIR_BIN = $(DIR_PROJECT_HOME)/bin

COMPILE_OPT_INC = -I$(DIR_INC)

OBJ_LIB = $(DIR_OBJ)/main.o 
################################
# following code is optional
# and defined in project.mak

ifdef TEST
	COMPILE_OPT_DEF+=-DTEST
	OBJ_LIB += $(DIR_OBJ)/test.o 
endif

ifdef DEBUG
	COMPILE_OPT_DEF += -DDEBUG
endif

ifdef HEXTXT
	COMPILE_OPT_DEF+=-DHEXTXT
	OBJ_LIB += $(DIR_OBJ)/hextxt.o 
endif

ifdef PROCESS_FILE
	COMPILE_OPT_DEF+=-DPROCESS_FILE
	OBJ_LIB += $(DIR_OBJ)/processFile.o 
endif

ifdef HELP
	COMPILE_OPT_DEF+=-DHELP
	OBJ_LIB += $(DIR_OBJ)/help.o 
endif
