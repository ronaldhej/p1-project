
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

    input *userInput;
    Edge *adjMatrix = initializeAdjMatrix(10);

    randomConnectedGraph(10,12,240,3,3, adjMatrix,"graph.gv");
    printf("\ngraph success");

    dijkstra(adjMatrix, 10,1,2,false);
    printf("\ndijkstra success");

    return 0;

    do {
        printUserManual();
        userInput = readInput();
        handleOption(userInput, adjMatrix);

    } while(userInput->option != 'q');
    free(userInput);
    free(adjMatrix);

  return 0;
}
