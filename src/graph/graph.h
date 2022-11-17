#pragma once
//
// Created by ronaldj on 11/7/22.
//

#ifndef P_1_GRAPH_H
#define P_1_GRAPH_H

#include <stdbool.h>

extern int V;

typedef struct {
    int timeInTransit;
    bool isAir;
} Edge;

int generateWeight(Edge edge);
void initGraph(Edge arr[][V]);
void addEdge(Edge arr[][V], int src, int dest, int weight, bool isAir);
Edge generateRandomEdges(Edge arr[][V], int seed, int (*equation)(int));
void printMatrix(Edge arr[][V]);
void dijkstra(Edge arr[][V], int src, int dest);

#endif //P_1_GRAPH_H
