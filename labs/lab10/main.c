#include <stdio.h>
#include <stdlib.h>

#include "cuckolib.h"

int main()
{
    char command;
    Cucko* cucko = NULL;
    unsigned int n;
    unsigned int key;
    int value;

    while (scanf(" %c", &command) == 1)
    {
        switch (command)
        {
            case 'c':
                scanf(" %d", &n);

                if (cucko != NULL)
                {
                    free_cucko(cucko);
                }

                size_t size = next_power_of_2(n);
                cucko = alloc_table(size);

                break;
            case 'i':
                scanf(" %u %d", &key, &value);
                unsigned int index = hash_function(*cucko, key, 1);

                insert_pair(&cucko, key, value, index, 0, 1);

                break;
            case 'r':
                scanf(" %u", &key);
                remove_pair(cucko, key);

                break;
            case 'b':
                scanf(" %u", &key);
                Keypair* target = search_pair(cucko, key);

                printf("%d -> ", key);

                if (target == NULL)
                {
                    printf("!E\n");
                }
                else
                {
                    printf("%d\n", target->value);
                }

                break;
            case 'f':
                free_cucko(cucko);

                return 0;
        }
    }
}