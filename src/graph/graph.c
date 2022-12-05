//
// Created by ronaldj on 11/7/22.
//
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// V is number of vertices
int V = 1000;

typedef struct {
    int timeInTransit;
    bool isAir;
} Edge;

typedef struct {
    int ID;
    char Title;
} Vertex;

typedef struct {
    int timeTo;
    int timeDep;
    int timeIn;
    int timeArr;
    int timeFrom;
} NodeWeight;

// Replace with travel timeInTransit formula
int generateWeight(Edge edge) {
    // NodeWeight node[nodeCount];

    // node[nodeCount].timeTo = 0;
    // node[nodeCount].timeDep = 0;
    int timeIn = edge.timeInTransit;
    // node[nodeCount].timeArr = 0;
    // node[nodeCount].timeFrom = 0;

    // bugs out every 4th iteration, resets i to 0
    int weight = 0; // node[nodeCount].timeTo + node[nodeCount].timeDep +
    // node[nodeCount].timeIn + node[nodeCount].timeArr +
    // node[nodeCount].timeFrom;

    return weight;
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

void dijkstra(Edge arr[][V], int src, int dest) {
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
            if (!sptSet[v] && arr[u][v].timeInTransit && dist[u] != INT_MAX &&
                dist[u] + arr[u][v].timeInTransit < dist[v]) {
                dist[v] = dist[u] + arr[u][v].timeInTransit;
            }
        }
    }
    printSolution(dist);
}

//  Full disclosure, this code is from  Richard Johnsonbaugh and Martin Kalin from the
//  Department of Computer Science and Information Systems, they have a great way of generating
//  connected graphs

void initArray(int *a, int end) {
    int i;

    for (i = 0; i < end; i++)
        *a++ = i;
}

/* Return a random integer between 0 and k-1 inclusive. */
int ran(int k) {
    return rand() % k;
}

void swap(int *a, int *b) {
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void permute(int *a, int n) {
    int i;

    for (i = 0; i < n - 1; i++)
        swap(a + i + ran(n - i), a + i);
}

void printGraph(int v,
                int e,
                char *out_file,
                Edge *adjMatrix) {
    int i, j, index;
    FILE *fp;

    if ((fp = fopen(out_file, "w")) == NULL) {
        printf("Unable to open file %s for writing.\n", out_file);
        return;
    }
    printf("\n\tWriting graph to file %s.\n", out_file);

    fprintf(fp, "graph G {\n");
    fprintf(fp, "\tlayout=fdp\n\tsplines=true\n\tK=2\n\tnode [shape=circle]\n");
    for (i = 1; i < v; i++)
        for (j = i + 1; j <= v; j++) {
            index = (i - 1) * v + j - 1;
            if (adjMatrix[index].timeInTransit) {
                int weight = adjMatrix[index].timeInTransit;
                if (adjMatrix[index].isAir) {
                    fprintf(fp, "%5d -- %5d [label=%5d, weight=%5d, color=red]\n", i, j, weight, weight);
                } else {
                    fprintf(fp, "%5d -- %5d [label=%5d, weight=%5d]\n", i, j, weight, weight);
                }
            }
        }
    fprintf(fp, "}");
    fclose(fp);
    printf("\tGraph is written to file %s.\n", out_file);
}


//connected graph

void randomConnectedGraph(int numNodes,
                            int numEdges,
                            int maxWgt,
                            int airportNum,
                            int maxAirRoutesPerHub,
                            char *outFile) {
    int i, j, count, index, *tree;
    Edge *adjMatrix;


    if ((adjMatrix = (Edge *) calloc(numNodes * numNodes, sizeof(Edge)))
        == NULL) {
        printf("Not enough room for this size graph\n");
        return;
    }


    if ((tree = (int *) calloc(numNodes, sizeof(int))) == NULL) {
        printf("Not enough room for this size graph\n");
        free(adjMatrix);
        return;
    }

    printf("\n\tBeginning construction of graph.\n");

    /*  Generate a random permutation in the array tree. */
    initArray(tree, numNodes);
    permute(tree, numNodes);

    /*  Next generate a random spanning tree.
        The algorithm is:

          Assume that vertices tree[ 0 ],...,tree[ i - 1 ] are in
          the tree.  Add an edge incident on tree[ i ]
          and a random vertex in the set {tree[ 0 ],...,tree[ i - 1 ]}.
     */

    for (i = 1; i < numNodes; i++) {
        j = ran(i);
        adjMatrix[tree[i] * numNodes + tree[j]].timeInTransit =
        adjMatrix[tree[j] * numNodes + tree[i]].timeInTransit = 1 + ran(maxWgt);
    }

    /* Add additional random edges until achieving at least desired number */
    for (count = numNodes - 1; count < numEdges;) {
        i = ran(numNodes);
        j = ran(numNodes);

        if (i == j)
            continue;

        if (i > j)
            swap(&i, &j);

        index = i * numNodes + j;
        if (!adjMatrix[index].timeInTransit) {
            adjMatrix[index].timeInTransit = 1 + ran(maxWgt);
            count++;
        }
    }

    //Airport hub adding loop
    for(count = 0; count < airportNum;) {
        int numRoutes = ran(maxAirRoutesPerHub);

        i = ran(numNodes);

        // Loop to add multiple routes from same airport hub
        for (int currRoutes = 0; currRoutes < numRoutes;) {
            j = ran(numNodes);

            if (i == j)
                continue;

            if (i > j)
                swap(&i, &j);

            index = i * numNodes + j;

            if(!adjMatrix[index].timeInTransit && !adjMatrix[index].isAir) {
                adjMatrix[index].timeInTransit = 1 + ran(maxWgt);
                adjMatrix[index].isAir = true;
                currRoutes++;
            }
        }

        count++;

    }

    printGraph(numNodes, count, outFile, adjMatrix);

    free(tree);
    free(adjMatrix);
}