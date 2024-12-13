/**
    @file input.c
    @author Sachi Vyas (smvyas)
    A program that reads: Reads words and lines on a character by character basis
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"
#include "replace.h"

/**
    Helps us read words and parse through an array of character to form a string
    @param str a character array with a capacity of 24 characters and a buffer
 */
void readWord ( char str[ FIELD_MAX + 1] ) 
{
    int ch = 0;
    int i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if ( i >= FIELD_MAX) {
            exit(101);
        }
        str[i++] = ch;
    }
    str[i] = '\0';
}

/**
    Helps us read line and parse through an array of character to form a sentence
    @param str a character array with a capacity of 80 characters and a buffer
 */
bool readLine( char str[ LINE_MAX + 1 ] ) 
{
    int ch = 0;
    int i = 0;
   
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (i >= LINE_MAX) {
            exit(103);
        }
        
        str[i++] = ch;
    }
    str[i] = '\0';

    if (ch == EOF && i == 0) {
        return false;
    }
    return true;
    
}