
/**
    @file numbers.c
    @author Sachi Vyas (smvyas)
    A program that: Helps us perform calculations when outputting stuff in the output file.
 */
#include "numbers.h"
#include <limits.h>
#include <ctype.h>
/** Number of fractional digits in a number representing a distance. */
#define DISTANCE_FRAC 1
/** Number to multiply to get the decimal removed */
#define CONSTANT 10

/**
    Adds two unsigned long numbers together
    @param *result pointer to a variable where the addition result is suppose to be stored
    @param a the first unsigned long number to add
    @param b the second unsigned long number to add
    @return boolean true if the operation was successful and false otherwise
 */
bool add( unsigned long *result, unsigned long a, unsigned long b ) 
{
    if (b > ULONG_MAX - a) {
        return false;
    }
    else {
        *result = a + b;
        return true;
    }
}

/**
    Subtracts two unsigned long numbers together
    @param *result pointer to a variable where the subtraction result is suppose to be stored
    @param a the first unsigned long number to subtract
    @param b the second unsigned long number to subtract
    @return boolean true if the operation was successful and false otherwise
 */
bool subtract( unsigned long *result, unsigned long a, unsigned long b )
{
    
    if (a < b) {
        return false;
    }
    else {
        *result = a - b;
        return true;
    }
}

/**
    Multiplies two unsigned long numbers together
    @param *result pointer to a variable where the multiplication result is suppose to be stored
    @param a the first unsigned long number to multiply
    @param b the second unsigned long number to multiply
    @return boolean true if the operation was successful and false otherwise
 */
bool multiply( unsigned long *result, unsigned long a, unsigned long b )
{   
    if (a != 0 && (a > ULONG_MAX / b)) {
        return false;
    }
    else {
        *result = a * b;
        return true;
    }
}

/**
    Subtracts two unsigned long numbers together
    @param *fp pointer to a file from where we are suppose to read the long number
    @param *result pointer to a variable where the long number is suppose to be stored
    @return boolean true if the long number was read successfully and false otherwise
 */
bool readLongNumber( FILE *fp, unsigned long *result )
{
    
    int ch;
    unsigned long value = 0;

    //skipping the white space before the number
    do {
        ch = fgetc(fp);
    } while (isspace(ch));

    if (ch == EOF) {
        return false;
    }

    while (!isdigit(ch)) {
        ungetc(ch, fp);
        return false;
    }
    //ch = fgetc(fp);
    while (isdigit(ch)) {
        int d = ch - '0';
        value = value * CONSTANT + d;
        ch = fgetc(fp);
        
    }

    if (ch != EOF) {
        ungetc(ch, fp);
    }

    *result = value;
    return true;
}

/**
    Reads distance values from the given input stream.
    @param *fp pointer to a file from where we are suppose to read the long number
    @param *result pointer to a variable where the long number is suppose to be stored
    @return boolean true if the long number was read successfully and false otherwise
 */
bool readDistance( FILE *fp, unsigned long *result )
{    
    int ch;
    unsigned long value = 0;
    int decimals = 0;

    //skipping the white space before the number
    do {
        ch = fgetc(fp);
    } while (isspace(ch));

    while (!isdigit(ch)) {
        ungetc(ch, fp);
        return false;
    }

    while (isdigit(ch)) {
        int d = ch - '0';
        value = value * CONSTANT + d;
        ch = fgetc(fp);
        
    }

    //checking is there is a '.' or not, if not there then just return the integers
    if (ch != '.') {
        ungetc(ch, fp);
        *result = value * CONSTANT;
        return true;
    }

    //now check if after decimal there is only one digit if not then put it back in the input stream
    ch = fgetc(fp);
    if (!isdigit(ch) && ch != '.') {
        ungetc(ch, fp);
        return false;
    }

    //convert from ASCII code for the next digit into the value of that digit
    decimals = ch - '0';
    
    //now if the character is digit then (if there is a second digit)
    ch = fgetc(fp);
    if (isdigit(ch)) {
        ungetc(ch, fp);
        return false;
    }
   
   *result = value * CONSTANT + decimals;
    return true;
}






