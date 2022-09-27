#Compiler for the default rule to use
CC = gcc

#options I want the default compile to use
CFLAGS = -Wall -std=c99 -g

#default rule if nothing is specified on a make command 
all: encode decode

#Making the encode program
encode: filebuffer.o state24.o encode.o
	gcc $(CFLAGS) encode.o filebuffer.o state24.o -o encode

#Making the decode program
decode: filebuffer.o state24.o decode.o
	gcc $(CFLAGS) decode.o filebuffer.o state24.o -o decode

#Rebuild encode.o if it's dependencies change
encode.o: encode.c state24.c state24.h filebuffer.c filebuffer.h 
	$(CC) $(CFLAGS) -c encode.c

#Rebuild decode.o if it's dependencies change
decode.o: decode.c state24.c state24.h filebuffer.c filebuffer.h  
	$(CC) $(CFLAGS) -c decode.c


#Rebuild filebuffer.o if any of it's dependencies change
filebuffer.o: filebuffer.c filebuffer.h
	gcc $(CFLAGS) -c filebuffer.c 

#Rebuild state24.o if any of it's dependencies change
state24.o: state24.c state24.h
	gcc $(CFLAGS) -c state24.c 


#Commands that clean the whole workspace of uneccessary junk
clean:
	rm -f filebuffer.o state24.o encode.o decode.o  
	rm -f decode 
	rm -f encode
	rm -f output.txt
	rm -f state24test
	rm -f filebuffertest
	
	
#-c compiles without linking
# -g generates debugging info
# -o is followed by what the executable of the linked object files should be is ssays relink