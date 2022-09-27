/** 
    @file map.c
    @author Jakari Robinson, David Sturgil
    Hash table implementation of a map.
*/
#include "map.h"
#include "vtype.h"
#include <stdlib.h>
#include <stdio.h>


/** Node containing a key / value pair. */
typedef struct NodeStruct {
  /** Pointer to the key part of the key / value pair. */
  VType *key;
  
  /** Pointer to the value part of the key / value pair. */
  VType *val;
  
  /** Pointer to the next node at the same element of this table. */
  struct NodeStruct *next;
} Node;

/** Representation of a hash table implementation of a map. */
struct MapStruct {
  /** Table of key / value pairs. */
  Node **table;

  /** Current length of the table. */
  int tlen;
  
  /** Current size of the map (number of different keys). */
  int size;
};


Map *makeMap( int len )
{
  Map *m = (Map *) malloc( sizeof( Map ) );
  m->size = 0;

  //set the length of the maps's table field (tlen) to 5
  m->tlen = len; 
  //calloc an array of (tlen) node pointers and make the table pointer point to this
  m->table = (Node **)calloc(m->tlen, sizeof(Node *));
  
  return m;
}

int mapSize( Map *m )
{
  return m->size;
}

VType *mapGet( Map *m, VType *key )
{
  //create unsigned int called index to store the hash of the key
  unsigned int index = 0; 
  //call the key's hash function and store it in that int above % tlen
  index = key->hash(key);
  index %= m->tlen;
  

  
  //Go to index of the map's table field
  Node *head = m->table[index];
  //if the pointer at that index of the map's table field is pointing to NULL return NULL the key wasn't in the map
  if(head == NULL) return NULL;

  //loop through the linked-list of nodes from the index pointer

  for(Node *n = head; n; n = n->next) {
    //If a nodes key equals the arguement key passed in 
      if(n->key->equals(key, n->key)) {
        //get the value of the current key and return it
        
          
        return (n->val);
    }

  }

  //If we got here we didn't find the key
  return NULL;
}

void freeMap( Map *m )
{

  //loop through each node pointer in the map's table field 
  for(int i = 0; i < m->tlen; i++) {
    //node pointer pointing to the start of the current linked list in the table
    Node *head = m->table[i];
     //for each node pointer loop through it's linked list of nodes
    while(head) {
      Node *next = head->next;
      //for each node call the destroy function it's key and value
       head->key->destroy(head->key);
       head->val->destroy(head->val);
       
       //free the node itself
       free(head);
       head = next; 
    }
    
  }
    //free the node pointer in maps table field
    free(m->table);
  
  //free the map itself
  free( m );
}

void mapSet( Map *m, VType *key, VType *val ) 
{
  //create an unsigned int called index to store the key's hash
  unsigned int index = 0; 
  //call key.hash and store hash in the index variable % tlen
  index = key->hash(key);
  index %= m->tlen;
  //Go to that index in the map table field
  Node *head = m->table[index];

    //If that index in the table was pointing to null malloc a new node for the linked list
    if(!m->table[index]) {

      Node *newNode = (Node *)malloc(sizeof(Node));
      newNode->key = key; 
      newNode->val = val;

      //add the new node to the front the list
       newNode->next =  m->table[index];
       m->table[index] = newNode;
      
      //increment the size count of the map
      m->size++;
      return; 
    }
    
    //loop through all the linked list nodes that pointer at index is pointing too
    for(Node *n = head; n; n = n->next) {
        //check if the current node's key is equal to the argument key
        if(n->key->equals(n->key, key)) {
          // if so call that nodes value's destroy method
          n->val->destroy(n->val);
          //set that nodes value field to point to the val passed into the function
          n->val = val; 

          //destory the malloced key we don't need it
          key->destroy(key);
          //return from the function
          return;           
        }
    }

    //If we got here the key wasn't in the map malloc a  new node with the given key and value
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key; 
    newNode->val = val;

    //add the new node to the front the list
    newNode->next = m->table[index];
    m->table[index] = newNode;
  
    //increment the size count of the map
    m->size++;
    
}

 
bool mapRemove( Map *m, VType *key ) 
{
  //create an unsigned int called index to store the key's hash
  unsigned int index = 0; 
  //call key.hash and store hash in the index variable % tlen
  index = key->hash(key);
  index %= m->tlen;

  //Go to the index in the map's table array 
  Node *head = m->table[index];

  //check if the front of the list is actually pointing to a node
  if(!head) {
    key->destroy(key);
    return false;
  }

  //Check if we have to remove the first node in the list
  if(head->key->equals(head->key, key)) {
    Node *n =  m->table[index];
    m->table[index] =  m->table[index]->next;
    n->key->destroy(head->key);
    n->val->destroy(head->val);
    free(n);
    m->size--;
    return true;

  }

  //We'd get here if we have to remove nodes that aren't the first node in the list
  Node *pred = head; 
  while(pred->next && pred->next->key->equals(pred->next->key, key)) {
    pred = pred->next;
  }
  //remove the node 
  if(pred->next) {
    Node *n = pred->next;
    pred->next = pred->next->next;
    n->key->destroy(n->key);
    n->val->destroy(n->val);
    free(n);
    m->size--;
    return true;
  }

  //If we got here there was nothing to remove
  return false;

}



