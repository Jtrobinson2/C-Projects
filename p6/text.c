/** 
    @file text.c
    @author Jakari Robinson
    Implementation of the Text VType.
*/

#include "text.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>




/**
 * @brief hashcode function for text structs
 * 
 * @param key the string used to generate the hashcode
 * @param length of the string inputted
 * @return unsigned int hashcode of string
 */
static unsigned int  hashCode(const char * key, size_t length) 
{
  //I'm storing the quotes with the string but that messes up the has so now I'm starting the hash without
  //the quotes (1 char above the start of the array and one char before the end)
  size_t i = 1;
  unsigned int  hash = 0;
  while (i < length - 1) {
    hash += key[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;

}

// print method for Text.
static void print( VType const *v )
{
  // Convert the VType pointer to a more specific type.
  Text const *this = (Text const *) v;
  printf( "%s", this->string );
}

// equals method for Text.
static bool equals( VType const *a, VType const *b )
{
  // Make sure the b object is also an Text.
  // (i.e., it uses the same print funtion)
  if ( b->print != print )
    return false;

  // Compare the val fields inside a and b.
  Text const *this = (Text const *) a;
  Text const *that = (Text const *) b;
  return strcmp(this->string, that->string) == 0; 
  // return strncmp(this->string, that->string) == 0;

}

// hash method for Text. 
static unsigned int hash( VType const *v )
{
  // Convert the VType pointer to a more specific type.
  Text const *this = (Text const *) v;

  //Call hashcode function passing in the string of the text obj and length of text obj
  unsigned int code = hashCode(this->string, this->stringLength);
  //return value from hashcode function
  return code;

}

// destroy method for Text.
static void destroy( VType *v )
{
  //Cast V to text object
  Text *this = (Text  *) v;
  //Free the string value in the text object
  free(this->string);
  // free the whole text struct itself
  free(this);

}

VType *parseText( char const *init, int *n )
{
  //Define int to store n
  int len  = 0; 
  //Define int to store the capacity of the temp char array
  int tempArrayCapacity = 10; 
  //Define an int to store the char count in the temp char array
  int tempArrayCharCount = 0;
  //Define a boolean to check if you've found the first quotation set it equal to false
  bool firstQuoteFound = false; 

  //boolean to see if second quote was found
  bool secondQuoteFound = false;
  //Malloc a temp char array with the size of the capacity 
  char *tempCharArray = (char *)calloc(tempArrayCapacity, sizeof(char));

  //length of the init string
  int initSize = strlen(init);


  //loop through the init array character by character
  for(int i = 0; i < initSize; i++) {
    //If adding another char to the temporary malloced char array makes it overflow resize the array
    if(tempArrayCharCount + 1 > tempArrayCapacity) {
      tempArrayCapacity *= 2; 
      tempCharArray = realloc(tempCharArray, tempArrayCapacity * sizeof (char) );
    }


    
    //if the current char is a space AND we haven't got the first quoatation don't add it to the char array
    if(isspace(init[i]) && !firstQuoteFound) {
      // increment n count 
      len++;
    }

  
      
    //Else if the current char is a quotation AND first quotation wasn't already true  set firstQuotation found to true
    else if(init[i] == '\"' && !firstQuoteFound)  {
      firstQuoteFound = true;
      tempCharArray[tempArrayCharCount] = init[i];  
      //increment char array char count 
      tempArrayCharCount++;
      
      //increment n count
      len++;
    }

      
    //Else if we found the first quotation ONLY and the current char isn't another quotation add the char to the char array
    else if(firstQuoteFound && !secondQuoteFound && init[i] != '\"') {
      tempCharArray[tempArrayCharCount] = init[i];
      //increment char array char count 
      tempArrayCharCount++;
      //increment n count
      len++;
    }  
  
    //Else if we found the first quotation and the current char is another quotation that means we've read the whole string don't add the char 
    //to the char array
    else if(firstQuoteFound && init[i] == '\"' && !secondQuoteFound) {
      secondQuoteFound = true; 
      tempCharArray[tempArrayCharCount] = init[i];
      //increment char array char count 
      tempArrayCharCount++;
      //increment n count
      len++;
    }
          
  }

      


  // Fill in the end pointer, if the caller asked for it.
  if ( n )
    *n = len;
  
  // Allocate an Text on the heap and fill in its fields.
  Text *this = (Text *) malloc( sizeof( Text ) );
  this->string = tempCharArray;
  this->stringLength = tempArrayCharCount; 
  this->print = print;
  this->equals = equals;
  this->hash = hash;
  this->destroy = destroy;

  // Return it as a poitner to the superclass.
  return (VType *) this;

}
