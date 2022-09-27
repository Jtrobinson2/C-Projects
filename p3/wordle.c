/**
 * @file wordle.c
 *
 * @author Jakari Robinson
 *
 * Entry point of the worlde program compiles all dependicies for
 * the program and plays the game
 */
#include "history.h"
#include "lexicon.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

/**
 * Static helper method to check if a char is in a given word
 * @param ch your looking for
 * @param word you searching for that has the char
 * @return true if the char was in the word
 * undefined behavior for words longer than 5 chars not including null terminator
 *
 */
static bool inWord(char ch, char word[]) {
    for (int i = 0; i < WORD_LEN; i++) {
        if (word[i] == ch) {
            return true;
        }
    }
    return false;
}

/**
 * Helper method to tell you how many times a char appears in a given word
 * @param ch you're looking to find the amount of instances of 
 * @param word word you're searching for the char in
 * @param wordLength of word you're searching in
 * @return amount of times that char is in that word
 */
static int instancesInWord(char ch, char word[], int wordLength) {
    int instanceCount = 0;

    for(int i = 0; i < wordLength; i++) {
        if(word[i] == ch) {
            instanceCount++; 
        }
    }
    return instanceCount;
}

/**
 * Main method of the program
 * @param numberOfCommandLineArgs number of command line arguements
 * @param commandLineArgs array of pointers to each of the command line argument strings
 * @return EXIT_STATUS
 */
