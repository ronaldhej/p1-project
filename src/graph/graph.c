//
// Created by ronaldj on 11/7/22.
//
#include <stdio.h>

int V = 8;

void init(int arr[][V]) {
    int i, j;
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            arr[i][j] = 0;
        }
    }
}

void addEdge(int arr[][V], int i, int j) {
    arr[i][j] = 1;
    arr[j][i] = 1;
}

void printMatrix(int arr[][V]) {
    int i, j, k;

    printf("x ");
    for (k = 0; k < V; k++) {
        printf("%d ", k);
    }
    printf("\n");
        for (i = 0; i < V; i++) {
            printf("%d ", i);
            for (j = 0; j < V; j++) {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        }

    }
