/**
    @file template.c
    @author Sachi Vyas (smvyas)
    A program that: Helps us give the needed output once all the functions are called together
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "replace.h"
#include "input.h"

/**
    Returns exit success if the program runs without errors or failure if the program doesn't
    @return integer based on if the program runs without errors or program doesn't
 */
int main() 
{ 
    char firstName[FIELD_MAX + 1]; 
    char lastName[FIELD_MAX + 1]; 
    char unityId[UNITY_MAX + 1]; 
    char pronouns[FIELD_MAX + 1];
    char p1[5] = "";
    char p2[5] = "";
    char p3[6] = "";
    readLine(firstName);
    readLine(lastName);
    readLine(unityId);
    readLine(pronouns);
    
    if (strlen(unityId) > UNITY_MAX) {
        exit(101);
    }
    if (strcmp(firstName, "") == 0 || strcmp(lastName, "") == 0 || 
    strcmp(unityId, "") == 0 || strcmp(pronouns, "") == 0) {
        exit(100);
    } 
    int currentVal = 1;
    int pIndex = 0;
    int count = 0;
    for (int i = 0; pronouns[i]; i++) {
        if (pronouns[i] == '/') {
            count++;
            if (currentVal == 1) {
                p1[pIndex] = '\0';
                pIndex = 0;
                currentVal++;
            }
            else if (currentVal == 2) {
                p2[pIndex] = '\0';
                pIndex = 0;
                currentVal++;
            }
            else if (currentVal == 3) {
                p3[pIndex] = '\0';
                break;
            }
        }
        else {
            if (currentVal == 1) {
                p1[pIndex++] = pronouns[i];
            }
            else if (currentVal == 2) {
                p2[pIndex++] = pronouns[i];
            }
            else if (currentVal == 3) {
                p3[pIndex++] = pronouns[i];
            }    
        }
    }
    if (count > 2 || count < 2) {
        exit(102);
    }
 
    char line[LINE_MAX + 1] = "";

    char upperCase1[5];
    strcpy(upperCase1, p1);
    upperCase1[0] = toupper(upperCase1[0]);

    char upperCase2[5];
    strcpy(upperCase2, p2);
    upperCase2[0] = toupper(upperCase2[0]);

    char upperCase3[5];
    strcpy(upperCase3, p3);
    upperCase3[0] = toupper(upperCase3[0]);

    while (readLine(line)) {
        char word[100] = "";
        int idx = 0;
        for (int j = 0; line[j]; j++) {
            if (!isalpha(line[j]) || isspace(line[j])) {
               
                if (idx > 0) {
                    word[idx] = '\0';
                    computeLen(line, strlen(FIRST), strlen(firstName));
                    replaceWord(line, FIRST, firstName);
                    
                    computeLen(line, strlen(LAST), strlen(lastName));
                    replaceWord(line, LAST, lastName);

                    computeLen(line, strlen(UNITY), strlen(unityId));     
                    if (strcmp(word, UNITY) == 0) {
                        replaceWord(line, UNITY, unityId);
                    }
                    if (strcmp(word, PRONOUN1) == 0 || strcmp(word, "He") == 0) {
                        if (strcmp(word, "He") == 0) {           
                            replaceWord(line, "He", upperCase1);                            
                        } else {
                            replaceWord(line, PRONOUN1, p1);
                        }
                    }
                    if (strcmp(word, PRONOUN2) == 0) {
                        if (strcmp(word, "Him") == 0) {
                            replaceWord(line, "Him", upperCase2);
                        }
                        replaceWord(line, PRONOUN2, p2);
                    }
                    if (strcmp(word, PRONOUN3) == 0 || strcmp(word, "Their") == 0 || 
                    strcmp(word, "His") == 0) {
                        if (strcmp(word, "His") == 0) {
                            replaceWord(line, "His", upperCase3);
                        }
                        else {
                            replaceWord(line, PRONOUN3, p3);
                        }
                    }
                    idx = 0;
                }              
            }
            else {
                word[idx++] = line[j];                               
            }    
        }
        if (strlen(line) >= LINE_MAX) {
            exit(103);
        }
        
        //this condition is to remove the extra line that was being print
        if (strlen(line) > 0) {
             printf("%s\n",line);  

        }  
    }
     
    return EXIT_SUCCESS;  
}