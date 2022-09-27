/**
 * @file history.h
 * @author Jakari Robinson
 * 
 * This file contains common functions and variables for history.c operations in wordle 
*/

/**
 * Reads the scores.txt file, increments the count
 * with the given number of guesses, prints the score history after it
 * updated then saves the new score history back to scores.txt
 * 
 * @param guessCount the amount of guesses the current win to be saved took
 */
void updateScore( int guessCount );
