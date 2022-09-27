/**
 * @file state24.c
 * @author Jakari Robinson
 * @brief component that stores the current state of the encoding or decoding
 * up to 24 bits. It's makes it easy to convert between bytse and encoding characters up to
 * 24 bits at a time
 * 
 */
#include "state24.h"
#include "filebuffer.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

//array to store 8 bit representation of characters (bytes)
byte validCharactersInBits[] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 
0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 
0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F
};
//array of valid characters (char)
char validCharacters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
'Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f',
'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v',
'w','x','y','z','0','1','2','3','4','5','6','7','8','9','+','/'};
/**
 * @brief Helper method to find the index of a char in an array
 * 
 * @param ch to find 
 * @return int index you found it in -1 if not in it.
 */
static int indexOf(char ch, char charArray[], int sizeOfArray) {
    for(int i = 0; i < sizeOfArray; i++) {
        if(ch == charArray[i]) return i; 
    }

    return -1; 
}

/**
 * @brief Helper method to convert char to 8 bits
 * 
 * @param ch to convert
 * @return byte representation according to writeup
 */
static byte convertTo8Bits(char ch) {
    //indexOf ch in encoding Character
    int indexOfCharInEncodingArray = indexOf(ch, validCharacters, 64);
    //return the value that the index of char is in th the 8  bit array
    return validCharactersInBits[indexOfCharInEncodingArray];
}

/**
 * @brief Helper function that takes a byte and returns the char it is actually
 * 
 * @param byteToConvert byte you want in char form
 * @return char from that byte
 */
static char eightBitsToChar(byte byteToConvert) {
    //loop through bits array  
    for(int i = 0; i < 64; i++) {
        //If the  bit at that index == the byte convert
        if(byteToConvert == validCharactersInBits[i]) {
            //return the char that bit maps too
            return validCharacters[i];
        }
    }

    //should never get here
    return 0; 
        
}

void initState( State24 *state ) {
       //empty the byte array by setting  three bytes in the array 0
        memset(state->byteArray, 0, sizeof(3* sizeof(byte)));
       //initialize the byteCount to 0
        state->bitCount = 0; 
        state->byteCount = 0; 
}

bool validChar( char ch ) {
    //Check if the character is an alpha
    if(isalpha(ch)) return true;
    //Check if the character is a digit
    if(isdigit(ch)) return true; 
    //Check if the character is a '+' or '/'
    if(ch == '+' || ch == '/') return true;
    //If it failed all tests return false
    else return false;
}

void addByte( State24 *state, byte b ) {
    //If the state's byte array  is already  at capacity do nothing
    if(state->byteCount == 3) return; 

    state->byteArray[state->byteCount] = b;

    state->byteCount++;
    state->bitCount+=8;
}

void addChar( State24 *state, char ch ) {
    //Check if the char is a valid char if not do nothing
    if(!validChar(ch)) return; 

    //convert the character to it's 8 bt representation
    byte charInBits = ((convertTo8Bits(ch)) << 2);
    //left shift the byte by 2
    

    //if we've not added any bytes add the first 8 bits to the beginning of the byte array, increment byte count
    if(state->bitCount < 6) {
        state->byteArray[0] = charInBits;
        state->bitCount+= 6; 
        
    } 
    //Else if we've already added the first byte, 
    else if (state->bitCount >= 6 && state->bitCount < 12) {
         
        byte tempCharInBits = charInBits;

        //add the highest order 2 bits from the char's bits to the lowest 2 bits of the first bytes bits 
       
        byte temp = state->byteArray[0];
        byte mask = temp & 0xFC;

        charInBits &= 0xC0;

        charInBits >>= 6;

        charInBits |= mask;

        state->byteArray[0] = charInBits;

        //lowest order 4 bits to the index; 
        tempCharInBits <<= 2;
        state->byteArray[1] = tempCharInBits;
        state->bitCount+= 6; 
        if(state->bitCount > 8) state->byteCount++;
        
        
    }

    //Else we've added the second char take the highest order two bits from the third char and put them in the lowest order two bits in the second char, 
    //then add the lowest order 6 bits from the chars bits to the third index of the byte array
    else if(state->bitCount >= 12 && state->bitCount < 18) {

        byte temp = charInBits; 
        //replacing lower order 4 bits index 1 with high order 4 bits of 2nd char
        charInBits &= 0xF0;

        charInBits >>=  4;

        byte secondElement = state->byteArray[1];

        secondElement &= 0xF0;

        secondElement |= charInBits;

        state->byteArray[1] = secondElement;

        //replacing highest order 6 bits of index 2 with lowest order 6 bits of third char  

        temp <<= 4; 

        state->byteArray[2] = temp;
        state->bitCount+=6; 
        if(state->bitCount >= 16) state->byteCount++;
        
        
        


    } 
    
    //Else we've already added the third char or the entire third index with the char
    else {
        byte temp = charInBits; 
        byte arrayThree = state->byteArray[2];

        charInBits &= 0xFC;
        charInBits >>= 2; 

        arrayThree &= 0xC0;

        charInBits |= arrayThree; 

        state->byteArray[2] = charInBits;
        state->bitCount+=6; 
        if(state->bitCount >= 24) state->byteCount++;
    }
    
}


