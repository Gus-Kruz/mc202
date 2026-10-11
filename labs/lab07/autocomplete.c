#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aclib.h"

int main()
{
  char command[13];
  long f;
  long k;

  Node *root = NULL;


  while (scanf(" %s", command) == 1)
  {
    if (strcmp(command, "INSERT") == 0)
    {
      Node *new_node = alloc_node();

      scanf(" %s", new_node->word);

      scanf(" %ld", &f);
      new_node->f = f;

      insert_word(&root, new_node);
    }

    else if (strcmp(command, "SEARCH") == 0) {
      char word[30];
      scanf(" %s", word);

      Node *found_node = search_word(root, word);

      if (found_node == NULL) {
        printf("%s not found.\n", word);
      } else {
        printf("%s %ld\n", word, found_node->f);
      }
    }

    else if (strcmp(command, "AUTOCOMPLETE") == 0) {
      char prefix[30];
      scanf(" %s", prefix);

      int size_prefix = strlen(prefix);

      scanf(" %ld", &k);

      MinHeap* H = alloc_heap(k);

      autocomplete(root, H, prefix, size_prefix);

      qsort(H->vec_node, H->size, sizeof(Node *), compare_f);

      if (H->size == 0) {
        printf("nothing for %s.", prefix);
      } else {
        for (int i = 0; i < k && i < H->size; i++) {
          printf("(%s,%ld) ", H->vec_node[i]->word, (H->vec_node[i]->f));
        }
      }
      printf("\n");

      free_heap(H);
    }

    else if (strcmp(command, "DELETE") == 0) {
      char word[30];
      scanf(" %s", word);

      delete_word(&root, word);

    } else if (strcmp(command, "PRINT") == 0) {

      if (root == NULL) {
        printf("the dictionary is empty.");
      } else {
        print_tree(root);
      }

      printf("\n");
    } else if (strcmp(command, "EXIT") == 0) {

      free_tree(root);
      return 0;
    }
  }
}
