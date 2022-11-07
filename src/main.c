#include "./graph/graph.h"

int main() {

    int adjMatrix[V][V];

    initGraph(adjMatrix);
    addEdge(adjMatrix, 0, 1, 1);
    addEdge(adjMatrix, 0, 2, 1);
    addEdge(adjMatrix, 1, 2, 1);
    addEdge(adjMatrix, 2, 3, 1);

    printMatrix(adjMatrix);

    return 0;
}
