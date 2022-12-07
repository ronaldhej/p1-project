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

void randomConnectedGraph(int numNodes,
                          int numEdges,
                          int maxWgt,
                          int airportNum,
                          int maxAirRoutesPerHub,
                          Edge *adjMatrix,
                          char *outFile);

#endif //P_1_GRAPH_H
