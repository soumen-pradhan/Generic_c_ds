#include "RBtree.h"

// Nodes

RBnode *RBnode_init(void *data, COLOR color) {
    RBnode *node = (RBnode *)malloc( sizeof(RBnode) );
    node->left = node->right = node->p = NULL;
    node->key = data;
    node->color = color;

    return node;
}

void RBnode_free(RBnode *node) {
    free(node->key);
    free(node);
}

// Tree

RBtree *RBtree_init(Comparator comp, Comparator equal) {
    RBtree *T = malloc( sizeof(RBtree) );
    T->nil = RBnode_init(NULL, BLACK);
    T->root = T->nil;

    T->comp = comp;
    T->equal = equal;

    return T;
}

void RB_subTree_free(RBtree *T, RBnode *node) {
    if (node == T->nil)
        return;

    if (node->left != T->nil) RB_subTree_free(T, node->left);
    if (node->right != T->nil) RB_subTree_free(T, node->right);
    RBnode_free(node);
}

void RBtree_free(RBtree *T) {
    RB_subTree_free(T, T->root);
    RBnode_free(T->nil);
    free(T);
}

// BST operations

RBnode *RBtree_search(RBtree *T, RBnode *node, void *val) {
    while (node != T->nil && T->equal(node->key, val)) {
        if (T->comp(val, node->key)) node = node->left;
        else node = node->right;
    }
    return node;
}

RBnode *RBtree_minimum(RBtree *T, RBnode *node) {
    while (node->left != T->nil) node = node->left;
    return node;
}

RBnode *RBtree_maximum(RBtree *T, RBnode *node) {
    while (node->right != T->nil) node = node->right;
    return node;
}

// Subroutines

void RBtree_left_rotate(RBtree *T, RBnode *x) {
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

void RBtree_right_rotate(RBtree *T, RBnode *x) {
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

void RBtree_transplant(RBtree *T, RBnode *u, RBnode *v) {
    if (u->p == T->nil) T->root = v;
    else if (u == u->p->left) u->p->left = v;
    else u->p->right = v;

    v->p = u->p;
}

// Insertion

void RBtree_insert_fixup(RBtree *T, RBnode *z) {
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
                    RBtree_left_rotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                RBtree_right_rotate(T, z->p->p);
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
                    RBtree_right_rotate(T, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                RBtree_left_rotate(T, z->p->p);
            }
        }
    }
    T->root->color = BLACK;
}

void RBtree_insert_(RBtree *T, RBnode *z) {
    RBnode *y = T->nil, *x = T->root;

    while (x != T->nil) {
        y = x;
        if (T->comp(z->key, x->key)) x = x->left;
        else x = x->right;
    }

    z->p = y;
    if (y == T->nil) T->root = z;
    else if (T->comp(z->key, y->key)) y->left = z;
    else y->right = z;

    z->left = z->right = T->nil;
    z->color = RED;

    RBtree_insert_fixup(T, z);
}

// Deletion

void RBtree_delete_fixup(RBtree *T, RBnode *x) {
    RBnode *w;
    while (x != T->root && x->color == BLACK) {
        if (x == x->p->left) {
            w = x->p->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                RBtree_left_rotate(T, x->p);
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
                    RBtree_right_rotate(T, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                RBtree_left_rotate(T, x->p);
                x = T->root;
            }
        }
        else {
            w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                RBtree_right_rotate(T, x->p);
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
                    RBtree_left_rotate(T, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                RBtree_right_rotate(T, x->p);
                x = T->root;
            }
        }
    }
}

void RBtree_delete(RBtree *T, RBnode *z) {
    RBnode *y = z, *x;
    COLOR yColor = y->color;

    if (z->left == T->nil) {
        x = z->right;
        RBtree_transplant(T, z, z->right);
    }
    else if (z->right == T->nil) {
        x = z->left;
        RBtree_transplant(T, z, z->left);
    }
    else {
        y = RBtree_minimum(T, z->right);
        yColor = y->color;
        x = y->right;
        if (y->p == z) x->p = y;
        else {
            RBtree_transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        RBtree_transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    if (yColor == BLACK) RBtree_delete_fixup(T, x);
    RBnode_free(z);
}
