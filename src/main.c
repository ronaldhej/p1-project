
#include "./graph/graph.h"
#include "./utility/utility.h"
#include "./pathfinding/pathfinding.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int randomTimeInTransit() {
    return (rand() % 300) + 60;
}

int main() {
    setbuf(stdout, 0);
    int numVertices = 100;

    Input *userInput;
    GraphValues *graphValues = malloc(sizeof(GraphValues));
    Edge *adjMatrix;
    char *outFile = "graph.gv";

    graphValues->numVertices = 0;
    graphValues->numEdges = 0;
    graphValues->maxWeight = 0;
    graphValues->maxHubs = 0;
    graphValues->maxAirRoutes = 0;

    //randomConnectedGraph(10,12,240,3,3, adjMatrix,"graph.gv");
    //randomConnectedGraph(6,8,240,2,2, adjMatrix,"graph.gv");
    //randomConnectedGraph(numVertices,120,240,4,12, adjMatrix,"graph.gv");

    //dijkstra(adjMatrix, numVertices,1,2,true);

    do {
        if (validateGraphValues(graphValues)) {
            adjMatrix = initializeAdjMatrix(numVertices);

            randomConnectedGraph(
                    numVertices,
                    graphValues->numEdges,
                    graphValues->maxWeight,
                    graphValues->maxHubs,
                    graphValues->maxAirRoutes,
                    adjMatrix,
                    outFile);
        }

        printUserManual();
        userInput = readInput();
        handleOption(userInput, graphValues, adjMatrix, &numVertices);

    } while(userInput->option != 'q');

    free(graphValues);
    free(userInput);
    free(adjMatrix);
    return 0;
}
