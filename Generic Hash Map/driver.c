/**
    @file driver.c
    @author Sachi Vyas (smvyas)
    A program that: Helps us run the code and contains the main method
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <setjmp.h>
#include <unistd.h> // Unix-specific isatty() function.
#include "map.h"
#include "value.h"
#include "input.h"
/** Maximum length of the command string */
#define CMD_LENGTH 10
/** Maximum length of the value in case it is a long sentence */
#define MAX_VALUE_LENGTH 1024
/** Maximum number of observations in the map */
#define MAP_MAX 1000
/** Number of parameters to read in when using the set command */
#define NUM_PARAMETERS 2
/** Interactive boolean variable to check the -term */
bool interactive = false;
/** Print out a usage message and exit unsuccessfully. */
static void usage()
{
  fprintf( stderr, "Usage: driver [-term]\n" );
  exit( EXIT_FAILURE );
}
/**
    Handles the different commands present and updates the given map or prints it to the terminal
    @param *map a pointer to the map to make changes to
    @param *line the line to parse through
    @param *env allows the method to signal errors to its caller without terminating the program
    @return bool to show if the command was executed successfully or not
 */
bool handleCommand(Map *map, char const *line, jmp_buf *env) 
{

    int lenLine = strlen(line);
    char *input = (char *)malloc(lenLine + 1);

    strcpy(input, line);
    char *origInput = input;
    char cmd[CMD_LENGTH];
    int n = 0;
    if (sscanf(input, "%15s%n", cmd, &n) != 1) {
        fprintf(stderr, "Error: Invalid command format\n");
        longjmp(*env, 1);
    }
    input += n;
    while (*input == ' ' || *input == '\t') {
        input++;
    }
    if (strcmp(cmd, "quit") == 0) {
        return true;
    } 
    else if (strcmp(cmd, "size") == 0) {
        printf("%d\n", mapSize(map));
        return false;
    } 
    else if (strcmp(cmd, "get") == 0) {
        char k[KEY_LIMIT + 1];
        int n = 0;
        if (sscanf(input, "%24s%n", k, &n) != 1) {
            fprintf(stderr, "Invalid command: %s\n", cmd);
            longjmp(*env, 1);
        }
        input += n;
        while (*input == ' ' || *input == '\t') {
            input++;
        }
        if (*input != '\0') {
            fprintf(stderr, "Invalid command: %s %s %s\n", cmd, k, input);
            exit(EXIT_FAILURE);
        }
        Value *val = mapGet(map, k);
        
        if (val != NULL) {
            val->print(val);
            printf("\n");
        } 
        else {
            if (!interactive) {
                fprintf(stderr, "Invalid command: %s %s\n", cmd, k);
                exit(EXIT_FAILURE);
            }
            else {
                printf("%s\n", "Invalid command");
            }
        }
        
        return false;
    } 
    
    else if (strcmp(cmd, "remove") == 0) {
        char k[KEY_LIMIT + 1];
        if (sscanf(input, "%24s", k) != 1) {
            fprintf(stderr, "Error: Missing or invalid key\n");
            longjmp(*env, 1);
        }
        mapRemove(map, k);
       
        return false;
    } 
    
    else if (strcmp(cmd, "set") == 0) {
        char key[KEY_LIMIT + 1];
        char valueStr[MAX_VALUE_LENGTH];
       
        if (sscanf(input, "%24s %[^\n]", key, valueStr) != NUM_PARAMETERS) {
            
            fprintf(stderr, "Error: Invalid set command format\n");
            longjmp(*env, 1);
        }
        Value *val = NULL;
        int len = strlen(valueStr);
        if (valueStr[0] == '"' && valueStr[len - 1] == '"') {
            val = parseString(valueStr);
        } 
        //&& strpbrk(valueStr, "0123456789") && strpbrk(valueStr, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") == NULL
        else if (strchr(valueStr, '.') != NULL) {
            val = parseDouble(valueStr);
        } 
        else {
            val = parseInteger(valueStr);
        }
        mapSet(map, key, val);
        return false;
    }
    else {
        fprintf(stderr, "Invalid command %s", cmd);
        exit(EXIT_FAILURE);
    }
    free(input);
    free(origInput);
    
}
/**
   Starting point for the program.
   @param argc number of command-line arguments.
   @param argv array of strings given as command-line arguments.
   @return exit status for the program.
 */
int main( int argc, char *argv[] )
{
  // See if our input is from a terminal.
    interactive = isatty( STDIN_FILENO );
  // Parse command-line arguments.
    int apos = 1;
    while ( apos < argc ) {
    // The -term option makes the program behave as if it's in interactive mode,
    // even if it's reading from a file.
        if ( strcmp( argv[ apos ], "-term" ) == 0 ) {
            interactive = true;
            apos += 1;
        } 
        else {
            usage();
        }
    }
    Map *map = makeMap(MAP_MAX);
    // if (map == NULL) {
    //     fprintf(stderr, "Map memory not allocated");
    //     return EXIT_FAILURE;
    // }
    jmp_buf env;
    if (setjmp(env) != 0) {
        fprintf(stderr, "Error: command ");
        return EXIT_FAILURE;
    }
    char *line = NULL;
    for (line = readLine(stdin); line != NULL; line = readLine(stdin)) {
        if (interactive) {
            printf("cmd> ");
            fflush(stdout);
        }
        // Process the command and check for the "quit" command.
        if (handleCommand(map, line, &env)) {
            free(line);
            break;
        }
        // Free the dynamically allocated line after processing.
        free(line);
    }
    if (feof(stdin)) {
        
        exit(EXIT_SUCCESS);
    }
    freeMap(map);
    return EXIT_SUCCESS;
}
