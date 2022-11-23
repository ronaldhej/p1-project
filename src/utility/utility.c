#include <stdio.h>

char option = '0';
char startingLocation[100] = "";
char finalDestination[100] = "";

void printStartingText() {
    do{
    printf("User options:\n"
           "t:    Calculate travel time\n"
           "Developer options:\n"
           "g:    Generate a graph using specified seed\n\n"
           "Choose an option:");

    scanf("%c", &option);
    if (option == 't') {
        printf("Please enter your starting location:");
        scanf("%s", startingLocation);

        printf("\nPlease enter your final destination:");
        scanf("%s", finalDestination);

        printf("Is %s -> %s your desired journey? (y/n):\n", startingLocation, finalDestination);
    } else if (option == 'g') {
        printf("Generating graph"); //TO-DO Not implemented
    }
    } while(option != 't' && option != 'g');
}









