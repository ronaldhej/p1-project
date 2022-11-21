#include <stdio.h>
#include <string.h>

char option = '0';
char start[100] = "";
char final[100] = "";
char startingLocation[100] = "";
char finalDestination[100] = "";

void printStartingText() {
    printf("User options:\n"
           "t:    Calculate travel time\n"
           "Developer options:\n"
           "g:    Generate a graph using specified seed\n\n"
           "Choose an option:");

    scanf("%c", &option);
    if (option == 't') {
        printf("Please enter your starting location:");
        scanf("%s", start);

        printf("\nPlease enter your final destination:");
        scanf("%s", final);

        strcpy(startingLocation, start);
        strcpy(finalDestination, final);

        printf("Is %s -> %s your desired journey? (y/n):\n", startingLocation, finalDestination);
    }

    if (option == 'g') {
        printf("Generating graph");
    }
}








