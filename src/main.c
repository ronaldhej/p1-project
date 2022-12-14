#include "./graph/graph.h"
#include "./utility/utility.h"
#include "./pathfinding/pathfinding.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//replace SEED with desired number
#define SEED 1234

int main() {
    setbuf(stdout, 0); //enables console output when debugging
    int numVertices = 0;

    Input *userInput;
    GraphValues *graphValues = malloc(sizeof(GraphValues));
    Edge *adjMatrix;
    char *outFile = "graph.gv";

    if (readValuesFromFile(graphValues)) {
        adjMatrix = initializeAdjMatrix(graphValues->numVertices);
        randomConnectedGraph(
                graphValues->numVertices,
                graphValues->numEdges,
                graphValues->maxHubs,
                graphValues->maxAirRoutes,
                adjMatrix,SEED, outFile);
    } else {
        printf("No graph exists, please generate a graph before travelling");
    }


    //main loop
    do {
        if (validateGraphValues(graphValues)) {
            free(adjMatrix);
            adjMatrix = initializeAdjMatrix(graphValues->numVertices);

            printf("\nGenerating graph...");
            randomConnectedGraph(
                    graphValues->numVertices,
                    graphValues->numEdges,
                    graphValues->maxHubs,
                    graphValues->maxAirRoutes,
                    adjMatrix,
                    SEED,
                    outFile);
            numVertices = graphValues->numVertices;

            graphValues->numVertices = 0;
            graphValues->numEdges = 0;
            graphValues->maxHubs = 0;
            graphValues->maxAirRoutes = 0;
        }
        waitForUser();

        printUserManual();
        userInput = readInput();
        handleOption(userInput, graphValues, adjMatrix, &numVertices);

    } while(userInput->option != 'q');

    //cleanup and exit
    free(graphValues);
    free(userInput);
    free(adjMatrix);
    return 0;
}
