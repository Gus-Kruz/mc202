#include <stdio.h>
#include <string.h>

#include "aux.h"

int main(void){
  node *root = NULL;
  int x;

  char command[13];
  charVec *palavra = init_charVec();
  while(scanf(" %s", command) != EOF){
    if(strcmp(command, "INSERT") == 0){
      read_charVec(palavra);
      scanf(" %d", &x);

      insert_node(&root, palavra, x);
    }
    else if(strcmp(command, "SEARCH") == 0){
      read_charVec(palavra);
      stack *s = find(root, palavra->data);
      node *n = pop_stack(s);

      if(n) printf("%s %d\n", n->palavra, n->freq);
      else printf("%s not found.\n", palavra->data);

      free_stack(s);
    }
    else if(strcmp(command, "AUTOCOMPLETE") == 0){
      read_charVec(palavra);
      scanf(" %d", &x);

      heap *query = range_query(root, palavra, x);
      if(!query) printf("nothing for %s.", palavra->data);
      else{
        for(int i=0; i<query->size; i++){
          node *q = query->data[i];
          printf("(%s,%d) ", q->palavra, q->freq);
        }

        free_heap(query);
      }

      printf("\n");
    }
    else if(strcmp(command, "DELETE") == 0){
      read_charVec(palavra);
      delete_node(&root, palavra->data);
    }
    else if(strcmp(command, "PRINT") == 0){
      if(root) inorder_print(root);
      else printf("the dictionary is empty.");
      printf("\n");
    }
    else if(strcmp(command, "EXIT") == 0){
      free_charVec(palavra);
      free_tree(root);
      break;
    }
  }
  return 0;
}
