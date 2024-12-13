/**
    @file map.h
    @author Sachi Vyas (smvyas)
    The header file for map.c file with the prototypes for methods
 */
#include <stdbool.h>

/** Maximum length of a location name. */
#define NAME_LIMIT 20
/**
    Helps us parse through the map
    @param filename it is a pointer to a file (constant variable)
 */
void readMap( char const *filename ) ;
/**
    Gets the distance between two locations
    @param *dist is a pointer to an unsigned long where the distance between two destinations will be stored
    @param *src pointer to a string representing the departure location
    @param *dest pointer to a string representing the arrival location
    @return bool true if the distance is found and false otherwise

 */
bool getDistance( unsigned long *dist, char const *src, char const *dest );
