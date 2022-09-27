/**
 * @file state24.h
 * @author Jakari Robinson  
 * @brief header file for state24.c which is responsible showing components  
 * for converting between bytes and the characters used in base64 encoding
 * 
 * 
 */

#ifndef _STATE64_H_
#define _STATE64_H_

#include <stdbool.h>

// Include filebuffer to get the byte type.
#include "filebuffer.h"

typedef struct {
  /**Array to hold the bytes */ 
  byte byteArray[3] ; 

  /**amount of bytes currently in array */
  int byteCount;  
  
  //amount of bits in array
  int bitCount;


} State24;

/**
 * Takes a pointer to a state24 struct and initialize what it's pointing to to an empty 
 * state where no bits have been added yet caller must allocate the struct this function
 * just fills in it's fields
 * 
 * @param state struct that needs to be initialized but was already allocated by caller
 */
void initState( State24 *state );

/**
 * function returns true if the char is one of the 64 encoding chars we want.
 * @param ch char
 */
bool validChar( char ch );

/**
 * @brief Function adds 8 bits to the state struct given by the bits of the byte
 * Behavior is undefined if the state doesn't contain enough room for 8 additional bits.
 * @param state to add the bits too
 * @param b the byte you want to add
 */
void addByte( State24 *state, byte b );

/**
 * @brief Adds 6 bits to the given state with the character passed in. Ex if 'a' is passed in 
 * the bit representation of 'a' (011010) is added to the state. Behavior is undefined if the given character 
 * isn't an encoding character or if there isn't enough room for six more bits.
 * 
 * @param state you want to add the bits of a character too
 * @param ch characters bit's you want added to the state
 */
void addChar( State24 *state, char ch );

/**
 * @brief fills in the given array with at most 3 bytes based on the sequence of bits
 * given in the state struct. Returns number of butes wirten to the array and sets the given state
 * to empty (so you don't have to call initState() again before you start adding more bits to the state)
 * 
 * @param state you want to get bytes from
 * @param buffer array you want filled with bytes
 * @return int number of bytes added to the array from the state
 */
int getBytes( State24 *state, byte buffer[] );

/**
 * @brief Fills a given array with character codes for at most 4 encoding characters.
 * based on the sequence of bits in the given state struct. Returns the number of characters
 * written to the array and sets the state to empty. you should probably null terminate the buffer array
 * so make the caller pass in a 5-character array. 
 * 
 * @param state you want to get chars from
 * @param buffer array you want to store the chars from the converted state bits
 * @return int number of chars written to the buffer array
 */
int getChars( State24 *state, char buffer[] );

#endif



