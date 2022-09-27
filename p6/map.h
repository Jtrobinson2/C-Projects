/** 
    @file map.h
    @author Jakari Robinson
    Header for the map component, a hash map.
*/

#ifndef MAP_H
#define MAP_H

#include "vtype.h"
#include <stdbool.h>

/** Incomplete type for the Map representation. */
typedef struct MapStruct Map;

/** Make an empty map.
    @param len Initial length of the hash table.
    @return pointer to a new map.
*/
Map *makeMap( int len );

/** Get the size of the given map.
    @param m Pointer to the map.
    @return Number of key/value pairs in the map. */
int mapSize( Map *m );
  
/** Return the value associated with the given key. The returned VType
    is still owned by the map.
    @param m Map to query.
    @param k Key to look for in the map.
    @return Value associated with the given key, or NULL if the key
    isn't in the map.
*/
VType *mapGet( Map *m, VType *key );

/** Free all the memory used to store a map, including all the
    memory in its key/value pairs.
    @param m The map to free.
*/
void freeMap( Map *m );

/**
 * @brief function removes they key value pair for the given key from the map 
 * freeing all the memory of that pair. returns  true if there was  matching key in the map
 * false otherwise. Caller is responsible for freeing the key arguement passed in
 * @param m map you're searching for the key in 
 * @param key key in the map you're looking to remove
 * @return true if you found the designated key in the map false otherwise
 * 
 */
bool mapRemove( Map *m, VType *key );

/**
 * @brief adds a key value pair to a given map. If the key already in the map it replaces the keys
 * value with a given value. The map now owns the key value pair. The map free's these two objects when they
 * are no longer needed (the key and value)
 * 
 * @param m map you want to add or set a key value pair into
 * @param key you want to set/add in the given map
 * @param val you want to set/add in the given map 
 */
void mapSet( Map *m, VType *key, VType *val );
  
#endif
