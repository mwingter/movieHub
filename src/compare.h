#ifndef COMPARE_H
#define COMPARE_H

typedef struct node node_t;
struct node {
    node_t *c[26];
    int id;
};

typedef struct {
    node_t *root;
    int size;
} trie_t;

trie_t *newTrie();
int get(trie_t *t, char *str);

#endif
