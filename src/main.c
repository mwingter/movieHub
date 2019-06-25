#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_functions.h"
#include "graphTad.h"
#include "utils.h"

char *moviePath = "assets/movies.txt";

int main(int argc, char const *argv[]){
	int operation, moviesCount;
	char *target;
	Graph *g = init();

	g->nodeList = getMovies(moviePath, &moviesCount);
	g->numVertex = moviesCount;
	
 	calculateEdges(g, moviesCount);

	do{
		printHeader();
		
		operation = op();
		
		switch(operation){
			case 1:
				printSelectTarget();
				target = getTarget();
				printRelatedMovies(g, target);
				free(target);
				break;
			case 2:
				printSelectTarget();
				target = getTarget();
				printUnrelatedMovies(g, target);
				free(target);
				break;
			case 3:
				printSelectTarget();
				target = getTarget();
				printSameCategory(g, target);
				free(target);
				break;
			case 4:
				printExit();
				break;
			default:
				fseek(stdin, 0, SEEK_END);
				printError();
		}
	}
	while(operation != EXIT);
	
	for(int i=0; i<moviesCount; i++){
		free(g->nodeList[i]);
	}
	free(g->nodeList); free(g);
	return 0;
}