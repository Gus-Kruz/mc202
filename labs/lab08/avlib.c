#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlib.h"

unsigned char vis_codigo(const char nome[])
{
    if (strcmp(nome, "restrito") == 0) return VIS_RESTRITO;
    if (strcmp(nome, "interno") == 0)  return VIS_INTERNO;
    if (strcmp(nome, "publico") == 0)  return VIS_PUBLICO;
    return VIS_BLOQUEADO;
}

const char* vis_nome(unsigned char vis)
{
    switch (vis)
    {
        case VIS_RESTRITO: return "restrito";
        case VIS_INTERNO:  return "interno";
        case VIS_PUBLICO:  return "publico";
        default:           return "bloqueado";
    }
}

unsigned char sts_codigo(const char nome[])
{
    if (strcmp(nome, "atualizado") == 0)    return EST_ATUALIZADO;
    if (strcmp(nome, "desatualizado") == 0) return EST_DESATUALIZADO;
    return EST_OBSOLETO;
}

const char* sts_nome(unsigned char sts)
{
    switch (sts)
    {
        case EST_ATUALIZADO:    return "atualizado";
        case EST_DESATUALIZADO: return "desatualizado";
        default:                return "obsoleto";
    }
}

Node* alloc_node(long id, unsigned char vis, unsigned char sts)
{
    Node* new_node = malloc(sizeof(Node));
    new_node->id = id;
    new_node->vis = vis;
    new_node->sts = sts;
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

    aux->left = old_root;

    *root = aux;

    update_height(old_root);
    update_height(aux);
}

void LLR(Node** root)
{
    Node* old_root = *root;
    Node* aux = old_root->left;

    old_root->left = aux->right;
    
    aux->right = old_root;

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

int calc_fb(Node* root) {
    int left_h = 0;
    int right_h = 0;

    if (root->left != NULL) {
        left_h = root->left->height;
    }

    if (root->right != NULL) {
        right_h = root->right->height;
    }

    return left_h - right_h;
}

void insert_node(Node** root, long id, unsigned char vis, unsigned char sts) 
{
    if (*root == NULL)
    {
        *root = alloc_node(id, vis, sts);
        return;
    }
    if (id == (*root)->id)
    {
        return;
    }

    if (id > (*root)->id)
    {
        insert_node(&((*root)->right), id, vis, sts);
    }

    else
    {
        insert_node(&((*root)->left), id, vis, sts);
    }

    update_height(*root);

    int fb = calc_fb(*root);

    if (fb == -2) 
    {
        int child_fb = calc_fb((*root)->right);

        if (child_fb <= 0)
        {
            RRR(root);
        }
        else
        {
            RLR(root);
        }
    }

    else if (fb == 2)
    {
        int child_fb = calc_fb((*root)->left);

        if (child_fb >= 0) {
            LLR(root);
        }
        else
        {
            LRR(root);
        }
    }

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

    if (x > root->id)
    {
        return search_node(root->right, x);
    }

    return search_node(root->left, x);
}

void update_node(Node* root, long x, unsigned char vis, unsigned char sts)
{
    Node* found_node = search_node(root, x);
    if (found_node == NULL)
    {
        return;
    }
    else
    {
        found_node->vis = vis;
        found_node->sts = sts;
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

void store_n(Node* root, int cntr_files[])
{   
    if(root == NULL) {
        return;
    }

    cntr_files[root->sts]++;

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