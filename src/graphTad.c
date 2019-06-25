#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "graphTad.h"
#include "compare.h"
#include "utils.h"

Graph *init(){
	return (Graph*)malloc(sizeof(Graph));
}
int compar_adj(const void *a, const void *b, void *r) {
	double *rd = (double *)r;
	int u = *(int *)a;
	int v = *(int *)b;
	double temp = rd[u]-rd[v];
	if (fabs(temp) < 1e-6) return 0;
	if (temp < 0) return -1;
	return 1;
}

void calculateEdges(Graph *g, int moviesCount){
	if (moviesCount > MAX_VERTEX) {
		printf("Maximum size reached.");
		exit(-1);
	}

	trie_t *trie = newTrie();
	char **words = NULL;
	int nWords = 0, *start = malloc(sizeof(int)*g->numVertex), *end = malloc(sizeof(int)*g->numVertex);

	for (int i = 0; i < g->numVertex; i++) {
		char *sin = g->nodeList[i]->sinopse;
		int len = strlen(sin);
		start[i] = nWords;
		for (int j = 0; j < len; j++) {
			if (!isalpha(sin[j])) continue;
			int k = j;
			while (k < len && isalpha(sin[k])) k++;
			words = realloc(words, (nWords + 1) * sizeof(char *));
			words[nWords++] = calloc(k-j+1, sizeof(char));
			strncpy(words[nWords-1], sin+j, k-j);
			
			for(int l=0; l<k-j; l++) words[nWords-1][l] = tolower(words[nWords-1][l])-'a';
			get(trie, words[nWords-1]);
			j = k;
		}
		end[i] = nWords;
	}
	for (int i = 0; i < g->numVertex; i++) {
		double *v = calloc(trie->size, sizeof(double));
		for (int j = start[i]; j < end[i]; j++) v[get(trie, words[j])]++;
		normalize(v, trie->size);
		g->nodeList[i]->sinopseVec = v;
	}	


	//calculate edge values
	for(int i=0; i<moviesCount; i++){
		for(int j=0; j<moviesCount; j++){
			g->p[i][j] = j;
			if(i != j) {
				g->m[i][j] = lexicalCompare(g->nodeList[i]->sinopseVec, 
					g->nodeList[j]->sinopseVec, trie->size);
			}
		}
		qsort_r(g->p[i], moviesCount, sizeof(int), compar_adj, g->m[i]);
	}

	for(int i=0; i<nWords; i++){
		free(words[i]);
	}
	free(words);
	free(start);
	free(end);

	//purge(trie);
}
//findRelatedMovies returns the first MAX_RELATED most related movies 
char **findRelatedMovies(Graph *g, char *movieTarget){
	int movieTargetIndex = getTargetIndex(g, movieTarget);
	if (movieTargetIndex == -1) {
		puts("Filme não encontrado.");
		return NULL;
	}
	char **relatedMovies = malloc(sizeof(char*) * MAX_RELATED);
	for(int i=0; i<MAX_RELATED; i++){
		//last ones will have the highest score > most related.
		Movie_Node *r = g->nodeList[g->p[movieTargetIndex][g->numVertex-1-i]];
		relatedMovies[i] = malloc(sizeof(char) * strlen(r->nome));
		strcpy(relatedMovies[i], r->nome);
	}	
	return relatedMovies;
}

//findUnrelatedMovies returns the first MAX_RELATED most unrelated movies 
char **findUnrelatedMovies(Graph *g, char *movieTarget){
	int movieTargetIndex = getTargetIndex(g, movieTarget);
	if (movieTargetIndex == -1) {
		puts("Filme não encontrado.");
		return NULL;
	}
	char **unrelatedMovies = malloc(sizeof(char*) * MAX_RELATED);
	for(int i=0; i<MAX_RELATED; i++){
		//first ones will have the lowest score > most unrelated (i+1 because i = 0 > self).
		Movie_Node *r = g->nodeList[g->p[movieTargetIndex][i+1]];
		unrelatedMovies[i] = malloc(sizeof(char) * strlen(r->nome));
		strcpy(unrelatedMovies[i], r->nome);
	}	
	return unrelatedMovies;
}

//findSameCategory returns all movies that share any category 
char **findSameCategory(Graph *g, char *movieTarget, int *n){
	int i = 0, matchCount = 0;
	
	int movieTargetIndex = getTargetIndex(g, movieTarget);
	if (movieTargetIndex == -1) {
		puts("Filme não encontrado.");
		return NULL;
	}
	
	char **sameCategory = malloc(sizeof(char*));
	for(;i<g->numVertex; i++){
		if(hasMatchingCategory(g->nodeList[movieTargetIndex], g->nodeList[i])
		 && movieTargetIndex != i){
			sscanf(g->nodeList[i]->nome, "%m[^\n]", &sameCategory[matchCount]);
			sameCategory = realloc(sameCategory, sizeof(char*) * (matchCount++ + 2));
		}
	}
	*n = matchCount;
	if (*n == 0) {
		free(sameCategory);
		return NULL;
	} 
	return sameCategory;
}

int hasMatchingCategory(Movie_Node *a, Movie_Node *b){
	//get array of strings of categories from A
	char **categoriesA = malloc(sizeof(char*) * 10);
	char **categoriesB = malloc(sizeof(char*) * 10);
	char saveptra[100];
	char saveptrb[100];
	int i=0, j=0;
	strcpy(saveptra, a->genero);
	strcpy(saveptrb, b->genero);
	categoriesA[i++] = strtok(a->genero, ", ");
	while((categoriesA[i++] = strtok(NULL, ", ")));
	categoriesB[j++] = strtok(b->genero, ", ");
	while((categoriesB[j++] = strtok(NULL, ", ")));

	int found = 0;
	//printf("comparacao dos filmes [%s] e [%s]\n", a->nome, b->nome);
	for(int k=0; k<i-1; k++){
		for(int l=0; l<j-1; l++){
			//printf("comparando: %s - %s\n", categoriesA[k], categoriesB[l]);
			if(!strcmp(categoriesA[k], categoriesB[l])){
				found++;
				break;
			}
		}
	}
	free(categoriesA);
	free(categoriesB);
	strcpy(a->genero, saveptra);
	strcpy(b->genero, saveptrb);
	return found;
}
