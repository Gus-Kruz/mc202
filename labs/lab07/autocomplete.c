#include <ctype.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

typedef struct node {
    char* word;
    long long f;
    struct node* left;
    struct node* right;
} node;

typedef struct din_word {
    char* word;
    long long size;
    long long cap;
    int factor;
} din_word;

typedef struct din_vec_node {
    node** vec_node;
    long long size;
    long long cap;
    int factor;
} din_vec_node;

din_word* alloc_W(){
    din_word* W = malloc(sizeof(din_word));
    W->size = 0;
    W->cap = 128;
    W->factor = 2;
    W->word = malloc(W->cap * sizeof(char));

    return W;
}

void resize_W(din_word* W) {
    W->cap *= W->factor;
    din_word* RW = realloc(W, W->cap);
    W = RW;
}

void free_W(din_word* W) {
    free(W->word);
    free(W);
}

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
    node** r_vec_node = realloc(N->vec_node, N->cap);
    N->vec_node = r_vec_node;
}

void free_N(din_vec_node* N) {
    free(N->vec_node);
    free(N);
}

int compare_vec_node(const void* n1, const void* n2) {
    int x = ((node*) n1)->f;
    int y = ((node*) n2)->f;

    char* w1 = ((node*) n1)->word;
    char* w2 = ((node*) n2)->word;
    if (x > y) {
        return 1;
    }
    else if (x == y) {
        if (strcmp(w1, w2) > 0) {
            return 1;
        }
        else {
            return -1;
        }
    }
    else {
        return -1;
    }
}

node* alloc_node() {
    node* new_node = malloc(sizeof(node));
    new_node->f = 0;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void read_word(din_word* W) {
    char curr_char;

    scanf(" %c", &curr_char);
    W->word[W->size++] = curr_char;
    
    while ((curr_char = getchar()) != EOF) {
        if (isspace(curr_char) || curr_char == '\n' || curr_char == '\0' ) {
            break;
        }
        if (W->size == W->cap) {
            resize_W(W);
        }
        W->word[W->size++] = curr_char;
    }
    W->word[W->size++] = '\0';
}

void insert_word2(node** p_root, node* new_node) {
    if (*p_root == NULL) {
        *p_root = new_node;
    }
    else {
        long long cmp = strcmp((*p_root)->word, new_node->word);
        if (cmp > 0) {
            insert_word2(&((*p_root)->left), new_node);
        }
        else if (cmp == 0) {
            (*p_root)->f = new_node->f;
            free(new_node);
        }
        else if (cmp < 0) {
            insert_word2(&((*p_root)->left), new_node);
        }
    }
}

node* search_word(node* root, char* word) {
    if (root == NULL) {
        return NULL;
    }
    long long cmp = strcmp(root->word, word);
    if (cmp > 0) {
        return search_word(root->right, word);
    }
    else if (cmp < 0) {
        return search_word(root->left, word);
    }
    else {
        return root;
    }
}

void autocomplete(node* root, din_vec_node* N, char* prefix, long long size_prefix) {
    if (root == NULL) {
        return;
    }

    long long cmp = strncmp(root->word, prefix, size_prefix);

    if (cmp == 0) {
        if(N->size == N->cap) {
            resize_N(N);
        }
        N->vec_node[N->size++] = root;
        autocomplete(root->right, N, prefix, size_prefix);
        autocomplete(root->left, N, prefix, size_prefix);
    }
    else if (cmp < 0) {
        autocomplete(root->right, N, prefix, size_prefix);
    }
    else {
        autocomplete(root->left, N, prefix, size_prefix);
    } 
}

node* get_small_succ(node* root) {
    
    node* curr = root->right;

    while (curr->left != NULL) {
        curr = curr->left;
    }

    return curr;
}

void delete_word2(node** p_root, char* word) {
    if (*p_root == NULL) {
        return;
    }

    long long cmp = strcmp((*p_root)->word, word);

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
        (*p_root)->word = succ->word;
        (*p_root)->f = succ->f;

        delete_word2(&((*p_root)->right), succ->word);
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

int main() {
    char command[13];
    long long f;
    long long k;

    node* root = NULL;

    while (scanf(" %s", command) == 1) {
        if (strcmp(command, "INSERT") == 0) {
            din_word* W = alloc_W();
            node* new_node = alloc_node();

            read_word(W);

            new_node->word = malloc(W->size* sizeof(char));
            strcpy(new_node->word, W->word);

            free_W(W);

            scanf(" %lld", &f);
            new_node->f = f;

            insert_word2(&root, new_node);
        }

        else if (strcmp(command, "SEARCH") == 0) {
            din_word* W = alloc_W();

            read_word(W);

            char* word = malloc(W->size * sizeof(char));
            strcpy(word, W->word);

            free_W(W);

            node* found_node = search_word(root, word);

            free(word);

            if (found_node == NULL) {
                printf("%s not found.\n", word);
            } else {
                printf("%s %lld\n", word, found_node->f);
            }
        }

        else if (strcmp(command, "AUTOCOMPLETE") == 0) {
            din_word* W = alloc_W();
            
            read_word(W);

            char* prefix = malloc(W->size * sizeof(char));
            strcpy(prefix, W->word);

            long long size_prefix = W->size - 1;

            free_W(W);
            
            din_vec_node* N = alloc_N();

            scanf(" %lld", &k);

            autocomplete(root, N, prefix, size_prefix);

            qsort(N->vec_node, N->size, sizeof(node), compare_vec_node);

            if (N->size == 0) {
                printf("nothing for %s.", prefix);
            }
            else {
                for (int i = 0; i < k && i < N->size; i++) {
                    printf("(%s,%lld) ", N->vec_node[i]->word, (N->vec_node[i]->f));
                }
            }
            printf("\n");

            free_N(N);
            free(prefix);
        }

        else if (strcmp(command, "DELETE") == 0) {
            din_word* W = alloc_W();

            read_word(W);

            char* word = malloc(W->size * sizeof(char));
            strcpy(word, W->word);

            free_W(W);

            delete_word2(&root, word);

            free(word);
        }
        else if (strcmp(command, "PRINT") == 0) {
            din_vec_node* N = alloc_N();

            tree_to_vec(root, N);

            qsort(N->vec_node, N->size, sizeof(node*), compare_vec_node);

            if (N->size == 0) {
                printf("the dictionary is empty");
            }
            else {
                for (int i = 0; i < N->size; i++) {
                    printf("%s ", N->vec_node[i]->word);
                }
            }

            printf("\n");

            free_N(N);
        }
        else if (strcmp(command, "EXIT") == 0) {
            din_vec_node* N = alloc_N();

            tree_to_vec(root, N);

            for (int i = 0; i < N->size; i++) {
                free(N->vec_node[i]);
            }

            free_N(N);
            return 0;
        }
    }
}