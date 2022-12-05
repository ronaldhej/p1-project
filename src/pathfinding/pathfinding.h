//
// Created by sande on 11/24/2022.
//

#ifndef P_1_PATHFINDING_H
#define P_1_PATHFINDING_H

void dijkstra(Edge adjMatrix[][V], int src, int dest, bool airAllowed);
void printSolution(int dist[], int pred[], int src);

#endif //P_1_PATHFINDING_H
