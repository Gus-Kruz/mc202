typedef struct Node
{
    long id;
    int height;
    unsigned char vis;
    unsigned char sts;
    struct Node* left;
    struct Node* right;

} Node;

enum { VIS_RESTRITO, VIS_INTERNO, VIS_PUBLICO, VIS_BLOQUEADO };
enum { EST_ATUALIZADO, EST_DESATUALIZADO, EST_OBSOLETO };

unsigned char vis_codigo(const char nome[]);
const char* vis_nome(unsigned char vis);
unsigned char sts_codigo(const char nome[]);
const char* sts_nome(unsigned char sts);

Node* alloc_node(long id, unsigned char vis, unsigned char sts);

int max(int a, int b);

void update_height(Node* root);

void RRR(Node** root);

void LLR(Node** root);

void LRR(Node** root);

void RLR(Node** root);

void insert_node(Node** root, long id, unsigned char vis, unsigned char sts);

Node* search_node(Node* root, long x);

void update_node(Node* root, long x, unsigned char vis, unsigned char sts);

void print_inorder(Node* root);

void store_n(Node* root, int cntr_files[]);

void free_tree(Node* root);

