#include "./graph/graph.h"
#include "./draw/draw.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define SEED 320

int randomTimeInTransit() {
    return (rand() % 300) + 60;
}

int main() {

  Edge adjMatrix[V][V];

  initGraph(adjMatrix);
  generateRandomEdges(adjMatrix, 1234, &randomTimeInTransit);

  printMatrix(adjMatrix);


    for (int i = 1; i <= 50; i++) {
        int travelTime = generateWeight(adjMatrix[i][0]);
        printf("Total travel time for node%d is %d min.\n", i, travelTime);
    }

  return 0;
}
