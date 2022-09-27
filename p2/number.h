/**
 * @file number.h
 * @author Jakari Robinson (jtrobin6)
 * 
 * This file defines constant and functions to be re-used in number.c and calc.c 
 */

  /** Exit status indicating that the program was given invalid input. */
  #define FAIL_INPUT 102

  #include "operation.h"


  /**
  * Function reads charaters from standard input and keeps reading until it reaches a non 
  * whitespace character or EOF. It returns the code for the first non whitespace character it finds (or EOF)
  * Whitespace doesn't include \n chars. This function is just used to skip past whitespace within expresions
  * @return char code for the next non whitespace char.
  */
  int skipSpace();
  
  /**
   * Function reads the next number from input. In numberC.10 it reads the number in base 10
   * vice versa for number25.c. If errors are detected in the input number the program is terminated
   * with the correct exit status
   *  @return number typed in from user
   */ 
  long parseValue();

  /**
   * Function prints the given value to standard output. In number10.c it will print the number
   * in base 10 vice versa for number25.c
   * 
   */  
  void printValue(long val);

  


