
#include "./graph/graph.h"
#include "./utility/utility.h"
#include "./pathfinding/pathfinding.h"
#include <stdbool.h>


// Replace with travel weight formula
int weightEquation(int x) { return x; }

int main() {

  struct edge adjMatrix[V][V];

  printStartingText();

  initGraph(adjMatrix);
  generateRandomEdges(adjMatrix, 1, &weightEquation);

  printMatrix(adjMatrix);

  dijkstra(adjMatrix, 1, 4, false);
  dijkstra(adjMatrix, 1, 4, true);
  return 0;
}
