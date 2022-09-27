/**
 * @file decode.c
 * @author Jakari Robinson
 * @brief program is responsible for converterting binary files 
 * to txt files
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "state24.h"
#include <ctype.h>
#include "filebuffer.h"

/**
 * @brief Main method of decode program
 * 
 * @param numberOfCommandLineArgs number of commandlineargs
 * @param commandLineArguements command line args  
 * @return EXIT SUCCESS
 */
int main(int numberOfCommandLineArgs, char *commandLineArguements[])  {
    //Check that we have valid command line args

    //If we don't have three arguements print "usage: decode <input-file> <output-file>" to stderr exit 1
    if(numberOfCommandLineArgs != 3)  {
        fprintf(stderr, "usage: decode <input-file> <output-file>");
        exit(EXIT_FAILURE);
    }
          
    //Attempt to open the input file
    FILE *inputFile = fopen(commandLineArguements[1], "r");

    //If it couldn't be opened perror "filename: No such file or directory" exit 1
    if(!inputFile) {
        
        perror(commandLineArguements[1]);
        exit(EXIT_FAILURE);
    }


    

    
    //Make and Load a file buffer with the input fileName
    FileBuffer *filebuffer = loadFileBuffer(commandLineArguements[1]);

    //Make a filebuffer that will be used to save to an output file
    FileBuffer *fileBufferToSave = makeFileBuffer();

    //Create a state24 struct to convert the bytes from the file to chars
    State24 *state24 = (State24 *) malloc(sizeof(State24));
    //init the state 24 struct
    initState(state24);

    char ch = fgetc(inputFile); 
    
    //check for that one case there is a period and it maps to an A
    while(ch != EOF) {
        if(ch == '.') {
            fprintf(stderr, "Invalid input file\n");
            free(state24);
            freeFileBuffer(fileBufferToSave);
            fclose(inputFile);
            exit(EXIT_FAILURE);
         
        }
        ch = fgetc(inputFile);
    }

    fclose(inputFile);

    //Loop through each byte in the filebuffer used to load the input file
    for(int i = 0; i < filebuffer->numOfBytes; i++) {
        //Check if the byte count on the state struct is at capactity
        if(state24->byteCount == 3) {
            //If so to getChars on the stateStruct passing in a 5 character array and store the int value of characters
            //written to the array in a variable
            bool equalsFound = false;
            byte getBytesArray[3]; 
            char getCharArray[4];
            State24 tempState24 = *state24; 
            int bytesFromGetBytes = getBytes(state24, getBytesArray);
            int charsFromGetChars = getChars(&tempState24, getCharArray);

            //checking for invalid chars
            for(int i = 0; i < charsFromGetChars; i++) {
                if(!validChar(getCharArray[i]) ||  (equalsFound && (getCharArray[i] != '='))) {
                    fprintf(stderr, "Invalid input file\n");
                    free(state24);
                    freeFileBuffer(fileBufferToSave);
                    exit(EXIT_FAILURE);
                }
                else if(getCharArray[i] == '=') {
                    equalsFound = true; 
                }
            }

            //loop through the byte array appending the bytes to the saveFileBuffer
            for(int i = 0; i < bytesFromGetBytes; i++) {
                appendFileBuffer(fileBufferToSave, getBytesArray[i]);
            }          
        }

        //if not at capcitiy add the byte to the state24 like normal
        addChar(state24, filebuffer->data[i]);
    }

    //if there were some left over bytes from the state array append them to the filebuffer
    if(state24->byteCount % 3 != 0) {
        byte getBytesArray[4];
        int bytesFromGetBytes = getBytes(state24, getBytesArray);
        for(int i = 0; i < bytesFromGetBytes; i++) {
            appendFileBuffer(fileBufferToSave, getBytesArray[i]);
        } 

    }

    saveFileBuffer(fileBufferToSave, commandLineArguements[2]);
    freeFileBuffer(fileBufferToSave);
    free(state24);



    
return EXIT_SUCCESS;
}