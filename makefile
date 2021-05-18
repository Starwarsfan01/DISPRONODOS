################################################################################
#               MAKEFILE created by Ángel D. Talero 27/Apr 2021                #
# 																			   #
#	make 		- compiles dc_solver										   #
#	make clean 	- clean compilation files									   #
#   make fsm 	- compiles a FSM version of dc_solver						   #			
################################################################################

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

matrix_fsm.o: matrix_fsm.c matrix.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)

.PHONY: fsm
fsm: dc_solver.c read.o matrix_fsm.o
	$(CC) $(CFLAGS) dc_solver.c read.o matrix_fsm.o -o $(TARGET)_fsm