#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "dequef.h"
#include "math.h"

/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef* df_alloc(long capacity, double factor) {
   dequef* D = malloc(sizeof(dequef));
   if (D == NULL) {
      return NULL;
   }

   // criando um vetor dinâmico para o array da deque
   D->data = malloc(capacity * sizeof(float));

   D->cap = capacity;
   D->mincap = capacity;
   D->factor = factor;

   // adotando que a deque inicia em 0, ao ser criada tem tamanho 0
   D->first = 0; 
   D->size = 0;

   return D;
}



/**
   Release a dequef and its data.
**/
void df_free(dequef* D) {
   free(D->data);

   free(D);
}



/**
   The size of the deque.
**/
long df_size(dequef* D) {
   return(D->size);
}



/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef* D, float x) {
   if (D->size == D->cap) {
      long new_cap = (long)(D->cap * D->factor);
      float* new_data = malloc(new_cap * sizeof(float));
      
      if (new_data == NULL) {
         return 0;
      }
      for (long i = 0; i < D->size; i++) {
            new_data[i] = D->data[(D->first + i) % D->cap];
      }

      free(D->data);
      D->data = new_data;
      D->cap = new_cap;
      D->first = 0;
   }

   D->data[(D->first + D->size) % D->cap] = x;
   D->size++;

   return 1;
}



/**
   Remove a float from the end of D and return it.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?

   note que na chamada na main, é verificado se a deque está vazia e somente quando
   a deque tem elementos é chamada
**/
float df_pop(dequef* D) {
   D->size--;
   float popado = D->data[(D->first + D->size) % D->cap];

   long limit = (long)(D->cap / (D->factor * D->factor));
   if (D->size <= limit && D->cap > D->mincap) {
   
      long new_cap = (long)(D->cap / D->factor);
      if (new_cap < D->mincap) {
         new_cap = D->mincap;
      }

      float* r_data = malloc(new_cap * sizeof(float));
      
      if (r_data != NULL) {
         for (long i = 0; i < D->size; i++) {
            r_data[i] = D->data[(D->first + i) % D->cap];
         }

         free(D->data);
         D->data = r_data;
         D->first = 0;
         D->cap = new_cap;
      }
   }

   return popado;
}




/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef* D, float x) {
   if (D->size == D->cap) {
      long new_cap = (long)(D->cap * D->factor);
      float* new_data = malloc(new_cap * sizeof(float));
      
      if (new_data == NULL) {
         return 0;
      }
      for (long i = 0; i < D->size; i++) {
         new_data[i] = D->data[(D->first + i) % D->cap];
      }

      free(D->data);
      D->data = new_data;
      D->cap = new_cap;
      D->first = 0;
   }

   if (D->first == 0) {
      D->first = D->cap - 1;
   } else {
      D->first--;
   }

   D->data[D->first] = x;
   D->size++;
   
   return 1;
}



/**
   Remove a float from the beginning of D and return it.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   It returns the float removed from D.
   What happens if D is empty before the call?

   note que a main lida com isso :p
**/
float df_eject(dequef* D) {
   float ejectado = D->data[D->first];
   

   D->first = (D->first + 1) % D->cap;
   D->size--;

   long limit = (long)(D->cap / (D->factor * D->factor));
   if (D->size <= limit && D->cap > D->mincap) {
      long new_cap = (long)(D->cap / D->factor);
      if (new_cap < D->mincap) {
         new_cap = D->mincap;
      }

      float* e_data = malloc(new_cap * sizeof(float));
      if (e_data != NULL) {
         for (long i = 0; i < D->size; i++) {
            e_data[i] = D->data[(D->first + i) % D->cap];
         }
            
         free(D->data);
         D->data = e_data;
         D->first = 0;
         D->cap = new_cap;
      }
   }

   return ejectado;
}



/**
   Return D[i].

   If i is not in [0,|D|-1]] what happens then?

   note que a main já lida com isso :P
**/
float df_get(dequef* D, long i) {
   float alvo;

   alvo = D->data[(D->first + i) % D->cap];

   return alvo;
}



/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] what happens then?

   note que a main já lida com isso :PP
**/
void df_set(dequef* D, long i, float x) {
   D->data[(D->first + i) % D->cap] = x;
}



/**
   Print the elements of D in a single line.
**/
void df_print(dequef* D) {
   printf("deque (%ld): ", D->size);

   for (int i = 0; i < D->size; i++) {
      printf("%.1f ", D->data[(D->first + i) % D->cap]);
   }

   printf("\n");
}
