/**
*   @file input.h
*   @author Jakari Robinson
*   
*   This file contains common functions and variables for input.c and files whom depend on it
*/ 

#include <stdio.h>
#include <stdbool.h>


/**
 *  Reads a single line of input from a given file 
 *  and returns it as pointer to the newly created malloced string
 *  Function reads a line of text infintely large
 *  If the function couldn't read anything return NULL
 *  @param fp file pointer to file you want to read from 
 *  @return *char to array containing line contents
 */
char *readLine( FILE *fp );

