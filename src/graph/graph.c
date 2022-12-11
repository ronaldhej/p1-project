//
// Created by ronaldj on 11/7/22.
//
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int timeInTransit;
    bool isAir;
} Edge;

// V is number of vertices
int V = 1000;

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

//initialize adjacency matrix and return the pointer
//allocates memory for numVertices*numVertices Edges
Edge* initializeAdjMatrix(int numVertices) {
    int numEdges = numVertices*numVertices;

    Edge *ptrMatrix = (Edge *) malloc(numEdges * sizeof(Edge*));

    if (ptrMatrix == NULL) {
        printf("Not enough room for this size graph\n");

        return NULL;
    }

    //initialize all edges
    for (int edge = 0; edge < numEdges; edge++) {
        ptrMatrix[edge].timeInTransit = 0;
        ptrMatrix[edge].isAir = false;
    }

    return ptrMatrix;
}

//convert 2D array coords to 1D array index
int indexFromCoords(int x, int y, int rowLength) {
    return y * rowLength + x;
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

    printf("graph G {\n");
    printf("\tlayout=fdp\n\tsplines=true\n\tK=2\n\tnode [shape=circle]\n");
    for (i = 1; i < v; i++)
        for (j = i + 1; j <= v; j++) {
            index = (i - 1) * v + j - 1;
            if (adjMatrix[index].timeInTransit) {
                int weight = adjMatrix[index].timeInTransit;
                if (adjMatrix[index].isAir) {
                    printf("%5d -- %5d [label=%5d, weight=%5d, color=red]\n", i, j, weight, weight);
                } else {
                    printf("%5d -- %5d [label=%5d, weight=%5d]\n", i, j, weight, weight);
                }
            }
        }
    printf("}");
}

//connected graph
void randomConnectedGraph(int numVertices,
                            int numEdges,
                            int maxWgt,
                            int airportNum,
                            int maxAirRoutesPerHub,
                            Edge *adjMatrix,
                            char *outFile) {
    int i, j, count, index, *tree;


    if ((tree = (int *) calloc(numVertices, sizeof(int))) == NULL) {
        printf("Not enough room for this size graph\n");
        free(adjMatrix);
        return;
    }

    printf("\n\tBeginning construction of graph.\n");

    /*  Generate a random permutation in the array tree. */
    initArray(tree, numVertices);
    permute(tree, numVertices);

    /*  Next generate a random spanning tree.
        The algorithm is:

          Assume that vertices tree[ 0 ],...,tree[ i - 1 ] are in
          the tree.  Add an edge incident on tree[ i ]
          and a random vertex in the set {tree[ 0 ],...,tree[ i - 1 ]}.
     */

    printf("\n\tBuilding 1D array.\n");
    for (i = 1; i < numVertices; i++) {
        j = ran(i);
        adjMatrix[tree[i] * numVertices + tree[j]].timeInTransit =
        adjMatrix[tree[j] * numVertices + tree[i]].timeInTransit = 1 + ran(maxWgt);
    }

    printf("\n\tAdding additional random edges.\n");
    /* Add additional random edges until achieving at least desired number */
    for (count = numVertices - 1; count < numEdges;) {
        i = ran(numVertices);
        j = ran(numVertices);

        if (i == j)
            continue;

        if (i > j)
            swap(&i, &j);

        index = i * numVertices + j;
        if (!adjMatrix[index].timeInTransit) {
            adjMatrix[index].timeInTransit = 1 + ran(maxWgt);
            count++;
        }
    }

    printf("\n\tAdding airport hubs.\n");
    //Airport hub adding loop
    for(count = 0; count < airportNum;) {
        int numRoutes = ran(maxAirRoutesPerHub);

        i = ran(numVertices);

        // Loop to add multiple routes from same airport hub
        for (int currRoutes = 0; currRoutes < numRoutes;) {
            j = ran(numVertices);

            if (i == j)
                continue;

            if (i > j)
                swap(&i, &j);

            index = i * numVertices + j;

            if(!adjMatrix[index].timeInTransit && !adjMatrix[index].isAir) {
                adjMatrix[index].timeInTransit = (1 + ran(maxWgt))/(maxWgt/2);
                adjMatrix[index].isAir = true;
                currRoutes++;
            }
        }

        count++;

    }
    printf("Printed Graph \n");
    printGraph(numVertices, count, outFile, adjMatrix);
/*

    printf("Printed pathfinding \n");
    dijkstra(adjMatrix,
             numVertices,
             1,
             2,
             false);
*/
    free(tree);
}
