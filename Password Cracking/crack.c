/**
    @file crack.c
    @author Sachi Vyas (smvyas)
    A program that: Helps us reads file input from the given input stream (stdin or a file) and returns the output in the needed format
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "md5.h"
#include "password.h"
/** Maximum number of words we can have in the dictionary. */
#define DLIST_LIMIT 1000
/** Maximum word length of the words in the dictionary */
#define MAX_WORD_LEN 15
/** Maximum username length */
#define USERNAME_LIMIT 32
/** Number of required arguments on the command line. */
#define REQ_ARGS 2
/** Type for representing a word in the dictionary. */
typedef char Password[ PW_LIMIT + 1 ];
/** Index where the dictionary file is in the command line */
#define DICTIONARY_IDX 1
/** Max line entry length */
#define MAX_LINE_LENGTH 256

/** A struct to store all the information collection from each shadow file */
typedef struct {
    char name[USERNAME_LIMIT + 1];
    char salt[SALT_LENGTH + 1];
    char hash[PW_HASH_LIMIT + 1];
} ShadowEntry;

/** Print out a usage message and exit unsuccessfully. */
static void usage()
{
    fprintf( stderr, "Usage: crack dictionary-filename shadow-filename\n" );
    exit(EXIT_FAILURE);
}
/**
    Helps us read a dictionary file
    @param *fp the pointer to a dictionary file
    @param words the variable to store the name in
    @param *counter keeps a track of the number of letters in the word
    @return 0 if the program executed sucessfully and 1 otherwise
 */
int readDictionary(const char *fp, Password words[], int *counter) 
{
    FILE *file = fopen(fp, "r");
    if (!file) {
        
        usage();
    }
    *counter = 0;
    while (*counter <= DLIST_LIMIT && fscanf(file, "%20s", words[*counter]) == 1) {  // Limit to MAX_WORD_LEN
        int len = strlen(words[*counter]);
        if (len > MAX_WORD_LEN) {
            fclose(file);
            fprintf(stderr, "Invalid dictionary word\n");
            exit(EXIT_FAILURE);
        }
        (*counter)++;
    }
    
    if (*counter > DLIST_LIMIT) {
        fprintf(stderr, "Too many dictionary words\n");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    return EXIT_SUCCESS;
}

/**
    Function to read the input from the shadow file
    @param *filename the name of the shadow file
    @param entries the shadowEntry represent a user entry which contain fields for 
    username, salt, and hashed password
    @param entryCount the pointer to an integer that maintains a record of the number of records
    @return 0 if the program executed sucessfully and 1 otherwise
 */
int readShadowFile(const char *filename, ShadowEntry entries[], int *counter) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    *counter = 0;
    int ch, i, j;
    char line[MAX_LINE_LENGTH + 1];
    //*entryCount < MAX_ENTRIES
    while (!feof(file)) {
        i = 0;
        while ((ch = fgetc(file)) != EOF && ch != '\n' && i < sizeof(line) - 1) {
            line[i++] = (char)ch;
        }
        line[i] = '\0';
        if (i == 0 && ch == EOF) {
            break;
        }
        i = 0; j = 0;
        // Parse username
        while (line[i] && line[i] != ':' && i < USERNAME_LIMIT) {
            if (isspace(line[i])) {
                fclose(file);
                fprintf(stderr, "Invalid shadow file entry\n");
                exit(EXIT_FAILURE);
            }
            entries[*counter].name[i] = line[i];
            i++;
        }
        if (line[i] != ':' || i == 0) {
            fclose(file);
            fprintf(stderr, "Invalid shadow file entry\n");
            exit(EXIT_FAILURE);
        }
        entries[*counter].name[i] = '\0';
        i++;
        if (strncmp(&line[i], "$1$", NUM_3) != 0) {
            fclose(file);
            fprintf(stderr, "Invalid shadow file entry\n");
            exit(EXIT_FAILURE);
        }
        i += NUM_3;
        // Parse salt
        for (j = 0; j < SALT_LENGTH; j++, i++) {
            if (line[i] == '\0' || line[i] == '$' || isspace(line[i])) {
                fclose(file);
                fprintf(stderr, "Invalid shadow file entry\n");
                exit(EXIT_FAILURE);
            }
            entries[*counter].salt[j] = line[i];
        }

        entries[*counter].salt[j] = '\0';
        if (strlen(entries[*counter].salt) > SALT_LENGTH + 1) {
            fprintf(stderr, "Invalid shadow file entry\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }

        if (line[i] != '$') {
            fclose(file);
            fprintf(stderr, "Invalid shadow file entry\n");
            exit(EXIT_FAILURE);
        }
        i++;
        // Parse hash
        j = 0;
        while (j < PW_HASH_LIMIT) {
            if (line[i] == '\0' || line[i] == ':' || isspace(line[i])) {
                fclose(file);
                fprintf(stderr, "Invalid shadow file entry\n");
                exit(EXIT_FAILURE);
            }
            entries[*counter].hash[j] = line[i];
            j++;
            i++;  
        }
        entries[*counter].hash[j] = '\0';
        (*counter)++;
    }
    fclose(file);
    return EXIT_SUCCESS;
}
/**
    Helps us compare if the passwords match in the dictionary and shadow file
    @param argc the number of arguments in the command line
    @param *argv pointer to a array that have been put in the command line
    @return 0 if the program executed sucessfully and 1 otherwise
 */
int main(int argc, char *argv[]) 
{
    
    if (argc < REQ_ARGS) { 
        usage();
    }
    FILE *outfile = stdout;
    char dictionary[DLIST_LIMIT][MAX_WORD_LEN + 1]; 
    int wordCount = 0;
    readDictionary(argv[DICTIONARY_IDX], dictionary, &wordCount);
    ShadowEntry shadowEntries[DLIST_LIMIT];

    int entryCount;
    readShadowFile(argv[REQ_ARGS], shadowEntries, &entryCount);
    char result[PW_HASH_LIMIT + 1];
    
    for (int i = 0; i < entryCount; i++) {  
        for (int j = 0; j < wordCount; j++) {

            hashPassword(dictionary[j], shadowEntries[i].salt, result);  
            if (strcmp(result, shadowEntries[i].hash) == 0) {  // Check if hash matches stored hash
               
                fprintf(outfile, "%s : %s\n", shadowEntries[i].name, dictionary[j]);  
                break;  
            }
        }
    }
    fclose(outfile);
    return EXIT_SUCCESS;
}
