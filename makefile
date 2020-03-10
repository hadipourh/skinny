# -*- MakeFile -*-

# Hosein Hadipour
# March 10, 2020

# The main structure of a make file commands is as follows: 
# target: dependencies
#       action
# Example: 
# output: main.o minor1.o minor2.o
#         g++ -o main main.o minor1.o minor2.o
# Some compiler flags:
# -E                       Preprocess only; do not compile, assemble or link.
# -S                       Compile only; do not assemble or link. (generates an assembly file and stop)
# -c                       Compile and assemble, but do not link. (generates an assembly code and converts it to the machine code by assembler)
# -o <file>                Place the output into <file>. (Links assembled files, and builds an executable file)
# -g    adds debugging information to the executable file
# -Wall turns on most, but not all, compiler warnings
# If you don't use a flag at all, your compiler (gcc here) do the process, compile

# compiler
# define the C compiler to use
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall
# the build target(s) executable:
TARGET1 = skinny-64-128
TARGET2 = skinny-64-192
TARGET3 = skinny-128-256
TARGET4 = skinny-128-384
# skinny-64-192 skinny-128-256 skinny-128-384
# If you execute make without a flag, it does the actions under the "all" target by default
all: skinny-64-128.o skinny-64-192.o skinny-128-256.o skinny-128-384.o
	$(CC) $(CFLAGS) -o $(TARGET1) skinny-64-128.o
	$(CC) $(CFLAGS) -o $(TARGET2) skinny-64-192.o
	$(CC) $(CFLAGS) -o $(TARGET3) skinny-128-256.o
	$(CC) $(CFLAGS) -o $(TARGET4) skinny-128-384.o
skinny-64-128.o: skinny-64-128.cpp
	$(CC) $(CFLAGS) -c skinny-64-128.cpp
skinny-64-192.o: skinny-64-192.cpp
	$(CC) $(CFLAGS) -c skinny-64-192.cpp
skinny-128-256.o: skinny-128-256.cpp
	$(CC) $(CFLAGS) -c skinny-128-256.cpp
skinny-128-384.o: skinny-128-384.cpp
	$(CC) $(CFLAGS) -c skinny-128-384.cpp
clean:
	rm -f *.o $(TARGET)