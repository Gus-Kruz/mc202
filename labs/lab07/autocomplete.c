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
    node* vec_node;
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
    N->vec_node = malloc(N->cap * sizeof(node));

    return N;
}

void resize_N(din_vec_node* N) {
    N->cap *= N->factor;
    din_vec_node* RN = realloc(N, N->cap);
    N = RN;
}

void free_N(din_vec_node* N) {
    free(N->vec_node);
    free(N);
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

void insert_word(node* root, node* new_node) {
    if (root == NULL) {
        root = new_node;
    } else {
    long long cmp = strcmp(root->word, new_node->word);
        if (cmp > 0){
            insert_word(root->right, new_node);
        } else if (cmp == 0) {
            root->f = new_node->f;
        } else if (cmp < 0) {
            insert_word(root->left, new_node);
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

void autocomplete(node* root, din_vec_node* N, char* prefix, long long size_prefix, long long k) {
    if (root == NULL) {
        return;
    }

    long long cmp = strncmp(root->word, prefix, size_prefix);

    if (cmp == 0) {
        if(N->size == N->cap) {
            resize_N(N);
        }
        N->vec_node[N->size++] = *root;
    }
    if (cmp < 0) {
        autocomplete(root->right, N, prefix, size_prefix, k);
    }
    else if (cmp > 0) {
        autocomplete(root->left, N, prefix, size_prefix, k);
    } 
}

void delete_word(node* root, char* word) {

}

void print_tree(node* root) {

}

void free_tree(node* root) {

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

            insert_word(root, new_node);
        }

        else if (strcmp(command, "SEARCH")) {
            din_word* W = alloc_W();

            read_word(W);

            char* word = malloc(W->size * sizeof(char));
            strcpy(word, W->word);

            free(W);

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

            autocomplete(root, N, prefix, size_prefix, k);
        }

        else if (strcmp(command, "DELETE")) {
            din_word* W = alloc_W();

            read_word(W);

            char* word = malloc(W->size * sizeof(char));
            strcpy(word, W->word);

            free(W);

            delete_word(root, word);
        }
        else if (strcmp(command, "PRINT") == 0) {
            print_tree(root);
        }
        else if (strcmp(command, "EXIT")) {
            free_tree(root);
            exit(EXIT_SUCCESS);
        }
    }
}