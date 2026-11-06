#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avlib.h"

int main()
{
    char comando;
    Node* root = NULL;

    long x;
    int cntr_files[3] = {0};
    char nivel[10];
    char sts[14];

    while (scanf(" %c", &comando) == 1)
    {
        switch (comando)
        {
            case 'i':
                scanf(" %ld %9s %13s", &x, nivel, sts);

                insert_node(&root, x, vis_codigo(nivel), sts_codigo(sts));

                break;
            case 'a':
                scanf(" %ld %s %s", &x, nivel, sts);
                update_node(root, x, vis_codigo(nivel), sts_codigo(sts));

                break;
            case 'b':
                scanf(" %ld", &x);
                Node* found_node = search_node(root, x);
                if (found_node == NULL) {
                    printf("%ld nao existe\n", x);
                }
                else
                {
                    printf("%ld, %s, %s\n", x, vis_nome(found_node->vis), sts_nome(found_node->sts));
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
                printf("atualizado: %d, desatualizado: %d, obsoleto: %d\n", cntr_files[0], cntr_files[1], cntr_files[2]);

                break;
            case 'f':
                free_tree(root);

                return 0;
        }
    }
    free_tree(root);

    return 0;
}