#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "aux.h"

// Vetor dinâmico para receber palavra
charVec *init_charVec(){
  charVec *vec = (charVec *)malloc(sizeof(charVec));
  vec->size = 0;
  vec->cap = 128; // Capacidade inicial para cada palavra

  char *data = (char *)malloc(vec->cap*sizeof(char));
  vec->data = data;

  return vec;
}

int bigger_charVec(charVec *vec){
  char *tmp = realloc(vec->data, 2*vec->cap*sizeof(char));
  if(!tmp) return 0;

  vec->data=tmp;
  vec->cap*=2;

  return 1;
}

int smaller_charVec(charVec *vec){
  if(vec->cap < 4) return 1;

  char *tmp = realloc(vec->data, vec->cap*sizeof(char)/2);
  if(!tmp) return 0;

  vec->data=tmp;
  vec->cap/=2;

  return 1;
}

int read_charVec(charVec *vec){
  scanf(" ");

  vec->size = 0;
  char c;
  while(1){
    if(scanf("%c", &c) == EOF){
      if(vec->size) break;
      else return 0;
    }

    if(c==' ' || c=='\n' || c=='\r' || c=='\t') break;
    if(vec->size == vec->cap && !bigger_charVec(vec))
      return 0;

    vec->data[vec->size++] = c;
  }
  if(vec->size == vec->cap) bigger_charVec(vec);
  vec->data[vec->size++] = '\0';

  if(vec->size<vec->cap/4) smaller_charVec(vec);

  return 1;
}

void free_charVec(charVec *vec){
  free(vec->data);
  free(vec);
}

// Funções para stack dinâmica
stack *init_stack(){
  stack *s = (stack *)malloc(sizeof(stack));
  s->pos = 0;
  s->cap = 5; // Capacidade inicial da pilha

  s->data = (node **)malloc(s->cap*sizeof(node *));

  return s;
}

int insert_stack(stack *s, node *n){
  if(s->pos==s->cap-1){
    s->cap*=2;
    node **tmp = realloc(s->data, s->cap*sizeof(node *));

    if(!tmp) return 0;
    s->data = tmp;
  }

  s->data[s->pos++] = n;
  return 1;
}

node *pop_stack(stack *s){
  if(s->pos<=0) return NULL;
  node *n = s->data[--s->pos];

  if(s->pos<s->cap/2 && s->cap > 5){
    s->cap/=2;
    node **tmp = realloc(s->data, s->cap*sizeof(node *));

    if(tmp) s->data = tmp;
  }

  return n;
}

void free_stack(stack *s){
  free(s->data);
  free(s);
}

// Funções para maxheap
heap *init_heap(int k){
  heap *h = (heap *)malloc(sizeof(heap));
  if(!h) return NULL;

  h->size = 0;
  h->cap = k;
  h->data = (node **)malloc(h->cap*sizeof(node *));

  return h;
}

void free_heap(heap *h){
  free(h->data);
  free(h);
}

// Retorna 1 caso n1 tenha preferência sobre n2
int cmp_node(node *n1, node *n2){
  if(n1->freq>n2->freq) return 1;
  else if(n1->freq==n2->freq){
    int cmp = strcmp(n1->palavra, n2->palavra); 
    if(cmp<0) return 1;
    else if(cmp>0) return -1;
    else return 0;
  }
  else return -1;
}

int cmp_node_q(const void *a, const void *b){
  node *n1 = *(node **)a;
  node *n2 = *(node **)b;

  if(n1->freq>n2->freq) return -1;
  else if(n1->freq==n2->freq){
    int cmp = strcmp(n1->palavra, n2->palavra); 
    if(cmp<0) return -1;
    else if(cmp>0) return 1;
    else return 0;
  }
  else return 1;
}

