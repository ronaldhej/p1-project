//
// Created by ronaldj on 11/7/22.
//
#include <stdio.h>
#include <stdbool.h>

struct edge {
    int weight;
    bool isAirport;
};

//V is number of vertices
int V = 8;

void initGraph(struct edge arr[][V]) {
    int i, j;
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            arr[i][j].weight = 0;
            arr[i][j].isAirport = false;
        }
    }
}

void addEdge(struct edge arr[][V], int i, int j, int weight, bool isAirport) {
    arr[i][j].weight = weight;
    arr[j][i].weight = weight;
    arr[i][j].isAirport = isAirport;
    arr[j][i].isAirport = isAirport;
}



void printMatrix(struct edge arr[][V]) {
    int i, j, k;

    printf("  ");
    for (k = 0; k < V; k++) {
        printf("%d ", k);
    }
    printf("\n");
        for (i = 0; i < V; i++) {
            printf("%d ", i);
            for (j = 0; j < V; j++) {
                printf("%d ", arr[i][j].weight);
            }
            printf("\n");
        }

    }
