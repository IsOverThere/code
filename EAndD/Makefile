include mak/project.mak
include mak/options.mak

all: tools.bin
	 
clean:
	rm -f $(DIR_OBJ)/*
	rm -f $(DIR_BIN)/* 

#$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
obj/%.o: src/%.c
#	@echo $(DIR_OBJ): $(DIR_SRC)
	$(COMPILER) $(COMPILE_OPT_DEF) $(COMPILE_OPT_INC) $< -o $@

tools.bin: $(OBJ_LIB)
	$(LINK) $(COMPILE_OPT_DEF) $(COMPILE_OPT_INC)  $(OBJ_LIB) -o $(DIR_BIN)/$@
	
