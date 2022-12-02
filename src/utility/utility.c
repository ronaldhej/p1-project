#include <stdio.h>
#include <malloc.h>

#include "../graph/graph.h"

typedef struct {
    char option;
    char startingLocation[64];
    char finalDestination[64];
} input;

//local prototypes, only used in utility
int handleOption(input* _input);

//prints the initial text, informing the user of how to interact with the program
void printUserManual() {
    printf("--- Program options ---"
           "User options:\n"
           "t:    Calculate travel time\n"
           "Developer options:\n"
           "g:    Generate a graph using specified seed\n\n"
           );
}

//reads input from the user, returns input
input* readInput() {
    input *userInput = malloc(sizeof(input));

    do {

        printf("Choose an option: ");
        scanf("%c", &userInput->option);

    //ask for input until input option is valid
    } while (!handleOption(userInput));

    return userInput;
}

#pragma region local functions

//different behavior determined by option
int handleOption(input* _input) {
    switch (_input->option) {

//USER-----------
        case 't':
            printf("Please enter your starting location: ");
            scanf("%s", (char *) _input->startingLocation);

            printf("Please enter your final destination: ");
            scanf("%s", (char *) _input->finalDestination);

            printf("Is %s -> %s your desired journey? (y/n):", _input->startingLocation,
                   _input->finalDestination); //TO-DO Not implemented
            break;

//DEVELOPER------
        case 'g':
            printf("Generating graph..."); //TO-DO Not implemented
            break;

        default:
            //catch invalid input and return false
            printf("Not a valid input\n");
            return 0;
    }
    return 1;
}

#pragma endregion