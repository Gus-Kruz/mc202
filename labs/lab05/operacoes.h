typedef struct no_elemento {
    int valor_elemento;
    struct no_elemento* prox;
} no_elemento;

typedef struct conjunto {
    int tamanho;
    struct no_elemento* head;
} conjunto;

void inicializar_conjunto(conjunto* c);

void adicionar_elemento(conjunto* c, int valor_novo_elemento);

void remover_elemento(conjunto* c, int valor_elemento_rem);

void conjunto_uniao(conjunto* c_i, conjunto* c_j, conjunto* c_k);

bool buscar_elemento(conjunto* c, int valor_buscado);

void conjunto_diferenca(conjunto*c_i, conjunto* c_j, conjunto* c_k);

void conjunto_intersecao(conjunto* c_i, conjunto* c_j, conjunto* c_k);

void imprimir_elementos(conjunto* c, int i_conjunto);

void limpar_vetor(conjunto vetor_conjuntos[]);