/**
 * @file lexicon.h
 * @author Jakari Robinson
 * 
 * This file contains common functions and variables for lexicon operations in wordle 
*/

#include <stdbool.h>
#include "io.h"

/** Maximum lengh of a word on the word list. */
#define WORD_LEN 5

/** Maximum number of words on the word list. */
#define WORD_LIMIT 100000

/**
 * Function reads word list from the file with the given name. It detects errors in the word list 
 * and prints an error message
 * 
 * @param filename[] of file you want to read from 
 */ 
void readWords( char const filename[] );

/**
 * function chooses a word from the word list and copies it 
 * into the word array
 * @param seed number you want to use to get the random word
 * @param word array that stores the word that you chose
 * */
void chooseWord( long seed, char word[] );

/**
 * checks the given word to see if it's in the word list
 * @param word word you want to check thats in the word list 
 * @return true if the word is in the list false if it isn't
 * 
 */ 
 bool inList( char const word[] );



