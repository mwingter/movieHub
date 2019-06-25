#ifndef PRINT_FUNCTIONS_H
#define PRINT_FUNCTIONS_H
#define EXIT 4

#include "graphTad.h"

//Interface
void printHeader();
void printSelectTarget();
void printRelatedMovies(Graph *g, char *movieTarget);
void printUnrelatedMovies(Graph *g, char *movieTarget);
void printSameCategory(Graph *g, char *movieTarget);
void printExit();
void printError();
//Internal
void printMatrix(Graph *g, int moviesCount);

#endif
