# defining the compiler to be used
COMPILER := g++

# define the flags to pass to the compiler
CFLAGS := -std=c++11

# define debug flags
DFLAG := -g

# define folders for the compilation
HEADERS_FOLDER := ./headers
SOURCE_FOLDER := ./source
DEPENDENCIES_FOLDER := ./dependencies
BIN_FOLDER := ./build
OBJ_FOLDER := ./obj
EXE_NAME := reinforcementAgentSuit
DEBUG_NAME := reinforcementAgentSuitDebug

release: generateObj
	@echo generating executable
	@$(COMPILER) -o $(BIN_FOLDER)/$(EXE_NAME).out $(OBJ_FOLDER)/*.o $(DEPENDENCIES_FOLDER)/*.a

debug: generateObjDebug
	@echo generating debug executable
	@$(COMPILER) -o $(BIN_FOLDER)/$(DEBUG_NAME).out $(OBJ_FOLDER)/*.o $(DEPENDENCIES_FOLDER)/*.a

generateObj:
	@clear
	@echo generating object files
	@$(COMPILER) $(CFLAGS) -I$(HEADERS_FOLDER) -I$(DEPENDENCIES_FOLDER)/include_search_engine/ -c $(SOURCE_FOLDER)/*.cpp
	@echo moving to obj folder
	@mv *.o $(OBJ_FOLDER)/

generateObjDebug:
	@clear
	@echo generating debug object files
	@$(COMPILER) $(CFLAGS) $(DFLAG) -I$(HEADERS_FOLDER) -I$(DEPENDENCIES_FOLDER)/include_search_engine/ -c $(SOURCE_FOLDER)/*.cpp
	@echo moving to obj folder
	@mv *.o $(OBJ_FOLDER)/

clean:
	@./clean.sh
