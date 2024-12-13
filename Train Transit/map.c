/**
    @file map.c
    @author Sachi Vyas (smvyas)
    A program that: Helps us parse through the map file.
 */
#include "map.h"
#include "numbers.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
/** Maximum number of locations. */
#define LOC_LIMIT 1000
/** Maximum number of tracks. */
#define TRACK_LIMIT ( LOC_LIMIT * ( LOC_LIMIT - 1 ) / 2 )


/** List to store the departure location */
static char srcList[LOC_LIMIT][NAME_LIMIT + 2];
/** List to store the arrival location */
static char destList[LOC_LIMIT][NAME_LIMIT + 2];
/** List to store the lengths */
static double trackLength[TRACK_LIMIT];
/** Index for track lengths list */
int m = 0;

/**
    Helps us parse through the map
    @param filename it is a pointer to a file (constant variable)
 */
void readMap( char const *filename ) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Can't open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    char l1[NAME_LIMIT + 2];
    char l2[NAME_LIMIT + 2];
    unsigned long distance = 0;
    int j = 0;  // Index for source list
    int k = 0;  // Index for destination list
    
    while (fscanf(file, "%21s", l1) == 1) {
        fscanf(file, "%21s", l2);

        readDistance(file, &distance);
        

        if (strlen(l1) > NAME_LIMIT || strlen(l2) > NAME_LIMIT) {
            fprintf(stderr, "Invalid map file: %s\n", filename);
            exit(EXIT_FAILURE);
        }
        
        for (int a = 0; a < m; a++) {
            if ((strcmp(srcList[a], l1) == 0 && strcmp(destList[a], l2) == 0) ||
            (strcmp(srcList[a], l2) == 0 && strcmp(destList[a], l1) == 0) ||(strcmp(srcList[a], destList[a]) == 0)) {
                fprintf(stderr, "Invalid map file: %s\n", filename);
                exit(EXIT_FAILURE);
            }
        }
        // Store the results
        if (m < TRACK_LIMIT) {
            strcpy(srcList[j], l1);
            strcpy(destList[k], l2);
            trackLength[m] = distance;
            j++;
            k++;
            m++;
        } else if (m > TRACK_LIMIT){
            fprintf(stderr, "Overflow\n");
            exit(EXIT_FAILURE);
        }
        if (j > LOC_LIMIT || k > LOC_LIMIT) {
            fprintf(stderr, "Invalid map file: %s\n", filename);
            exit(EXIT_FAILURE);
        }
    }

   
    fclose(file);
}

/**
    Gets the distance between two locations
    @param *dist is a pointer to an unsigned long where the distance between two destinations will be stored
    @param *src pointer to a string representing the departure location
    @param *dest pointer to a string representing the arrival location
    @return bool true if the distance is found and false otherwise

 */
bool getDistance( unsigned long *dist, char const *src, char const *dest ) 
{
    for (int i = 0; i < m; ++i) {

        if (strcmp(srcList[i], src) == 0 && strcmp(destList[i], dest) == 0) {
            *dist = trackLength[i];
            if (trackLength[i] > ULONG_MAX) {
                return false;
            }
            return true;
        }

        if (strcmp(srcList[i], dest) == 0 && strcmp(destList[i], src) == 0) {
            *dist = trackLength[i]; 
            if (trackLength[i] > ULONG_MAX) {
                return false;
            }
            return true; 
        }
    }
    return false;
}
