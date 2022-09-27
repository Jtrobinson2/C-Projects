/**
 * @file operation.h
 * @author Jakari Robinson (jtrobin6)
 * 
 * This files defines common operation functions and variables for the calculator that will be used in operation.c 
 */

  /**Exit status for an overflow failure */ 
  #define OVERFLOW_FAILURE_CODE 100

  /**
  * Function adds the given paramtrs and returns the result. 
  * It is used to detect overflow and terminates the program if overflow occurs
  * @param a first long you want to add 
  * @param b second long you want to add 
  * @return long result of adding both longs
  */
  long plus(long a, long b);

  /**
   * Function subtracts two longs and if it detects overflow terminates the program
   * @param a the first long you want to subtract
   * @param b the second long you want  to subtract
   * @return the result of the subtraction.
   */
  long minus(long a, long b); 
  /**
   *  Function divdes does a / b and returns the result. If you try to divide by zero
   * the program will be terminated. Overflow is also detected
   * @param a first number you want in the numerator
   * @param b the second number you want in the denominator
   * @return result of a / b 
   * */ 
  long divide(long a, long b);

  /**
   * Does multiplcation with two specified longs passed in detects overflow and terminates 
   * the program
   * @param a first long you want to multiply 
   * @param b sescond long you want to multiply 
   * @return the result of multiplication.
   *  */ 
  long times(long a, long b);
  
   
  