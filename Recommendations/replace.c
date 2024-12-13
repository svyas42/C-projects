/**
    @file replace.c
    @author Sachi Vyas (smvyas)
    A program that: Replaces the word in the line and also computes the length of the line if the replacement is made.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "replace.h"

/**
    Replaces the given part with the word in a line
    @param line the character array of line to make the replacement in
    @param part the character array of the word to replace
    @param word the character array of the word that is being put in
 */
void replaceWord( char line[], char part[], char word[] ) 
{
    char buffer[LINE_MAX + 1];
    int lenPart = strlen(part);
    int wordPart = strlen(word);

    int idx = 0;
    int i = 0;

    while (line[i] != '\0') {
        int partIdx = 1;
        for (int k = 0; k < lenPart; k++) {
            if (line[i + k] != part[k]) {
                partIdx = 0;
                break;
            }
        }

        if (partIdx == 1) {
            for (int j = 0; j < wordPart; j++) {
                buffer[idx++] = word[j];
            }
            i += lenPart;
        }
        else {
            buffer[idx++] = line[i++];
        }

        if (strlen(word) > FIELD_MAX) {
            exit(101);
        }
    }
    buffer[idx] = '\0';
    for (int i = 0; buffer[i] != '\0'; i++) {
        line[i] = buffer[i];
    }
    line[idx] = '\0';
 
}

/**
    Computer the length of a line if the replacement were to be made
    @param line the character array of line to make the replacement in
    @param part_length the length of the word to replace
    @param word_length the length of the new word that is being put in
 */
void computeLen( char line[], int part_length, int word_length )
{
    int b = strlen(line);
    int totalLength = 0;
 
    totalLength = b + (word_length - part_length);
    
   

    if (totalLength > LINE_MAX + 1) {
        exit(103);
    }
    
}