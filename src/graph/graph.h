#pragma once
//
// Created by ronaldj on 11/7/22.
//

#ifndef P_1_GRAPH_H
#define P_1_GRAPH_H

#include <stdbool.h>

extern int V;

struct edge {
    int weight;
    bool isAir;
};


void initGraph(struct edge arr[][V]);
void addEdge(struct edge arr[][V], int src, int dest, int weight, bool isAir);
void printMatrix(struct edge arr[][V]);
void dijkstra(struct edge arr[][V], int src, int dest);

#endif //P_1_GRAPH_H
