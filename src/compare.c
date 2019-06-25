#include <stdlib.h>
#include <string.h>
#include "compare.h"

trie_t *newTrie() {
    trie_t *t = malloc(sizeof(trie_t));
    t->size = 0;
    t->root = NULL;
    return t;
}

static node_t *_add(node_t *cur, char *s, int i, int len) {
    if (cur == NULL) {
        cur = calloc(1, sizeof(node_t));
        cur->id = -1;
    }
    if (i == len) {
        return cur;
    }
    cur->c[(int) s[i]] = _add(cur->c[(int) s[i]], s, i+1, len);
    return cur;
}

static node_t *_find(node_t *cur, char *s, int i, int len) {
    if (cur == NULL || i == len) {
        return cur;
    }
    return _find(cur->c[(int) s[i]], s, i+1, len);
}

int get(trie_t *t, char *str){
    int n = strlen(str);
    t->root = _add(t->root, str, 0, n);
    node_t *node = _find(t->root, str, 0, n);

    if (node->id == -1) return node->id = t->size++;
    return node->id;
}

// void purge(trie_t *t){
//     for(int i=0; i<t->size; i++){
//         pur
//     }   
// }
