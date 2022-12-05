
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

    printUserManual();
    input *userInput = readInput();
    handleInput(userInput);
    free(userInput);

  return 0;
}
