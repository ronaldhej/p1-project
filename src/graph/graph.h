#pragma once

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
                          int airportNum,
                          int maxAirRoutesPerHub,
                          Edge *adjMatrix,
                          int seed,
                          char *outFile);

void initArray(int *a, int end);
void permute(int *a, int n);
int bellcurveSpread(int spread);
int ran(int k);
void swap(int *a, int *b);

void printGraph(int v,
                char *out_file,
                Edge *adjMatrix);

#endif //P_1_GRAPH_H
