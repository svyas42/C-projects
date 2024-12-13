/**
    @file value.h
    @author Sachi Vyas (smvyas)
    A program that: Prototype of the functions in value.c
 */
#ifndef VALUE_H
#define VALUE_H

#include <stdbool.h>

/** Abstract type used to represent an arbitrary type of value. */
typedef struct ValueStruct {
  /** Pointer to a function that prints this value to the terminal.
      @param v Pointer to the value object to print. */
  void (*print)( struct ValueStruct const *v );

  /** Pointer to a function that frees memory for this Value instance.
      @param v Pointer to the value object to free. */
  void (*destroy)( struct ValueStruct *v );

  /** Arbitrary data used to represent the integer/string/etc for this value. */
  void *data;
} Value;

/** Return true if the given string contains only whitespace.  This
    is useful for making sure there's nothing extra at the end of a line
    of user input.
    @param str String to check for blanks.
    @return True if the string contains only blanks.
*/
bool blankString( char const *str );

/** If possible, parse an integer from the given string and return a
    Value instance containing it.  Return NULL if the string isn't in the
    proper format.
    @param str String from which to parse an integer.
    @return new Value containing the integer, or NULL if it's not in the proper format.
*/
Value *parseInteger( char const *str );
/**
    Helps us parse through a double
    @param *str pointer to a string to parse a double from
    @return Value the double parsed from the string
*/
Value *parseDouble( char const *str );
/**
    Helps us parse through an integer
    @param *str pointer to a string to parse an integer from
    @return Value the integer parsed from the string
*/
Value *parseString( char const *str );
 
#endif
