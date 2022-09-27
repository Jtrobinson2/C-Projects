/**
 * @file filebuffer.c
 * @author Jakari Robinson
 * @brief Component has a struct and functions to help read and write 
 * binary files 
 */

#include "filebuffer.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

FileBuffer *makeFileBuffer() {
    //Create a filebuffer pointer to malloced memory for filebuffer
    FileBuffer *buffer = (FileBuffer *) malloc(sizeof(FileBuffer));
    //Set numOfBytes to 0
    buffer->numOfBytes = 0;  
    //Set bytearray capacity to 50
    buffer->capacity = 50; 
    //Make the byte array pointer point to calloced 50 bytes of memory
    buffer->data = (byte *) calloc(50, sizeof(byte));
    //return pointer fileBuffer
    return buffer;

}



void freeFileBuffer( FileBuffer *buffer ) {
    //Free the calloced byte array
    free(buffer->data);

    //free the entire file buffer struct
    free(buffer);
}

void appendFileBuffer( FileBuffer *buffer, byte val ) {
    //Check if we're at capacity if so resize the array and update the capacity
    if(buffer->numOfBytes == buffer->capacity) {
        buffer->capacity *= 2;
        buffer->data = realloc(buffer->data, buffer->capacity * sizeof(byte));
    }
    //add the byte to count index in the byte array
    buffer->data[buffer->numOfBytes] = val;
    //increment bytecount 
    buffer->numOfBytes++;
}

FileBuffer *loadFileBuffer( char const *filename ) {

    //Create a new file buffer struct
    FileBuffer *buffer = makeFileBuffer();
    //Make  temp byte array
    byte tempByteArray[3];

    //Open the the file in read binary mode
    FILE *file = fopen(filename, "rb");

    while(fread(tempByteArray, sizeof(byte), 1, file) > 0) {

       for(int i = 0; i < 1; i++) {
           appendFileBuffer(buffer, tempByteArray[i]);
       }
      
    }

    //close the file  
    fclose(file);

    //return a pointer to the new file buffer
    return buffer; 
}

void saveFileBuffer( FileBuffer *buffer, char const *filename ) {
    //open the file in write binary mode
    FILE *file  = fopen(filename, "wb");
    //use frwrite to write the byte arrayto the file
    fwrite(buffer->data, sizeof(byte), buffer->numOfBytes, file);
    //close the file
    fclose(file);
}