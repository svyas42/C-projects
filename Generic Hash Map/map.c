/**
    @file map.c
    @author Sachi Vyas (smvyas)
    A program that: Helps us make changes in the map by allowing us to set, add, and remove elements
 */
#include "map.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
/** Magic number used in the uint32_t function */
#define NUM_6 6
/** Magic number used in the uint32_t function */
#define NUM_10 10
/** Magic number used in the uint32_t function */
#define NUM_3 3
/** Magic number used in the uint32_t function */
#define NUM_11 11
/** Magic number used in the uint32_t function */
#define NUM_15 15

/** Node containing a key / value pair. */
typedef struct NodeStruct {
  /** String key for this map entry. */
  char key[ KEY_LIMIT + 1 ];
  
  /** Pointer to the value part of the key / value pair. */
  Value *val;
  
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

/**
    This function makes an empty, dynamically allocated Map, initializing its fields and returning a pointer to it.
    @param len gives the number of elements in the hash table.
    @return a pointer to a allocated map
 */
Map *makeMap( int len ) 
{
    Map *m = (Map*)malloc(sizeof(Map));
    // if (m == NULL) {
    //     return NULL;
    // }
    m->tlen = len;
    m->size = 0;
    m->table = (Node **) calloc(len, sizeof(Node *));
    // if (!m->table) {
    //     free(m);
    //     exit(EXIT_FAILURE);
    // }
    return m;
}

/**
    Function returns the current number of key / value pairs in the given map.
    @param *m pointer to a map to return the size for
    @return the size of the map
 */
int mapSize( Map *m ) 
{
    // if (m == NULL) {
    //     return 0;
    // }
    return m->size;
}

/**
    The key hashing function to use to help us compute the Jenkins 32-bit hash function
    @param *key pointer to a key that we need to hash
    @param length the length of the key
    @return hash of the key as a 32 bit hash
*/
uint32_t jenkins_one_at_a_time_hash(const uint8_t *key, size_t length) 
{
    uint32_t hash = 0;
    size_t i = 0;
    while (i != length) {
        hash += key[i++];
        hash += (hash << NUM_10);
        hash ^= (hash >> NUM_6);
    }
    hash += (hash << NUM_3);
    hash ^= (hash >> NUM_11);
    hash += (hash << NUM_15);
    return hash;
}

/**
    Sets a given key value pair in the map
    @param *m the pointer to a map to put the key-value pair in
    @param *key pointer to a key to put in the map
    @param *val pointer to a value of the key
 */
void mapSet( Map *m, char const *key, Value *val ) 
{
    if (m == NULL || key == NULL || val == NULL) {
        return;
    }
    uint32_t hashVal = jenkins_one_at_a_time_hash((const uint8_t *) key, strlen(key));
    int idx = hashVal % m->tlen;
    Node *curr = m->table[idx];
    while(curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            free(curr->val);
            curr->val = val;
        }
      curr = curr->next;
    }
    Node *newMap = (Node *)malloc(sizeof(Node));
    strncpy(newMap->key, key, KEY_LIMIT);
    newMap->key[KEY_LIMIT] = '\0';
    newMap->val = val;
    newMap->next = m->table[idx];
    m->table[idx] = newMap;
    m->size++;
}

/**
    Gets a value from the map based on the key
    @param *m a pointer to a map
    @param *key a pointer to key
    @return Value the value of the given key
 */
Value *mapGet( Map *m, char const *key ) 
{
  
    uint32_t hashVal = jenkins_one_at_a_time_hash((const uint8_t *) key, strlen(key));
    int idx = hashVal % m->tlen;
    Node *curr = m->table[idx];
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            return curr->val;
        }
    }
    return NULL;
}

/**
    Removes a given key-value pair from the map
    @param *m pointer to a map
    @param *key pointer to a key
    @return bool returns true or false based on the fact if the key-value pair is successfully removed from the map
 */
bool mapRemove( Map *m, char const *key ) 
{
    uint32_t hashVal = jenkins_one_at_a_time_hash((const uint8_t *) key, strlen(key));
    int idx = hashVal % m->tlen;
    Node *curr = m->table[idx];
    Node *prev = NULL;
    while (curr != NULL) {
        if (strcmp(curr->key, key) == 0) {
            if (prev == NULL) {
                m->table[idx] = curr->next;
            }
           
            free(curr);

            m->size--;
            return true;
        }
    }
    return false;
}

/**
    Frees a map
    @param *m pointer to a map to free
 */
void freeMap( Map *m ) 
{
    /**
    for (int i = 0; i < m->tlen; i++) {
        free(m->table[i]);
    }
    free(m->table);
    free(m);
    */

    for (int i = 0; i < m->tlen; i++) {
        Node *curr = m->table[i];

        // Free each linked list at this index
        while (curr != NULL) {
            Node *next = curr->next;

            if (curr->val && curr->val->destroy) {
                curr->val->destroy(curr->val);
            }
            free(curr);
            curr = next;
        }
    }
    free(m->table);
    free(m);
}
