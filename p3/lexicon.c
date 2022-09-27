#include "lexicon.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

/** Large prime multiplier used to choose a word pseudo-randomly. */
#define MULTIPLIER 4611686018453

//Array of strings to store all the words
char wordArray[WORD_LIMIT][WORD_LEN + 1];

//Stores the current amount of words in the word array
int wordCount = 0; 


void readWords( char const filename[] ) {
    //Attempt to open a file with the given fileName
    FILE *file = fopen(filename, "r");

    //If you can't open the file (file pointer is null) then print Can't open word list: filename to standard error
    //and exit the program with exit status of 1
    if(!file) {
        fprintf(stderr, "Can't open word list: %s", filename);
        exit(EXIT_FAILURE);
    }

    //character array to store words to check for duplicates
    char stringArray[WORD_LEN + 2]; 

    //Read the words from the file
    while(readLine(file, stringArray, WORD_LEN + 1)) {

        //If the word you read wasn't exactly 5  characters exit with a status of 1 with the 
        //message Invalid word file printed to standard error
        if(strlen(stringArray) != WORD_LEN) {
             fprintf(stderr, "Invalid word file\n");
             exit(EXIT_FAILURE);
        }


        //if the word wasn't exactly five lowerecase characters exit with a status of 1
        for(int i = 0; stringArray[i]; i++) {
            if(!(stringArray[i] >= 'a' && stringArray[i] <= 'z')) {
                 fprintf(stderr, "Invalid word file\n");
                 exit(EXIT_FAILURE);
            }
        }

        //Check if your about to read one too many words if so exit the program
        if(wordCount + 1 > WORD_LIMIT) {
             fprintf(stderr, "Invalid word file\n");
             exit(EXIT_FAILURE);
        }

        //add the word to the wordList 
        strcpy(wordArray[wordCount], stringArray);

        //reset the string array for the next word read in
        char emptyString[7] =  {'\0'};

        strcpy(emptyString, stringArray);

        wordCount++;
    }


     //After reading all the words check if you actually read any words from the file
     if(wordCount == 0) {
         fprintf(stderr, "Invalid word file\n");
         exit(EXIT_FAILURE);
     }

     //Now check for duplicates in the word list, if you find one exit with a status of 1 
     //with the message invalid word file printed to stanrdard error
     for(int i = 0; i < wordCount; i++) {

         //get the current word
         char currentWord[6] = {'\0'};
         strcpy(currentWord, wordArray[i]);
        
        //compare it with the rest of the words
        for(int j = i + 1 ; j < wordCount; j++) {
            //if you find a duplicate word exit
            if(strcmp(currentWord, wordArray[j]) == 0) {
                 fprintf(stderr, "Invalid word file\n");
                 exit(EXIT_FAILURE);
            } 
        }

        
     }
    
     //Free up memory   
    fclose(file);

}


void chooseWord( long seed, char word[] ) { 

    //get the index of the chosen word
    long index = (seed % wordCount) * MULTIPLIER % wordCount;

    //Get the chosen word from the wordArray using the index 
    strcpy(word, wordArray[index]);
    
}

 bool inList( char const word[] ) {
     //loop through all the words
     for(int i = 0; i < wordCount; i++) {

         //check the current word at a given index
         if(strcmp(wordArray[i], word) == 0) {
             return true;
         }
     }
    
    //return false since we didn't find the word
     return false;

 }