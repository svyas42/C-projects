/**
    @file block.h
    @author Sachi Vyas (smvyas)
    A program that: Prototype for block.c
 */

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "magic.h"

/** A (partially filled) block of up to 64 bytes. */
typedef struct {
  // Array of bytes in this block. */
  byte data[ BLOCK_SIZE ];

  // Number of bytes in the data array currently in use.
  int len;
} Block;


/**
    Making a new dynamically allocated block
 */
Block *makeBlock();
/**
    Helps us free a block
    @param *block the pointer to a block to free
 */ 
void freeBlock( Block *block );
/**
    Function stores the given byte value at the end of the given block.
    @param *dest the block to append the byte to appen to
    @param b the byte to append
 */ 
void appendByte( Block *dest, byte b );
/**
    Function stores all the bytes from the given string at the end of the given block.
    @param *dest the pointer in the block where we need to append the string
    @param *src the string that we are suppose to append to the block
 */ 
void appendString( Block *dest, char const *src ); 


#endif
