#ifndef RBTREE_H
#define RBTREE_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum _COLOR { RED = 0, BLACK } COLOR;
// For generic types
typedef bool (*Comparator)(void *, void *);

// Nodes in the tree

typedef struct _RBnode {
    struct _RBnode *left, *right, *p;
    void *key;
    COLOR color;
} RBnode;

RBnode *RBnode_init(void *data, COLOR color);
void RBnode_free(RBnode *node);

// Structure of Tree

typedef struct RBtree {
    RBnode *root, *nil;
    Comparator comp, equal;
} RBtree;

RBtree *RBtree_init(Comparator comp, Comparator equal);
void RB_subTree_free(RBtree *T, RBnode *node);
void RBtree_free(RBtree *T);

// BST operations

RBnode *RBtree_search(RBtree *T, RBnode *node, void *val);
RBnode *RBtree_minimum(RBtree *T, RBnode *node);
RBnode *RBtree_maximum(RBtree *T, RBnode *node);

// Subroutines

void RBtree_left_rotate(RBtree *T, RBnode *x);
void RBtree_right_rotate(RBtree *T, RBnode *x);
void RBtree_transplant(RBtree *T, RBnode *u, RBnode *v);

// Insertion

void RBtree_insert_fixup(RBtree *T, RBnode *z);
void RBtree_insert_(RBtree *T, RBnode *z);

#define RBtree_insert(T, data)\
    do {\
        void *key = malloc( sizeof(data) );\
        memcpy(key, &data, sizeof(data));\
        RBtree_insert_(T, RBnode_init(key, RED));\
    } while (false)

// Deletion

void RBtree_delete_fixup(RBtree *T, RBnode *x);
void RBtree_delete(RBtree *T, RBnode *z);

#endif