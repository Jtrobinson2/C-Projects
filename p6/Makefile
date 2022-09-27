#Compiler for the default rule to use
CC = gcc

#options I want the default compile to use
CFLAGS = -Wall -std=c99 -g

#default rule if nothing is specified on a make command 
all: driver

#Making the driver program
driver: input.o map.o integer.o text.o driver.o
	gcc $(CFLAGS) input.o map.o integer.o text.o driver.o -o driver

#Rebuild map.o if it's dependencies change
map.o: vtype.c vtype.h map.h map.c 
	$(CC) $(CFLAGS) -c map.c

#Rebuild input.o if it's dependencies change
input.o: input.h input.c
	$(CC) $(CFLAGS) -c input.c

#Rebuild integer.o if it's dependencies change
integer.o: vtype.c vtype.h  integer.h integer.c
	$(CC) $(CFLAGS) -c integer.c

#Rebuild text.o if it's dependencies change
text.o: vtype.c vtype.h  text.h text.c
	$(CC) $(CFLAGS) -c text.c

#How to build vtype
vtype.o: vtype.c vtype.h  
	$(CC) $(CFLAGS) -c vtype.c

#Rebuild driver.o if any of it's dependecies change
driver.o: map.o integer.o text.o input.o vtype.o driver.c
	$(CC) $(CFLAGS) -c driver.c	





#Commands that clean the whole workspace of uneccessary junk
clean:
	rm -f driver.o input.o map.o decode.o vtype.o mapTest.o integer.o textTest.o text.o
	rm -f textTest
	rm -f mapTest

	
	
#-c compiles without linking
# -g generates debugging info
# -o is followed by what the executable of the linked object files should be is ssays relink