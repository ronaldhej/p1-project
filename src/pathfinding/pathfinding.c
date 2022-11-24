//
// Created by sande on 11/24/2022.
//

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
            if (!sptSet[v] && arr[u][v].weight && dist[u] != INT_MAX &&
                dist[u] + arr[u][v].weight < dist[v]) {
                dist[v] = dist[u] + arr[u][v].weight;
            }
        }
    }
    printSolution(dist);
}