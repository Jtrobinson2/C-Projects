#Compiler for the default rule to use
CC = gcc

#options I want the default compile to use
CFLAGS = -Wall -std=c99 -g

#default rule if nothing is specified on a make command 
all: wordle

#Making the wordle program
wordle: history.o lexicon.o io.o wordle.o
	gcc $(CFLAGS) history.o lexicon.o io.o wordle.o -o wordle

#Rebuild history.o if it's dependencies change
history.o: history.c history.h
	$(CC) $(CFLAGS) -c history.c

#Rebuild worlde.o if it's dependencies change
wordle.o: lexicon.c lexicon.h history.c history.h io.c io.h wordle.c 
	$(CC) $(CFLAGS) -c wordle.c


#Rebuild lexicon.o if any of it's dependencies change
lexicon.o: lexicon.c lexicon.h
	gcc $(CFLAGS) -c lexicon.c 

#Rebuild io.o if any of it's dependencies change
io.o: io.c io.h
	gcc $(CFLAGS) -c io.c 


#Commands that clean the whole workspace of uneccessary junk
clean:
	rm -f history.o io.o lexicon.o  
	rm -f wordle 
	rm -f scores.txt
	

#-c compiles without linking
# -g generates debugging info
# -o is followed by what the executable of the linked object files should be is ssays relink

