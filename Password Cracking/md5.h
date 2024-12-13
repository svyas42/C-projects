/**
    @file md5.h
    @author Sachi Vyas (smvyas)
    A program that: Prototype for md5.c
 */
#ifndef _MD5_H_
#define _MD5_H_

#include "block.h"

/** Number of bytes in a MD5 hash */
#define HASH_SIZE 16
/** Setting a variable for the 32 bit */
#define BIT_32 32
/** Setting a variable for the 48 bit */
#define BIT_48 48
/** Setting a variable for the 8 bit */
#define MULTIPLIER_8 8
/** Setting a variable for number 3 */
#define NUM_3 3
/** Variable for number 4 */
#define NUM_4 4
/** Mutiplier 2 */
#define NUM_2 2
/** Variable for number 7 */
#define NUM_7 7
/** Variable for number 6 */
#define NUM_6 6
/** Variable for number 15 */
#define NUM_15 15
/** Variable for padding 64 bits */
#define PAD_NUM 56
/** Variable for 64 bits */
#define TOTAL_BITS 64
/** Variable for number 5 */
#define NUM_5 5
/** Variable for number 12 */
#define NUM_12 12
/** Variable for number 24 */
#define NUM_24 24

/**
    Performs the F function for the first round in the MD5 algorithm.
    @param B the first word input
    @param C the second word input
    @param D the third word input
    @return word as a result of the operations on the given words
 */
word fVersion0( word B, word C, word D );
/**
    Performs the F function for the second round in the MD5 algorithm.
    @param B the first word input
    @param C the second word input
    @param D the third word input
    @return word as a result of the operations on the given words
 */ 
word fVersion1( word B, word C, word D );
/**
    Performs the F function for the third round in the MD5 algorithm.
    @param B the first word input
    @param C the second word input
    @param D the third word input
    @return word as a result of the operations on the given words
 */
word fVersion2( word B, word C, word D );
/**
    Performs the F function for the fourth round in the MD5 algorithm.
    @param B the first word input
    @param C the second word input
    @param D the third word input
    @return word as a result of the operations on the given words
 */
word fVersion3( word B, word C, word D );
/**
    Performs the G function for the first round in the MD5 algorithm.
    @param idx the current iteration index within the round
    @return idx the index of the word to be used
 */
int gVersion0( int idx );
/**
    Performs the G function for the second round in the MD5 algorithm.
    @param idx the current iteration index within the round
    @return idx the index of the word to be used
 */
int gVersion1( int idx );
/**
    Performs the G function for the third round in the MD5 algorithm.
    @param idx the current iteration index within the round
    @return idx the index of the word to be used
 */
int gVersion2( int idx );
/**
    Performs the G function for the fourth round in the MD5 algorithm.
    @param idx the current iteration index within the round
    @return idx the index of the word to be used
 */
int gVersion3( int idx );
/**
    Function implements the rotate left operation from the MD5 algorithm, shifting 
    the given value to the left by s bits
    @param value the value to rotate left
    @param s an integer that is the number of bits of shift the given value
    @return word after the rotation has been performed
 */
word rotateLeft( word value, int s );
/**
    This function implements an iteration of the MD5 algorithm on a 64-byte block (16 words)
    @param M[] the contents of the block
    @param *A variable representing the MD5 state, which is passed by reference
    @param *B variable representing the MD5 state, which is passed by reference
    @param *C variable representing the MD5 state, which is passed by reference
    @param *D variable representing the MD5 state, which is passed by reference
    @param int i the iteration number,a value between 0 and 63
 */
void md5Iteration( word M[ BLOCK_WORDS ], word *A, word *B, word *C, word *D, int i );
/**
    This function pads the given block, bringing its length up to 64 bytes, adding byte values as described in the MD5 algorithm
    @param *block pointer to a block that is suppose to be padded
 */ 
void padBlock( Block *block );
/**
    Pads the given input block, computes the MD5 hash using the helper functions above
    @param *block a pointer to a block that is suppose to be padded
    @param hash[] array that stores the result after hashing
 */ 
void md5Hash( Block *block, byte hash[ HASH_SIZE ] ); 



#endif
