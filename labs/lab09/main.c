#include <stdio.h>
#include <stdbool.h>

#include "libtree.h"

int main()
{
    char comando;
    Bnode* root = NULL;
    int t = 0;
    int x;
    long start;
    long end;

    while (scanf(" %c", &comando) == 1)
    {
        switch (comando)
        {
            case 'c':
                scanf(" %d", &t);
                if (root != NULL)
                {
                    free_postorder(root);
                    root = NULL;
                }
                break;
            case 'i':
                scanf(" %d %ld %ld", &x, &start, &end);
                insert_index(&root, t, x, start, end);
                break;
            case 'b': {
                scanf(" %d", &x);
                Index* target = search_index(root, x);
                if (target == NULL)
                {
                    printf("%d nao esta na arvore\n", x);
                }
                else
                {
                    printf("%d: %ld %ld\n", x, target->start, target->end);
                }
                break;
            }
            case 'p':
                print_in_level(root);
                break;
            case 'l':
                print_in_order(root);
                break;
            case 'f':
                if (root != NULL)
                {
                    free_postorder(root);
                    root = NULL;
                }
                return 0;
        }
    }

    if (root != NULL)
    {
        free_postorder(root);
        root = NULL;
    }

    return 0;
}
