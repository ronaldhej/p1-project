#include <stdio.h>
#include <malloc.h>

// Make startingLocation and finalDestination dynamic.

void printStartingText() {

    char option;
    char *startingLocation;
    char *finalDestination;

    startingLocation = (char*) malloc(sizeof(startingLocation));
    finalDestination = (char*) malloc(sizeof(finalDestination));

    printf("User options:\n"
           "t:    Calculate travel time\n"
           "Developer options:\n"
           "g:    Generate a graph using specified seed\n\n"
           "Choose an option:");

    scanf("%c", &option);
    switch (option) {
        case 't':
            printf("Please enter your starting location:");
            scanf("%s", startingLocation);

            printf("Please enter your final destination:");
            scanf("%s", finalDestination);

            printf("Is %s -> %s your desired journey? (y/n):", startingLocation, finalDestination); //TO-DO Not implemented
            break;
        case 'g':
            printf("Generating graph"); //TO-DO Not implemented
            break;
        default:
            printf("Not a valid input");
    }
    free(startingLocation);
    free(finalDestination);
}