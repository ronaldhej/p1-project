#include <stdio.h>
#include <stdbool.h>
#include "../graph/graph.h"
#include <string.h>

#define STRING_EDGE_MAX 256

void graphToDotFile(Edge graph[][V], const char* outFilePath) {
    FILE* oFile = fopen(outFilePath, "w");

    //write nodes to file
    int i, j;
    for (i = 0; i < V; i++) {
        fprintf(oFile, "%d [shape=circle]\n", i);
    }
    fprintf(oFile, "\n");

    //iterate through rows of edges in graph
    for (i = 0; i < V; i++) {
        //limit nested for loop by i
        //since we only have to look at one half of the relations (assuming the relation set is symmetric)
        // + ignore reflexive relations
        for (j = 0; j < i; j++) {
            int weight = graph[i][j].timeInTransit;
            bool isAir = graph[i][j].isAir;

            //write edge to file
            char edgeString[STRING_EDGE_MAX];

            //only add edge to file if it exists
            if (weight > 0) {
                float w = (float)(weight/100.0);
                fprintf(oFile, "%d -- %d ", i, j);
                if (isAir) {
                    fprintf(oFile, "[len = %.2f, color = red];\n", w);
                } else {
                    fprintf(oFile, "[len = %.2f, label = %.2f];\n", w, w);
                }
            }
        }
    }

    fclose(oFile);
}