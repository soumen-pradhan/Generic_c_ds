#include <stdio.h>
#include <stdbool.h>

#include "RBtree.h"
#include "Stack.h"
#include "Vector.h"

// Comparator and printing function to be supplied by user (Here, int)
// These functions determine the type to be used in Tree

bool int_less(void *a, void *b) { return *((int *)a) < *((int *)b); }
bool int_equal(void *a, void *b) { return *((int *)a) == *((int *)b); }

void printTree(RBtree *T, RBnode *node, int depth) {
    if (node == T->nil)
        return;

    printTree(T, node->right, depth+1);

    for (int i = 0; i < depth-1; i++) printf("     ");
    int key = *((int *)node->key);

    if (node->p == T->nil) printf("%d", key);
    else if (node->p->left == node) printf("`---%d", key);
    else printf(".---%d", key);
    printf("\n");

    printTree(T, node->left, depth+1);
}

void print_vec(Vector *vec) {
    int *a = (int *)vec->elem;
    for (int i = 0; i < vec->size; i++) {
        printf("%d ", a[i]);
    }
    putchar('\n');
}

int main(int argc, char const *argv[])
{
    Vector *vec = Vector_init(int);
    int a[3] = {3, 1, 2};
    for (int i = 0; i < atoi(argv[1]); i++) {
        Vector_push(vec, a[i%3]);
        printf("%d, %ld\n", i, vec->cap);
    }
    print_vec(vec);
    int v;
    Vector_access(vec, 5, v);
    printf("%d\n", v);
    Vector_free(vec);
}

