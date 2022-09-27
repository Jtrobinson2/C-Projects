  /**
   * @file number10.c
   * @author Jakari Robinson (jtrobin6)
   * 
   * This file implements functionality for skipping spaces, parsing values and printing values in calc.c
   *  
   */
  #include "number.h"
  #include <stdio.h>
  #include <stdbool.h>
  #include <stdlib.h>


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
    return ch - '0';
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

   //If the character is a letter exit appropriately
   if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
     exit(FAIL_INPUT);
   }

    //If the first char is a negative sign
    if(ch == '-') {
      negativeNumber = true; 

      //get the next char 
      ch = getchar();

      //if we get another negative character or something that's invalid the whole thing is wrong
      if(ch == '-' || ch < '0' || ch > '9') {
        exit(FAIL_INPUT);
      }
    }



    
   // Keep reading as long as we're seeing digits.
   while (ch >= '0' && ch <= '9') {
    // Convert from ASCII code for the next digit into the value
    // of that digit.  For example 'A' -> 10 or '7' -> 7
    long d = charToDigit(ch);
    
    // Slide all digits we've read so far one place value to the
    // left.
    
    value = times(value, 10);
    
  
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
    printf("%ld\n", val);
  }




