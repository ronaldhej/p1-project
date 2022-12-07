#include <stdio.h>
#include <malloc.h>

#include "../graph/graph.h"
#include "../pathfinding/pathfinding.h"

typedef struct {
    char option;
    int startingLocation;
    int finalDestination;
} Input;

typedef struct {
    int numVertices;
    int numEdges;
    int maxWeight;
    int maxHubs;
    int maxAirRoutes;
} GraphValues;

//prints the initial text, informing the user of how to interact with the program
void printUserManual() {
    printf("\n--- Program options ---\n"
           "User options:\n"
           "t:    Calculate travel time\n"
           "q:    Exit program\n"
           "Developer options:\n"
           "g:    Generate a graph using specified seed\n\n"
           );
}

//reads Input from the user, returns Input
Input* readInput() {
    Input *userInput = malloc(sizeof(Input));

    printf("Choose an option:");
    scanf(" %c", &userInput->option);

    //ask for Input until Input option is valid

    return userInput;
}

#pragma region local functions

//different behavior determined by option
void handleOption(Input *_input, GraphValues *graphValues, Edge *adjMatrix, int *numVertices) {
    switch (_input->option) {

//USER-----------
        case 't': {
            char confirm = 'x';
            if (!adjMatrix) {
                printf("Please generate graph first \n");
                break;
            }
            do {
                printf("Please enter your starting location: \n");
                scanf(" %d", &_input->startingLocation);

                printf("Please enter your final destination: \n");
                scanf(" %d",  &_input->finalDestination);

                printf("Is %d -> %d your desired journey? (y/n):\n", _input->startingLocation,
                       _input->finalDestination);

                do {
                    scanf(" %c", &confirm);
                    if(confirm != 'y' && confirm != 'n') printf("Please enter y for yes or n for no:\n");
                } while(confirm != 'y' && confirm != 'n');
            } while(confirm == 'n');


            printf("\n%d->", _input->startingLocation);
            printf("%d\n",_input->finalDestination);

            if (numVertices == NULL) {
                printf("nVertices is undeclared!\n");
                break;
            }

            dijkstra(adjMatrix,
                     *numVertices,
                     _input->startingLocation,
                     _input->finalDestination,
                     false);

            dijkstra(adjMatrix,
                     *numVertices,
                     _input->startingLocation,
                     _input->finalDestination,
                     true);
            break;
        }

        case 'q': {
            break;
        }

//DEVELOPER------
        case 'g': {
            int nEdges, maxWgt, nAirports, maxAirPerHub;

            printf("\n_____ Graph setup wizard:\n");

            printf("[1/5] Number of vertices:  ");
            scanf(" %d", numVertices);

            printf("[2/5] Number of edges:  ");
            scanf(" %d", &nEdges);

            printf("[3/5] Maximum value for weights: ");
            scanf(" %d", &maxWgt);

            printf("[4/5] Number of airport hubs: ");
            scanf(" %d", &nAirports);

            printf("[5/5] Maximum air routes per airport hub: ");
            scanf(" %d", &maxAirPerHub);

            printf("\nGenerating graph...");
            graphValues->numVertices = *numVertices;
            graphValues->numEdges = nEdges;
            graphValues->maxWeight = maxWgt;
            graphValues->maxHubs = nAirports;
            graphValues->maxAirRoutes = maxAirPerHub;

            break;
        }

        default:
            //catch invalid Input and return false
            printf("Not a valid Input\n");
            break;
    }
}

#pragma endregion
