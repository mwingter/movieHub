#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "graphTad.h"

Movie_Node **getMovies(char *moviePath, int *totalMovies){
	FILE *fp = fopen(moviePath, "r");
	if (!fp){
		printf("couldnt load moviePath.");
		exit(-1);
	}

	int moviesCount = 0;
	Movie_Node **movies = (Movie_Node**)malloc(sizeof(Movie_Node*) * (moviesCount+1));
	while(!feof(fp)){ 
		movies[moviesCount] = (Movie_Node*)malloc(sizeof(Movie_Node));

 		fscanf(fp, "%[^\n]", movies[moviesCount]->nome);			
		fscanf(fp, "%*c%d%*c", &movies[moviesCount]->ano);
		fscanf(fp, "%[^\n]%*c", movies[moviesCount]->genero);
		fscanf(fp, "%[^\n]%*c", movies[moviesCount]->sinopse);

		moviesCount++;
		movies = (Movie_Node**)realloc(movies, sizeof(Movie_Node*) * (moviesCount+1));
	}
	*totalMovies = moviesCount;
	fclose(fp);
	return movies;
}

char *getTarget() {
	char *s;
	scanf("%m[^\n]%*c", &s);
	return s; 
}

int op(){
	int i;
	scanf("%d%*c", &i);
	return i; 	
}

double lexicalCompare(double *u, double *v, int n){
	double dot = 0;
	for (int i = 0; i < n; i++) dot += u[i] * v[i];
	return fabs(dot);
}

void normalize(double *v, int n){
	double s = 0;
	for (int i = 0; i < n; i++) s += 1.0 * v[i] * v[i];
	s = sqrt(s);
	for (int i = 0; i < n; i++) v[i] /= s;
}

int getTargetIndex(Graph *g, char *movieTarget){
	for(int i=0; i<g->numVertex; i++){
		if(!strcmp(movieTarget, g->nodeList[i]->nome)) return i;
	}
	return -1; 
}