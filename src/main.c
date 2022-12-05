
#include "./graph/graph.h"
#include "./utility/utility.h"
#include "./pathfinding/pathfinding.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int randomTimeInTransit() {
    return (rand() % 300) + 60;
}


int main() {

    //V is vertices, e is number of edges, out_file is name of file to save to
    randomConnectedGraph(100, 120, 250, 3, 10,"graph.gv");

  return 0;
}