void insert_minheap(heap *h, node *n){
  if(h->size==h->cap){ // Insert at root and heapify down
    node *firstNode = h->data[0];
    if(cmp_node(n, firstNode) == 1) h->data[0] = n;
    else return;

    int parentPos = 0;
    int childPos1 = 1;
    int childPos2 = 2;

    node *tmp;
    while(1){
      if(childPos2>=h->size) childPos2 = childPos1;
      if(childPos1>=h->size) break;

      int smallerChild = cmp_node(h->data[childPos1], h->data[childPos2]) == 1 ? childPos2 : childPos1;

      if(cmp_node(h->data[parentPos], h->data[smallerChild]) == 1){
        tmp = h->data[smallerChild];
        h->data[smallerChild] = h->data[parentPos];
        h->data[parentPos] = tmp;

        parentPos = smallerChild;
      } else break;

      childPos1 = 2*parentPos+1;
      childPos2 = 2*parentPos+2;
    }
  }
  else{ // Insert at end and heapify up
    h->data[h->size++] = n;

    node *tmp;

    int childPos = h->size-1;
    int parentPos = (childPos-1)/2;
    while(cmp_node(h->data[childPos], h->data[parentPos]) == -1){
      tmp = h->data[childPos];
      h->data[childPos] = h->data[parentPos];
      h->data[parentPos] = tmp;

      childPos = parentPos;
      parentPos = (childPos-1)/2;
    }
  }
}

// Funções relacionadas à árvore AVL
void rotate_left(node **root, node *n, node *parent){
  node *right = n->right;
  n->right = right->left;
  right->left = n;

  if(parent == NULL) *root = right;
  else if(parent->left == n) parent->left = right;
  else parent->right = right;
}

void rotate_right(node **root, node *n, node *parent){
  node *left = n->left;
  n->left = left->right;
  left->right = n;

  if(parent == NULL) *root = left;
  else if(parent->left == n) parent->left = left;
  else parent->right = left;
}

// Retorna stack referente ao caminho de busca
stack *find(node *root, char *palavra){
  node *n = root;
  stack *s = init_stack();

  int cmp=1;
  while(n!=NULL && cmp != 0){
    insert_stack(s, n);

    cmp = strcmp(n->palavra, palavra);
    if(cmp>0) n=n->left;
    else if(cmp<0) n=n->right;
  }
  if(!n) insert_stack(s, n);

  return s;
}

void inorder_print(node *n){
  if(!n) return;

  inorder_print(n->left);
  printf("%s ", n->palavra);
  inorder_print(n->right);
}

bool rebalance(node **root, node *pn, node *n){
  bool decreased = true;

  if(n->fb>0){ // LEFT-something
    node *leftChild = n->left;
    if(leftChild->fb<0){ // LEFT-RIGHT
      node *gChild = leftChild->right;
      if(gChild->fb==1){
        leftChild->fb = 0;
        n->fb = -1;
      } else if(gChild->fb==-1){
        leftChild->fb = 1;
        n->fb = 0;
      } else{
        leftChild->fb = 0;
        n->fb = 0;
      }
      gChild->fb = 0;
      rotate_left(root, leftChild, n);
    } else if(leftChild->fb==0){ // +2/0
      n->fb = 1;
      leftChild->fb = -1;
      decreased = false;
    } else{ // LEFT-LEFT
      leftChild->fb = 0;
      n->fb = 0;
    }

    rotate_right(root, n, pn);
  }
  else if(n->fb<0){ // RIGHT-something
    node *rightChild = n->right;
    if(rightChild->fb>0){ // RIGHT-LEFT
      node *gChild = rightChild->left;
      if(gChild->fb==1){
        rightChild->fb = -1;
        n->fb = 0;
      } else if(gChild->fb==-1){
        rightChild->fb = 0;
        n->fb = 1;
      } else{
        rightChild->fb = 0;
        n->fb = 0;
      }
      gChild->fb = 0;
      rotate_right(root, rightChild, n);
    } else if(rightChild->fb==0){ // -2/0
      n->fb = -1;
      rightChild->fb = 1;
      decreased = false;
    } else{ // RIGHT-RIGHT
      rightChild->fb = 0;
      n->fb = 0;
    }

    rotate_left(root, n, pn);
  }

  return decreased;
}

