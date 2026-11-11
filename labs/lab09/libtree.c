#include <stdio.h>
#include <stdlib.h>
#include "libtree.h"

Bnode* alloc_bnode(int t, bool leaf)
{
    Bnode* new_node = (Bnode*) malloc(sizeof(Bnode));
    if (new_node == NULL)
    {
        return NULL;
    }

    new_node->n = 0;
    new_node->tier = t;
    new_node->indexes = (Index*) malloc((2 * t - 1) * sizeof(Index));
    new_node->children = (Bnode**) malloc((2 * t) * sizeof(Bnode*));
    new_node->leaf = leaf;

    for (int i = 0; i < 2 * t; i++)
    {
        new_node->children[i] = NULL;
    }
    return new_node;
}

Index* search_index(Bnode* root, int x)
{
    if (root == NULL || root->n == 0)
    {
        return NULL;
    }

    int i = 0;
    while (i < root->n && x > root->indexes[i].key)
    {
        i++;
    }

    if (i < root->n && x == root->indexes[i].key)
    {
        return &(root->indexes[i]);
    }

    if (root->leaf)
    {
        return NULL;
    }

    return search_index(root->children[i], x);
}

void split_child(Bnode* parent, int pos)
{
    int t = parent->tier;
    Bnode* child = parent->children[pos];
    Bnode* new_node = alloc_bnode(t, child->leaf);

    new_node->n = t - 1;

    for (int j = 0; j < t - 1; j++)
    {
        new_node->indexes[j] = child->indexes[j + t];
    }

    if (!child->leaf)
    {
        for (int j = 0; j < t; j++)
        {
            new_node->children[j] = child->children[j + t];
            child->children[j + t] = NULL;
        }
    }

    child->n = t - 1;

    for (int j = parent->n; j >= pos + 1; j--)
    {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[pos + 1] = new_node;

    for (int j = parent->n - 1; j >= pos; j--)
    {
        parent->indexes[j + 1] = parent->indexes[j];
    }
    parent->indexes[pos] = child->indexes[t - 1];

    parent->n++;
}

static void insert_non_full(Bnode* node, Index new_index)
{
    int i = node->n - 1;

    if (node->leaf)
    {
        while (i >= 0 && node->indexes[i].key > new_index.key)
        {
            node->indexes[i + 1] = node->indexes[i];
            i--;
        }
        node->indexes[i + 1] = new_index;
        node->n++;
    }
    else
    {
        while (i >= 0 && node->indexes[i].key > new_index.key)
        {
            i--;
        }
        i++;

        if (node->children[i]->n == 2 * node->tier - 1)
        {
            split_child(node, i);

            if (new_index.key > node->indexes[i].key)
            {
                i++;
            }
        }
        insert_non_full(node->children[i], new_index);
    }
}

void insert_index(Bnode** p_root, int tier, int x, long start, long end)
{

    if (*p_root != NULL && search_index(*p_root, x) != NULL)
    {
        return;
    }

    Index new_index;
    new_index.key = x;
    new_index.start = start;
    new_index.end = end;

    if (*p_root == NULL)
    {
        *p_root = alloc_bnode(tier, true);
        (*p_root)->indexes[0] = new_index;
        (*p_root)->n = 1;
        return;
    }

    if ((*p_root)->n == 0)
    {
        (*p_root)->indexes[0] = new_index;
        (*p_root)->n = 1;
        return;
    }

    if ((*p_root)->n == 2 * (*p_root)->tier - 1)
    {
        Bnode* new_root = alloc_bnode((*p_root)->tier, false);
        new_root->children[0] = *p_root;
        split_child(new_root, 0);
        *p_root = new_root;
    }

    insert_non_full(*p_root, new_index);
}

int calc_height(Bnode* root)
{
    if (root == NULL || root->n == 0)
    {
        return 0;
    }

    int height = 1;
    Bnode* curr = root;

    while (!curr->leaf)
    {
        curr = curr->children[0];
        height++;
    }

    return height;
}

void print_target_level(Bnode* node, int target_level, int curr_level)
{
    if (node == NULL || node->n == 0)
    {
        return;
    }

    if (curr_level == target_level)
    {
        printf("[");
        for (int i = 0; i < node->n; i++)
        {
            printf("%d", node->indexes[i].key);
            if (i < node->n - 1)
            {
                printf(",");
            }
        }
        printf("] ");
    }
    else if (!node->leaf)
    {
        for (int i = 0; i <= node->n; i++)
        {
            print_target_level(node->children[i], target_level, curr_level + 1);
        }
    }
}

void print_in_level(Bnode* root)
{
    if (root == NULL || root->n == 0)
    {
        printf("A arvore esta vazia.\n");
        return;
    }

    int height = calc_height(root);

    for (int i = 0; i < height; i++)
    {
        printf("nivel %d: ", i);
        print_target_level(root, i, 0);
        printf("\n");
    }
}

static void print_in_order_rec(Bnode* node)
{
    if (node == NULL || node->n == 0)
    {
        return;
    }

    int i;
    for (i = 0; i < node->n; i++)
    {
        if (!node->leaf)
        {
            print_in_order_rec(node->children[i]);
        }
        printf("%d ", node->indexes[i].key);
    }
    if (!node->leaf)
    {
        print_in_order_rec(node->children[i]);
    }
}

void print_in_order(Bnode* root)
{
    if (root == NULL || root->n == 0)
    {
        printf("A arvore esta vazia.\n");
        return;
    }

    print_in_order_rec(root);
    printf("\n");
}

void free_postorder(Bnode* root)
{
    if (root == NULL)
    {
        return;
    }

    if (!root->leaf)
    {
        for (int i = 0; i <= root->n; i++)
        {
            free_postorder(root->children[i]);
        }
    }

    free(root->indexes);
    free(root->children);
    free(root);
}
