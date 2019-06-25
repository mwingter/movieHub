#ifndef UTILS_H
#define UTILS_H
#include "graphTad.h"


int op();
char *getTarget();
double lexicalCompare(double *u, double *v, int n);
Movie_Node **getMovies(char *moviePath, int *moviesCount);
int getTargetIndex(Graph *g, char *movieTarget);
void normalize(double *v, int n);

#endif
