/**
    @file block.c
    @author Sachi Vyas (smvyas)
    A program that: Helps us allocate memory to the block and appending bytes and strings
 */
#include "block.h"
#include "magic.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
    Making a new dynamically allocated block
 */
Block *makeBlock() 
{
    Block *b = (Block*)malloc(sizeof(Block));
    if (b == NULL) {
        return NULL;
    }
    b->len = 0;
    return b;
}
/**
    Helps us free a block
    @param *block the pointer to a block to free
 */
void freeBlock( Block *block ) 
{
    free(block);
}
/**
    Function stores the given byte value at the end of the given block.
    @param *dest the block to append the byte to appen to
    @param b the byte to append
 */
void appendByte( Block *dest, byte b ) 
{
    if (dest->len >= BLOCK_SIZE) {
        fprintf(stderr, "Block overflow\n");
        exit(EXIT_FAILURE);
    }
    dest->data[dest->len++] = b;
}
/**
    Function stores all the bytes from the given string at the end of the given block.
    @param *dest the pointer in the block where we need to append the string
    @param *src the string that we are suppose to append to the block
 */
void appendString( Block *dest, char const *src ) 
{
    
    int length = strlen(src);
    if (dest->len + length >  BLOCK_SIZE) {
        fprintf(stderr, "Block overflow\n");
        exit(EXIT_FAILURE);
    }
    
    while (*src) {
        appendByte(dest, (byte) (*src++));
    }
}
