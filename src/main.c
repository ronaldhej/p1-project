#include "./graph/graph.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define SEED 320

typedef struct {
    int timeTo;
    int timeDep;
    int timeIn;
    int timeArr;
    int timeFrom;
} NodeWeight;

// Replace with travel weight formula
int generateWeight(int nodeCount) {
    NodeWeight node[nodeCount];


    node[nodeCount].timeTo = 0;
    node[nodeCount].timeDep = 0;
    node[nodeCount].timeIn = rand() % (nodeCount + SEED);
    node[nodeCount].timeArr = 0;
    node[nodeCount].timeFrom = 0;


    //bugs out every 4th iteration, resets i to 0
    int weight = node[nodeCount].timeTo + node[nodeCount].timeDep + node[nodeCount].timeIn + node[nodeCount].timeArr + node[nodeCount].timeFrom;
    if (weight < 60) {
        weight = 60;
    }
    if (weight > 360) {
        weight = 360;
    }

    return weight;
}

int main() {

  //struct edge adjMatrix[V][V];

  //initGraph(adjMatrix);
  //generateRandomEdges(adjMatrix, 1234, &generateWeight);

  //printMatrix(adjMatrix);

  //dijkstra(adjMatrix, 1, 4);

    for (int i = 1; i <= 50; i++) {
        int travelTime = generateWeight(i);
        printf("Total travel time for node%d is %d min.\n", i, travelTime);
    }

  return 0;
}
