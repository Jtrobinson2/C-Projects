#Compiler for the default rule to use
CC = gcc

#options I want the default compile to use
CFLAGS = -Wall -std=c99 -g

#default rule if nothing is specified on a make command 
all: agency

#Making the agency program
agency: agency.o database.o input.o
	gcc $(CFLAGS) agency.o database.o input.o -o agency

#Rebuild database.o if it's dependencies change
database.o: database.c database.h input.h input.c 
	$(CC) $(CFLAGS) -c database.c

#Rebuild input.o if it's dependencies change
input.o: input.c input.h  
	$(CC) $(CFLAGS) -c input.c


#Rebuild agency.o if any of it's dependencies change
agency.o: database.c database.h input.c input.h agency.c
	gcc $(CFLAGS) -c agency.c 


#Commands that clean the whole workspace of uneccessary junk
clean:
	rm -f database.o input.o agency.o  
	rm -f agency 
	rm -f output.txt
	
#-c compiles without linking
# -g generates debugging info
# -o is followed by what the executable of the linked object files should be is ssays relink
