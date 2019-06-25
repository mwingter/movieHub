#ifndef GRAPHTAD_H
#define GRAPHTAD_H

#define MAX_VERTEX 200
#define MAX_RELATED 5

typedef struct {
	char nome[100];
	int ano;
	char genero[50];
	char sinopse[5000];
	double *sinopseVec;
}Movie_Node;

typedef struct {
	int numVertex;
	double m[MAX_VERTEX][MAX_VERTEX];
	int p[MAX_VERTEX][MAX_VERTEX];
	Movie_Node **nodeList;
}Graph;


Graph *init();
void calculateEdges(Graph *g, int moviesCount);

char **findRelatedMovies(Graph *g, char *movieTarget);
char **findUnrelatedMovies(Graph *g, char *movieTarget);
char **findSameCategory(Graph *g, char *movieTarget, int *n);

int hasMatchingCategory(Movie_Node *a, Movie_Node *b);

#endif
