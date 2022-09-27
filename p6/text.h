/**
 * @file text.h
 * @author Jakari Robinson
 * @brief Header file for text.c component
 * 
 */

#ifndef TEXT_H
#define TEXT_H

#include "vtype.h"

/** Subclass of VType for storing strings. */
typedef struct {
  /** Inherited from VType */
  void (*print)( struct VTypeStruct const *v );

  /** Inherited from VType */
  bool (*equals)( struct VTypeStruct const *a,
                  struct VTypeStruct const *b );

  /** Inherited from VType */
  unsigned int (*hash)( struct VTypeStruct const *b );

  /** Inherited from VType */
  void (*destroy)( struct VTypeStruct *v );

  /** Value stored by this text object. */
  char *string;

  /**length of the string stored in text field */ 
  int stringLength;
} Text;

/** Make an instance of text holding a value parsed from the init string.
    @param init String containing the initializaiton value as text.
    @param n Optional return for the number of characters used from init.
    @return pointer to the new VType instance.
*/
VType *parseText( char const *init, int *n );

#endif


