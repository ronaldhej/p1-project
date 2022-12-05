//
// Created by sande on 11/24/2022.
//
#include<stdio.h>
#include<stdbool.h>

#define V 10
#define INFINITY 9999

void printSolution(int dist[], int pred[], int src);

typedef struct {
    int weight;
    bool isAir;
} Edge;

void dijkstra(Edge adjMatrix[][V], int src, int dest, bool airAllowed) {
    int dist[V], pred[V], cost[V][V];
    int count, mindistance, next, i, j;
    bool visited[V];

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {

            if (adjMatrix[i][j].weight == 0) {
                cost[i][j] = INFINITY;

            }
            else {
                if(airAllowed == true){
                    cost[i][j] = adjMatrix[i][j].weight;
                }
                else if(airAllowed == false){
                    if(adjMatrix[i][j].isAir == true){
                        cost[i][j] = INFINITY;
                    }
                    else if(adjMatrix[i][j].isAir == false){
                        cost[i][j] = adjMatrix[i][j].weight;
                    }
                }
            }
        }
    }

    printf("\nsrc: %d dest: %d", src, dest);

    for (i = 0; i < V; i++) {
        dist[i] = cost[src][i];
        pred[i] = src;
        visited[i] = false;
    }

    dist[src] = 0;
    visited[src] = true;
    count = 1;

    while (count < V - 1) {
        mindistance = INFINITY;

        for (i = 0; i < V; i++)
            if (dist[i] < mindistance && visited[i] == false) {
                mindistance = dist[i];
                next = i;
            }

        visited[next] = true;
        for (i = 0; i < V; i++)
            if (visited[i] == false)
                if (mindistance + cost[next][i] < dist[i]) {
                    dist[i] = mindistance + cost[next][i];
                    pred[i] = next;
                }
        count++;
    }

    printSolution(dist, pred, src);
}

void printSolution(int dist[], int pred[], int src) {
    printf("\nVertex \t\t Distance from Source");
    for (int i = 0; i < V; i++) {
        printf("\n%d \t\t\t\t %d", i, dist[i]);
    }

    for (int i = 0; i < V; i++) {
        printf("\nPath to node %d = %d", i, i);
        int j = i;
        do {
            j = pred[j];
            printf("<-%d", j);
        } while (j != src);
    }
}