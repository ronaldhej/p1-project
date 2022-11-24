//
// Created by ronaldj on 11/7/22.
//
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 200
#define MAX_WEIGHT 150

struct edge {
  int weight;
  bool isAir;
};

// V is number of vertices
int V = 10;

void initGraph(struct edge arr[][V]) {
  int i, j;
  for (i = 0; i < V; i++) {
    for (j = 0; j < V; j++) {
      arr[i][j].weight = 0;
      arr[i][j].isAir = false;
    }
  }
}

void addEdge(struct edge arr[][V], int src, int dest, int weight, bool isAir) {
  arr[src][dest].weight = weight;
  arr[dest][src].weight = weight;
  arr[src][dest].isAir = isAir;
  arr[dest][src].isAir = isAir;
}

struct edge generateRandomEdges(struct edge arr[][V], int seed,
                                int (*equation)(int)) {
  int numEdge;
  srand(seed);

  numEdge = 1 + rand() % MAX_EDGES;

  while (numEdge > V * (V - 1) / 2) {
    numEdge = 1 + rand() % MAX_EDGES;
  }

  printf("Number of edges generated: %d\n", numEdge);

  for (int j = 0; j <= numEdge; j++) {
    int a = rand() % V;
    int b = rand() % V;

    addEdge(arr, a, b, equation(1 + rand() % MAX_WEIGHT), false);
  }
}

void printMatrix(struct edge arr[][V]) {
  int i, j, k;

  printf("  ");
  for (k = 0; k < V; k++) {
    printf("%d ", k);
  }
  printf("\n");
  for (i = 0; i < V; i++) {
    printf("%d ", i);
    for (j = 0; j < V; j++) {
      printf("%d ", arr[i][j].weight);
    }
    printf("\n");
  }
}