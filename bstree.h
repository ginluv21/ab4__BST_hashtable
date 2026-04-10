#ifndef BSTREE_H
#define BSTREE_H

#include <stdint.h>

struct bstree {
    char *key;
    uint32_t value;
    struct bstree *left;
    struct bstree *right;
};

struct bstree *bstree_create(char *key, uint32_t value);
void bstree_add(struct bstree *tree, char *key, uint32_t value);
struct bstree *bstree_lookup(struct bstree *tree, char *key);
struct bstree *bstree_min(struct bstree *tree);
struct bstree *bstree_max(struct bstree *tree);
struct bstree *bstree_delete(struct bstree *root, char *key);
void bstree_free(struct bstree *tree);

#endif