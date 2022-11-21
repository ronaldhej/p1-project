
#include "./graph/graph.h"
#include <stdbool.h>


// Replace with travel weight formula
int weightEquation(int x) { return x; }

int main() {

  struct edge adjMatrix[V][V];

  initGraph(adjMatrix);
  generateRandomEdges(adjMatrix, 1234, &weightEquation);

  printMatrix(adjMatrix);

  dijkstra(adjMatrix, 1, 4);
  return 0;
}
