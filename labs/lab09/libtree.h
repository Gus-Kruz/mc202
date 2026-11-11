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
    int tier;
    Index* indexes;
    struct Bnode** children;
    bool leaf;
} Bnode;

Bnode* alloc_bnode(int t, bool leaf);

Index* search_index(Bnode* root, int x);

void split_child(Bnode* parent, int pos);

void insert_index(Bnode** p_root, int tier, int x, long start, long end);

int calc_height(Bnode* root);

void print_target_level(Bnode* node, int target_level, int curr_level);

void print_in_level(Bnode* root);

void print_in_order(Bnode* root);

void free_postorder(Bnode* root);
