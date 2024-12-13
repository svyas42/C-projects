/**
    @file md5.c
    @author Sachi Vyas (smvyas)
    A program that: Helps us implement the md5 algorithm
 */
#include "md5.h"
#include "magic.h"
#include "block.h"
#include <stdlib.h>
#include <stdio.h>  // Maybe for some debugging
#include <string.h>

/** Initialization value to be added to each word in the MD5 state */
#define VALUE_A 0x67452301
/** Initialization value to be added to each word in the MD5 state */
#define VALUE_B 0xefcdab89
/** Initialization value to be added to each word in the MD5 state */
#define VALUE_C 0x98badcfe
/** Initialization value to be added to each word in the MD5 state */
#define VALUE_D 0x10325476

/** Function type for the f functions in the md5 algorithm. */
typedef word (*FFunction)( word, word, word );

/** Function type for the g functions in the md5 algorithm. */
typedef int (*GFunction)( int );

/**
    Performs the F function for the first round in the MD5 algorithm.
    @param B the first word input
    @param C the second word input
    @param D the third word input
    @return word as a result of the operations on the given words
 */
word fVersion0( word B, word C, word D ) 
{
    return (B & C) | (~B & D);
}
/**
    Performs the F function for the second round in the MD5 algorithm.
    @param B the first word input
    @param C the second word input
    @param D the third word input
    @return word as a result of the operations on the given words
 */
word fVersion1( word B, word C, word D )
{
    return (B & D) | (C & ~D);
}
/**
    Performs the F function for the third round in the MD5 algorithm.
    @param B the first word input
    @param C the second word input
    @param D the third word input
    @return word as a result of the operations on the given words
 */
word fVersion2( word B, word C, word D )
{
    return B ^ C ^ D;
}
/**
    Performs the F function for the fourth round in the MD5 algorithm.
    @param B the first word input
    @param C the second word input
    @param D the third word input
    @return word as a result of the operations on the given words
 */
word fVersion3( word B, word C, word D )
{
    return C ^ (B | ~D);    
}
/**
    Performs the G function for the first round in the MD5 algorithm.
    @param idx the current iteration index within the round
    @return idx the index of the word to be used
 */
int gVersion0( int idx )
{
    return idx;
}
/**
    Performs the G function for the second round in the MD5 algorithm.
    @param idx the current iteration index within the round
    @return idx the index of the word to be used
 */
int gVersion1( int idx )
{
    return (NUM_5 * idx + 1) % HASH_SIZE;
}
/**
    Performs the G function for the third round in the MD5 algorithm.
    @param idx the current iteration index within the round
    @return idx the index of the word to be used
 */
int gVersion2( int idx )
{
    return (NUM_3 * idx + NUM_5) % HASH_SIZE;
}
/**
    Performs the G function for the fourth round in the MD5 algorithm.
    @param idx the current iteration index within the round
    @return idx the index of the word to be used
 */
int gVersion3( int idx )
{
    return (NUM_7 * idx) % HASH_SIZE;
}
/**
    Function implements the rotate left operation from the MD5 algorithm, shifting 
    the given value to the left by s bits
    @param value the value to rotate left
    @param s an integer that is the number of bits of shift the given value
    @return word after the rotation has been performed
 */
word rotateLeft( word value, int s )
{
    return (value << s) | (value >> (BIT_32 - s));
}
/**
    This function implements an iteration of the MD5 algorithm on a 64-byte block (16 words)
    @param M[] the contents of the block
    @param *A variable representing the MD5 state, which is passed by reference
    @param *B variable representing the MD5 state, which is passed by reference
    @param *C variable representing the MD5 state, which is passed by reference
    @param *D variable representing the MD5 state, which is passed by reference
    @param int i the iteration number,a value between 0 and 63
 */
void md5Iteration( word M[ BLOCK_WORDS ], word *A, word *B, word *C, word *D, int i ) 
{
    FFunction f;
    GFunction g;
    if (i < HASH_SIZE) {
        f = fVersion0;
        g = gVersion0;
    }
    else if (i < BIT_32) {
        f = fVersion1;
        g = gVersion1;
    }
    else if (i < BIT_48) {
        f = fVersion2;
        g = gVersion2;
    }
    else {
        f = fVersion3;
        g = gVersion3;
    }
    word W = f(*B, *C, *D);
    int gIdx = g(i);
    word d = M[gIdx];
    word holder = *A + W + md5Noise[i] + d;
    holder = rotateLeft(holder, md5Shift[i]);
    holder += *B;
    *A = *D;
    *D = *C;
    *C = *B;
    *B = holder;
}
/**
    This function pads the given block, bringing its length up to 64 bytes, adding byte values as described in the MD5 algorithm
    @param *block pointer to a block that is suppose to be padded
 */
void padBlock( Block *block ) 
{  
    int len1 = block->len;

    block->data[len1] = 0x80;
    int padLength = len1;
   
    padLength++;
    while (padLength < PAD_NUM) {
        block->data[padLength++] = 0x00;
    }
    unsigned long long lengthOfBit = (unsigned long long) len1 * MULTIPLIER_8;
    for (int i = 0; i < MULTIPLIER_8; i++) {
        block->data[padLength++] = (byte) (lengthOfBit >> (MULTIPLIER_8 * i ));
    }
    block->len = padLength;   
}
/**
    Pads the given input block, computes the MD5 hash using the helper functions above
    @param *block a pointer to a block that is suppose to be padded
    @param hash[] array that stores the result after hashing
 */
void md5Hash( Block *block, byte hash[ HASH_SIZE ] ) 
{
    word w1 = VALUE_A, w2 = VALUE_B, w3 = VALUE_C, w4 = VALUE_D;
    padBlock(block);
    word M[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++) {
        M[i] = block->data[i * NUM_4] | 
        (block->data[i * NUM_4 + 1] << MULTIPLIER_8) |
        (block->data[i * NUM_4 + NUM_2] << HASH_SIZE | 
        (block->data[i * NUM_4 + NUM_3] << NUM_24));
    }
    for (int i = 0; i < TOTAL_BITS; i++) {
        md5Iteration(M, &w1, &w2, &w3, &w4, i);
    }
    w1 += VALUE_A;
    w2 += VALUE_B;
    w3 += VALUE_C;
    w4 += VALUE_D;

    memcpy(hash, &w1, NUM_4);
    memcpy(hash + NUM_4, &w2, NUM_4);
    memcpy(hash + MULTIPLIER_8, &w3, NUM_4);
    memcpy(hash + NUM_12, &w4, NUM_4);
         
}
