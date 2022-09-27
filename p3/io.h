/**
 * @file io.h
 * @author Jakari Robinson
 * 
 * This file contains common functions and variables for io operations in wordle 
*/

#include <stdio.h>




/**
 * Function reads a line of text from a file and stores it in a char array. 
 * The function only reads the first n characters the rest is discarded. Returns boolean true if it could 
 * read the line, false if there was no additional input. True also means there was an additional 
 * line of input 
 * 
 * @param *fp pointer to the file you want to read a line from
 * @param str[] char array you want to store the line in
 * @param n amount of characters you want to store in the char array
 * */ 
bool readLine( FILE *fp, char str[], int n );

/**
* Function changes the terminal output text color to green
* 
*/
void colorGreen();

/**
* Function changes the terminal output text color to yellow
*/
void colorYellow();

/** 
*This function changes the text color back to the default.
*/
void colorDefault(); 


