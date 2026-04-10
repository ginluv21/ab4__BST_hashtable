#include <stdlib.h>
#include <string.h>
#include "bstree.h"

struct bstree *bstree_create(char *key, uint32_t value) {
    struct bstree *node = (struct bstree *)malloc(sizeof(struct bstree));
    if (node != NULL) {
        node->key = strdup(key); // Обязательно копируем ключ!
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void bstree_add(struct bstree *tree, char *key, uint32_t value) {
    if (tree == NULL) return;
    
    struct bstree *parent = NULL;
    while (tree != NULL) {
        parent = tree;
        int cmp = strcmp(key, tree->key);
        if (cmp < 0) {
            tree = tree->left;
        } else if (cmp > 0) {
            tree = tree->right;
        } else {
            tree->value = value; // Ключ уже есть, обновляем значение
            return; 
        }
    }
    
    struct bstree *node = bstree_create(key, value);
    if (strcmp(key, parent->key) < 0) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

struct bstree *bstree_lookup(struct bstree *tree, char *key) {
    while (tree != NULL) {
        int cmp = strcmp(key, tree->key);
        if (cmp == 0) {
            return tree;
        } else if (cmp < 0) {
            tree = tree->left;
        } else {
            tree = tree->right;
        }
    }
    return NULL;
}

struct bstree *bstree_min(struct bstree *tree) {
    if (tree == NULL) return NULL;
    while (tree->left != NULL) {
        tree = tree->left;
    }
    return tree;
}

struct bstree *bstree_max(struct bstree *tree) {
    if (tree == NULL) return NULL;
    while (tree->right != NULL) {
        tree = tree->right;
    }
    return tree;
}

struct bstree *bstree_delete(struct bstree *root, char *key)
{
    if (root == NULL)
        return NULL;

    int cmp = strcmp(key, root->key);

    if (cmp < 0) {
        root->left = bstree_delete(root->left, key);
    }
    else if (cmp > 0) {
        root->right = bstree_delete(root->right, key);
    }
    else {
        // 0 или 1 ребёнок
        if (root->left == NULL) {
            struct bstree *tmp = root->right;
            free(root->key);
            free(root);
            return tmp;
        }
        else if (root->right == NULL) {
            struct bstree *tmp = root->left;
            free(root->key);
            free(root);
            return tmp;
        }

        // 2 ребёнка
        struct bstree *min = bstree_min(root->right);

        free(root->key);
        root->key = strdup(min->key); // Копируем ключ, чтобы не потерять память
        root->value = min->value;

        root->right = bstree_delete(root->right, min->key);
    }

    return root;
}

void bstree_free(struct bstree *tree) {
    if (tree == NULL) return;
    bstree_free(tree->left);
    bstree_free(tree->right);
    free(tree->key);
    free(tree);
}