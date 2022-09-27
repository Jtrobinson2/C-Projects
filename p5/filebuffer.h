/**
 * @file filebuffer.h
 * @author Jakari Robinson 
 * @brief Header file for reading and writing from binary files component filebuffer.c
 * 
 */

#ifndef _FILEBUFFER_H_
#define _FILEBUFFER_H_

/** A shorthand for talking about a byte. */
typedef unsigned char byte;

/** Representation of a resizable array of bytes, with functions to
    make it easy to read and write the contents of this array to a
    file. */
typedef struct {
  /** Resizable array of bytes stored in this filebuffer. */
  byte *data;

  // More fields added by you.
  
  /**Number of bytes in the data array */ 
  int numOfBytes; 

  /**Capacity of data array */
  int capacity; 

} FileBuffer;

/**
 * @brief Dynamically allocates a file buffer, initializes it so it contains an 
 * empty sequence of bytes and returns the pointer to the new filebuffer
 * 
 * @return FileBuffer* pointer to the created file buffer
 */
FileBuffer *makeFileBuffer();

/**
 * @brief frees all memeory used to represent the file buffer
 * 
 * @param buffer you want to destroy
 */
void freeFileBuffer( FileBuffer *buffer );

/**
 * @brief Adds a byte to the end of the array of bytes stored in the file buffer 
 * resizes data array if necessary
 * 
 * @param buffer array you want to add the byte to
 * @param val the byte you want to add
 */
void appendFileBuffer( FileBuffer *buffer, byte val );

/**
 * @brief reads binary input file, stores it's contents in a resizeable array 
 * in a new filebuffer struct and returns a pointer to the new file buffer.
 * 
 * @param filename file you want to read binary from 
 * @return FileBuffer* you want to store the contents of that file
 */
FileBuffer *loadFileBuffer( char const *filename );

/**
 * @brief saves the contents of the filebuffer to a binary file with the
 *  given name
 * 
 * @param buffer you want to save the contents of 
 * @param filename file you want to save the buffer too
 */
void saveFileBuffer( FileBuffer *buffer, char const *filename );
#endif
