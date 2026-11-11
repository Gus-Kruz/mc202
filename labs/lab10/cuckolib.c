#include <stdlib.h>
#include <stdbool.h>

#include "cuckolib.h" 

Keypair* alloc_keypair(unsigned int key, int value)
{
    Keypair* new_keypair = malloc(sizeof(Keypair));

    new_keypair->key = key;
    new_keypair->value = value;

    return new_keypair;
}

unsigned int next_power_of_2(unsigned int n)
{
    size_t size = n * 2;

    size--;

    size |= size >> 1;
    size |= size >> 2;
    size |= size >> 4;
    size |= size >> 8;
    size |= size >> 16;
    size |= size >> 32;

    return size+1;
}

unsigned int generate_random_32bit()
{
    unsigned int r1 = (unsigned int) rand();
    unsigned int r2 = (unsigned int) rand();
    unsigned int r3 = (unsigned) rand();
    
    return r1 ^ (r2 << 15) ^ (r3 << 30);
}

Cucko* alloc_table(size_t size)
{
    Cucko* cucko = malloc(sizeof(Cucko));

    Keypair** table = malloc(size * sizeof(Keypair*));

    for (size_t i = 0; i < size; i++)
    {
        table[i] = NULL;
    }

    cucko->table = table;
    cucko->n_pairs = 0;
    cucko->size = size;

    unsigned int m = __builtin_ctzll(size);
    cucko->shift = 32 - m;
    
    cucko->a1 = generate_random_32bit() | 1; 
    cucko->a2 = generate_random_32bit() | 1;

    return cucko;
}

void resize_cucko(Cucko** p_cucko)
{
    Cucko* new_cucko = alloc_table((*p_cucko)->size << 1);

    for (int i = 0; i < (*p_cucko)->size; i++)
    {
        new_cucko->table[i] = (*p_cucko)->table[i];
    }

    new_cucko->n_pairs = (*p_cucko)->n_pairs;
    new_cucko->shift--;

    free(*p_cucko);

    *p_cucko = new_cucko;
}

unsigned int hash_function(Cucko cucko, unsigned int key, bool parity)
{
    if(parity)
    {
        return (cucko.a1 * key) >> cucko.shift;
    }
    else
    {
        return (cucko.a2 * key) >> cucko.shift;
    }
}

void insert_pair(Cucko** p_cucko, unsigned int key, int value, int tries, bool parity)
{
    unsigned int index = hash_function(**p_cucko, key, parity);

    if (tries >= 100 || (*p_cucko)->n_pairs >= (*p_cucko)->size * 0.7) {
        resize_cucko(p_cucko);
        insert_pair(p_cucko, key, value, 0, parity);
    }

    if ((*p_cucko)->table[index] != NULL)
    {
        if ((*p_cucko)->table[index]->key == key)
        {
            (*p_cucko)->table[index]->value = value;

            return;
        }
        else
        {
            insert_pair(p_cucko, (*p_cucko)->table[index]->key, (*p_cucko)->table[index]->value, ++tries, !parity);
            return;
        }
    }

    Keypair* new_keypair = alloc_keypair(key, value);
    (*p_cucko)->table[index] = new_keypair;
    
    return;
}

void remove_pair(Cucko* cucko, unsigned int key)
{
    unsigned int index = hash_function(*cucko, key, 1);

    if (cucko->table[index] != NULL && cucko->table[index]->key == key)
    {
        free(cucko->table[index]);
        cucko->table[index] = NULL;

        return;
    }
    else
    {
        index = hash_function(*cucko, key, 1);

        if (cucko->table[index] != NULL && cucko->table[index]->key == key)
        {
            free(cucko->table[index]);
            cucko->table[index] = NULL;

            return;
        }
    }

    return;
}

Keypair* search_pair(Cucko* cucko, unsigned int key)
{
    unsigned int index = hash_function(*cucko, key, 1);

    if (cucko->table[index] != NULL && cucko->table[index]->key == key)
    {
        return cucko->table[index];
    }
    else
    {
        index = hash_function(*cucko, key, 1);

        if (cucko->table[index] != NULL && cucko->table[index]->key == key)
        {
            return cucko->table[index];
        }
    }

    return NULL;
}

void free_cucko(Cucko* cucko)
{
    for (size_t i = 0; i < cucko->size; i++)
    {
        if (cucko->table[i] != NULL)
        {
            free(cucko->table[i]);
        }
    }

    free(cucko->table);

    free(cucko);

    return;
}