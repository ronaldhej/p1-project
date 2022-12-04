//
// Created by sande on 11/24/2022.
//
#include<stdio.h>
#include<stdbool.h>

#define V 10
#define INT_MAX 200
#define INFINITY 9999

struct edge {
    int weight;
    bool isAir;
};

void printSolution(int dist[], int pred[], int src);

void dijkstra(struct edge adjList[][V], int src, int dest) {
    int dist[V], pred[V];
    struct edge cost[V][V];
    int count, mindistance, next, i, j;
    bool visited[V];

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {

            if (adjList[i][j].weight == 0) {
                cost[i][j].weight = INFINITY;
                cost[i][j].isAir = adjList[i][j].isAir;

            } else {
                cost[i][j].weight = adjList[i][j].weight;
                cost[i][j].isAir = adjList[i][j].isAir;
            }
        }
    }

    printf("src: %d dest: %d\n", src, dest);

    for (i = 0; i < V; i++) {
        dist[i] = cost[src][i].weight;
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
                if (mindistance + cost[next][i].weight < dist[i]) {
                    dist[i] = mindistance + cost[next][i].weight;
                    pred[i] = next;
                }
        count++;
    }

    printSolution(dist, pred, src);
}

void printSolution(int dist[], int pred[], int src) {
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t\t\t %d\n", i, dist[i]);
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