//
// Created by sande on 11/24/2022.
//

#ifndef P_1_PATHFINDING_H
#define P_1_PATHFINDING_H

void dijkstra(struct edge arr[][V], int src, int dest);
void printSolution(int dist[]);
int minDistance(int dist[], bool visited[]);

#endif //P_1_PATHFINDING_H
