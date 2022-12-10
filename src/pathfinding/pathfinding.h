//
// Created by sande on 11/24/2022.
//

#ifndef P_1_PATHFINDING_H
#define P_1_PATHFINDING_H

#include "../graph/graph.h"

void dijkstra(Edge* adjMatrix, int numNodes, int src, int dest, bool airAllowed);
void printSolution(int dist[], int pred[], int src);
int indexFromCoords(int x, int y, int rowLength);

#endif //P_1_PATHFINDING_H
