CC		= @gcc
OBJS	= matrix.o read.o
CFLAGS	= -Wall
TARGET	= dc_solver

all: $(TARGET)

#Target dc_solver
$(TARGET): dc_solver.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

#Objects
matrix.o: matrix.c matrix.h

read.o: read.c read.h

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)