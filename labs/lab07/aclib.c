#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aclib.h"

Node* alloc_node()
{
  Node* new_node = malloc(sizeof(Node));
  new_node->f = 0;
  new_node->left = NULL;
  new_node->right = NULL;

  return new_node;
}

MinHeap* alloc_heap(int k)
{ 
  MinHeap* H = malloc(sizeof(MinHeap));
  H->cap = k;
  H->size = 0;

  H->vec_node = malloc(k * sizeof(Node*));

  return H;
}

void swap(MinHeap* H, int a, int b)
{
  Node* temp = H->vec_node[a];
  H->vec_node[a] = H->vec_node[b];
  H->vec_node[b] = temp;
}

void insert_heap(MinHeap* H, Node* new_node)
{
  H->vec_node[H->size] = new_node;
  int index = H->size;
  H->size++;

  int index_father = (index - 1) / 2;

  // heapify up verificando casos de desempate
  while (index > 0 && (H->vec_node[index_father]->f > H->vec_node[index]->f ||
        (H->vec_node[index_father]->f == H->vec_node[index]->f && 
        strcmp(H->vec_node[index_father]->word, H->vec_node[index]->word) < 0)))
  {
    swap(H, index, (index - 1) / 2);

    index = (index - 1) / 2;
    index_father = (index - 1) / 2;
  }
}

int compare_f(const void* n1, const void* n2)
{
  Node* x = *((Node**) n1);
  Node* y = *((Node**) n2);

  int cmp = strcmp(x->word, y->word);

  if (x->f < y->f)
  {
    return 1;
  }
  else if (x->f > y->f)
  {
    return -1;
  }
  else
  {
    return cmp;
  }
}

void free_heap(MinHeap* H) {
  free(H->vec_node);
  free(H);
}

void insert_word(Node** p_root, Node* new_node)
{
  if (*p_root == NULL)
  {
    *p_root = new_node;
    return;
  } 
  else
  {
    int cmp = strcmp((*p_root)->word, new_node->word);
    if (cmp == 0)
    {
      (*p_root)->f = new_node->f;
      free(new_node);
      return;
    }
    else if (cmp > 0)
    {
      insert_word(&((*p_root)->left), new_node);
    }
    else
    {
      insert_word(&((*p_root)->right), new_node);
    }
  }
}

Node* search_word(Node* root, char* word)
{
  if (root == NULL)
  {
    return NULL;
  }

  int cmp = strcmp(root->word, word);

  if (cmp > 0)
  {
    return search_word(root->left, word);
  }
  else if (cmp < 0)
  {
    return search_word(root->right, word);
  }
  else
  {
    return root;
  }
}

void autocomplete(Node* root, MinHeap* H, char prefix[], int size_prefix)
{
  if (root == NULL)
  {
    return;
  }

  int cmp = strncmp(root->word, prefix, size_prefix);

  if (cmp == 0)
  {
    /* se o nó tem o prefixo, tenta inserir o nó na heap,
    caso o heap tenha atingido o limite 
    faz o heapify down considerando o caso de desempate */
    if (H->size == H->cap)
    {
      if (root->f > H->vec_node[0]->f ||
        (root->f == H->vec_node[0]->f && strcmp(root->word, H->vec_node[0]->word) < 0))
        {
        H->vec_node[0] = root;
        int index = 0;

        while (1)
        {
          int left = 2 * index + 1;
          int right = 2 * index + 2;
          int smallest = index;

          if (left < H->size && (H->vec_node[left]->f < H->vec_node[smallest]->f ||
            (H->vec_node[left]->f == H->vec_node[smallest]->f && strcmp(H->vec_node[left]->word, H->vec_node[smallest]->word) > 0)))
            {
              smallest = left;
            }

          if (right < H->size && (H->vec_node[right]->f < H->vec_node[smallest]->f ||
              (H->vec_node[right]->f == H->vec_node[smallest]->f && strcmp(H->vec_node[right]->word, H->vec_node[smallest]->word) > 0)))
              {
              smallest = right;
              }

          if (smallest != index)
          {
            swap(H, index, smallest);
            index = smallest;
          }

          else
          {
            break;
          }
        }
      }
    }

    else
    {
      insert_heap(H, root);
    }

    autocomplete(root->right, H, prefix, size_prefix);
    autocomplete(root->left, H, prefix, size_prefix);

  }
  else if (cmp > 0)
  {
    autocomplete(root->left, H, prefix, size_prefix);
  }
  else
  {
    autocomplete(root->right, H, prefix, size_prefix);
  }
}

void print_tree(Node* root)
{
  if (root != NULL)
  {
    print_tree(root->left);
    printf("%s ", root->word);
    print_tree(root->right);
  }
}

Node* get_small_succ(Node* root)
{
  Node* curr = root->right;

  while (curr->left != NULL)
  {
    curr = curr->left;
  }

  return curr;
}

void delete_word(Node** p_root, char word[])
{
  if (*p_root == NULL)
  {
    return;
  }

  int cmp = strcmp((*p_root)->word, word);

  if (cmp > 0)
  {
    delete_word(&((*p_root)->left), word);
  }
  else if (cmp < 0)
  {
    delete_word(&((*p_root)->right), word);
  }
  else
  {
    // caso 1: nó tem no máximo um filho
    if ((*p_root)->left == NULL)
    {
      Node* aux = (*p_root);
      *p_root = (*p_root)->right;

      free(aux);

      return;
    }

    if ((*p_root)->right == NULL)
    {
      Node* aux = (*p_root);
      (*p_root) = (*p_root)->left;

      free(aux);

      return;
    }
    /* caso 2: nó tem 2 filhos, troco as informações do root com o sucessor e
        apago o sucessor*/
    Node* succ = get_small_succ((*p_root));
    strcpy((*p_root)->word, succ->word);
    (*p_root)->f = succ->f;

    delete_word(&((*p_root)->right), succ->word);
  }
}

void free_tree(Node* root)
{
  if (root != NULL)
  {
    free_tree(root->left);
    free_tree(root->right);
    free(root);
  }
}