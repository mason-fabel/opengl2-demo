APPLICATION_NAME := hw5
CC := g++
CFLAGS := -Wall -Wextra -Wpedantic -O2
LFLAGS := -lglut -lGLU -lGL -lm
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SRC))

.PHONY : all clean rebuild

all : $(APPLICATION_NAME)

$(APPLICATION_NAME) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(OBJ) : $(SRC)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean :
	\rm -f $(APPLICATION_NAME) $(APPLICATION_NAME).hex $(OBJ)

rebuild :
	make clean
	make all
