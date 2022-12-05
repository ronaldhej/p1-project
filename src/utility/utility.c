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
        scanf(" %c", &userInput->option);

    //ask for input until input option is valid
    } while (!handleOption(userInput));

    return userInput;
}

void handleInput(input *_input) {

}

#pragma region local functions

//different behavior determined by option
int handleOption(input* _input) {
    switch (_input->option) {

//USER-----------
        case 't': {
            printf("Please enter your starting location: ");
            scanf(" %s", (char *) _input->startingLocation);

            printf("Please enter your final destination: ");
            scanf(" %s", (char *) _input->finalDestination);

            printf("Is %s -> %s your desired journey? (y/n):", _input->startingLocation,
                   _input->finalDestination); //TO-DO Not implemented
            break;
        }

//DEVELOPER------
        case 'g': {
            int nVertices, nEdges, maxWgt, nAirports, maxAirPerHub;
            char *outFile = "graph.gv";

            printf("\n_____ Graph setup wizard:\n");

            printf("[1/5] Number of vertices:  ");
            scanf(" %d", &nVertices);

            printf("[2/5] Number of edges:  ");
            scanf(" %d", &nEdges);

            printf("[3/5] Maximum value for weights: ");
            scanf(" %d", &maxWgt);

            printf("[4/5] Number of airport hubs: ");
            scanf(" %d", &nAirports);

            printf("[5/5] Maximum air routes per airport hub: ");
            scanf(" %d", &maxAirPerHub);

            printf("\nGenerating graph...");
            randomConnectedGraph(
                    nVertices,
                    nEdges,
                    maxWgt,
                    nAirports,
                    maxAirPerHub,
                    outFile);
            break;
        }

        default:
            //catch invalid input and return false
            printf("Not a valid input\n");
            return 0;
    }
    return 1;
}

#pragma endregion
