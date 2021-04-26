#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG(x) printf("%s = %d\n", #x, x);

void MEM(void *p, size_t type) {
    char *mem = (char *)p;
    for (int i = 0; i < type; i++)
        printf("%02hhX ", mem[i]);
    putchar('\n');
}

typedef struct _Node {
    unsigned char i, j;
} Node;

typedef struct _Qu {
    Node *nds;
    size_t fr, sz, cap;
} Qu;

Qu *qu_init() {
    Qu *q = malloc(sizeof(Qu));
    q->nds = malloc(sizeof(Node) * 8);
    q->fr = q->sz = 0;
    q->cap = 8;

    memset(q->nds, 0x00, sizeof(Node) * 8);
    
    return q;
}

void qu_free(Qu *q) {
    free(q->nds);
    free(q);
}

void qu_resz(Qu *q, size_t maxEl) {
    Node *__tmp = realloc(q->nds, sizeof(Node) * maxEl);
    if (__tmp != NULL)
        q->nds = __tmp;
    else {
       qu_free(q);
       puts ("Error (re)allocating memory");
       exit (1);
     }

    q->cap = maxEl;
    memset(q->nds + q->fr + q->sz, 
           0x00,
           sizeof(Node) * (q->cap - (q->fr + q->sz)));
}

void qu_push(Qu *q, Node data) {
    if (q->fr + q->sz >= q->cap)
        qu_resz(q, q->cap * 2);
        
    q->nds[q->fr + q->sz++] = data;
}

Node qu_pop(Qu *q) {
    Node r = {-1, -1};
    if (q->sz == 0)
        return r;
    
    r = q->nds[q->fr++];
    q->sz--;

    // if (q->fr - 1 >= q->cap / 2) {
    //     memmove(q->nds, &(q->nds[q->fr]), sizeof(Node) * q->sz);
    //     q->nds = realloc(q->nds, q->cap / 2);
    //     q->fr = 0;
    // }
    
    return r;
}

const static size_t move = 8;
const static Node moves[8] = {
    {-1, -1},
    {-1,  1},
    {-1,  0},
    { 0, -1},
    { 1, -1},
    { 0,  1},
    { 1,  0},
    { 1,  1}
};

bool isSafe(int rows,
            int mat[rows][rows],
            bool proc[rows][rows],
            Node pos)
{
    return (
        (pos.i >= 0) && (pos.i < rows) &&
        (pos.j >= 0) && (pos.j < rows) &&
        (mat[pos.i][pos.j]) && 
        (proc[pos.i][pos.j] == false)
    );
}

void bfs(int rows,
         int mat[rows][rows],
         bool proc[rows][rows],
         Node pos)
{
    static int turn = 1;
    Qu *qu = qu_init();
    qu_push(qu, pos);

    proc[pos.i][pos.j] = true;
    mat[pos.i][pos.j] = turn;

    while (qu->sz != 0) {
        Node front = qu_pop(qu);
        
        for (int k = 0; k < move; k++) {
            Node neigh = { front.i + moves[k].i, front.j + moves[k].j };
            if (isSafe(rows, mat, proc, neigh)) {
                proc[neigh.i][neigh.j] = true;
                mat[neigh.i][neigh.j] = turn;
                qu_push(qu, neigh);
            }
        }
    }
    qu_free(qu);
    turn++;
}

int main(int argc, char const *argv[])
{
    int rows = 10, temp;
    scanf("%d", &rows);

    int mat[rows][rows];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    // int mat[10][10] =
    // {
    //     { 1, 0, 1, 0, 0, 0, 1, 1, 1, 1 },
    //     { 0, 0, 1, 0, 1, 0, 1, 0, 0, 0 },
    //     { 1, 1, 1, 1, 0, 0, 1, 0, 0, 0 },
    //     { 1, 0, 0, 1, 0, 1, 0, 0, 0, 0 },
    //     { 1, 1, 1, 1, 0, 0, 0, 1, 1, 1 },
    //     { 0, 1, 0, 1, 0, 0, 1, 1, 1, 1 },
    //     { 0, 0, 0, 0, 0, 1, 1, 1, 0, 0 },
    //     { 0, 0, 0, 1, 0, 0, 1, 1, 1, 0 },
    //     { 1, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
    //     { 1, 1, 1, 1, 0, 0, 0, 1, 1, 1 }
    // };

    bool proc[rows][rows];
    memset(proc, 0x00, sizeof(proc));

    int island = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (mat[i][j] && proc[i][j] == 0) {
                bfs(10, mat, proc, (Node){i, j});
                island++;
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (mat[i][j] != 0)
                printf("%d ", mat[i][j]);
            else 
                printf("  ");
        }
        putchar('\n');
    }

    printf("islands = %d\n", island);
}



// IMPORTANT
// ALWAYS check resizing condition. I only used size (and not front + size)
// Lost me 3 hours

// Also queue just grows and never shrinks