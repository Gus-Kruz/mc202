#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlib.h"

Node* alloc_node(long id, const char* vis, const char* sts)
{
    Node* new_node = malloc(sizeof(Node));
    new_node->id = id;
    strcpy(new_node->vis, vis);
    strcpy(new_node->sts, sts);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;

    return new_node;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void update_height(Node* root)
{
    if (root != NULL)
    {
        int val = 1;

        if (root->left != NULL)
        {
            val = root->left->height + 1;
        }

        if (root->right != NULL)
        {
            val = max(val, root->right->height + 1);
        }

        root->height = val;
    }
}

void RRR(Node** root)
{
    Node* old_root = *root;
    Node* aux = old_root->right;

    old_root->right = aux->left;
    if (aux->left != NULL) 
        aux->left->parent = old_root;

    aux->left = old_root;
    aux->parent = old_root->parent;
    old_root->parent = aux;

    *root = aux;

    update_height(old_root);
    update_height(aux);
}

void LLR(Node** root)
{
    Node* old_root = *root;
    Node* aux = old_root->left;

    old_root->left = aux->right;
    if (aux->right != NULL) 
        aux->right->parent = old_root;

    aux->right = old_root;
    aux->parent = old_root->parent;
    old_root->parent = aux;

    *root = aux;

    update_height(old_root);
    update_height(aux);
}

void LRR(Node** root)
{
    RRR(&((*root)->left));
    LLR(root);
}

void RLR(Node** root)
{
    LLR(&((*root)->right));
    RRR(root);
}

void insert_node(Node** root, Node* new_node) 
{
    if (*root == NULL)
    {
        *root = new_node;
        return;
    }
    if (new_node->id == (*root)->id)
    {
        free(new_node);
        return;
    }

    int left_h = 0;
    int right_h = 0;

    if (new_node->id > (*root)->id)
    {
        insert_node(&((*root)->right), new_node);
        (*root)->right->parent = *root;

        if ((*root)->left != NULL)
        {
            left_h = ((*root)->left->height);
        }
        if ((*root)->right != NULL)
        {
            right_h = ((*root)->right->height);
        }
        if (abs(left_h - right_h) == 2)
        {
            if ((*root)->right != NULL && new_node->id < (*root)->right->id)
            {
                RLR(root);
            }
            else 
            {
                RRR(root);
            }
        }
    }

    else
    {
        insert_node(&((*root)->left), new_node);
        (*root)->left->parent = *root;

        if ((*root)->left != NULL)
        {
            left_h = ((*root)->left->height);
        }
        if ((*root)->right != NULL)
        {
            right_h = ((*root)->right->height);
        }
        if (abs(left_h - right_h) == 2)
        {
            if ((*root)->left != NULL && new_node->id < (*root)->left->id)
            {
                LLR(root);
            }
            else 
            {
                LRR(root);
            }
        }
    }

    update_height(*root);

}

Node* search_node(Node* root, long x)
{

    if (root == NULL)
    {
        return NULL;
    }

    if (root->id == x)
    {
        return root;
    }

    else if (x > root->id)
    {
        return search_node(root->right, x);
    }
    else
    {
        return search_node(root->left, x);
    }
}

void update_node(Node* root, long x, char nivel[], char sts[])
{
    Node* found_node = search_node(root, x);
    if (found_node == NULL)
    {
        return;
    }
    else
    {
        strcpy(found_node->vis, nivel);
        strcpy(found_node->sts, sts);
    }

}

void print_inorder(Node* root)
{
    if (root == NULL)
    {
        return;
    }

    print_inorder(root->left);
    printf("%ld ", root->id);
    print_inorder(root->right);
}

void store_n(Node* root, long cntr_files[])
{   
    if(root == NULL) {
        return;
    }

    if (strcmp(root->sts, "atualizado") == 0)
    {
        cntr_files[0]++;
    }
    else if (strcmp(root->sts, "desatualizado") == 0)
    {
        cntr_files[1]++;
    }
    else if (strcmp(root->sts, "obsoleto") == 0)
    {
        cntr_files[2]++;
    }

    store_n(root->left, cntr_files);
    store_n(root->right, cntr_files);

}

void free_tree(Node* root)
{
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}