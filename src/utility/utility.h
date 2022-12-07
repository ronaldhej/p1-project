//
// Created by sande on 11/21/2022.
//

#ifndef P_1_UTILITY_H
#define P_1_UTILITY_H

typedef struct {
    char option;
    char startingLocation[8];
    char finalDestination[8];
} input;

void printUserManual();
input* readInput();
void handleOption(input *_input, Edge *adjMatrix);


#endif //P_1_UTILITY_H