#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <string>
#include <iostream>

typedef enum _COLOR { RED = 0, BLACK } COLOR;
// typedef enum _KID { LEFT = 0, RIGHT } KID;

typedef struct _RBnode {
    struct _RBnode *left, *right, *p;
    int key;
    COLOR color;
} RBnode;

typedef struct _Tree {
    RBnode *root, *nil;
} Tree;

RBnode *init_RBnode(int val, bool black) {
    RBnode *node = (RBnode *)malloc( sizeof(RBnode) );
    node->left = node->right = node->p = NULL;
    node->key = val;
    black == true ? node->color = BLACK : node->color = RED;

    return node;
}

void printTree(Tree *T, RBnode *node, int depth) {
    if (node == T->nil)
        return;

    std::string space;
    for (int i = 0; i < depth-1; i++) space += "     ";

    printTree(T, node->right, depth+1);

    std::cout << space;
    if (node->p == T->nil) std::cout << node->key;
    else if (node->p->left == node) std::cout << "`---" << node->key;
    else std::cout << ".---" << node->key;
    std::cout << "\n";

    printTree(T, node->left, depth+1);
}

Tree *init_Tree() {
    Tree *tree = (Tree *)malloc( sizeof(Tree) );
    tree->nil = init_RBnode(0, true);
    tree->root = tree->nil;

    return tree;
}

// void free_Tree(Tree *T, RBnode *node) {
//     if (node->left != T->nil) free_Tree(node->left);
//     if (node->right != T->nil) free_Tree(node->right);
//     free(node);
// }

RBnode *tree_search(Tree *T, RBnode *node, int val) {
    while (node != T->nil && node->key != val) {
        if (val < node->key) node = node->left;
        else node = node->right;
    }
    return node;
}

RBnode *tree_minimum(Tree *T, RBnode *node) {
    while (node->left != T->nil) node = node->left;
    return node;
}

RBnode *tree_maximum(Tree *T, RBnode *node) {
    while (node->right != T->nil) node = node->right;
    return node;
}



void left_rotate(Tree *T, RBnode *x) {
    RBnode *y = x->right;
    x->right = y->left;

    if (y->left != T->nil)
        y->left->p = x;

    y->p = x->p;

    if (x->p == T->nil)
        T->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else 
        x->p->right = y;

    y->left = x;
    x->p = y;
}

void right_rotate(Tree *T, RBnode *x) {
    RBnode *y = x->left;
    x->left = y->right;

    if (y->right != T->nil)
        y->right->p = x;

    y->p = x->p;

    if (x->p == T->nil)
        T->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else 
        x->p->right = y;

    y->right = x;
    x->p = y;
}

void insert_fixup(Tree *T, RBnode *z) {
    RBnode *y;
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z == z->p->right) {
                    z = z->p;
                    left_rotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(T, z->p->p);
            } 
        }
        else {
            y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z == z->p->left) {
                    z = z->p;
                    right_rotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(T, z->p->p);
            }
        }
    }
    T->root->color = BLACK;
}

void insert(Tree *T, RBnode *z) {
    RBnode *y = T->nil, *x = T->root;

    while (x != T->nil) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->p = y;
    if (y == T->nil) T->root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    z->left = z->right = T->nil;
    z->color = RED;

    insert_fixup(T, z);
}

void transplant(Tree *T, RBnode *u, RBnode *v) {
    if (u->p == T->nil) T->root = v;
    else if (u == u->p->left) u->p->left = v;
    else u->p->right = v;

    v->p = u->p;
}

void RBdelete_fixup(Tree *T, RBnode *x) {
    RBnode *w;
    while (x != T->root && x->color == BLACK) {
        if (x == x->p->left) {
            w = x->p->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(T, x->p);
                w = x->p->right;
            }
            else if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->p;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(T, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(T, x->p);
                x = T->root;
            }
        }
        else {
            w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(T, x->p);
                w = x->p->left;
            }
            else if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->p;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(T, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                right_rotate(T, x->p);
                x = T->root;
            }
        }
    }
}

void RBdelete(Tree *T, RBnode *z) {
    RBnode *y = z, *x;
    COLOR yColor = y->color;

    if (z->left == T->nil) {
        x = z->right;
        transplant(T, z, z->right);
    }
    else if (z->right == T->nil) {
        x = z->left;
        transplant(T, z, z->left);
    }
    else {
        y = tree_minimum(T, z->right);
        yColor = y->color;
        x = y->right;
        if (y->p == z) x->p = y;
        else {
            transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    if (yColor == BLACK) RBdelete_fixup(T, x);
}

int main(int argc, char const *argv[]) {
    Tree *T = init_Tree();

    srand(time(nullptr));

    for (int i = 0; i < 16; i++){
        insert(T, init_RBnode(5, true));
    }
    
    printTree(T, T->root, 0);
    // RBdelete(T, T->root);
    // printTree(T, T->root, 0);

    printf("min: %d, max: %d\n", tree_minimum(T, T->root)->key, tree_maximum(T, T->root)->key);
}