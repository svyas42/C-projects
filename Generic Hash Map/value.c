/**
    @file value.c
    @author Sachi Vyas (smvyas)
    A program that: Helps us parse through the line to get the integer, double, and string components
 */
#include "value.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
    Checks if a string is blank
    @param *str pointer to string to check
    @return bool based on the fact if the string is blank or not
 */
bool blankString( char const *str )
{
  // Skip spaces.
  while ( isspace( *str ) )
    ++str;

  // Return false if we see non-whitespace before the end-of-string.
  if ( *str )
    return false;
  return true;
}

/**
    Generic destroy method, suitable for most types of values.  It
    assumes the data can be freed as a single block of heap memory.
    @param *v pointer to a value to destroy
 */
static void destroyGeneric( Value *v )
{
    //printf("Destroying value of type: %p\n", v->data);

  free( v->data );
  free( v );
}

/**
    Print method for Integer.
    @param *v pointer to a value integer to print
 */
static void printInteger( Value const *v )
{
  // Print the data as an integer.
  printf( "%d", * (int *) v->data );
}

/**
    Print method for double
    @param *v pointer to value double to print
 */
static void printDouble( Value const *v )
{
  // Print the data as an integer.
  printf( "%lf", * (double *) v->data );
}

/**
    Print method for string
    @param *v pointer to value string to print
 */
static void printString( Value const *v )
{
  // Print the data as an string
  printf( "%s", (char *) v->data );
}

/** If possible, parse an integer from the given string and return a
    Value instance containing it.  Return NULL if the string isn't in the
    proper format.
    @param str String from which to parse an integer.
    @return new Value containing the integer, or NULL if it's not in the proper format.
*/
Value *parseInteger( char const *str )
{
    // Parse an integer value from the given string.
    int val, n;
    if ( sscanf( str, "%d%n", &val, &n ) != 1 )
        return NULL;

    // Make sure there's nothing extra after the integer value
    if ( ! blankString( str + n ) )
        return NULL;
    
    // Allocate space for the value struct and the integer in its data field.
    Value *this = (Value *) malloc( sizeof( Value ) );
    this->data = malloc( sizeof( int ) );
    * (int *) this->data = val;

    // Fill in function pointers and return this value.
    this->print = printInteger;
    this->destroy = destroyGeneric;
    return this;
}

/**
    Helps us parse through a double
    @param *str pointer to a string to parse a double from
    @return Value the double parsed from the string
*/
Value *parseDouble( char const *str ) 
{
    double val;
    int n;
    if (sscanf( str, "%lf%n", &val, &n ) != 1) {
        return NULL;
    }

    if ( ! blankString( str + n ) ) {
        return NULL;
    }

    Value *this = (Value *)malloc(sizeof(Value));
    this->data = malloc(sizeof(double));
   
    * (double *) this->data = val;

    this->print = printDouble;
    //printf("Destroying value of type: %p\n", this->data);
    this->destroy = destroyGeneric;
    return this;
}

/**
    Helps us parse through an integer
    @param *str pointer to a string to parse an integer from
    @return Value the integer parsed from the string
*/
Value *parseString(char const *str) {
    
    char *unescapedStr = (char *)malloc(strlen(str) + 1);
    const char *escapeStr = str;
    char *withoutEscape = unescapedStr;

    while (*escapeStr != '\0') {
        if (*escapeStr == '\\') {
            escapeStr++; 
            switch (*escapeStr) {
                case 'n':
                    *withoutEscape++ = '\n';
                    break;
                case 't':
                    *withoutEscape++ = '\t';
                    break;
                case '"':
                    *withoutEscape++ = '"';
                    break;
                case '\\':
                    *withoutEscape++ = '\\';
                    break;
                default:
                    free(unescapedStr);
                    return NULL;
                
            }
        } else {
            *withoutEscape++ = *escapeStr;
        }
        escapeStr++;
    }
    *withoutEscape = '\0'; 

    Value *this = (Value *)malloc(sizeof(Value));
  
    this->data = unescapedStr;
    this->print = printString;
    this->destroy = destroyGeneric;
    return this;
}

