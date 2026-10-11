typedef struct Node 
{
  char word[30];
  long f;
  struct Node* left;
  struct Node* right;
} Node;

typedef struct MinHeap
{
  Node** vec_node;
  int size;
  int cap;
} MinHeap;

Node* alloc_node();

MinHeap* alloc_heap(int k);

void swap(MinHeap* H, int a, int b);

void insert_heap(MinHeap* H, Node* new_node);

int compare_f(const void* n1, const void* n2);

void free_heap(MinHeap* H);

void insert_word(Node** p_root, Node* new_node);

Node* search_word(Node* root, char* word);

void autocomplete(Node* root, MinHeap* H, char prefix[], int size_prefix);

void print_tree(Node* root);

Node* get_small_succ(Node* root);

void delete_word(Node** p_root, char word[]);

void free_tree(Node* root);






