#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtab.h"

unsigned int KRHash(char *s){
    unsigned int h = 0, hash_mul = 31;
    while (*s)
        h = h * hash_mul + (unsigned int)*s++;
    return h % HASH_SIZE;
}

unsigned int ELFHash(char *s){
    unsigned int h = 0, g;
    while (*s) {
        h = (h << 4) + (unsigned int)*s++;
        g = h & 0xF0000000L;
        if (g)
            h ^= g >> 24;
        h &= ~g;
    }
    return h % HASH_SIZE;
}

void hashtab_init(struct listnode **hashtab){
    for (int i = 0; i < HASH_SIZE; i++)
        hashtab[i] = NULL;
}

void hashtab_add(struct listnode **hashtab, char *key, uint32_t value,
                 unsigned int (*hash_func)(char *))
{
    unsigned int index = hash_func(key);
    struct listnode *node;

    for (node = hashtab[index]; node != NULL; node = node->next) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
    }

    node = (struct listnode *)malloc(sizeof(struct listnode));
    if (node != NULL) {
        node->key   = strdup(key);
        node->value = value;
        node->next  = hashtab[index];
        hashtab[index] = node;
    }
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key,
                                unsigned int (*hash_func)(char *))
{
    unsigned int index = hash_func(key);
    struct listnode *node;

    for (node = hashtab[index]; node != NULL; node = node->next)
        if (strcmp(node->key, key) == 0)
            return node;
    return NULL;
}

void hashtab_delete(struct listnode **hashtab, char *key,
                    unsigned int (*hash_func)(char *))
{
    unsigned int index = hash_func(key);
    struct listnode *node = hashtab[index];
    struct listnode *prev = NULL;

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            if (prev == NULL)
                hashtab[index] = node->next;
            else
                prev->next = node->next;
            free(node->key);
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

int hashtab_collisions(struct listnode **hashtab){
    int collisions = 0;

    for (int i = 0; i < HASH_SIZE; i++) {
        int chain_len = 0;
        struct listnode *node = hashtab[i];
        while (node != NULL) {
            chain_len++;
            node = node->next;
        }
        if (chain_len > 1)
            collisions += chain_len - 1;
    }
    return collisions;
}

void hashtab_free(struct listnode **hashtab){
    for (int i = 0; i < HASH_SIZE; i++) {
        struct listnode *node = hashtab[i];
        while (node != NULL) {
            struct listnode *next = node->next;
            free(node->key);
            free(node);
            node = next;
        }
    }
}

unsigned int DJB2Hash(char *str){
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash % HASH_SIZE;
}