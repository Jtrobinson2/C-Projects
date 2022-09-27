/**
*   @file input.c
*   @author Jakari Robinson 
*   
*   Code that handles I/O operations in the agency program
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


char *readLine( FILE *fp ) {
    //Create a variable to keep track of the char arrays capacity
    int capacity = 11; 

    //Create a varibale to keep track of the char count in the char array
    int charCount = 0; 

    //Create a char array with a set capacity and malloc it
    char *readLine = (char *)calloc(11, sizeof(char));

    //Get the first char to read call it current char
    char currentChar = fgetc(fp);



    //start reading chars while you haven't hit end of file or a new line
    while(currentChar != EOF && currentChar != '\n') {
        //if the char count is equal to the capacity of the array
        if(charCount == capacity) {  
        //resize the array 
        capacity *= 2;

        readLine = (char *) realloc(readLine, capacity * sizeof(char));

        }

        //then store the new char
        readLine[charCount] = currentChar; 
        
        //incrememnt the char count
        charCount++;

        currentChar = fgetc(fp);

    }


        //After reading all the chars if char count was 0 meaning we couldn't read anything return NULL
        if(charCount == 0) {
            //free the memory
            free(readLine);
            return NULL;
        }

        //check if the char count is at capacity already before we close of the char array with a  null terminator
        if(charCount == capacity) {
             //If it's at capacity resize the array again
            capacity *= 2;
            readLine = (char *) realloc(readLine, capacity * sizeof(char));
        }
       
        //Reguardless if it's at capacity or not add the null terminator to the char array
        readLine[charCount] = '\0';

        //return the pointer to the malloced char array
        return readLine; 
}
