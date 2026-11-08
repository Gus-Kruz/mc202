#include "libtree.h"

Bnode* alloc_bnode(int t, bool leaf)
{
    Bnode* new_node = (Bnode*) malloc(sizeof(Bnode));

    new_node->n = 0;
    new_node->indexes = (Index*) malloc((2 * t - 1)*sizeof(Index));
    new_node->children = (Bnode**) malloc((2 * t)*sizeof(Bnode*));
    new_node->leaf = leaf;
    
    for (int i = 0; i < 2 * t; i++)
    {
        new_node->children[i] = NULL;
    }
}

Index* search_index(Bnode* root, int x)
{
    for (int i = 0; i < root->n; i++)
    {
        if (root->indexes[i].key >= x) {
            if (x == root->indexes[i].key)
            {
                return &(root->indexes[i]);
            }

            if (root->leaf) {
                return NULL;
            }

            search_index(root->children[i], x);
        }

        else if (root->leaf) {
                return NULL;
            }
    }
}

void split_child(Bnode* parent, int pos, int t)
{
    Bnode* child = parent->children[pos];
    Bnode* new_node = alloc_bnode(t, child->leaf);

    bool paridade;

    if (t % 2 == 0)
    {
        paridade = true;
    }

    else
    {
        paridade = false;
    }

    new_node->n = (t+1)/2 - 1;

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