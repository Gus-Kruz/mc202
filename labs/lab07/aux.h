#ifndef AUX_H
#define AUX_H

typedef struct{
  char *data;
  int size; // Talvez mudar para long long
  int cap;
} charVec;

typedef struct node{
  char *palavra;
  int freq; // Talvez mudar para long long
  int fb; // Fator de balanceamento dos nós

  struct node *left;
  struct node *right;
} node;

// Stack dinâmica para armazenar caminho da busca
typedef struct{
  node **data;
  int pos;
  int cap;
} stack;

// Heap para range_query
typedef struct{
  node **data;
  int size;
  int cap;
} heap;
void free_heap(heap *h);

void free_stack(stack *s);
node *pop_stack(stack *s);

// Vetor dinâmico para receber palavra
charVec *init_charVec();
void free_charVec(charVec *vec);
int read_charVec(charVec *vec);

// Árvore AVL
void free_tree(node *n);
void inorder_print(node *n);

stack *find(node *root, char *palavra);
void insert_node(node **root, charVec *palavra, int freq);
heap *range_query(node *root, charVec *prefix, int k);
void delete_node(node **root, char *palavra);

#endif
