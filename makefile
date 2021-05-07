# Makefile for compiling dc_solver.c
CC		= gcc
TARGET	= dc_solver
OBJS	= dc_solver.o read.o matrix.o
CFLAGS	= -Wall

# Target
$(TARGET): $(OBJS):
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Objects
dc_solver.o: dc_solver.c dc_solver.h
read.o: read.c read.h
matrix.o: matrix.c matrix.h

# Clean
.PHONY: clean
clean:
	@rm -f *.o output