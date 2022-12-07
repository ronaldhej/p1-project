
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
    Edge *adjMatrix;
    do {
        printUserManual();
        userInput = readInput();
        handleOption(userInput, adjMatrix);

    } while(userInput->option != 'q');
    free(userInput);
    free(adjMatrix);

  return 0;
}
