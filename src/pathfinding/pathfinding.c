//
// Created by sande on 11/24/2022.
//
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <math.h>

#include "../graph/graph.h"

#define V 10
#define INFINITY 9999

void printMatrix(int matrix[], int length) {
    for (int i = 0; i < length*length; i++) {
        if (matrix[i] == INFINITY) {
            printf("_");
        } else {
            printf("%d", matrix[i]);
        }

        if ((i+1) % length == 0 && i > 0)
            printf("\n");
        else
            printf("\t");
    }
}

//return unvisited vertex with shortest distance to source
int shortestUnvisitedVertex(int const dist[], bool const visited[], int numVertex) {
    int min = INFINITY;
    int bestVert = -1;

    for (int i = 0; i < numVertex; i++) {
        //compare vert to current best vert
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            bestVert = i;
        }
    }

    return bestVert;
}

bool fullyVisited(bool visited[], int numVertices) {
    //return if unvisited vertex exists
    for (int i = 0; i < numVertices; i++) {
        if (visited[i] == false) return false;
    }
    return true;
}

void examineVertex(int vertIndex, int currentVert, int vert, int cost[], int dist[], int pred[], bool visited[]) {
    if (cost[vertIndex] < INFINITY && !visited[vertIndex]) {
        int newDist = dist[currentVert] + cost[vertIndex];
        if (newDist < dist[vert]) {
            dist[vert] = newDist;
            pred[vert] = currentVert;
        }
    }
}

void dijkstra(Edge adjMatrix[], int v, int src, int dest, bool airAllowed) {
    int dist[v], pred[v], cost[v*v];
    int count, i;
    bool visited[v];

    //populate cost matrix
    for (i = 0; i < v*v; i++) {
        //weird inverse indexing
        int x = (int) floor((double) i / (double) v);
        int y = i % v;
        cost[i] = INFINITY;

        int adjIndex = indexFromCoords(x,y,v);
        int t_transit = adjMatrix[adjIndex].timeInTransit;
        //add cost for rail
        if (!adjMatrix[adjIndex].isAir && t_transit > 0) {
            //alternating x and y is to ensure symmetry
            cost[indexFromCoords(x, y,v)] = t_transit;
            cost[indexFromCoords(y,x,v)] = t_transit;
        }

        //air is not allowed -> iteration is done
        if (!airAllowed) continue;

        //add cost for air
        if (adjMatrix[adjIndex].isAir && t_transit > 0) {
            cost[indexFromCoords(x, y,v)] = t_transit;
            cost[indexFromCoords(y,x,v)] = t_transit;
        }
    }

    printf("\n");

    //print cost matrix
    //printMatrix(cost, v);

    //decrement src & dest
    //ie. vertex 1 would in code be vertex 0
    src--;
    dest--;

    //initialize arrays
    for (i = 0; i < v; i++) {
        dist[i]     = INFINITY; //distance to source
        pred[i]     = 0;
        visited[i]  = false;
    }

    dist[src] = 0;
    visited[src] = true;
    count = 1;

    //visit vertices
    int currentVert = src;
    while(1) {
        if (count >= 10000000) break; //FAILSAFE

        //examine adjacent vertices
        for (int vert = 0; vert <= v; vert++) {
            int vertIndex = indexFromCoords(currentVert, vert, v);
            examineVertex(vertIndex, currentVert, vert, cost, dist, pred, visited);
        }

        //visit next vertex unless graph has been fully visited
        if (fullyVisited(visited, v)) break; //<- probably belongs inside while statement
        currentVert = shortestUnvisitedVertex(dist, visited, v);
        visited[currentVert] = true;
        count++;
    }
    //printf("\ncount:%d\n", count);

    //solution
    printf("%s", (airAllowed) ? "AIR " : "RAIL " );
    printf("ROUTE : \n");
    printf("%d", dest+1);
    int vertex = pred[dest];
    while (vertex != src) {

        printf(" <- %d", vertex+1);
        vertex = pred[vertex];
    }
    printf(" <- %d", src+1);
}