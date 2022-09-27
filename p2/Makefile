#Compiler for the default rule to use
CC = gcc

#options I want the default compile to use
CFLAGS = -Wall -std=c99 -g

#default rule if nothing is specified on a make command 
all: calc10 calc25

#Making the calc10 program
calc10: calc.o number10.o operation.o
	gcc $(CFLAGS) calc.o number10.o operation.o -o calc10

#Making the calc25 program
calc25: calc.o number25.o operation.o
	gcc $(CFLAGS) calc.o number25.o operation.o -o calc25

#Rebuild operation.o if it's dependencies change
operation.o: operation.c operation.h
	$(CC) $(CFLAGS) -c operation.c


#Rebuild number10.o if any of it's dependencies change
number10.o: number10.c number.h
	gcc $(CFLAGS) -c number10.c 

#Rebuild number25.o if any of it's dependencies change
number25.o: number25.c number.h
	gcc $(CFLAGS) -c number25.c 

#Rebuild calc.o if any of it's dependencies change
calc.o: operation.h number.h calc.c
	gcc $(CFLAGS) -c calc.c

#Commands that clean the whole workspace of uneccessary junk
clean:
	rm -f calc.o number10.o number25.o operation.o 
	rm -f calc10 calc25
	rm -f output.txt

#-c compiles without linking
# -g generates debugging info
# -o is followed by what the executable of the linked object files should be is ssays relink

