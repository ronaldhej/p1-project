#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../graph/graph.h"

//time constants for airports in minutes
#define A_TRANSFER_TO_LOCATION      57
#define A_DWELL_AT_LOCATION         118
#define A_AVERAGE_TRANSIT           143
#define A_DWELL_AT_DESTINATION      39
#define A_TRANSFER_FROM_DESTINATION 61

//time constants for rail stations in minutes
#define R_TRANSFER_TO_LOCATION      24
#define R_DWELL_AT_LOCATION         20
#define R_AVERAGE_TRANSIT           198
#define R_DWELL_AT_DESTINATION      12
#define R_TRANSFER_FROM_DESTINATION 21

//initialize adjacency matrix and return the pointer
//allocates memory for numVertices*numVertices Edges
Edge* initializeAdjMatrix(int numVertices) {
    int numEdges = numVertices*numVertices;

    Edge *ptrMatrix = (Edge *) calloc(numEdges*numEdges, sizeof(Edge*));

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

//  Full disclosure, a lot of this code is from  Richard Johnsonbaugh and Martin Kalin from the
//  Department of Computer Science and Information Systems, they have a great way of generating
//  connected graphs, it has however been modified to fit our use case

//connected graph
void randomConnectedGraph(int numVertices,
                            int numEdges,
                            int airportNum,
                            int maxAirRoutesPerHub,
                            Edge *adjMatrix,
                            int seed,
                            char *outFile) {
    int i, j, count, index, *tree;

    //Set seed for rand
    srand(seed);


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

        //define time in transit
        adjMatrix[tree[i] * numVertices + tree[j]].timeInTransit =
        adjMatrix[tree[j] * numVertices + tree[i]].timeInTransit = R_AVERAGE_TRANSIT + bellcurveSpread(178);

        //define time of dwell departure
        adjMatrix[tree[i] * numVertices + tree[j]].dwellDeparture =
        adjMatrix[tree[j] * numVertices + tree[i]].dwellDeparture = R_DWELL_AT_LOCATION + bellcurveSpread(6);

        //define time of dwell arrival
        adjMatrix[tree[i] * numVertices + tree[j]].dwellArrival =
        adjMatrix[tree[j] * numVertices + tree[i]].dwellArrival = R_DWELL_AT_DESTINATION + bellcurveSpread(4);
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
            adjMatrix[index].timeInTransit = R_AVERAGE_TRANSIT + bellcurveSpread(178);
            adjMatrix[index].dwellDeparture = R_DWELL_AT_DESTINATION + bellcurveSpread(6);
            adjMatrix[index].dwellArrival = R_DWELL_AT_DESTINATION + bellcurveSpread(4);
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
                adjMatrix[index].timeInTransit = A_AVERAGE_TRANSIT + bellcurveSpread(98);
                adjMatrix[index].isAir = true;
                adjMatrix[index].dwellDeparture = A_DWELL_AT_LOCATION + bellcurveSpread(20);
                adjMatrix[index].dwellArrival = A_DWELL_AT_DESTINATION + bellcurveSpread(20);
                currRoutes++;
            }
        }

        count++;

    }
    printf("Printed Graph \n");
    printGraph(numVertices, count, outFile, adjMatrix);

    system("dot -Tsvg graph.gv -o output.svg");
    system("dot -Tpng graph.gv -o output.png");

    free(tree);
}

void initArray(int *a, int end) {
    int i;

    for (i = 0; i < end; i++)
        *a++ = i;
}

void permute(int *a, int n) {
    int i;

    for (i = 0; i < n - 1; i++)
        swap(a + i + ran(n - i), a + i);
}

void swap(int *a, int *b) {
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

/* Return a random integer between 0 and k-1 inclusive. */
int ran(int k) {
    return rand() % k;
}

//returns a random signed offset using simple bell curve equation
int bellcurveSpread(int spread) {
    //random number between 0-1;
    int decimalCount = 100;
    double x = (double)(rand() % decimalCount) / decimalCount;

    //bellcurve equation
    double offset = 1.0/pow(1+pow(x, 2.0),(3.0/2.0));

    //inverse offset
    offset = 1-offset;
    offset *= spread;

    //50% chance of offset being negative
    if (rand() % 2 == 1) {
        offset *= -1;
    }

    return (int)round(offset);
}

void printGraph(int v,
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
    //write connections to file
    for (i = 1; i < v; i++)
        for (j = i + 1; j <= v; j++) {
            index = (i - 1) * v + j - 1;
            int weight = adjMatrix[index].timeInTransit;
            if (!weight) continue; //skip iteration if undefined

            if (adjMatrix[index].isAir) {
                fprintf(fp, "%5d -- %5d [label=%5d, weight=%5d, color=red]\n", i, j, weight, weight);
            } else {
                fprintf(fp, "%5d -- %5d [label=%5d, weight=%5d]\n", i, j, weight, weight);
            }
        }
    fprintf(fp, "}");
    fclose(fp);
    printf("\tGraph is written to file %s.\n", out_file);
}
