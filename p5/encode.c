/**
 * @file encode.c
 * @author Jakari Robinson
 * @brief  program is responsible for encoding binary files to txt files
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "state24.h"
#include "filebuffer.h"

/**
 * @brief Main method of encode program
 * 
 * @param numberOfCommandLineArgs number of commandlineargs
 * @param commandLineArguements command line args  
 * @return EXIT SUCCESS
 */
int main(int numberOfCommandLineArgs, char *commandLineArguements[])  {
    //boolean for if -b flag was enabled All the encoded output will be output on one line, with just one newline character at the end. otherwise newlines are 76 chars and at the end
    bool  bflagEnabled = false;

    //boolean for if -p flag was enabled then no padding 
    bool pFlagEnabled = false;

    //variable for bflag
    char bFlag[] = {"-b"};
    //variable for pflag
    char pFlag[] = {"-p"};

    char *inputF;

    char *outputF;

    int maxCharCount = 76;


    //variable to keep track of char count
    int charCount = 0; 
    
    //Check that we have valid command line args

    //If we have five or more args
    if(numberOfCommandLineArgs >= 5 ) {
        //Check that we have a "-b" and "-p" update the booleans accordingly
        if(strcmp(commandLineArguements[1], bFlag) == 0) {
            bflagEnabled = true;  
        } else {
            fprintf(stderr, "usage: encode [-b] [-p] <input-file> <output-file>\n");
            exit(EXIT_FAILURE);
        }

        if(strcmp(commandLineArguements[2], pFlag) == 0)  {
            pFlagEnabled = true; 
        } else {
            fprintf(stderr, "usage: encode [-b] [-p] <input-file> <output-file>\n");
            exit(EXIT_FAILURE);
        }

        //Check that the last two are not "-b" "-p"
        if(strcmp(commandLineArguements[numberOfCommandLineArgs - 2], bFlag) == 0 || strcmp(commandLineArguements[numberOfCommandLineArgs - 1], pFlag) == 0) {
           //If these checks fail print to stderr "usage: encode [-b] [-p] <input-file> <output-file>\n" exit status 1 
            fprintf(stderr, "usage: encode [-b] [-p] <input-file> <output-file>\n");
            exit(EXIT_FAILURE);
        }

        inputF = commandLineArguements[3];
        outputF = commandLineArguements[4];
        

    
    }

    //If we have three args check that the last two aren't "-b" or "-p" update the booleans accordingly BUT if this fails  print to stderror "usage: encode [-b] [-p] <input-file> <output-file>\n" exit status 1        
    else if(numberOfCommandLineArgs == 3) {
       if(strcmp(commandLineArguements[numberOfCommandLineArgs - 2], bFlag) == 0 || strcmp(commandLineArguements[numberOfCommandLineArgs - 1], pFlag) == 0) {
           //If these checks fail print to stderr "usage: encode [-b] [-p] <input-file> <output-file>\n" exit status 1 
            fprintf(stderr, "usage: encode [-b] [-p] <input-file> <output-file>\n");
            exit(EXIT_FAILURE);
        }

        inputF = commandLineArguements[1];
        outputF = commandLineArguements[2];

    } 
    //Else we don't even have the right amount of commmand args
    else {
        fprintf(stderr, "usage: encode [-b] [-p] <input-file> <output-file>\n");
        exit(EXIT_FAILURE);
    }


    
    //Attempt to open the input file
    FILE *inputFile = fopen(inputF, "r");

    //If it couldn't be opened perror "filename: No such file or directory" exit 1
    if(!inputFile) {
        
        perror(inputF);
        exit(EXIT_FAILURE);
    }

    fclose(inputFile);
    
    //Attempt to open the output file
    FILE *outputFile = fopen(outputF, "r");

    //Make and Load a file buffer with the input fileName
    FileBuffer *filebuffer = loadFileBuffer(inputF);

    //Make a filebuffer that will be used to save to an output file
    FileBuffer *fileBufferToSave = makeFileBuffer();

    //Create a state24 struct to convert the bytes from the file to chars
    State24 *state24 = (State24 *) malloc(sizeof(State24));
    //init the state 24 struct
    initState(state24);

    //Loop through each byte in the filebuffer used to load the input file
    for(int i = 0; i < filebuffer->numOfBytes; i++) {
        //if not at capcitiy add the byte to the state24 like normal
        addByte(state24, filebuffer->data[i]);
        
        //Check if the byte count on the state struct is at capactity
        if(state24->byteCount == 3) {
            
            //If so to getChars on the stateStruct passing in a 5 character array and store the int value of characters
            //written to the array in a variable
            char getCharsArray[5]; 
            int charsFromGetChars = getChars(state24, getCharsArray); 
            
            //Loop through the chars in the character array (up to variable storing how much was written to it) and append each char to the save file 
            //buffer
            for(int i = 0; i < charsFromGetChars; i++) {

                //if adding the next char is the 76th AND bflag is enabled char append a new line to the save file buffer
                if(!bflagEnabled && charCount + 1 == maxCharCount)  {
                    appendFileBuffer(fileBufferToSave, getCharsArray[i]);
                    appendFileBuffer(fileBufferToSave, '\n');
                     //reset the char count to 0
                    charCount = 0; 
                } else {
                    //add the char like normal 
                    appendFileBuffer(fileBufferToSave, getCharsArray[i]);
                    charCount++;
                }
                       
            }          
        }

        //check if we're on the last iteration and if the state still had bytes left do padding behavior
        else if(i == filebuffer->numOfBytes - 1 && state24->byteCount != 3) {
                    //If we had one left over byte (state bytecount == 1)
        if(state24->byteCount == 1) {
            //if padding was enabled
            if(!pFlagEnabled) {
                char state24Chars[3];
                //store the chars found here in an int call getChars on the state24 to get the two chars from the first byte
                int charsFromGetChar =  getChars(state24, state24Chars);
                //append the two chars to the save file buffer
                appendFileBuffer(fileBufferToSave, state24Chars[0]);
                appendFileBuffer(fileBufferToSave, state24Chars[1]);
                //append two '=' to the save file buffer          
                appendFileBuffer(fileBufferToSave, '=');
                appendFileBuffer(fileBufferToSave, '=');      
            }

            //else if padding wasn't enabled 
            else if(pFlagEnabled) {
                char state24Chars[3];
                 //store the chars found here in an int call getChars on the state24 to get the two chars from the first byte
                int charsFromGetChar = getChars(state24, state24Chars);
                //append the two chars to the save file buffer 
                appendFileBuffer(fileBufferToSave, state24Chars[0]);
                appendFileBuffer(fileBufferToSave, state24Chars[1]);        
            }
         
        }

        //If we had two left over bytes (state bytecoutn == 2)
        else if(state24->byteCount == 2) {
            //if padding was enabled
            if(!pFlagEnabled) {
                char state24Chars[4];
                 //store the chars found here in an int call getChars on the state24 to get the three chars from the two bytes
                int charsFromGetChar = getChars(state24, state24Chars);
                //append the three chars to the save file buffer
                appendFileBuffer(fileBufferToSave, state24Chars[0]);
                appendFileBuffer(fileBufferToSave, state24Chars[1]);
                appendFileBuffer(fileBufferToSave, state24Chars[2]);

                //append one '=' to the save file buffer  
                appendFileBuffer(fileBufferToSave, '=');             
            }

            //else if padding wasn't enabled 
            else if(pFlagEnabled) {
                //store the chars found here in an int call getChars on the state24 to get the three chars from the two bytes
                char state24Chars[4];
                int charsFromGetChar = getChars(state24, state24Chars);
                //append the two chars to the save file buffer  
                appendFileBuffer(fileBufferToSave, state24Chars[0]);
                appendFileBuffer(fileBufferToSave, state24Chars[1]);
                appendFileBuffer(fileBufferToSave, state24Chars[2]);              
                }    

            }
        }

    }

    appendFileBuffer(fileBufferToSave, '\n');

    //Call saveFileBuffer passing in the saveFilebuffer and the filename is the output file from the command args 
    saveFileBuffer(fileBufferToSave, commandLineArguements[numberOfCommandLineArgs - 1]);


    
    free(state24);
    freeFileBuffer(filebuffer);
    freeFileBuffer(fileBufferToSave);        
    return EXIT_SUCCESS;


}
