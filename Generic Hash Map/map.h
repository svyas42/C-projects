/**
    @file map.h
    @author Sachi Vyas (smvyas)
    A program that: Prototype for the map.c function
 */
#ifndef MAP_H
#define MAP_H

#include "value.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
/** Incomplete type for the Map representation. */
typedef struct MapStruct Map;

// Maximum length of a key.
#define KEY_LIMIT 24

/**
    This function makes an empty, dynamically allocated Map, initializing its fields and returning a pointer to it.
    @param len gives the number of elements in the hash table.
    @return a pointer to a allocated map
 */
Map *makeMap( int len );
/**
    Function returns the current number of key / value pairs in the given map.
    @param *m pointer to a map to return the size for
    @return the size of the map
 */
int mapSize( Map *m );
/**
    The key hashing function to use to help us compute the Jenkins 32-bit hash function
    @param *key pointer to a key that we need to hash
    @param length the length of the key
    @return hash of the key as a 32 bit hash
*/
uint32_t jenkins_one_at_a_time_hash(const uint8_t *key, size_t length);
/**
    Sets a given key value pair in the map
    @param *m the pointer to a map to put the key-value pair in
    @param *key pointer to a key to put in the map
    @param *val pointer to a value of the key
 */
void mapSet( Map *m, char const *key, Value *val );
/**
    Gets a value from the map based on the key
    @param *m a pointer to a map
    @param *key a pointer to key
    @return Value the value of the given key
 */
Value *mapGet( Map *m, char const *key );
/**
    Removes a given key-value pair from the map
    @param *m pointer to a map
    @param *key pointer to a key
    @return bool returns true or false based on the fact if the key-value pair is successfully removed from the map
 */
bool mapRemove( Map *m, char const *key );

/**
    Frees a map
    @param *m pointer to a map to free
 */
void freeMap( Map *m ); 
#endif
