//
// Created by sande on 11/24/2022.
//
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#include "../graph/graph.h"

#define V 10
#define INFINITY 9999

void printSolution(int dist[], int pred[], int src, int v);

void dijkstra(Edge adjMatrix[], int v, int src, int dest, bool airAllowed) {
    int dist[v], pred[v], cost[v*v];
    int count, mindistance, next, index, i, j;
    bool visited[v];

    for (i = 1; i <= v; i++) {
        for (j = i; j <= v; j++) {
            index = (i - 1) * v + j - 1;
            printf("\nCost %d: %d", i-1, adjMatrix[index].timeInTransit);
        }
    }

    for (i = 1; i < v; i++) {
        for (j = i+1; j <= v; j++) {
            index = (i - 1) * v + j - 1;
            if (adjMatrix[index].timeInTransit == 0) {
                cost[index] = INFINITY;
            }
            else {
                if(airAllowed == true){
                    cost[index] = adjMatrix[index].timeInTransit;
                }
                else if(airAllowed == false){
                    if(adjMatrix[index].isAir == true){
                        cost[index] = INFINITY;
                    }
                    else if(adjMatrix[index].isAir == false){
                        cost[index] = adjMatrix[index].timeInTransit;
                    }
                }
            }
        }
    }

    printf("\nsrc: %d dest: %d", src, dest);

    for (i = 0; i < v; i++) {
        dist[i] = cost[v];
        pred[i] = src;
        visited[i] = false;

    }

    dist[src] = 0;
    visited[src] = true;
    count = 1;

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