/**
 * @file history.c
 * @author Jakari Robinson
 * 
 * File contains operations for updates score history when the user wins the 
 * wordle program
 */

#include "history.h"
#include <stdlib.h>
#include <stdio.h>



void updateScore( int guessCount ) {
    //create an int array to store the scores you'll be reading from the file
    int scores[10] = {};

    //open the scores.txt file
    FILE *fp = fopen("scores.txt", "r");

    //if the file didn't exist
    if(!fp) {

        //create the file 
        fp = fopen("scores.txt", "w");

        //add the win to the current index of the array
        if(guessCount >= 10) {
            scores[9] += 1;
        } else {
            scores[guessCount - 1] += 1;
        }

        //print out the array to stdin
        for(int i = 0; i < 10; i++) {
            if(i == 9) {
                printf("10+ :%5d\n", scores[i]);
            } else {
                printf(" %d  :%5d\n", i + 1, scores[i]);
            }
        }
        
        //write the new arrary to the newly created scores.txt
        for(int i = 0; i < 10; i++) {
            if(i == 9) {
                fprintf(fp, "%d\n", scores[i]);
            } else {
                 fprintf(fp, "%d ", scores[i]);
            }
        }

        fclose(fp);

    } 
    
    //If the scores.txt file did exist
    else {
    
        //read 10 ints from the file and store them in the int array
        for(int i = 0; i < 10; i++) {
            fscanf(fp, "%d", &scores[i]);
        }

        //Increment the value at the index that corresponds to the guess count 
        //While rememebering Check if the guess count is 10 or more which means alter the final index value
        if(guessCount >= 10) {
            scores[9] += 1;
        } else {
            scores[guessCount - 1] += 1;
        }

        //loop through the modified int array and print each value to standard input as shown in the writeup
        for(int i = 0; i < 10; i++) {
            if(i == 9) {
                printf("10+ :%5d\n", scores[i]);
            } else {
                printf(" %d  :%5d\n", i + 1, scores[i]);
            }

        }

        //close the file for reading
        fclose(fp);

        //save the contents of the new array back to the file
        fp = fopen("scores.txt", "w");

        for(int i = 0; i < 10; i++) {
            if(i == 9) {
                fprintf(fp, "%d\n", scores[i]);
            } else {
                fprintf(fp, "%d ", scores[i]);
            }
            
        }
        //free up memory 
        fclose(fp);
        
    }

}

