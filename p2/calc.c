  /**
  * @file calc.c
  * @author Jakari Robinson jtrobin6
  * 
  * Top level component of the calculator program, this file uses all the 
  * other components and is responsible for evaluating whole expressions and printing
  * the result to the terminal. This contains the main function
  *
 */

  #include "operation.h"
  #include "number.h"
  #include <stdio.h>
  #include <stdbool.h>
  #include <stdlib.h>
  
  /**
   * Function reads parts of an expression between plus or minus operators. Each time 
   * this is called it reads a sequence of one or more number with a multiple or divide operator in 
   * between and returns the value that the part of the expression evaluates to.
   * If there is just a number with no operators after it just returns the number. 
   * @return the result of the terms operations or the term itself 
   *  
   * */ 
  static long parseTerm() {

  long result = 0; 

  int character = getchar();

    

  while(character != '+'  && character != '\n' && character != EOF) {
    ungetc(character, stdin);
    result = parseValue();

    skipSpace();
    character = getchar();
    if(character == '/') {
        skipSpace();
        long divisor = parseValue();
        result = (result / divisor);
        skipSpace(); 
        character = getchar();
    } else if(character == '*') {
        skipSpace();
        long multiplier = parseValue();
        result = (result * multiplier); 
        skipSpace();
        character = getchar();   
    } else {
      if(character == '+' || character == '-') {
        ungetc(character, stdin);
        return result;
      } 
      
      else if(character == EOF || character == '\n') {
        return result; 
      }

      character = getchar(); 
    }

  } 
  ungetc(character, stdin);
  return result;

}

  /**Entry point to the program
   * @return EXIT_STATUS (0 if successful)
   * 
   */   
  int main( void ) {
    skipSpace();
    int character = getchar(); 
    long result = 0; 
    bool firstIteration = true;

    while(character != '\n' && character != EOF) {
      if(firstIteration) {
        skipSpace();
        ungetc(character, stdin);
        result = parseTerm();
        skipSpace();
        
        firstIteration = false;
      }

      else {
        result += parseTerm();
        skipSpace();
        character = getchar();
        //if the next char is an addition
        if(character == '+' ) {
          skipSpace();
          // add the next parsed term
          result += parseTerm();
        } else if(character == '-') {
            skipSpace();
            result -= parseTerm();
        } else {
          if(character == EOF || character == '\n') {
            printValue(result);
            exit(EXIT_SUCCESS);
          }
        }
        if(character == EOF || character == '\n') {
           printValue(result);
           exit(EXIT_SUCCESS);
        }
        character = getchar(); 

        }
    
    }
    ungetc(character, stdin);
    printValue(result);

}