int getBytes( State24 *state, byte buffer[] ) {

    int bytesRead = state->byteCount;

    //loop through the byte data array (to size of byte array) in state struct and add each byte to the given buffer array 
    for(int i = 0; i < state->byteCount; i++) {
        buffer[i] = state->byteArray[i];
    }
    //set all the variables in the state struct to there intialization state
    initState(state);

    //return bytes read
    return bytesRead;


}

int getChars( State24 *state, char buffer[] ) {
    //get the size of the state byte array
    int bitCount = state->bitCount; 
    //if the size is 0 return 0?
    if(bitCount == 0) return 0; 
    //if the state byte array has ONLY one byte
    if(bitCount > 6 && bitCount < 12) {
        if(bitCount == 8) {
            //Get the value of the first index 
            byte firstByte = state->byteArray[0];
            //right shift the first index value 
            byte rightShiftedFirstIndex = firstByte >> 2; 
            //call 8 bits to char
            char charFromByte =  eightBitsToChar(rightShiftedFirstIndex);
            //store the char in the first index in the buffer array
            buffer[0] = charFromByte;

            //get the value at index zero and left shift it by 6
            byte zeroLeftShift = (state->byteArray[0]) << 6;
            //get the value at index 1 in a variable and right shift it by 4
            byte oneRightShift = (state->byteArray[1]) >> 4;
            //left shift by 2 the value above and store it in a variable
            oneRightShift <<= 2; 
            //or the value above with the variable that has the left shift of six on index 0
            oneRightShift |= zeroLeftShift;

            //right shift it back by two   
            oneRightShift >>= 2; 
            //call 8 bits to char on the variable above
            char charTwo = eightBitsToChar(oneRightShift);
            //add the second char to the buffer[1]
            buffer[1] = charTwo;
            state->bitCount+=6;
            initState(state);  
            return 2;   

        } else {
            //Get the value of the first index 
            byte firstByte = state->byteArray[0];
            //right shift the first index value 
            byte rightShiftedFirstIndex = firstByte >> 2; 
            //call 8 bits to char
            char charFromByte =  eightBitsToChar(rightShiftedFirstIndex);
            //store the char in the first index in the buffer array
            buffer[0] = charFromByte;
            //null terminate the final index buffer[1-4]
            buffer[1] = '\0';
            buffer[2] = '\0';
            buffer[3] = '\0';
            buffer[4] = '\0';
            //empty and re-initalize the state struct
            initState(state);
            //return 1 
            state->bitCount+=6;       
            return 1;              
        }

    }

    

    //Else if the state byte array has two bytes
    else if(bitCount >= 12 && bitCount < 18) {
        //Get the value of the first index 
        byte firstByte = state->byteArray[0];
        //right shift the first index value 
        byte rightShiftedFirstIndex = firstByte >> 2; 
        //call 8 bits to char
        char charFromByte =  eightBitsToChar(rightShiftedFirstIndex);
        //store the char in the first index in the buffer array
        buffer[0] = charFromByte;
    
        //get the value at index zero and left shift it by 6
        byte zeroLeftShift = (state->byteArray[0]) << 6;
        //get the value at index 1 in a variable and right shift it by 4
        byte oneRightShift = (state->byteArray[1]) >> 4;
        //left shift by 2 the value above and store it in a variable
        oneRightShift <<= 2; 
        //or the value above with the variable that has the left shift of six on index 0
        oneRightShift |= zeroLeftShift;

        //right shift it back by two   
        oneRightShift >>= 2; 
        //call 8 bits to char on the variable above
        char charTwo = eightBitsToChar(oneRightShift);
        //add the second char to the buffer[1]
        buffer[1] = charTwo;

        state->bitCount+=6; 


        //left shift the byte in idx 1 by 4 and store it in a variable (1)
        byte oneLeftShift = (state->byteArray[1]) << 4;
        //right shift the byte in idx 2 by six and store the variable (2)
        byte twoRightShift =  (state->byteArray[2]) >> 6;
        //right shift byte from (1) by 2 (3)
        oneLeftShift >>= 2; 
        //or (3) and (2) and store it in a variable
        oneLeftShift |= twoRightShift; 
        //call 8 bits to char on variable above
        char charThree = eightBitsToChar(oneLeftShift);
        //add the char to buffer[2]
        buffer[2] = charThree;  

        //null terminate the final index in the buffer array buffer[3] & buffer[4]
        buffer[3] = '\0';
        buffer[4] = '\0';
        //empty and re-initalize the state struct
        initState(state);
        //return 2       
        return 3;  
    }        

    //Else if the state byte array has three bytes
    else if(state->bitCount < 18) {
        //Get the value of the first index 
        byte firstByte = state->byteArray[0];
        //right shift the first index value 
        byte rightShiftedFirstIndex = firstByte >> 2; 
        //call 8 bits to char
        char charFromByte =  eightBitsToChar(rightShiftedFirstIndex);
        //store the char in the first index in the buffer array
        buffer[0] = charFromByte;
    
        //get the value at index zero and left shift it by 6
        byte zeroLeftShift = (state->byteArray[0]) << 6;
        //get the value at index 1 in a variable and right shift it by 4
        byte oneRightShift = (state->byteArray[1]) >> 4;
        //left shift by 2 the value above and store it in a variable
        oneRightShift <<= 2; 
        //or the value above with the variable that has the left shift of six on index 0
        oneRightShift |= zeroLeftShift;

        //right shift it back by two   
        oneRightShift >>= 2; 
        //call 8 bits to char on the variable above
        char charTwo = eightBitsToChar(oneRightShift);
        //add the second char to the buffer[1]
        buffer[1] = charTwo;

        //left shift the byte in idx 1 by 4 and store it in a variable (1)
        byte oneLeftShift = (state->byteArray[1]) << 4;
        //right shift the byte in idx 2 by six and store the variable (2)
        byte twoRightShift =  (state->byteArray[2]) >> 6;
        //right shift byte from (1) by 2 (3)
        oneLeftShift >>= 2; 
        //or (3) and (2) and store it in a variable
        oneLeftShift |= twoRightShift; 
        //call 8 bits to char on variable above
        char charThree = eightBitsToChar(oneLeftShift);
        //add the char to buffer[2]
        buffer[2] = charThree;  

        buffer[3] = '\0';
        buffer[4] = '\0';


            initState(state);
            return 3; 
    
    }



      else if(state->bitCount <= 24) {
        
        //Get the value of the first index 
        byte firstByte = state->byteArray[0];
        //right shift the first index value 
        byte rightShiftedFirstIndex = firstByte >> 2; 
        //call 8 bits to char
        char charFromByte =  eightBitsToChar(rightShiftedFirstIndex);
        //store the char in the first index in the buffer array
        buffer[0] = charFromByte;
    
        //get the value at index zero and left shift it by 6
        byte zeroLeftShift = (state->byteArray[0]) << 6;
        //get the value at index 1 in a variable and right shift it by 4
        byte oneRightShift = (state->byteArray[1]) >> 4;
        //left shift by 2 the value above and store it in a variable
        oneRightShift <<= 2; 
        //or the value above with the variable that has the left shift of six on index 0
        oneRightShift |= zeroLeftShift;

        //right shift it back by two   
        oneRightShift >>= 2; 
        //call 8 bits to char on the variable above
        char charTwo = eightBitsToChar(oneRightShift);
        //add the second char to the buffer[1]
        buffer[1] = charTwo;

        //left shift the byte in idx 1 by 4 and store it in a variable (1)
        byte oneLeftShift = (state->byteArray[1]) << 4;
        //right shift the byte in idx 2 by six and store the variable (2)
        byte twoRightShift =  (state->byteArray[2]) >> 6;
        //right shift byte from (1) by 2 (3)
        oneLeftShift >>= 2; 
        //or (3) and (2) and store it in a variable
        oneLeftShift |= twoRightShift; 
        //call 8 bits to char on variable above
        char charThree = eightBitsToChar(oneLeftShift);
        //add the char to buffer[2]
        buffer[2] = charThree;  
        
        //left shift the byte at index 3 by 2
        byte indexthreeLeftShift = (state->byteArray[2]) << 2;

        //right shift the variable above by 2
        indexthreeLeftShift >>= 2;

        //call 8 bits to char on variable above
        char fourthChar = eightBitsToChar(indexthreeLeftShift);
        //store the char in buffer[3]
        buffer[3] = fourthChar; 
        //null terminate the final index in the buffer array buffer[4]
        buffer[4] = '\0';

    
        //empty and re-initalize the state struct
        initState(state);
        return 4;
     }             
   
    //should never get here but return 0
    return 0;


}



