/** 
    @file driver.c
    @author Jakari Robinson, David Sturgil
    Main program for the hash map program.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "map.h"
#include "vtype.h"
#include "integer.h"
#include "text.h"
#include "input.h"

/** Maximum length for a command name. */
#define MAX_CMD 10

/** 
    Front-end for the Integer and Text parsing functions.  This tries
    to make an integer from the given string, and, failing that, tries
    to make a Text object.
    @param init String containing the initializaiton text.
    @param n Optional return for the number of characters used from init.
    @return pointer to the new VType instance.
    
 */
static VType *parseVType( char const *init, int *n )
{
  VType *val = parseInteger( init, n );

  // Add this code back when your text component is working.
  if ( ! val )
    val = parseText( init, n );
  
  return val;
}

/** Return true if the given string contains only whitespace.  This
    is useful for making sure there's nothing extra at the end of a line
    of user input.
    @param str String to check for blanks.
    @return True if the string contains only blanks.
*/
static bool blankString( char *str )
{
  // Skip spaces.
  while ( isspace( *str ) )
    ++str;

  // Return false if we see non-whiespace before the end-of-string.
  if ( *str )
    return false;
  return true;
}

/**
   Starting point for the program.
   @return exit status for the program.
 */
int main()
{
  // Make our map, with a 100-element table.
  Map *map = makeMap( 100 );

  // Keep reading input from the user.
  char *line;
  printf( "cmd> " );
  while ( ( line = readLine( stdin ) ) ) {
    // Echo the command back to the user.
    printf( "%s\n", line );

    // Extract the first word from the command.
    bool valid = false;
    char cmd[ MAX_CMD + 1 ];
    int n;
    if ( sscanf( line, "%10s%n", cmd, &n ) == 1 ) {
      // Pos keeps up with where we are in parsing the command.
      char *pos = line + n;
      if ( strcmp( cmd, "get" ) == 0 ) {
        // Parse the key from the command.
        VType *k = parseVType( pos, &n );
        if ( k ) {
          pos += n;

          // Make sure we got a key and there's nothing extra in the command.
          if ( blankString( pos ) ) {
            valid = true;
            VType *v = mapGet( map, k );
            // Report the value for this key, or undefined.
            if ( v ) {
              v->print( v );
              printf( "\n" );
            } else
              printf( "Undefined\n" );
          }

          // Free the key we parsed from the input.
          k->destroy( k );
        }
      } else if ( strcmp( cmd, "size" ) == 0 ) {
        // Any extra input after the command?
        if ( blankString( pos ) ) {
          // Report the size of the map.
          valid = true;
          printf( "%d\n", mapSize( map ) );
        }
      }

      //Else If the command says remove
      else if(strcmp( cmd, "remove" ) == 0) {
        //Parse the key from the command (like in get)
         VType *k = parseVType( pos, &n );
        //If the key is not null
        if( k ) {
          //pos +=n 
          pos += n; 
          ///If there is stuff after the key (blanstring == false)
          if(!blankString(pos)) {
            //set valid to false;
            valid = false; 
            //destroy the key
            k->destroy(k);            
          } 

          //Else there wasn't anything after the key
          else {
            valid = true; 
            //do map.remove(k)
            bool removedSuccessfully = mapRemove(map, k);
            //if map.remove returns false print "Not in map\n"
            if(!removedSuccessfully) printf("Not in map\n");
            //destroy the key
            k->destroy(k);                  
          }
    
        }
        //Else (if the key was null) set valid to false 
        else {
          valid = false;
        }   

      }

      //Else If the command says set 
      else if(strcmp( cmd, "set" ) == 0) {
        //Parse the key from the command (like in get)
        VType *k = parseVType( pos, &n );
        //if the key is not null
        if(k) {
          //pos+=n
          pos += n; 
          //If there is nothing after the key (blansktring == true)
          if(blankString(pos)) {
            //set valid to false
            valid = false; 
            //destroy they key
            k->destroy(k);            
          }

          //Else there was stuff after the first key
          else {
            //Parse the next key
             VType *value = parseVType( pos, &n );
            //pos+=n
            pos += n; 
            //if the next key was null (meaning it was invalid)
            if(!value) {
                //set valid to false
                valid = false; 
                //destory the first key
                k->destroy(k);              
            }

            //else the next key was valid (not null)
            else {
              //check to make sure there isn't garbage after the last key If (blankString != true)
              if(!blankString(pos)) {
                //If there was garbage after the last key set valid to false
                valid = false;
                //destroy both keys 
                k->destroy(k);
                value->destroy(value);                     
              }

              //else there wasn't anything after the last key 
              else {
                 //call map.set with first key and second key (value)
                //set valid to true
                mapSet(map, k, value);
       
                valid = true;                 
              }
                
            }
              
          }
     
      
        }


        //Else the first key was null (meaning there was nothing after set) 
        else {
          
          //set valid to false        
          valid = false; 
        }
          
    }

          
      else if ( strcmp( cmd, "quit" ) == 0 ) {
        // Free the current command and the map before exitign.
        
        free( line );
        freeMap( map );
        exit( EXIT_SUCCESS );
      }
    }

    // Print a message if we didn't get a valid command.
    if ( ! valid )
      
      printf( "Invalid command\n" );

    // Free the last command and prompt for another one.
    free( line );
    printf( "\ncmd> " );
  }

  // Free the map before exiting.
  freeMap( map );
  return EXIT_SUCCESS;
}
