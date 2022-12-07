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

void printSolution(int dist[], int pred[], int src, int v);

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

void ensureMatrixSymmetry(int matrix[], int numVertices) {
    return;
}

void dijkstra(Edge adjMatrix[], int v, int src, int dest, bool airAllowed) {
    int dist[v], pred[v], cost[v*v];
    int count, mindistance, next, index, i, j;
    bool visited[v];

    /*for (i = 1; i <= v; i++) {
        for (j = i; j <= v; j++) {
            index = (i - 1) * v + j - 1;
            printf("\nCost %d: %d", i-1, adjMatrix[index].timeInTransit);
        }
    }*/

    //populate cost matrix
    for (i = 0; i < v*v; i++) {
        //wierd inverse indexing
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
    for (i = 0; i < v*v; i++) {
        if (cost[i] == INFINITY) {
            printf("_");
        } else {
            printf("%d", cost[i]);
        }

        if ((i+1) % v == 0 && i > 0)
            printf("\n");
        else
            printf("\t");
    }

    printf("\nsrc: %d dest: %d\n", src, dest);
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
        if (count >= 1000000) break;

        //examine adjacent vertices
        for (int vert = 0; vert <= v; vert++) {
            int vertIndex = indexFromCoords(currentVert, vert, v);
            if (cost[vertIndex] < INFINITY && !visited[vertIndex]) {
                int newDist = dist[currentVert] + cost[vertIndex];
                if (newDist < dist[vert]) {
                    dist[vert] = newDist;
                    pred[vert] = currentVert;
                }
            }
        }

        //visit next vertex unless fully visited
        if (fullyVisited(visited, v)) break; //<- probably belongs inside while statement
        currentVert = shortestUnvisitedVertex(dist, visited, v);
        visited[currentVert] = true;
        count++;
    }
    printf("\ncount:%d\n", count);

    for (i = 0; i < v; i++) {
        printf("vert[%d] distance : %d\n",(i+1),dist[i]);
    }
    printf("\n");
    for (i = 0; i < v; i++) {
        printf("predecessor to vert[%d] : %d\n",(i+1),pred[i]+1);
    }

    //solution
    printf("SOLUTION : \n");
    printf("%d", dest+1);
    int vertex = pred[dest];
    while (vertex != src) {

        printf(" <- %d", vertex+1);
        vertex = pred[vertex];
    }
    printf(" <- %d", src+1);
    return;
    while (count < v - 1) {
        mindistance = INFINITY;

        for (i = 0; i < v; i++)
            if (dist[i] < mindistance && visited[i] == false) {
                mindistance = dist[i];
                next = i;
            }

        visited[next] = true;
        for (i = 1; i < v; i++){
            for (j = i+1; j <= v; j++){
                index = (i - 1) * v + j - 1;
                if (visited[i] == false)
                    if (mindistance + cost[index] < dist[i]) {
                        dist[i] = mindistance + cost[index];
                        pred[i] = next;
                }
            }
        }
        count++;
    }

    printSolution(dist, pred, src, v);
}

void printSolution(int dist[], int pred[], int src, int v) {
    printf("\nVertex \t\t Distance from Source");
    for (int i = 0; i < v; i++) {
        printf("\n%d \t\t\t\t %d", i+1, dist[i]);
    }

    for (int i = 0; i < v; i++) {
        printf("\nPath to node %d = %d", i+1, i+1);
        int j = i;
        do {
            j = pred[j];
            printf("<-%d", j+1);
        } while (j != src);
    }
}