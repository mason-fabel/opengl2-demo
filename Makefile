CC := g++
CFLAGS := -Wall -Wextra -Wpedantic -O2
LFLAGS := -lglut -lGLU -lGL -lm
PROGS := plot2d plot3d rubik
SRC := $(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o, $(SRC))

.PHONY : all clean rebuild

all : $(PROGS)

% : %.o
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

$(OBJ) : $(SRC)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean :
	rm -f $(PROGS) $(OBJ)

rebuild :
	make clean
	make all
