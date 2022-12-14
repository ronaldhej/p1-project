#ifndef P_1_UTILITY_H
#define P_1_UTILITY_H

typedef struct {
    char option;
    char startingLocation[8];
    char finalDestination[8];
} Input;

typedef struct {
    int numVertices;
    int numEdges;
    int maxHubs;
    int maxAirRoutes;
} GraphValues;

void printUserManual();
Input* readInput();
void waitForUser();
void handleOption(Input *_input, GraphValues *graphValues, Edge *adjMatrix, int *numVertices);
bool validateGraphValues(GraphValues *graphValues);
void writeValuesToFile(GraphValues *graphValues);
bool readValuesFromFile(GraphValues* graphValues);
void calculateRoutes(Edge *adjMatrix, int numVertices, Input* input);
void setupGraphValues(GraphValues *graphValues);


#endif //P_1_UTILITY_H