//
// Created by ronaldj on 11/7/22.
//
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct edge {
    int weight;
    bool isAir;
};

//V is number of vertices
int V = 8;

void initGraph(struct edge arr[][V]) {
    int i, j;
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            arr[i][j].weight = 0;
            arr[i][j].isAir = false;
        }
    }
}

void addEdge(struct edge arr[][V], int src, int dest, int weight, bool isAir) {
    arr[src][dest].weight = weight;
    arr[src][dest].weight = weight;
    arr[src][dest].isAir = isAir;
    arr[src][dest].isAir = isAir;
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

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }

    return min_index;
}

void printSolution(int dist[]) {
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t\t\t %d\n", i, dist[i]);
    }
}

void dijkstra(struct edge arr[][V], int src, int dest) {
    int dist[V];
    printf("src: %d dest: %d\n", src, dest);

    bool sptSet[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX, sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        if (u == dest) {
            break;
        }
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && arr[u][v].weight
                && dist[u] != INT_MAX
                && dist[u] + arr[u][v].weight < dist[v]) {
                dist[v] = dist[u] + arr[u][v].weight;
            }
        }
    }
    printSolution(dist);
}
