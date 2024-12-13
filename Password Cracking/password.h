/**
    @file password.h
    @author Sachi Vyas (smvyas)
    A program that: Prototype for password.c
 */
#ifndef _PASSWORD_H_
#define _PASSWORD_H_
#include "magic.h"
#include "md5.h"
/** Required length of the salt string. */
#define SALT_LENGTH 8

/** Maximum length of a password.  Just to simplify our program; passwords
    aren't really required to be this short. */
#define PW_LIMIT 15

/** Maximum length of a password hash string created by hashPassword() */
#define PW_HASH_LIMIT 22

/**
    Given a password and a salt string, this function computes the alternate hash used in the MD5 password encryption algorithm and leaves it in the altHash array.
    @param pass[] the array which has the password
    @param salt[] the array which contains the salt string
    @param altHash the array that holds the result of the alternate hashing
 */
void computeAlternateHash( char const pass[], char const salt[ SALT_LENGTH + 1 ], byte altHash[ HASH_SIZE ] );
/**
    Function computes the first intermediate hash used in the MD5 password encryption algorithm
    @param pass[] the array which has the password
    @param salt[] the array which contains the salt string
    @param intHash the array that holds the result of the first intermediate hash
 */
void computeFirstIntermediate( char const pass[], char const salt[ SALT_LENGTH + 1 ], byte altHash[ HASH_SIZE ], 
byte intHash[ HASH_SIZE ] );
/**
    Function computes the next intermediate hash used in the MD5 password encryption algorithm.
    @param pass[] the array which has the password
    @param salt[] the array which contains the salt string
    @param inum the iteration number for the algorithm
    @param intHash the array that holds the result of the next intermediate hash
 */
void computeNextIntermediate( char const pass[], char const salt[ SALT_LENGTH + 1 ], int inum, byte intHash[ HASH_SIZE ] );
/**
    This function converts it to a string of printable characters in the set
    @param hash the 16 byte hash value
    @param result the array to store the result
 */
void hashToString( byte hash[ HASH_SIZE ], char result[ PW_HASH_LIMIT + 1 ] );
/**
    Function computes an MD5 hash of the password and stores it in the result array.
    @param pass[] the array which has the password
    @param salt[] the array which contains the salt string
    @param result[] the array to store the hashed password
 */
void hashPassword( char const pass[], char const salt[ SALT_LENGTH + 1 ], char result[ PW_HASH_LIMIT + 1 ] );


#endif
