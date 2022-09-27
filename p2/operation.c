/**
 * @file operation.c
 * @author Jakari Robinson (jtrobin6)
 * 
 * This files implements plus minus mutliply and divide  functions to be used in calc.c 
 */
  #include "operation.h"
  #include <stdbool.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <limits.h>

  /**
  * Function adds the given paramtrs and returns the result. 
  * It is used to detect overflow and terminates the program if overflow occurs
  * @param a first long you want to add 
  * @param b second long you want to add 
  * @return long result of adding both longs
  */
  long plus(long a, long b) {
      long sum = a + b; 
       //if both nums are positive and the sum was negative it overflowed
       if(a && b > 0 && sum < 0) {
           exit(EXIT_FAILURE);
       } 
       //If both nums are negative and the sum is positive it overflowed
       else if((a && b < 0) && (sum > 0)) {
           exit(EXIT_FAILURE);
       } else {
           return a + b; 
       }
           
    }
  

  /**
   * Function subtracts two longs and if it detects overflow terminates the program
   * @param a the first long you want to subtract
   * @param b the second long you want  to subtract
   * @return the result of the subtraction.
   */
  long minus(long a, long b) {
      long diff = a - b;
    
      //we'll only get overflow if we have a positive minus an negative or negative -  positive    
      if((a > 0) && (b < 0) && (diff < 0) ) {
          //above is saying if its positive minus negative 
          //and the result is negative it overflowed
          exit(OVERFLOW_FAILURE_CODE);
      } else if((a < 0) && (b > 0) && (diff > 0)) {
          //if it's negative - positive and the result is positive it overflowed
          exit(OVERFLOW_FAILURE_CODE);
      }
       else {
           return diff;
       }

  }
  /**
   *  Function divdes does a / b and returns the result. If you try to divide by zero
   * the program will be terminated. Overflow is also detected
   * @param a first number you want in the numerator
   * @param b the second number you want in the denominator
   * @return result of a / b 
   * */ 
  long divide(long a, long b) {
      //If we try to divide by zero exit the program
      if(b == 0) {
          exit(101);
      } 
      //One possible overflow LONG_MIN / -1
      else if(a == LONG_MIN && b == -1) {
          exit(OVERFLOW_FAILURE_CODE);
      } else {
          return a / b;
      } 
  }

  /**
   * Does multiplcation with two specified longs passed in detects overflow and terminates 
   * the program
   * @param a first long you want to multiply 
   * @param b sescond long you want to multiply 
   * @return the result of multiplication.
   *  */ 
  long times(long a, long b) {
      

      //if we're dealing with two positives
      if(a > 0 && b > 0) {
          long x = LONG_MAX / b; 
          if(a > x) {
              exit(OVERFLOW_FAILURE_CODE);
          }
      } 
      //if we're dealing with positive negative cases
      else if(a > 0 && b < 0) {
          long x = LONG_MIN / a; 
          if(b < x) {
              exit(OVERFLOW_FAILURE_CODE);
          }
      }
      //if we're dealing with positive negative cases
       else if(a < 0 && b > 0) {
          long  x = LONG_MIN / b; 
          if(a < x) {
              exit(OVERFLOW_FAILURE_CODE);
          }
      } 
          return a * b;
      

  }


   
  