# Compiler for C code
CC=g++
# Compiler for asm code
ASM=nasm

# Flags for C files
CFLAGS=-c
# Flags for asm files
ASMFLAGS=-felf64

# Flags for common build
ALLCOMPFLAGS=-no-pie


all: bin_patch

bin_patch: bin_patch.o alib.o
	$(CC) $(ALLCOMPFLAGS) bin_patch.o alib.o -o bin_patch

bin_patch.o: bin_patch.cpp
	$(CC) $(CFLAGS) bin_patch.cpp

alib.o: alib.s
	$(ASM) $(ASMFLAGS) alib.s

clean:
	rm -rf *.o bin_patch
