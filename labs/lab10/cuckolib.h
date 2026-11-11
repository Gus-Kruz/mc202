#include <stdbool.h>

typedef struct Keypair {
    unsigned int key;
    int value;
} Keypair;

typedef struct Cucko {
    Keypair** table;
    size_t size;
    int n_pairs;
    int shift;
    unsigned int a1;
    unsigned int a2;

} Cucko;

Keypair* alloc_keypair(unsigned int key, int value);

unsigned int next_power_of_2(unsigned int n);

unsigned int generate_random_32bit();

Cucko* alloc_table(size_t size);

void resize_cucko(Cucko** p_cucko);

unsigned int hash_function(Cucko cucko, unsigned int key, bool parity);

void insert_pair(Cucko** p_cucko, unsigned int key, int value, unsigned int index, int tries, bool parity);

void remove_pair(Cucko* cucko, unsigned int key);

Keypair* search_pair(Cucko* cucko, unsigned int key);

void free_cucko(Cucko* cucko);