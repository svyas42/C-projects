/**
    @file replace.h
    @author Sachi Vyas (smvyas)
    The header file for replace.c file with the defined variables and prototypes for methods
 */

/** Maximum length of a unity ID. */
#define UNITY_MAX 8

/** Maximum length of all other replacement strings. */
#define FIELD_MAX 24

/** Maximum length of lines in the memo. */
#define LINE_MAX 80

/** Placeholder for the first name. */
#define FIRST "John"

/** Placeholder for the last name. */
#define LAST "Doe"

/** Placeholder for the unity ID. */
#define UNITY "jdoe"

/** Placeholder for the subjective pronoun. */
#define PRONOUN1 "he"

/** Placeholder for the objective pronoun. */
#define PRONOUN2 "him"

/** Placeholder for the possessive adjective. */
#define PRONOUN3 "his"

/** 
    Prototype for the replace word method in replace.c
    @param line the character array of line to make the replacement in
    @param part the character array of the word to replace
    @param word the character array of the word that is being put in
 */
void replaceWord( char [], char [], char [] );

/** 
    Prototype for the compute length method in replace.c
    @param line the character array of line to make the replacement in
    @param part_length the length of the word to replace
    @param word_length the length of the new word that is being put in 
*/
void computeLen( char [], int, int );