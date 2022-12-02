
#include "./graph/graph.h"
#include "./utility/utility.h"

#include <stdbool.h>
#include <stdlib.h>


// Replace with travel weight formula
int weightEquation(int x) { return x; }

int main() {

    struct edge adjMatrix[V][V];

    printUserManual();
    input *userInput = readInput();
    handleInput(userInput);
    free(userInput);

    //initGraph(adjMatrix);
    //generateRandomEdges(adjMatrix, 1234, &weightEquation);
    //printMatrix(adjMatrix);

    return 0;
}
