/**
 * @file io.c
 * @author Jakari Robinson
 * 
 * Program provides IO functionality to the wordle program
 * 
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "io.h"

bool readLine( FILE *fp, char str[], int n ) {
    
    /*Implementation from class textbook **/
    char currentChar = fgetc(fp); 
    int charsRead = 0; 
    


    while(currentChar != '\n' && currentChar != EOF) {
        if(charsRead < n) {
            str[charsRead] = currentChar;
            currentChar = fgetc(fp); 
            charsRead++;
        } else {
            currentChar = fgetc(fp);
        }

        
    }

    //close the string array off with null terminator
    str[charsRead] = '\0';

    //if we couldn't read anything return false; 
    if(charsRead == 0) {
        return false;
    } 

    return true; 
}

void colorGreen() {
    //print hexcode for green 
    printf("%s", "\x1B\x5B\x33\x32\x6D");
}

void colorYellow() {
    //print hexcode for yellow 
    printf("%s", "\x1B\x5B\x33\x33\x6D");
}

void colorDefault() {
    //print hexcode for black 
    printf("%s", "\x1B\x5B\x30\x6D");
}
