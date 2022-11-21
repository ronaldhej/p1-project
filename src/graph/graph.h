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


void dijkstra(Edge arr[][V], int src, int dest);

void randomConnectedGraph(int v,
                            int e,
                            int maxWgt,
                            char *outFile);

#endif //P_1_GRAPH_H
