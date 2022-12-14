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
    int maxHubs;
    int maxAirRoutes;
} GraphValues;

void writeValuesToFile(GraphValues *graphValues);
bool readValuesFromFile(GraphValues* graphValues);

//prints the initial text, informing the user of how to interact with the program
void printUserManual() {
    printf("\n--- Program options ---\n"
           "User options:\n"
           "t:    Calculate travel time\n"
           "q:    Exit program\n"
           "-----------------------\n"
           "Developer options:\n"
           "g:    Generate a graph using specified seed\n"
           );
    printf("-----------------------\n");
}

//reads Input from the user, returns Input
Input* readInput() {
    Input *userInput = malloc(sizeof(Input));

    printf("Choose an option:");
    scanf(" %c", &userInput->option);

    //ask for Input until Input option is valid

    return userInput;
}

//Enter anything to continue.
//Used to give the user a chance to view outputs
void waitForUser() {
    printf("\nEnter anything to continue:\n");
    char _;
    scanf(" %c", &_);
}

void calculateRoutes(Edge *adjMatrix, int numVertices, Input* input) {
    //run dijkstra on adjacency matrix using both modes of transportation
    printf("\ntravelling from %d to %d\n", input->startingLocation, input->finalDestination);
    dijkstra(adjMatrix,
             numVertices,
             input->startingLocation,
             input->finalDestination,
             false);

    dijkstra(adjMatrix,
             numVertices,
             input->startingLocation,
             input->finalDestination,
             true);
}

//Simple validation of graph values.
//In this case making sure no value is zero.
bool validateGraphValues(GraphValues *graphValues) {
    if (graphValues->numVertices == 0) return false;
    if (graphValues->numEdges == 0) return false;
    if (graphValues->maxHubs == 0) return false;
    if (graphValues->maxAirRoutes == 0) return false;

    return true;
}

void setupGraphValues(GraphValues *graphValues) {

    printf("\n_____ Graph setup wizard:\n");

    printf("[1/4] Number of vertices:  ");
    scanf(" %d", &graphValues->numVertices);

    printf("[2/4] Number of edges:  ");
    scanf(" %d", &graphValues->numEdges);

    printf("[3/4] Number of airport hubs: ");
    scanf(" %d", &graphValues->maxHubs);

    printf("[4/4] Maximum air routes per airport hub: ");
    scanf(" %d", &graphValues->maxAirRoutes);

    writeValuesToFile(graphValues);
}

//Different behavior determined by option.
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

            //make sure number of vertices is defined
            if (numVertices == NULL) {
                printf("nVertices is undeclared!\n");
                break;
            }
            calculateRoutes(adjMatrix, *numVertices, _input);

            break;
        }

        case 'q': {
            break;
        }

//DEVELOPER------
        case 'g': {
            setupGraphValues(graphValues);
            break;
        }

        default:
            //catch invalid Input and return false
            printf("Not a valid Input\n");
            break;
    }
}

//graph values functions
bool readValuesFromFile(GraphValues* graphValues) {
    graphValues->numVertices = 0;
    graphValues->numEdges = 0;
    graphValues->maxHubs = 0;
    graphValues->maxAirRoutes = 0;

    FILE* file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Failed to open data file! (read)\n");
        return false;
    }

    fscanf(file, "%d", &graphValues->numVertices);
    fscanf(file, "%d", &graphValues->numEdges);
    fscanf(file, "%d", &graphValues->maxHubs);
    fscanf(file, "%d", &graphValues->maxAirRoutes);

    fclose(file);
    return true;
}

void writeValuesToFile(GraphValues *graphValues) {
    FILE* file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Failed to open data file! (write)\n");
    }

    fprintf(file, "%d\n", graphValues->numVertices);
    fprintf(file, "%d\n" , graphValues->numEdges);
    fprintf(file, "%d\n" , graphValues->maxHubs);
    fprintf(file, "%d\n" , graphValues->maxAirRoutes);

    fclose(file);
}