void insert_node(node **root, charVec *palavra, int freq){
  stack *s = find(*root, palavra->data);
  // Atualiza registro se já existir
  node *lastNode = pop_stack(s);
  if(lastNode){
    lastNode->freq = freq;
    free_stack(s);
    return;
  }

  // Cria novo nó
  node *nn = (node *)malloc(sizeof(node));
  nn->palavra = (char *)malloc(palavra->size*sizeof(char));
  strcpy(nn->palavra, palavra->data);
  nn->freq = freq;
  nn->fb = 0;
  nn->left=NULL;
  nn->right=NULL;

  if(s->pos==0){
    free_stack(s);
    *root = nn; // Árvore vazia
    return;
  }

  lastNode = pop_stack(s);
  int cmp = strcmp(lastNode->palavra, palavra->data);

  if(cmp>0) lastNode->left = nn;
  else lastNode->right = nn;

  node *pn = lastNode;
  node *n = nn;
  do{
    if(pn->right==n) pn->fb--;
    else pn->fb++;

    if(pn->fb==0) break;
    else if(abs(pn->fb)>=2){
      rebalance(root, pop_stack(s), pn);
      break;
    }

    n = pn;
  } while((pn = pop_stack(s)));

  free_stack(s);
}

void tree_on_heap(node *n, heap *h){
  if(!n) return;

  insert_minheap(h, n);
  tree_on_heap(n->left, h);
  tree_on_heap(n->right, h);
}

// Retorna array de apontadores para palavras do autocomplete
heap *range_query(node *root, charVec *prefix, int k){
  if(k<=0) return NULL;

  int len = prefix->size-1;
  node *n = root;

  int cmp;
  while(n){
    cmp = strncmp(n->palavra, prefix->data, len);

    if(cmp<0) n = n->right;
    else if(cmp>0) n = n->left;
    else break;
  }
  if(!n) return NULL;

  // Utiliza um max-heap vetorizado para guardar palavras
  heap *h = init_heap(k);
  insert_minheap(h, n);

  node *l = n->left;
  while(l){
    if(strncmp(l->palavra, prefix->data, len) == 0){
      insert_minheap(h, l);
      tree_on_heap(l->right, h);
      l=l->left;
    } else l=l->right;
  }

  node *r = n->right;
  while(r){
    if(strncmp(r->palavra, prefix->data, len) == 0){
      insert_minheap(h, r);
      tree_on_heap(r->left, h);
      r=r->right;
    } else r=r->left;
  }

  qsort(h->data, h->size, sizeof(node *), cmp_node_q);

  return h;
}

void delete_node(node **root, char *palavra){
  stack *s = find(*root, palavra);
  node *target = pop_stack(s);
  if(!target){ // Caso nó não exista
    free_stack(s);
    return;
  }

  if(target->left && target->right){ // Tem dois filhos
    insert_stack(s, target);
    node *sub = target->right;

    while(sub->left){ // Acha sucessor
      insert_stack(s, sub);
      sub = sub->left;
    }
    insert_stack(s, sub);

    // Troca apenas palavra, freq
    char *tmpChar = target->palavra;
    target->palavra = sub->palavra;
    sub->palavra = tmpChar;

    int tmpFreq = target->freq;
    target->freq = sub->freq;
    sub->freq = tmpFreq;

    target = pop_stack(s); // target = sub;
  }

  node *child = target->left ? target->left : target->right;
  node *parent = pop_stack(s);

  bool wasRight;
  if(parent){
    wasRight = (parent->right==target);

    if(wasRight) parent->right = child;
    else parent->left = child;
  } else *root = child;

  free(target->palavra);
  free(target);

  while(parent){
    if(wasRight) parent->fb++;
    else parent->fb--;

    if(abs(parent->fb)==1) break;
    else if(abs(parent->fb)>=2){
      child = parent;
      parent = pop_stack(s);
      if(parent) wasRight = (parent->right==child);

      if(!rebalance(root, parent, child)) break;
      continue;
    }

    child = parent;
    parent = pop_stack(s);
    if(parent) wasRight = (parent->right==child);
  }

  free_stack(s);
}

void free_tree(node *n){
  if(!n) return;

  free_tree(n->left);
  free_tree(n->right);

  free(n->palavra);
  free(n);
}
