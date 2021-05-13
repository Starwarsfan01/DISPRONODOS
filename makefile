# Makefile for compiling dc_solver.c
CC		= @gcc
TARGET	= dc_solver
OBJS	= read.o matrix.o
CFLAGS	= -Wall

# Target
$(TARGET): $(OBJS) dc_solver.o
	$(CC) $(CFLAGS) $^ -o $(TARGET)

# Objects
dc_solver.o: dc_solver.c
read.o: read.c read.h
matrix.o: matrix.c matrix.h

# Clean
.PHONY: clean
clean:
	@rm -rf *.o $(TARGET)
	@rm -rf ./test/test

# Test
.PHONY: test
test: $(OBJS) ./test/test.c
	$(CC) $(CFLAGS) $^ -o ./test/$@
	@./test/$@