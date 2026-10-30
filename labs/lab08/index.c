#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avlib.h"

int main()
{
    char comando;
    Node* root = NULL;

    long x;
    long cntr_files[3] = {0};
    char nivel[20];
    char sts[20];

    Node* new_node;

    while (scanf(" %c", &comando) == 1)
    {
        switch (comando)
        {
            case 'i':
                new_node = alloc_node();  
                scanf(" %ld %s %s", &(new_node->id), new_node->vis, new_node->sts);
                
                insert_node(&root, new_node);

                break;
            case 'a':
                scanf(" %ld %s %s", &x, nivel, sts);
                update_node(root, x, nivel, sts);

                break;
            case 'b':
                scanf(" %ld", &x);
                Node* found_node = search_node(root, x);
                if (found_node == NULL) {
                    printf("%ld nao existe\n", x);
                }
                else
                {
                    printf("%ld, %s, %s\n", x, found_node->vis, found_node->sts);
                }

                break;
            case 'l':
                if (root == NULL)
                {
                    printf("indice vazio\n");
                }
                else
                {
                    printf("documentos: ");
                    print_inorder(root);
                    printf("\n");
                }

                break;
            case 't':
                for (int i =0; i < 3; i++)
                {
                    cntr_files[i] = 0;
                }

                store_n(root, cntr_files);
                printf("atualizado: %ld, desatualizado: %ld, obsoleto: %ld\n", cntr_files[0], cntr_files[1], cntr_files[2]);

                break;
            case 'f':
                free_tree(root);

                return 0;
        }
    }
}