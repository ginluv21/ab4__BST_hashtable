#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "bstree.h"
#include "hashtab.h"

#define MAX_WORDS 400000

char *words[MAX_WORDS];

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int load_words(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) return -1;
    char buffer[64];
    int count = 0;
    while (count < MAX_WORDS && fscanf(file, "%63s", buffer) == 1) {
        words[count] = strdup(buffer);
        count++;
    }
    fclose(file);
    return count;
}

/* ========================================================================= */
void experiment1_bst_vs_hash()
{
    printf("\nТаблица 1. Эксперимент 1: время поиска (lookup) в BST и Хеш-таблице (ELFHash)\n");
    printf("------------------------------------------------------------------------\n");
    printf(" #  | Кол-во элементов | bstree_lookup, с    | hashtab_lookup, с\n");
    printf("------------------------------------------------------------------------\n");

    struct bstree *tree = NULL;
    struct listnode *ht[HASH_SIZE];
    hashtab_init(ht);

    int current_n = 0;
    int step = 1;

    volatile int dummy = 0;

    for (int n = 20000; n <= MAX_WORDS; n += 20000) {

        for (int i = current_n; i < n; i++) {
            if (tree == NULL)
                tree = bstree_create(words[i], i);
            else
                bstree_add(tree, words[i], i);

            hashtab_add(ht, words[i], i, ELFHash);
        }
        current_n = n;

        double t_start = wtime();
        for (int k = 0; k < 100000; k++) {
            char *key = words[rand() % n];
            dummy += (bstree_lookup(tree, key) != NULL);
        }
        double bst_time = (wtime() - t_start) / 100000.0;

        t_start = wtime();
        for (int k = 0; k < 100000; k++) {
            char *key = words[rand() % n];
            dummy += (hashtab_lookup(ht, key, ELFHash) != NULL);
        }
        double hash_time = (wtime() - t_start) / 100000.0;

        printf("%-3d | %-16d | %-19.8f | %.8f\n",
               step++, n, bst_time, hash_time);
    }
    printf("------------------------------------------------------------------------\n");
}

/* ========================================================================= */
void experiment2_add_bst_vs_hash()
{
    printf("\nТаблица 2. Эксперимент 2: время добавления (add) в BST и Хеш-таблицу\n");
    printf("------------------------------------------------------------------------\n");
    printf(" #  | Кол-во элементов | bstree_add, с       | hashtab_add, с\n");
    printf("------------------------------------------------------------------------\n");

    struct bstree *tree = NULL;
    struct listnode *ht[HASH_SIZE];
    hashtab_init(ht);

    int current_n = 0;
    int step = 1;

    volatile int dummy = 0;

    for (int n = 20000; n <= MAX_WORDS; n += 20000) {

        for (int i = current_n; i < n - 1; i++) {
            if (tree == NULL)
                tree = bstree_create(words[i], i);
            else
                bstree_add(tree, words[i], i);

            hashtab_add(ht, words[i], i, ELFHash);
        }

        /* 🔥 ИСПРАВЛЕННЫЙ ЗАМЕР BST */
        double t_start = wtime();
        for (int k = 0; k < 100000; k++) {
            char *key = words[rand() % n];
            bstree_add(tree, key, k);
            dummy++;
        }
        double bst_time = (wtime() - t_start) / 100000.0;

        /* 🔥 ИСПРАВЛЕННЫЙ ЗАМЕР HASH */
        t_start = wtime();
        for (int k = 0; k < 100000; k++) {
            char *key = words[rand() % n];
            hashtab_add(ht, key, k, ELFHash);
            dummy++;
        }
        double hash_time = (wtime() - t_start) / 100000.0;

        /* добавляем реальный элемент */
        char *new_key = words[n - 1];

        if (tree == NULL)
            tree = bstree_create(new_key, n - 1);
        else
            bstree_add(tree, new_key, n - 1);

        hashtab_add(ht, new_key, n - 1, ELFHash);

        current_n = n;

        printf("%-3d | %-16d | %-19.8f | %.8f\n",
               step++, n, bst_time, hash_time);
    }
    printf("------------------------------------------------------------------------\n");
}

/* ========================================================================= */
void experiment6_collisions()
{
    printf("\nТаблица 6. Эксперимент 6: сравнение KRHash и ELFHash\n");
    printf("+-----+--------+----------------------------+----------------------------+\n");
    printf("|  #  |   N    |         KRHash             |         ELFHash            |\n");
    printf("|     |        | lookup, с  | Коллизий      | lookup, с  | Коллизий      |\n");
    printf("+-----+--------+------------+---------------+------------+---------------+\n");

    struct listnode *ht_kr[HASH_SIZE];
    struct listnode *ht_elf[HASH_SIZE];
    hashtab_init(ht_kr);
    hashtab_init(ht_elf);

    int current_n = 0;
    int step = 1;

    volatile int dummy = 0;

    for (int n = 20000; n <= MAX_WORDS; n += 20000) {

        for (int i = current_n; i < n; i++) {
            hashtab_add(ht_kr, words[i], i, KRHash);
            hashtab_add(ht_elf, words[i], i, ELFHash);
        }
        current_n = n;

        double t_start = wtime();
        for (int k = 0; k < 100000; k++) {
            char *key = words[rand() % n];
            dummy += (hashtab_lookup(ht_kr, key, KRHash) != NULL);
        }
        double kr_time = (wtime() - t_start) / 100000.0;

        t_start = wtime();
        for (int k = 0; k < 100000; k++) {
            char *key = words[rand() % n];
            dummy += (hashtab_lookup(ht_elf, key, ELFHash) != NULL);
        }
        double elf_time = (wtime() - t_start) / 100000.0;

        int kr_col = hashtab_collisions(ht_kr);
        int elf_col = hashtab_collisions(ht_elf);

        printf("| %-3d | %-6d | %-10.8f | %-13d | %-10.8f | %-13d |\n",
               step++, n, kr_time, kr_col, elf_time, elf_col);
    }
    printf("+-----+--------+------------+---------------+------------+---------------+\n");
}

/* ========================================================================= */
int main()
{
    srand(time(NULL));

    printf("Загрузка %d слов из файла 'words.txt'...\n", MAX_WORDS);
    int count = load_words("words.txt");

    if (count < MAX_WORDS) {
        printf("Ошибка: загружено только %d слов из %d.\n", count, MAX_WORDS);
        return 1;
    }

    printf("Успешно загружено %d слов.\n\n", count);

    experiment1_bst_vs_hash();
    experiment2_add_bst_vs_hash();
    experiment6_collisions();

    for (int i = 0; i < count; i++)
        free(words[i]);

    return 0;
}