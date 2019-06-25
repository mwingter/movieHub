#include <stdio.h>
#include <stdlib.h>
#include "graphTad.h"

void printHeader(){
	puts("================MOVIE HUB==============");
	puts("Selecione a opção desejada:");
	puts("(1) - Filmes relacionados");
	puts("(2) - Filmes aversos");
	puts("(3) - Filmes de uma mesma categoria");
	puts("(4) - Sair");
	puts("================MOVIE HUB==============");
}

void printSelectTarget(){
	puts("Digite o titulo alvo...");
}

void printExit(){
	puts("Saindo...");
}

void printError(){
	puts("Opção invalida! Por favor escolha uma opção valida.");
}

void printRelatedMovies(Graph *g, char *movieTarget){
	char **relatedMovies = findRelatedMovies(g, movieTarget);
	if(relatedMovies == NULL) return;
	printf("Filmes relacionados a [%s]\n", movieTarget);
	for(int i=0;i<MAX_RELATED;i++){
		printf("%s\n", relatedMovies[i]);
		free(relatedMovies[i]);
	}

	free(relatedMovies);
	return;
}

void printUnrelatedMovies(Graph *g, char *movieTarget){
	char **unrelatedMovies = findUnrelatedMovies(g, movieTarget);
	if(unrelatedMovies == NULL) return;
	printf("Filmes não relacionados a [%s]\n", movieTarget);
	for(int i=0;i<MAX_RELATED;i++){
		printf("%s\n", unrelatedMovies[i]);
		free(unrelatedMovies[i]);
	}

	free(unrelatedMovies);
	return;
}

void printSameCategory(Graph *g, char *movieTarget){
	int n;
	char **sameCategory = findSameCategory(g, movieTarget, &n);
	if(sameCategory == NULL) return;

	printf("Filmes de mesma categoria que [%s]:\n", movieTarget);
	for(int i=0;i<n;i++){
		printf("%s\n", sameCategory[i]);
		free(sameCategory[i]);
	}

	free(sameCategory);
	return;
}

void printMatrix(Graph *g, int moviesCount){
	puts("-------------matrix-------------");
	for(int i=0; i<moviesCount; i++){
		for(int j=0; j<moviesCount; j++)
			printf("%lf  ", g->m[i][j]);
		puts("");
	}
}
