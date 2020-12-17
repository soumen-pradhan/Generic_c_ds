#include "RBtree.h"
#include <time.h>

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

int main(int argc, char const *argv[]) {
    RBtree *T = RBtree_init(int_less, int_equal);

    srand(time(NULL));
    printTree(T, T->root, 0);
    for (int i = 0; i < 13; i++) {
        int a = rand()%100; // Only a variable can be used to insert. Do not use a pointer or literal.
        RBtree_insert(T, a);
    }
    printTree(T, T->root, 0);
    puts("Delete left of Root");
    RBtree_delete(T, T->root->left);
    printTree(T, T->root, 0);
    RBtree_free(T);
}
