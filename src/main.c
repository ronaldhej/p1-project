#include "./graph/graph.h"
#include <stdbool.h>

int main() {

    struct edge adjMatrix[V][V];

    initGraph(adjMatrix);
    addEdge(adjMatrix, 0, 1, 1, true);
    addEdge(adjMatrix, 0, 2, 1, false);
    addEdge(adjMatrix, 1, 2, 1, false);
    addEdge(adjMatrix, 2, 3, 1, true);

    printMatrix(adjMatrix);

    return 0;
}
