#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char word[30];
    long f;
    struct node* left;
    struct node* right;
} node;

typedef struct din_vec_node {
    node** vec_node;
    long size;
    long  cap;
    int factor;
} din_vec_node;

din_vec_node* alloc_N() {
    din_vec_node* N = malloc(sizeof(din_vec_node));
    N->size = 0;
    N->cap = 64;
    N->factor = 2;
    N->vec_node = malloc(N->cap * sizeof(node*));

    return N;
}

void resize_N(din_vec_node* N) {
    N->cap *= N->factor;
    node** r_vec_node = realloc(N->vec_node, N->cap * sizeof(node*));
    N->vec_node = r_vec_node;
}

void free_N(din_vec_node* N) {
    free(N->vec_node);
    free(N);
}

int compare_f(const void* n1, const void* n2) {
    node* x = *((node**) n1);
    node* y = *((node**) n2);

    int cmp = strcmp(x->word, y->word);

    if (x->f < y->f) {
        return 1;
    }
    else if (x->f > y->f) {
        return -1;
    }
    else {
        return cmp;
    }
}

int compare_l(const void* n1, const void* n2) {
    node* x = *((node**) n1);
    node* y = *((node**) n2);

    int cmp = strcmp(x->word, y->word);

    return cmp;
}

node* alloc_node() {
    node* new_node = malloc(sizeof(node));
    new_node->f = 0;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void insert_word2(node** p_root, node* new_node) {
    if (*p_root == NULL) {
        *p_root = new_node;
        return;
    }
    else {
        int cmp = strcmp((*p_root)->word, new_node->word);
        if (cmp == 0) {
            (*p_root)->f = new_node->f;
            free(new_node);
            return;
        }
        else if (cmp > 0) {
            insert_word2(&((*p_root)->left), new_node);
        }
        else {
            insert_word2(&((*p_root)->right), new_node);
        }
    }
}

node* search_word(node* root, char* word) {
    if (root == NULL) {
        return NULL;
    }
    int cmp = strcmp(root->word, word);
    if (cmp > 0) {
        return search_word(root->left, word);
    }
    else if (cmp < 0) {
        return search_word(root->right, word);
    }
    else {
        return root;
    }
}

void tree_to_vec(node* root, din_vec_node* N) {
    if (root == NULL) {
        return;
    }
    if (root->left != NULL) {
        tree_to_vec(root->left, N);
    }
    if (root->right != NULL) {
        tree_to_vec(root->right, N);
    }
    if(N->size == N->cap) {
            resize_N(N);
        }
    N->vec_node[N->size++] = root;
    
}

void autocomplete(node* root, din_vec_node* N, char prefix[], int size_prefix) {
    if (root == NULL) {
        return;
    }

    int cmp = strncmp(root->word, prefix, size_prefix);
    if (cmp == 0) {
        if(N->size == N->cap) {
            resize_N(N);
        }
        N->vec_node[N->size++] = root;
        autocomplete(root->right, N, prefix, size_prefix);
        autocomplete(root->left, N, prefix, size_prefix);
    }
    else if (cmp > 0) {
        autocomplete(root->left, N, prefix, size_prefix);
    }
    else {
        autocomplete(root->right, N, prefix, size_prefix);
    } 
}

void print_in_order(node* root) {
    if (root != NULL) {
        print_in_order(root->left);
        printf("%s ",root->word);
        print_in_order(root->right);
    }
}

node* get_small_succ(node* root) {
    
    node* curr = root->right;

    while (curr->left != NULL) {
        curr = curr->left;
    }

    return curr;
}

void delete_word2(node** p_root, char word[]) {
    if (*p_root == NULL) {
        return;
    }

    int cmp = strcmp((*p_root)->word, word);

    if (cmp > 0) {
        delete_word2(&((*p_root)->left), word);
    }
    else if (cmp < 0) {
        delete_word2(&((*p_root)->right), word);
    }
    else {
        // caso 1: nó tem no máximo um filho
        if ((*p_root)->left == NULL) {
            node* aux = (*p_root);
            *p_root = (*p_root)->right;
            free(aux);
            return;
        }

        if ((*p_root)->right == NULL) {
            node* aux = (*p_root);
            (*p_root) = (*p_root)->left;
            free(aux);
            return;
        }
        // caso 2: nó tem 2 filhos, troco as informações do root com o sucessor e apago o sucessor
        node* succ = get_small_succ((*p_root));
        strcpy((*p_root)->word, succ->word);
        (*p_root)->f = succ->f;

        delete_word2(&((*p_root)->right), succ->word);
    }
}

void free_post_order(node* root) {
    if (root != NULL) {
        free_post_order(root->left);
        free_post_order(root->right);
        free(root);
    }
}

int main() {
    char command[13];
    long f;
    long k;

    din_vec_node* N = alloc_N();

    node* root = NULL;

    while (scanf(" %s", command) == 1) {
        if (strcmp(command, "INSERT") == 0) {
            node* new_node = alloc_node();

            scanf(" %s", new_node->word);

            scanf(" %ld", &f);
            new_node->f = f;

            insert_word2(&root, new_node);
        }

        else if (strcmp(command, "SEARCH") == 0) {
            char word[30];
            scanf(" %s", word);

            node* found_node = search_word(root, word);

            if (found_node == NULL) {
                printf("%s not found.\n", word);
            } else {
                printf("%s %ld\n", word, found_node->f);
            }
        }

        else if (strcmp(command, "AUTOCOMPLETE") == 0) {
            char prefix[30];
            scanf(" %s", prefix);

            int size_prefix = strlen(prefix);

            scanf(" %ld", &k);

            autocomplete(root , N, prefix, size_prefix);

            qsort(N->vec_node, N->size, sizeof(node*), compare_f);

            if (N->size == 0) {
                printf("nothing for %s.", prefix);
            }
            else {
                for (int i = 0; i < k && i < N->size; i++) {
                    printf("(%s,%ld) ", N->vec_node[i]->word, (N->vec_node[i]->f));
                }
            }
            printf("\n");

            N->size = 0;
        }

        else if (strcmp(command, "DELETE") == 0) {
            char word[30];
            scanf(" %s", word);

            delete_word2(&root, word);

        }
        else if (strcmp(command, "PRINT") == 0) {

            if (root == NULL) {
                printf("the dictionary is empty.");
            }
            else {
                print_in_order(root);
            }

            printf("\n");
        }
        else if (strcmp(command, "EXIT") == 0) {

            free_post_order(root);
            free_N(N);
        }
    }
}