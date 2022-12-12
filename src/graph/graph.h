#pragma once
//
// Created by ronaldj on 11/7/22.
//

#ifndef P_1_GRAPH_H
#define P_1_GRAPH_H

#include <stdbool.h>

typedef struct {
    int timeInTransit;
    bool isAir;
    int dwellDeparture;
    int dwellArrival;
} Edge;

Edge* initializeAdjMatrix(int numVertices);

void randomConnectedGraph(int numNodes,
                          int numEdges,
                          int maxWgt,
                          int airportNum,
                          int maxAirRoutesPerHub,
                          Edge *adjMatrix,
                          int seed,
                          char *outFile);

#endif //P_1_GRAPH_H
