#include <stdlib.h>
#include <stdbool.h>

typedef struct Index {
    int key;
    long start;
    long end;
} Index;

typedef struct Bnode
{
    int n;
    Index* indexes;
    struct Bnode** children;
    bool leaf;
} Bnode;

Bnode* alloc_bnode(int t, bool leaf);

Bnode* search_index(Bnode* root, int x);

void split_child(Bnode* parent, int index, int t);