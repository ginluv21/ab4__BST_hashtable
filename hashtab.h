#ifndef HASHTAB_H
#define HASHTAB_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define HASH_SIZE 400000

struct listnode {
    char *key;
    uint32_t value;
    struct listnode *next;
};

unsigned int KRHash(char *s);
unsigned int ELFHash(char *s);
void hashtab_init(struct listnode **hashtab);
void hashtab_add(struct listnode **hashtab, char *key, uint32_t value,
                 unsigned int (*hash_func)(char *));
struct listnode *hashtab_lookup(struct listnode **hashtab, char *key,
                                unsigned int (*hash_func)(char *));
void hashtab_delete(struct listnode **hashtab, char *key,
                    unsigned int (*hash_func)(char *));
int hashtab_collisions(struct listnode **hashtab);
void hashtab_free(struct listnode **hashtab);
unsigned int DJB2Hash(char *str);

#endif