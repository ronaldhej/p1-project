//
// Created by ronaldj on 11/7/22.
//
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 200
#define MAX_WEIGHT 150

typedef struct {
  int timeInTransit;
  bool isAir;
} Edge;

typedef struct {
    int ID;
    char Title;
} Vertex;

typedef struct {
    int timeTo;
    int timeDep;
    int timeIn;
    int timeArr;
    int timeFrom;
} NodeWeight;

// Replace with travel timeInTransit formula
int generateWeight(Edge edge) {
    //NodeWeight node[nodeCount];


    //node[nodeCount].timeTo = 0;
    //node[nodeCount].timeDep = 0;
    int timeIn = edge.timeInTransit;
    //node[nodeCount].timeArr = 0;
    //node[nodeCount].timeFrom = 0;


    //bugs out every 4th iteration, resets i to 0
    int weight = 0;//node[nodeCount].timeTo + node[nodeCount].timeDep + node[nodeCount].timeIn + node[nodeCount].timeArr + node[nodeCount].timeFrom;

    return weight;
}






// V is number of vertices
int V = 10;

void initGraph(Edge arr[][V]) {
  int i, j;
  for (i = 0; i < V; i++) {
    for (j = 0; j < V; j++) {
      arr[i][j].timeInTransit = 0;
      arr[i][j].isAir = false;
    }
  }
}

void addEdge(Edge arr[][V], int src, int dest, int weight, bool isAir) {
  arr[src][dest].timeInTransit = weight;
  arr[dest][src].timeInTransit = weight;
  arr[src][dest].isAir = isAir;
  arr[dest][src].isAir = isAir;
}

Edge generateRandomEdges(Edge arr[][V], int seed,
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

void printMatrix(Edge arr[][V]) {
  int i, j, k;

  printf("  ");
  for (k = 0; k < V; k++) {
    printf("%d ", k);
  }
  printf("\n");
  for (i = 0; i < V; i++) {
    printf("%d ", i);
    for (j = 0; j < V; j++) {
      printf("%d ", arr[i][j].timeInTransit);
    }
    printf("\n");
  }
}

int minDistance(int dist[], bool sptSet[]) {
  int min = INT_MAX, min_index;

  for (int v = 0; v < V; v++) {
    if (sptSet[v] == false && dist[v] <= min) {
      min = dist[v], min_index = v;
    }
  }

  return min_index;
}

void printSolution(int dist[]) {
  printf("Vertex \t\t Distance from Source\n");
  for (int i = 0; i < V; i++) {
    printf("%d \t\t\t\t %d\n", i, dist[i]);
  }
}

void dijkstra(Edge arr[][V], int src, int dest) {
  int dist[V];
  printf("src: %d dest: %d\n", src, dest);

  bool sptSet[V];

  for (int i = 0; i < V; i++) {
    dist[i] = INT_MAX, sptSet[i] = false;
  }

  dist[src] = 0;

  for (int count = 0; count < V - 1; count++) {
    int u = minDistance(dist, sptSet);
    sptSet[u] = true;
    if (u == dest) {
      break;
    }
    for (int v = 0; v < V; v++) {
      if (!sptSet[v] && arr[u][v].timeInTransit && dist[u] != INT_MAX &&
          dist[u] + arr[u][v].timeInTransit < dist[v]) {
        dist[v] = dist[u] + arr[u][v].timeInTransit;
      }
    }
  }
  printSolution(dist);
}
