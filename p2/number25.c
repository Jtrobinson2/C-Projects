   /**
   * @file number25.c
   * @author Jakari Robinson (jtrobin6)
   * 
   * This file implements functionality for skipping spaces, parsing values and printing values in calc.c (base 25 version)
   *  
   */
  #include "number.h"
  #include <stdlib.h>
  #include <stdio.h>
  #include <stdbool.h>

  /**
  * Function reads charaters from standard input and keeps reading until it reaches a non 
  * whitespace character or EOF. It returns the code for the first non whitespace character it finds (or EOF)
  * Whitespace doesn't include \n chars. This function is just used to skip past whitespace within expresions
  * @return char code for the next non whitespace char.
  */
  int skipSpace() {
      int ch = getchar();
      while(ch != EOF && ch == ' ') {
          ch = getchar();
      }

      ungetc( ch, stdin );
      
      return ch; 
  }
   /**
   * Function converts a character to it's digit 
   * @param ch code you want to convert
   *  */ 
  int charToDigit(int ch) {
    //Checking A-O characters
    //if the char is a digit return the normal value
    if (ch >= '0' && ch <= '9') {
       return ch - '0';
    } 
    //if the char is a letter return the digit value for letters
    else if(ch >= 'A' && ch <= 'O') {
      return (ch - 'A') + 10;
    } 
    //should never get here
    return -1;
   

    

  }

     /**
   * Function converts a digit to character 
   * @param ch code you want to convert
   *  */ 
  int digitToChar(int ch) {
    //Checking A-O characters
    //if the char is a digit return the char
    if (ch >= 0 && ch <= 9) {
       return ch + '0';
    } 
    //if the char is a letter return the char value for the digit
    else if((ch + 'A' + 10  >= 'A') && (ch + 'O' + 10 <= 'O')) {
      if(((ch - 'A') + 10) == 'A') return 'A';
      if(((ch - 'B') + 10) == 'B') return 'B';
      if(((ch - 'C') + 10) == 'C') return 'C';
      if(((ch - 'D') + 10) == 'D') return 'D';
      if(((ch - 'E') + 10) == 'E') return 'E';
      if(((ch - 'F') + 10) == 'F') return 'F';
      if(((ch - 'G') + 10) == 'G') return 'G';
      if(((ch - 'H') + 10) == 'H') return 'H';
      if(((ch - 'I') + 10) == 'I') return 'I';
      if(((ch - 'J') + 10) == 'J') return 'J';
      if(((ch - 'K') + 10) == 'K') return 'K';
      if(((ch - 'L') + 10) == 'L') return 'L';
      if(((ch - 'M') + 10) == 'M') return 'M';
      if(((ch - 'N') + 10) == 'N') return 'N';
      if(((ch - 'O') + 10) == 'O') return 'O';
    } 
    //should never get here
    return -1;
   

    

  }


  
  /**
   * Function reads the next number from input. In numberC.10 it reads the number in base 10
   * vice versa for number25.c. If errors are detected in the input number the program is terminated
   * with the correct exit status
   *  @return number typed in from user
   */ 
  long parseValue() {

    //boolean for negative number found
    bool negativeNumber = false;

   // Value we've parsed so far.
   long value = 0;

   // Get the next input character.
   int ch = getchar();


       //If the first char is a negative sign
    if(ch == '-') {
      negativeNumber = true; 

      //get the next char 
      ch = getchar();

      //if we get another negative character or something that's invalid the whole thing is wrong
      if((ch == '-' || ch < '0' || ch > '9') && !(ch >= 'A' && ch <= 'O')) {
        printf("We failed negative test with char %c", ch);
        exit(FAIL_INPUT);
      }
    }

   //If the character isn't  a letter or in the number range 
   if((ch < '0' || ch > '9') && (ch < 'A' || ch > 'O')) {
     printf("We failed here with char %c", ch);
     exit(FAIL_INPUT);
   }





    
   // Keep reading as long as we're seeing digits or base 25 letters
   while ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'O')) {
    // Convert from ASCII code for the next digit into the value
    // of that digit.  For example 'A' -> 10 or '7' -> 7
    long d = charToDigit(ch);
    
    // Slide all digits we've read so far one place value to the
    // left.
    value = times(value, 25);
    
  
    // Add this digit as a new, low-order digit.
    value = plus(value, d);


    
    // Get the next input character.
    ch = getchar();
  }

    // ch was one character past the end of the number.  Put it back on
    // the input stream so it's there for other code to parse (see notes
    // below about ungetc()).
    ungetc( ch, stdin );
    
    //if the number was negative multiply the final value by -1
    if(negativeNumber) {
      return times(value, -1);
    }

    return value;
    
  }

  /**
   * Function prints the given value to standard output. In number10.c it will print the number
   * in base 10 vice versa for number25.c
   * 
   */  
  void printValue(long val) {
    if(val < 25) {
      printf("%ld\n", val);
      return;
    }    
    else {
      printf("%ld", val % 25);
      printValue(val / 25);
    }

  }


