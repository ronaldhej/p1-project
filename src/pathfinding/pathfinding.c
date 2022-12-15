#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "../graph/graph.h"
#include "../pathfinding/pathfinding.h"

#define INFINITY 9999

void dijkstra(Edge adjMatrix[], int v, int src, int dest, bool airAllowed) {
    int dist[v], pred[v], cost[v*v];
    int count, i, j;
    bool visited[v];

    //populate cost matrix
    for (i = 0; i < v; i++)
    for (j = 0; j < v; j++) {
        //indexing from 2D coordinates
        int adjIndex = indexFromCoords(i,j,v);
        int t_transit = adjMatrix[adjIndex].timeInTransit;

        cost[adjIndex] = INFINITY;

        if(t_transit > 0) {
            t_transit += adjMatrix[adjIndex].dwellDeparture;
            t_transit += adjMatrix[adjIndex].dwellArrival;
        }

        //add cost for rail
        if (!adjMatrix[adjIndex].isAir && t_transit > 0) {
            //alternating x and y is to ensure symmetry
            cost[indexFromCoords(i, j,v)] = t_transit;
            cost[indexFromCoords(j,i,v)] = t_transit;
        }

        //air is not allowed -> iteration is done
        if (!airAllowed) continue;

        //add cost for air
        if (adjMatrix[adjIndex].isAir && t_transit > 0) {
            cost[indexFromCoords(i,j,v)] = t_transit;
            cost[indexFromCoords(j,i,v)] = t_transit;
        }
    }

    printf("\n");

    //print cost matrix
    //printMatrix(cost, v);

    //decrement src & dest
    //ie. vertex 1 would in code be vertex 0
    src--;
    dest--;

    //initialize arrays
    for (i = 0; i < v; i++) {
        dist[i]     = INFINITY; //distance to source
        pred[i]     = 0;
        visited[i]  = false;
    }

    dist[src] = 0;
    visited[src] = true;
    count = 1;

    //visit vertices
    int currentVert = src;
    while(!fullyVisited(visited, v)) {

        //examine adjacent vertices
        for (int vert = 0; vert < v; vert++) {
            int vertIndex = indexFromCoords(currentVert, vert, v);
            examineVertex(vertIndex, currentVert, vert, cost, dist, pred, visited);
        }

        //visit next vertex unless graph has been fully visited
        currentVert = shortestUnvisitedVertex(dist, visited, v);
        visited[currentVert] = true;
        count++;
    }
    //printf("\ncount:%d\n", count);

    //solution
    printf("%s", (airAllowed) ? "AIR " : "RAIL " );
    printf("ROUTE : \n");
    printf("%d", dest+1);
    int vertex = pred[dest];
    while (vertex != src) {

        printf(" <- %d", vertex+1);
        if (vertex == pred[vertex] && pred[vertex] != src) {
            printf(" ERROR: stuck at vertex: %d\n", vertex+1);
            break;
        }
        vertex = pred[vertex];
    }
    printf(" <- %d", src+1);

    int timeInMinutes = accumulateTime(pred, cost, v, dest, src);
    printf("\nTotal travel time : ");
    printMinutes(timeInMinutes);
}

//convert 2D array coords to 1D array index
int indexFromCoords(int x, int y, int rowLength) {
    return y * rowLength + x;
}

bool fullyVisited(bool visited[], int numVertices) {
    //return false if unvisited vertex exists
    for (int i = 0; i < numVertices; i++) {
        if (visited[i] == false) return false;
    }
    return true;
}

void examineVertex(int vertIndex, int currentVert, int vert, const int cost[], int dist[], int pred[], bool visited[]) {

    if (cost[vertIndex] < INFINITY && !visited[vert]) {
        int newDist = dist[currentVert] + cost[vertIndex];
        if (newDist < dist[vert]) {
            dist[vert] = newDist;
            pred[vert] = currentVert;
        }
    }
}

//return unvisited vertex with shortest distance to source
int shortestUnvisitedVertex(int const dist[], bool const visited[], int numVertex) {
    int min = INFINITY;
    int bestVert = -1;

    for (int i = 0; i < numVertex; i++) {
        //compare vert to current best vert
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            bestVert = i;
        }
    }

    return bestVert;
}

//calculate total travel time of journey in minutes
int accumulateTime(const int pred[], int cost[], int v, int dest, int src) {
    int t_accumulated = 0;
    int toVertex = dest;
    int fromVertex = pred[toVertex];

    //iterate through every section of a journey
    while (toVertex != src) {


        int edgeTime = cost[indexFromCoords(toVertex, fromVertex, v)];
        printf("\n");
        printf("from %d to %d costs %d\n", fromVertex+1, toVertex+1, edgeTime);
        //add time of transit
        t_accumulated += edgeTime;

        toVertex = fromVertex;
        fromVertex = (fromVertex != src) ? pred[fromVertex] : src;
    }

    return t_accumulated;
}

//only used for debugging
void printMatrix(int matrix[], int length) {
    for (int i = 0; i < length*length; i++) {
        if (matrix[i] == INFINITY) {
            printf("_");
        } else {
            printf("%d", matrix[i]);
        }

        if ((i+1) % length == 0 && i > 0)
            printf("\n");
        else
            printf("\t");
    }
}

//prints minutes as hours and remaining minutes
void printMinutes(int minutes) {
    int hours = (int) floor((double) minutes / 60.0);
    minutes %= 60;

    if (hours <= 0) {
        printf("%d minutes\n", minutes);
        return;
    }

    printf("%d hours and %d minutes\n", hours, minutes);
}