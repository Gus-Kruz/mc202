#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node // ok
{
    long id;
    long height;
    char vis[10];
    char sts[14];
    struct Node* parent;
    struct Node* left;
    struct Node* right;

} Node;

Node* alloc_node() // ok
{
    Node* new_node = malloc(sizeof(Node));
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;

    return new_node;
}

int max(int a, int b) { // ok
    return (a > b) ? a : b;
}

void update_height(Node* root) // ok
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

void RRR(Node** root) // ok
{
    Node* aux = (*root)->right;

    (*root)->right = aux->left;

    if (aux->left != NULL)
        aux->left->parent = (*root);

    aux->left = (*root);

    aux->parent = (*root)->parent;

    (*root)->parent = aux;

    if (aux->parent != NULL
        && (*root)->id < aux->parent->id) {
        aux->parent->left = aux;
    }
    else {
        if (aux->parent != NULL)
            aux->parent->right = aux;
    }

    *root = aux; // supostamente funcional

    update_height((*root)->left);
    update_height((*root)->right);
    update_height(*root);
    update_height((*root)->parent);
}

void LLR(Node** root) // ok
{
    Node* aux = (*root)->left;

    (*root)->left = aux->right;

    if (aux->right != NULL)
    {
        aux->right->parent = *root;
    }

    aux->right = *root;
    
    aux->parent = (*root)->parent;

    (*root)->parent = aux;

    if (aux->parent != NULL && (*root)->id < aux->parent->id)
    {
        aux->parent->left = aux;
    }
    else
    {
        if (aux->parent != NULL) {
            aux->parent->right = aux;
        }
    }

    *root = aux; // supostamente funcional

    update_height((*root)->left);
    update_height((*root)->right);
    update_height(*root);
    update_height((*root)->parent);
}

void LRR(Node** root) // ok
{
    RRR(&((*root)->left));
    LLR(&((*root)->parent));
}

void RLR(Node** root) // ok
{
    LLR(&((*root)->right));
    RRR(&((*root)->parent));
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
        return;
    }

    int left_h = 0;
    int right_h = 0;

    if (new_node->id > (*root)->id)
    {
        insert_node(&((*root)->right), new_node);

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

        if ((*root)->right != NULL)
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

void store_n(Node* root, long* n_upd, long* n_out, long* n_obs)
{   
    if(root == NULL) {
        return;
    }

    if (strcmp(root->sts, "atualizado") == 0)
    {
        (*n_upd)++;
    }
    else if (strcmp(root->sts, "desatualizado") == 0)
    {
        (*n_out)++;
    }
    else if (strcmp(root->sts, "obsoleto") == 0)
    {
        (*n_obs)++;
    }

    store_n(root->left, n_upd, n_out, n_obs);
    store_n(root->right, n_upd, n_out, n_obs);

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

int main()
{
    char comando;
    Node* root = NULL;

    long x;
    char nivel[10];
    char sts[14];

    long n_upd = 0;
    long n_out = 0;
    long n_obs = 0;
    Node* new_node;

    while (scanf(" %c", &comando) == 1)
    {
        switch (comando)
        {
            case 'i':
                new_node = alloc_node();  
                scanf(" %ld %s %s", &(new_node->id), new_node->vis, new_node->sts);
                
                insert_node(&root, new_node);

                break;
            case 'a':
                scanf(" %ld %s %s", &x, nivel, sts);
                update_node(root, x, nivel, sts);

                break;
            case 'b':
                scanf(" %ld", &x);
                Node* found_node = search_node(root, x);
                if (found_node == NULL) {
                    printf("%ld nao existe\n", x);
                }
                else
                {
                    printf("%ld, %s, %s\n", x, found_node->vis, found_node->sts);
                }

                break;
            case 'l':
                if (root == NULL)
                {
                    printf("indice vazio\n");
                }
                else
                {
                    printf("documentos: ");
                    print_inorder(root);
                    printf("\n");
                }

                break;
            case 't':
                n_upd = 0;
                n_out = 0;
                n_obs = 0;

                store_n(root, &n_upd, &n_out, &n_obs);
                printf("atualizado: %ld, desatualizado: %ld, obsoleto: %ld", n_upd, n_out, n_obs);

                break;
            case 'f':
                free_tree(root);

                return 0;
        }
    }
}