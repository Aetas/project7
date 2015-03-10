#sheblamo

#Same as saying CXX
CC = g++
CPPFLAGS = -Wall -Werror -std=c++0x I
OBJ = main.o functions.o
OUTPUT = main.o
ODIR = ./bin

vpath = %.h ./include
vpath = %.cpp ./src

JSON_C_DIR=/usr
CPPFLAGS += -I$(JSON_C_DIR)/include/json-c
LDFLAGS+= -L$(JSON_C_DIR)/lib -ljson-c

program: $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(ODIR)/$(OUTPUT) $(LDFLAGS)

main.o : ./src/Assignment7.cpp ./include/MovieTree.h
	$(CC) $(CPPFLAGS) -c $(LDFLAGS)

functions.o : ./src/MovieTree.cpp ./include/MovieTree.h
	$(CC) $(CPPFLAGS) -c $(LDFLAGS)

.PHONY : clean
clean :
	rm program $(OBJ)

# Creates a log to keep track of things changed
log : Assignment7.cpp $(OBJ)
	lpt -p $?
	touch log

