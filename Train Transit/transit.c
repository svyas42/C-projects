
/**
    @file transit.c
    @author Sachi Vyas (smvyas)
    A program that: Helps us parse through the route file and output the needed output and the main method to help us read the command line arguments.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "numbers.h"
#include "map.h"
/** Number of required arguments on the command line. */
#define REQ_ARGS 2
/** Creating a constant to divide by a constant */
#define DIVISOR 10

/**
   Report a usage message and exit unsuccessfully.
*/
static void usage()
{
    fprintf(stderr, "Usage: transit [-v] [-r report-filename] map-filename route-filename\n");
    exit(EXIT_FAILURE);
}
/**
    Helps us process and parse through the route file
    @param *filename pointer to a file to look into and parse
    @param *outfile pointer to a file to write to
    @param verbose to check if the -v is present in the command line or not
 */
void processRoute(const char *filename, FILE *outfile, bool verbose)
{
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Can't open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    unsigned long passengerDrop = 0, passengerPick = 0, passengerDistance = 0;
    unsigned long cp = 0, totalPassengerDistance = 0, totalDistance = 0;
    unsigned long totalPassengers = 0;
    unsigned long distance = 0;
    char src[NAME_LIMIT + 2], dest[NAME_LIMIT + 2], prevSrc[NAME_LIMIT + 2];

// Print table headers based on verbosity
    if (verbose) {
        fprintf(outfile, "%-20s %-20s %20s %21s %21s\n", "Depart", "Arrive", "Passengers", "Distance", "Passenger Distance");
    } else {
        fprintf(outfile, "%-20s %-20s %21s\n", "Depart", "Arrive", "Passenger Distance");
    }

    bool firstLocation = true;

    while (fscanf(file, "%21s", src) == 1) {
        if (!readLongNumber(file, &passengerDrop)) {
            fprintf(stderr, "Invalid route file: %s\n", filename);
            exit(EXIT_FAILURE);
        }
        if (!readLongNumber(file, &passengerPick)) {
            fprintf(stderr, "Invalid route file: %s\n", filename);
            exit(EXIT_FAILURE);
        }

        if (firstLocation) {
            cp = passengerPick;
            firstLocation = false;
            passengerDrop = 0;
            strcpy(prevSrc, src);  
            continue; 
        }

        strcpy(dest, src);
        if (!getDistance(&distance, prevSrc, dest)) {
            fprintf(stderr, "Invalid map file: %s\n", filename);
            exit(EXIT_FAILURE);
        }

        if (!multiply(&passengerDistance, cp, distance)) {
            fprintf(stderr, "Overflow\n");
            exit(EXIT_FAILURE);
        }

        if (!add(&totalPassengerDistance, totalPassengerDistance, passengerDistance)) {
            fprintf(stderr, "Overflow\n");
            exit(EXIT_FAILURE);
        }
        if (!add(&totalPassengers, totalPassengers, cp)) {
            fprintf(stderr, "Overflow\n");
            exit(EXIT_FAILURE);
        }
        if (!add(&totalDistance, totalDistance, distance)) {
            fprintf(stderr, "Overflow\n");
            exit(EXIT_FAILURE);
        }

        unsigned long distWhole = distance / DIVISOR;
        unsigned long fractionPart = distance % DIVISOR;
        unsigned long wholePassengerDistance = passengerDistance / DIVISOR;
        unsigned long fractionPassengerDistance = passengerDistance % DIVISOR;

        if (verbose) {
            fprintf(outfile, "%-20s %-20s %20lu %19lu.%1lu %19lu.%1lu\n", prevSrc, dest, cp, distWhole, fractionPart, wholePassengerDistance, fractionPassengerDistance);
        } else {
            fprintf(outfile, "%-20s %-20s %19lu.%1lu\n", prevSrc, dest, wholePassengerDistance, fractionPassengerDistance);
        }
        if (passengerDrop > cp) {
            fprintf(stderr, "Overflow\n");
            exit(EXIT_FAILURE);
        }
        cp = (cp - passengerDrop) + passengerPick;
        
        

        strcpy(prevSrc, src);
    }


    unsigned long totalDistWhole = totalDistance / DIVISOR;
    unsigned long totalFractionPart = totalDistance % DIVISOR;
    unsigned long wholeTotalPassengerDistance = totalPassengerDistance / DIVISOR;
    unsigned long decimalPassengerDistance = totalPassengerDistance % DIVISOR;
    if (verbose) {
        fprintf(outfile, "%-20s %-20s %20lu %19lu.%1lu %19lu.%1lu\n", "Total", "", totalPassengers, totalDistWhole, totalFractionPart, wholeTotalPassengerDistance, 
        decimalPassengerDistance);
    } else {
        fprintf(outfile, "%-20s %-20s %19lu.%1lu\n", "Total", "", wholeTotalPassengerDistance, decimalPassengerDistance);
    }

    fclose(file);  
}
    
/**
    Returns one if the operation was successful
    @param argc the number of arugments in the command line
    @param *argv[] array of char pointers, one for each argument
    @return 0 or 1 if the program has successfully executed or not
 */
int main(int argc, char *argv[])
{   
    bool verbose = false; 
    char *reportFile = NULL; 
    char *mapFile = NULL; 
    char *routeFile = NULL; 
    FILE *outfile = stdout; 
    
    if (argc < REQ_ARGS) {
        usage();
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) {
            if (verbose) { 
                usage();
                //return EXIT_FAILURE;
            }
            verbose = true;
        } 
        else if (strcmp(argv[i], "-r") == 0) {
            if (i + 1 < argc) { 
                if (reportFile) {
                    usage();
                    //return EXIT_FAILURE;
                }
                reportFile = argv[i + 1];
                i++; 
            } 
        } 
        else {
            if (!mapFile) {
                mapFile = argv[i]; 
            } 
            else if (!routeFile) {
                routeFile = argv[i];
            } 
            else {
                usage(); 
                //return EXIT_FAILURE;
            }
        }
    }
    if (mapFile == NULL || routeFile == NULL) {
        usage();
    }
    if (reportFile) {
        outfile = fopen(reportFile, "w");
        if (!outfile) {
            
            fprintf(stderr, "Can't open file: %s\n", reportFile);
            return EXIT_FAILURE;
        }
    }
    
    readMap(mapFile);
    processRoute(routeFile, outfile, verbose);
    if (outfile != stdout) {
        fclose(outfile);
   }
    return EXIT_SUCCESS;
}
