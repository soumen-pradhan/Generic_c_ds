#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "RBtree.h"
#include "Stack.h"
#include "Vector.h"

// Comparator and printing function to be supplied by user (Here, int)
// These functions determine the type to be used in Tree

bool intLess(void *a, void *b) { return *((int *)a) < *((int *)b); }
bool intEqual(void *a, void *b) { return *((int *)a) == *((int *)b); }

void printIntTree(RBtree *T, RBnode *node, int depth) {
    if (node == T->nil)
        return;

    printIntTree(T, node->right, depth+1);

    for (int i = 0; i < depth-1; i++) printf("     ");
    int key = *((int *)node->key);

    if (node->p == T->nil) printf("%d", key);
    else if (node->p->left == node) printf("`---%d", key);
    else printf(".---%d", key);
    printf("\n");

    printIntTree(T, node->left, depth+1);
}

void printIntVec(Vector *vec) {
    int *a = (int *)vec->elem;
    for (int i = 0; i < vec->size; i++) {
        printf("%d ", a[i]);
    }
    putchar('\n');
}

int main(int argc, char const *argv[])
{
    int val[5];
    for (int i = 0; i < 5; i++) {
        val[i] = rand() % 500;
    }

    long int elem = argc > 1 ? strtol(argv[1], NULL, 10) : 20;

    {
        puts("RBtree");
        RBtree *tr = RBtree_init(intLess, intEqual);
        for (int i = 0; i < elem; i++) {
            RBtree_insert(tr, val[i%5]);
        }
        printIntTree(tr, tr->root, 0);
        RBtree_free(tr);
    }
    {
        puts("Stack");
        Stack *stk = Stack_init(int);
        for (int i = 0; i < elem; i++) {
            Stack_push(stk, val[i%5]);
        }
        int t;
        for (int i = 0; i < elem; i++) {
            Stack_pop(stk, t);
            printf("%d ", t);
        }
        putchar('\n');
        Stack_free(stk);
    }
    {
        puts("Vector");
        Vector *vec = Vector_init(int);
        for (int i = 0; i < elem; i++) {
            Vector_push(vec, val[i%5]);
        }
        printIntVec(vec);
        Vector *vec2 = Vector_init(int);
        for (int i = 0; i < elem; i++) {
            Vector_push(vec2, val[i%5]);
        }
        Vector_push_vector(vec, vec2);
        printIntVec(vec);
        Vector_free(vec);
        Vector_free(vec2);
    }
    
}
