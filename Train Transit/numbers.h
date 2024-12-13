/**
    @file numbers.h
    @author Sachi Vyas (smvyas)
    The header file for numbers.c file with the prototypes for methods
 */
#include <stdbool.h>
#include <stdio.h>
/**
    Adds two unsigned long numbers together
    @param *result pointer to a variable where the addition result is suppose to be stored
    @param a the first unsigned long number to add
    @param b the second unsigned long number to add
    @return boolean true if the operation was successful and false otherwise
 */
bool add( unsigned long *result, unsigned long a, unsigned long b );
/**
    Subtracts two unsigned long numbers together
    @param *result pointer to a variable where the subtraction result is suppose to be stored
    @param a the first unsigned long number to subtract
    @param b the second unsigned long number to subtract
    @return boolean true if the operation was successful and false otherwise
 */
bool subtract( unsigned long *result, unsigned long a, unsigned long b );
/**
    Multiplies two unsigned long numbers together
    @param *result pointer to a variable where the multiplication result is suppose to be stored
    @param a the first unsigned long number to multiply
    @param b the second unsigned long number to multiply
    @return boolean true if the operation was successful and false otherwise
 */
bool multiply( unsigned long *result, unsigned long a, unsigned long b );
/**
    Subtracts two unsigned long numbers together
    @param *fp pointer to a file from where we are suppose to read the long number
    @param *result pointer to a variable where the long number is suppose to be stored
    @return boolean true if the long number was read successfully and false otherwise
 */
bool readLongNumber( FILE *fp, unsigned long *result );
/**
    Reads distance values from the given input stream.
    @param *fp pointer to a file from where we are suppose to read the long number
    @param *result pointer to a variable where the long number is suppose to be stored
    @return boolean true if the long number was read successfully and false otherwise
 */
bool readDistance( FILE *fp, unsigned long *result );
