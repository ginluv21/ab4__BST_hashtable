#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"
#include "hashtab.h"

#define N 20

char *words[N] = {
    "apple","banana","cherry","date","elderberry",
    "fig","grape","honey","kiwi","lemon",
    "mango","nectarine","orange","peach","pear",
    "plum","raspberry","strawberry","tomato","watermelon"
};

void print_sep() {
    printf("------------------------------------------------------------\n");
}

void print_bst(struct bstree *t) {
    if (!t) return;
    print_bst(t->left);
    printf("(%s:%d) ", t->key, t->value);
    print_bst(t->right);
}

void print_hash(struct listnode *ht[]) {
    printf("\nHASH TABLE:\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        struct listnode *node = ht[i];
        if (node) {
            printf("[%d]: ", i);
            while (node) {
                printf("(%s:%d) -> ", node->key, node->value);
                node = node->next;
            }
            printf("NULL\n");
        }
    }
}

int main()
{
    struct bstree *tree = NULL;
    struct listnode *ht[HASH_SIZE];
    hashtab_init(ht);

    printf("\n=== ДЕМОНСТРАЦИЯ ===\n");

    /* ================= 1. ДОБАВЛЕНИЕ 10 ================= */
    print_sep();
    printf("[1] Добавление первых 10\n");

    for (int i = 0; i < 10; i++) {
        if (!tree)
            tree = bstree_create(words[i], i);
        else
            bstree_add(tree, words[i], i);

        hashtab_add(ht, words[i], i, ELFHash);

        printf("ADD | %s (%d)\n", words[i], i);
    }

    printf("\nBST:\n"); print_bst(tree); printf("\n");
    print_hash(ht);

    /* ================= 2. ДОБАВЛЕНИЕ ЕЩЁ 10 ================= */
    print_sep();
    printf("[2] Добавление ещё 10\n");

    for (int i = 10; i < 20; i++) {
        bstree_add(tree, words[i], i);
        hashtab_add(ht, words[i], i, ELFHash);

        printf("ADD | %s (%d)\n", words[i], i);
    }

    printf("\nBST:\n"); print_bst(tree); printf("\n");
    print_hash(ht);

    /* ================= 3. MIN / MAX ================= */
    print_sep();
    printf("[3] MIN / MAX\n");

    struct bstree *min = bstree_min(tree);
    struct bstree *max = bstree_max(tree);

    printf("MIN: %s (%d)\n", min->key, min->value);
    printf("MAX: %s (%d)\n", max->key, max->value);

    /* ================= 4. ПОИСК ================= */
    print_sep();
    printf("[4] Поиск\n");

    char *find[] = {"apple","mango","watermelon","none"};

    for (int i = 0; i < 4; i++) {
        struct bstree *b = bstree_lookup(tree, find[i]);
        struct listnode *h = hashtab_lookup(ht, find[i], ELFHash);

        printf("FIND | %-12s | BST:%s | HASH:%s\n",
               find[i],
               b ? "OK" : "NO",
               h ? "OK" : "NO");
    }

    /* ================= 5. УДАЛЕНИЕ 10 (ВТОРАЯ ПОЛОВИНА) ================= */
    print_sep();
    printf("[5] Удаляем 10 элементов (вторая половина)\n");

    for (int i = 10; i < 20; i++) {
        tree = bstree_delete(tree, words[i]);
        hashtab_delete(ht, words[i], ELFHash);

        printf("DEL | %s\n", words[i]);
    }

    /* ================= 6. ПРОВЕРКА ================= */
    print_sep();
    printf("[6] Проверка состояния\n");

    printf("\nBST:\n"); print_bst(tree); printf("\n");
    print_hash(ht);

    printf("\nПроверка:\n");

    for (int i = 0; i < 20; i++) {
        struct bstree *b = bstree_lookup(tree, words[i]);
        struct listnode *h = hashtab_lookup(ht, words[i], ELFHash);

        printf("%-12s | BST:%s | HASH:%s\n",
               words[i],
               b ? "OK" : "DELETED",
               h ? "OK" : "DELETED");
    }

    /* ================= 7. КОЛЛИЗИИ ================= */
    print_sep();
    printf("[7] Коллизии\n");
    printf("Total collisions: %d\n", hashtab_collisions(ht));

    print_sep();
    printf("=== ГОТОВО ===\n");

    return 0;
}