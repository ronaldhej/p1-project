
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
    int numVertices = 100;

    input *userInput;
    Edge *adjMatrix = initializeAdjMatrix(numVertices);

    //randomConnectedGraph(10,12,240,3,3, adjMatrix,"graph.gv");
    //randomConnectedGraph(6,8,240,2,2, adjMatrix,"graph.gv");
    randomConnectedGraph(numVertices,120,240,4,12, adjMatrix,"graph.gv");

    dijkstra(adjMatrix, numVertices,1,2,true);


    free(userInput);
    free(adjMatrix);
    return 0;

    do {
        printUserManual();
        userInput = readInput();
        handleOption(userInput, adjMatrix);

    } while(userInput->option != 'q');

  return 0;
}