int main(int numberOfCommandLineArgs, char *commandLineArguements[]) 
{
    //boolean keeping track of terminal colors
    bool terminalIsBlack = true; 
    bool terminalIsYellow = false; 
    bool terminalIsGreen = false;

    // Define a boolean to signal if the user won
    bool wordGuessed = false;

    // define an int to hold how many guesses were made
    int guessCount = 0;

    // define an array of length 5 to store the chosen word
    char chosenWord[WORD_LEN + 1] = {};

    // define an long to store the possible seed from the user
    long userChosenSeed = 0;



    // If we have more than three or less than 2 then print this message to standard error:
    // usage: wordle <word-list-file> [seed-number], and exit the program with a status of 1
    if (numberOfCommandLineArgs == 1 || numberOfCommandLineArgs > 3) {
        fprintf(stderr, "usage: wordle <word-list-file> [seed-number]");
        fprintf(stdin, commandLineArguements[0]);
        exit(EXIT_FAILURE);
    }
    // If we have (two) command line arguements the  last one is the file name
    // Get the file name and readwords from the file
    else if (numberOfCommandLineArgs == 2) {
        readWords(commandLineArguements[1]);

        // choose the seed number based on time
        userChosenSeed = time(0);

        // choose the word
        chooseWord(userChosenSeed, chosenWord);
    }

    // If we have three command line arguments get the file name and seed number
    else if (numberOfCommandLineArgs == 3) { 
        readWords(commandLineArguements[1]);
        userChosenSeed = atol(commandLineArguements[2]);

        // If we can't parse the seeed number into a positive long then print this message to standard error:
        // usage: wordle <word-list-file> [seed-number], and exit the program with a status of 1
        if (userChosenSeed <= 0) {
            fprintf(stderr, "usage: wordle <word-list-file> [seed-number]");
            exit(EXIT_FAILURE);
        }
        // choose the word
        chooseWord(userChosenSeed, chosenWord);
    }

    // keep reading the users guesses while they haven't guessed the word and we haven't hit EOF (EOF handled in readline)
    while (!wordGuessed) {
        // stores the current word read from stdin
        char currentWord[WORD_LEN + 2] = {};

        //array to keep track of yellow characters for duplicate purposes
        char yellowCharArray[WORD_LEN + 1] = {};

        //array to keep track of green characters for duplicate purposes
        char greenCharArray[WORD_LEN + 1] = {};

        //int to keep up with where to add new yellow chars so they are consecutive in the char array
        int yellowCharIndex = 0; 

        //int to keep up with where to add new yellow chars so they are consecutive in the char array
        int greenCharIndex = 0;

        // read the current word
        bool successfulRead = readLine(stdin, currentWord, 6);

        //Check if the word we read in was too long
        if(strlen(currentWord) > 5) {
            printf("Invalid guess\n");
            continue;
        }

        // If the user types in "quit" or if we hit EOF
        if (strcmp(currentWord, "quit") == 0 || !successfulRead) {
            printf("The word was \"%s\"\n", chosenWord);
            exit(EXIT_SUCCESS);
        }
        // If the user guesses an word that isn't in the word list print Invalid guess \n to stdin
        // after reading an invalid guess ignure the entire line of input and wait for the users to make another guess
        else if (!inList(currentWord)) {
            printf("Invalid guess\n");
            continue;
        }

        // If they made valid guess
        else {
            // if the whole word equals the whole chosen word execute the win sequence
            if (strcmp(currentWord, chosenWord) == 0) {
                guessCount++;
                wordGuessed = true; 
                break;
            }

            // If the valid guess wasn't right
            else {
                //Get all the green chars from there guess for comparison later
                for(int j = 0; j < WORD_LEN; j++) {
                            
                    char guessedLetterAtIndex = currentWord[j];
                    char correctLetterAtIndex = chosenWord[j];

                    if(guessedLetterAtIndex == correctLetterAtIndex) {
                        greenCharArray[greenCharIndex++] = guessedLetterAtIndex;
                    }

                }


                // if the whole word wasn't right loop through all the chars in the guessed word
                for (int i = 0; i < WORD_LEN; i++) {

                    char guessedLetterAtIndex = currentWord[i];
                    char correctLetterAtIndex = chosenWord[i];

                    // if the char at index i in the guessed word == the char at index i in the chosen word
                    if (guessedLetterAtIndex == correctLetterAtIndex) {

                        //check if the terminal is already green 
                        if(!terminalIsGreen) {
                            // change the terminal color to green
                            colorGreen();
                            terminalIsGreen = true;
                            terminalIsBlack = false; 
                            terminalIsYellow = false;
                        }
                        // print the given char
                        putchar(guessedLetterAtIndex);
                    }
                    // else if the char at index i is in the chosen word but in the wrong spot
                    else if (inWord(guessedLetterAtIndex, chosenWord)) {

                        //if the amount of green chars of that character throughout the guessed word is the same as the amount of that char in the target word
                         int instancesofGreenCharForChecking = instancesInWord(guessedLetterAtIndex, greenCharArray, strlen(greenCharArray));

                         int instancesOfGreenCharInWord = instancesInWord(guessedLetterAtIndex, chosenWord, WORD_LEN);

                         if(instancesofGreenCharForChecking == instancesOfGreenCharInWord) {
                            //don't add  the yellow char to the yellow char array
                            //print the color to be black instead                
                            if(!terminalIsBlack) {
                                colorDefault();    
                                terminalIsYellow = false; 
                                terminalIsBlack = true; 
                                terminalIsGreen = false;
                                putchar(guessedLetterAtIndex);
                                continue;
                            }
                            
                         }


                        // if those checks are clear add the char to the yellow char array to keep track
                        yellowCharArray[yellowCharIndex++] = guessedLetterAtIndex;
                        
                        //check how many instances of the char are in the chosen word
                        int instancesOfYellowChar = instancesInWord(guessedLetterAtIndex, chosenWord, WORD_LEN);


                        //check how many instances we have already picked up from the yellow char array
                        int instancesOfYellowCharFound = instancesInWord(guessedLetterAtIndex, yellowCharArray, strlen(yellowCharArray));

                        //check how many instances we already picked up in the green char array
                        int instanceOfGreenCharFound = instancesInWord(guessedLetterAtIndex, greenCharArray, strlen(greenCharArray));


                        //if the adding one to the instances we've picked up is greater than or equal to the amount of that yellow char in the word
                        //Or adding another is greater than or equal to the amount green char 
                        if(instancesOfYellowCharFound > instancesOfYellowChar || instanceOfGreenCharFound >= instancesOfYellowChar || instanceOfGreenCharFound + instancesOfYellowCharFound > instancesOfYellowChar) {
                            //don't color that char yellow print it out as black                    
                            if(!terminalIsBlack) {
                                // change the terminal color to black
                                colorDefault();    
                                terminalIsYellow = false; 
                                terminalIsBlack = true; 
                                terminalIsGreen = false;
                            }
                            putchar(guessedLetterAtIndex);
                            continue;

                        } else {
                            // change the terminal color to yellow if it's not yellow
                            if(!terminalIsYellow) {
                                colorYellow();    
                                terminalIsYellow = true; 
                                terminalIsBlack = false; 
                                terminalIsGreen = false;
                            }

                        }

                        // print the given char
                        putchar(guessedLetterAtIndex);
                } 
                // else the char isn't in the word
                else {
                    //check if the terminal is already black
                    if(!terminalIsBlack) {
                        // change the terminal color to default
                        colorDefault();
                        terminalIsBlack = true; 
                        terminalIsGreen = false; 
                        terminalIsYellow = false;
                    }
                    
                    putchar(guessedLetterAtIndex);

                    }
                }
                
            }

            //change the terminal color to default when you've printed all the characters in the guess word (if it's not already default)
            if(!terminalIsBlack) {
                colorDefault();
                terminalIsBlack = true; 
                terminalIsYellow = false; 
                terminalIsGreen = false;
            }

            //terminate the line
            putchar('\n');
            guessCount++;
        }
    }



    // if the guess count was 1 print out Solved in 1 guess to stdin
    if(guessCount == 1) {
        printf("Solved in 1 guess\n");
        // then print the score history report
        updateScore(guessCount); 
    } 
    
    // If the guess count was > 1 print out the line Solved in n guesses where n is the guessCount
    else if(guessCount > 1) {
        printf("Solved in %d guesses\n", guessCount);
        // then print the score history report
        updateScore(guessCount);
    }

    return EXIT_SUCCESS;
}