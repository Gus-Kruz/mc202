typedef struct Node
{
    long id;
    long height;
    char vis[20];
    char sts[20];
    struct Node* parent;
    struct Node* left;
    struct Node* right;

} Node;

Node* alloc_node();

int max(int a, int b);

void update_height(Node* root);

void RRR(Node** root);

void LLR(Node** root);

void LRR(Node** root);

void RLR(Node** root);

void insert_node(Node** root, Node* new_node);

Node* search_node(Node* root, long x);

void update_node(Node* root, long x, char nivel[], char sts[]);

void print_inorder(Node* root);

void store_n(Node* root, long cntr_files[]);

void free_tree(Node* root);

