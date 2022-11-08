#include "./graph/graph.h"
#include <stdbool.h>

int main() {

    struct edge adjMatrix[V][V];

    initGraph(adjMatrix);
    addEdge(adjMatrix, 0, 1, 1, true);
    addEdge(adjMatrix, 0, 2, 1, false);
    addEdge(adjMatrix, 1, 2, 5, false);
    addEdge(adjMatrix, 2, 3, 1, true);
    addEdge(adjMatrix, 3, 6, 2, true);
    addEdge(adjMatrix, 3, 5, 3, false);
    addEdge(adjMatrix, 3, 4, 10, false);
    addEdge(adjMatrix, 5, 6, 2, false);

    printMatrix(adjMatrix);

    dijkstra(adjMatrix, 1, 4);
    return 0;
}
