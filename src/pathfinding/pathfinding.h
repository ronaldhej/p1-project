#ifndef P_1_PATHFINDING_H
#define P_1_PATHFINDING_H

#include "../graph/graph.h"

int dijkstra(Edge* adjMatrix, int numNodes, int src, int dest, bool airAllowed);
int indexFromCoords(int x, int y, int rowLength);
int shortestUnvisitedVertex(int const dist[], bool const visited[], int numVertex);
bool fullyVisited(bool visited[], int numVertices);
void examineVertex(int vertIndex, int currentVert, int vert, const int cost[], int dist[], int pred[], bool visited[]);
int accumulateTime(const int pred[], int cost[], int v, int dest, int src);

void printMatrix(int matrix[], int length);

#endif //P_1_PATHFINDING_H
