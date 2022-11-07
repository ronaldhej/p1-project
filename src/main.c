#include <stdio.h>
#include <stdlib.h>
#include "./graph/graph.h"

int main() {

    int adjMatrix[V][V];

    init(adjMatrix);
    addEdge(adjMatrix, 0, 1);
    addEdge(adjMatrix, 0, 2);
    addEdge(adjMatrix, 1, 2);
    addEdge(adjMatrix, 2, 0);
    addEdge(adjMatrix, 2, 3);

    printMatrix(adjMatrix);

    return 0;
}
