GREEN   = @echo "\033[0;32m";
DFLT    = @echo "\033[0;m";
 
ifeq ($(ASAN), 1)
ASAN =-fsanitize=address
else
ASAN =
endif

COMPILATOR  = g++
INC     	= 
SFML    	= -lsfml-graphics -lsfml-window -lsfml-system
OPT     	= -O3
DEF     	= -DNDEBUG
CFLAGS  	= $(OPT) $(DEF) $(ASAN) -g $(INC) 
DLL			= -ldl -lm -lpthread -pthread
OBJ     	= obj/
EXE     	= main
 
FILES   	= $(OBJ)main.o \
			$(OBJ)src/Stack.o \
			$(OBJ)src/diff_work_with_file.o \
			$(OBJ)src/diff_tree.o \
			$(OBJ)src/diff_defferentiator.o \
			$(OBJ)src/catalog_tree_read_from_file.o \
			$(OBJ)src/tree_in_latex.o \
 
 
#
# Rules
#
 
all: $(FILES)
	$(GREEN)
	@echo 'Linking $@ (changed $?)';
	$(DFLT)
	@$(COMPILATOR) $(CFLAGS) $(FILES) $(SFML) $(DLL) -o $(EXE)
	
obj/%.o: %.cpp
	$(GREEN)
	@echo 'Building $@ (changed $?)';
	$(DFLT)
	@$(COMPILATOR) $(CFLAGS) $^ -c
	@mkdir -p $(@D)
	@mv $(@F) $@
	
clean:
	$(GREEN)
	@echo 'Cleaning the project';
	$(DFLT)
	@rm $(FILES)

run: all
	./$(EXE)
