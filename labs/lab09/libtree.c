#include "libtree.h"

Bnode* alloc_bnode(int t, bool leaf)
{
    Bnode* new_node = (Bnode*) malloc(sizeof(Bnode));

    new_node->n = 0;
    new_node->indexes = (Index*) malloc(t*sizeof(Index));
    new_node->children = (Bnode**) malloc((t+1)*sizeof(Bnode*));
    new_node->leaf = leaf;
    
    for (int i = 0; i<=t; i++)
    {
        new_node->children[i] = NULL;
    }
}

void split_child(Bnode* parent, int pos, int t)
{
    Bnode* child = parent->children[pos];
    Bnode* new_node = alloc_bnode(t, child->leaf);

    new_node->n = t/2\;

    for (int i = 0; i < t/2; i++)
    {
        new_node->indexes[i] = child->indexes[i + t/2 + 1];
    }

    if (!child->leaf)
    {
        for (int i = 0; i < t/2; i++)
        {
            new_node->children[i] = child->children[i + t/2];
        }
    }

    child->n = t/2;

    for (int i = parent->n; i > pos; i--) // abrir espaço para o novo apontador filho
    {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[pos+1] = new_node;

    for (int i = parent->n - 1; i >= pos; i--)
    {
        parent->indexes[i+1] = parent->indexes[i];
    }

    parent->indexes[pos] = child->indexes[t/2 -1];
    parent->n++;
}