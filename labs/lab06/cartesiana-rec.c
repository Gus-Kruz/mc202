#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int label;
    struct node* left;
    struct node* right;
} node;

typedef struct {
    node** v_queue;
    int first;
    int last;
} queue;

int find_min(int A[], int idx_l, int idx_r) {
    int idx_min = idx_l;

    for (int i = idx_l + 1; i <= idx_r; i++) {
        if (A[i] < A[idx_min]) {
            idx_min = i;
        }
    }

    return idx_min;
}

void build_cartesian(node* root, int A[], int idx_l, int idx_r) {
    int idx_min = find_min(A, idx_l, idx_r);
    root->label = idx_min;

    if (idx_min > idx_l) {
        root->left = malloc(sizeof(node));
        build_cartesian(root->left, A, idx_l, idx_min - 1);
    } else {
        root->left = NULL;
    }
    if (idx_min < idx_r) {
        root->right = malloc(sizeof(node));
        build_cartesian(root->right, A, idx_min + 1, idx_r);
    } else {
        root->right = NULL;
    }
}

void enqueue(queue* q, node* new) {
    q->v_queue[q->last++] = new; 
}

node* dequeue(queue* q) {
    return (q->v_queue[q->first++]);
}

int queue_size(queue* q) {
    return q->last - q->first;
}

void print_bfs(node* root, int n) {
    queue* q = malloc(sizeof(queue));
    q->v_queue = malloc(n * sizeof(node*));
    q->first = 0;
    q->last = 0;

    enqueue(q, root);

    while(queue_size(q)) {
        int size_level = queue_size(q);

        for (int i = 0; i < size_level; i++) {
            node* p = dequeue(q);

            printf("%d ", p->label);
            
            if (p->left != NULL) {
                enqueue(q, p->left);
            }
            if (p->right != NULL) {
                enqueue(q, p->right);
            }
            free(p);
        }
        printf("\n");
    }
    free(q->v_queue);
    free(q);
}

int main() {
    int n;

    scanf(" %d", &n);

    while (n != 0) {
        int* A = malloc(n * sizeof(int));

        for(int i = 0; i < n; i++) {
            scanf(" %d", &A[i]);
        }

        node* root = malloc(sizeof(node));
        build_cartesian(root, A, 0, n-1);
        print_bfs(root, n);
        printf("\n");
        free(A);
        scanf(" %d", &n);
    }
}