/**
    @file password.c
    @author Sachi Vyas (smvyas)
    A program that: Helps us compute the password
 */
#include "password.h"
#include "magic.h"
#include "md5.h"
#include "block.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/** Number of iterations of hashing to make a password. */
#define PW_ITERATIONS 1000

/**
    Given a password and a salt string, this function computes the alternate hash used in the MD5 password encryption algorithm and leaves it in the altHash array.
    @param pass[] the array which has the password
    @param salt[] the array which contains the salt string
    @param altHash the array that holds the result of the alternate hashing
 */
void computeAlternateHash( char const pass[], char const salt[ SALT_LENGTH + 1 ], byte altHash[ HASH_SIZE ] ) 
{
    
    int lenPass = strlen(pass);
    int lenSalt = strlen(salt);
    int total = lenPass + lenSalt + lenPass;
    
    Block block;
    block.len = total;
    
    memcpy(block.data, pass, lenPass);
    memcpy(block.data + lenPass, salt, lenSalt);
    memcpy(block.data + lenPass + lenSalt, pass, lenPass);
    padBlock(&block);
    md5Hash(&block, altHash);
}
/**
    Function computes the first intermediate hash used in the MD5 password encryption algorithm
    @param pass[] the array which has the password
    @param salt[] the array which contains the salt string
    @param intHash the array that holds the result of the first intermediate hash
 */
void computeFirstIntermediate( char const pass[], char const salt[ SALT_LENGTH + 1 ], byte altHash[ HASH_SIZE ], 
byte intHash[ HASH_SIZE ] ) 
{ 
    Block block;
    block.len = 0;

    if (block.len + strlen(pass) <= PAD_NUM) {
        appendString(&block, pass);
    }
    if (block.len + NUM_3 <= PAD_NUM) {  
        appendString(&block, "$1$");
    }
    if (block.len + strlen(salt) <= PAD_NUM) {
        appendString(&block, salt);
    }

    int lenPass = strlen(pass);
    if (block.len < PAD_NUM) {
        for (int i = 0; i < lenPass; i++) {
            appendByte(&block, altHash[i]);
        }
    }
    int numOfBitInPassLen = 0;
    int tempLen = lenPass;

    while (tempLen > 0) {
        numOfBitInPassLen++;
        tempLen >>= 1;
    }
    if (numOfBitInPassLen < sizeof(lenPass)) {
        for (int i = 0; i < numOfBitInPassLen; i++) {
            if (lenPass & (1 << i)) {
                appendByte(&block, 0x00);
            }
            else {
                appendByte(&block, pass[0]);
            }
        }
    }
    else {    
        for (int i = 0; i < numOfBitInPassLen; i++) {
            if (lenPass & (1 << i)) {
                appendByte(&block, 0x00);
            }
            else {
                appendByte(&block, pass[0]);
            }
        }
    }

    md5Hash(&block, intHash);
   
}
/**
    Function computes the next intermediate hash used in the MD5 password encryption algorithm.
    @param pass[] the array which has the password
    @param salt[] the array which contains the salt string
    @param inum the iteration number for the algorithm
    @param intHash the array that holds the result of the next intermediate hash
 */
void computeNextIntermediate( char const pass[], char const salt[ SALT_LENGTH + 1 ], int inum, byte intHash[ HASH_SIZE ] ) 
{
    Block block;
    block.len = 0;
   
    if (inum % NUM_2 == 0) {
        for (int i = 0; i < HASH_SIZE; i++) {
            appendByte(&block, intHash[i]);
        }
    }
    if (inum % NUM_2 == 1) {
        appendString(&block, pass);
    }
    if (inum % NUM_3 != 0) {
        appendString(&block, salt);
    }
    if (inum % NUM_7 != 0) {
       appendString(&block, pass);
    }
    if (inum % NUM_2 == 0) {
        appendString(&block, pass);
    }
    if (inum % NUM_2 == 1) {
        for (int i = 0; i < HASH_SIZE; i++) {
            appendByte(&block, intHash[i]);
        }
    }
   
    md5Hash(&block, intHash);
}
/**
    This function converts it to a string of printable characters in the set
    @param hash the 16 byte hash value
    @param result the array to store the result
 */
void hashToString( byte hash[ HASH_SIZE ], char result[ PW_HASH_LIMIT + 1 ] ) 
{
    byte hashPermute[HASH_SIZE];
    for (int i = 0; i < HASH_SIZE; i++) {
        hashPermute[i] = hash[pwPerm[i]];
    }

    int idxBit = 0;
    int idxResult = 0;

    //-2
    while (idxBit < HASH_SIZE * MULTIPLIER_8 - 1) {
        int j = 0;
        for (int i = 0; i < NUM_6; i++) {
            int idxByte = (idxBit + i) / MULTIPLIER_8;
            int byteInBits = (idxBit + i) % MULTIPLIER_8;
            
            j |= ((hashPermute[idxByte] >> byteInBits) & 1) << i;
        }
        //printf("Index Bit: %d, j: %d, Mapped Char: %c\n", idxBit, j, pwCode64[j]);
        result[idxResult++] = pwCode64[j];
        idxBit += NUM_6;
    }
    int k = (hashPermute[NUM_15] & 0x03);

    //idxResult++
    result[idxResult] = pwCode64[k];
    result[idxResult++] = '\0'; 
}
/**
    Function computes an MD5 hash of the password and stores it in the result array.
    @param pass[] the array which has the password
    @param salt[] the array which contains the salt string
    @param result[] the array to store the hashed password
 */
void hashPassword( char const pass[], char const salt[ SALT_LENGTH + 1 ], char result[ PW_HASH_LIMIT + 1 ] ) 
{
    byte altHash[HASH_SIZE];
    byte intHash[HASH_SIZE];
    computeAlternateHash(pass, salt, altHash);

    computeFirstIntermediate(pass, salt, altHash, intHash);
    for (int i = 0; i < PW_ITERATIONS; i++) {
        computeNextIntermediate(pass, salt, i, intHash);
    }      
    hashToString(intHash, result);
    //printf("Hash result: %s\n", result);
}
