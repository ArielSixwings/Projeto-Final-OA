################################################################################
# ArvoreB
# @file makefile to compile prject.
# Authors:
#		- Eduardo Lemos Rocha
#   - Ariel Vieira Lima Serafim
################################################################################



# Set Varibles #################################################################

# Directory and name of the executable:
EXEC = main

#Directory of source code:
DIR_SOURCE = src
SOURCE = $(wildcard $(DIR_SOURCE)/*.cpp)

# Directory of includeded headers and headers:
DIR_INCLUDE = inc
INCLUDE = $(wildcard $(DIR_INCLUDE)/*.hpp)

# Directory of objects and objects:
DIR_OBJ = Objects
OBJS= $(addprefix $(DIR_OBJ)/,$(notdir $(SOURCE:.cpp=.o)))

# Compilator and flags:
CC = g++
LIBS  = -lm -pthread
CFLAGS = -std=c++14 -c -Wall -g -W -Wextra -I $(DIR_INCLUDE)

# ################ #############################################################


# Make commands ################################################################

all: $(EXEC)

debug: CFLAGS += -ggdb
debug: reset all

.PHONY: clean reset
clean:
	rm -f $(DIR_OBJ)/*.o
	rm -rf $(DIR_OBJ)
reset: clean
	rm -f $(EXEC)

# ################# ############################################################


# Build ########################################################################

$(EXEC): $(OBJS)
	$(CC)  $^ -o $@ $(LIBS)

$(DIR_OBJ)/main.o: $(DIR_SOURCE)/main.cpp
	@mkdir -p $(DIR_OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

$(DIR_OBJ)/%.o: $(DIR_SOURCE)/%.cpp $(DIR_INCLUDE)/%.hpp
	@mkdir -p $(DIR_OBJ)
	$(CC) -c $< -o $@ $(CFLAGS)

# ######### ####################################################################
