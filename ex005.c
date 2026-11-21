#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int key, degree, mark;
    struct Node *parent, *child, *left, *right;
} Node;
Node *min = NULL;
Node *newNode(int key) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->key = key;
    n->degree = n->mark = 0;
    n->parent = n->child = NULL;
    n->left = n->right = n;
    return n;
}
void addToRoot(Node *n) {
    n->parent = NULL;
    if (!min) {
          n->left = n->right = n;
          min = n;
          return;
    }
    n->left = min;
    n->right = min->right;
    min->right->left = n;
    min->right = n;
    if (n->key < min->key)
          min = n;
}
void insert(int key) {
    addToRoot(newNode(key));
}
void link(Node *y, Node *x) {


    y->parent = x;
    y->mark = 0;
    if (!x->child) {
           x->child = y;
           y->left = y->right = y;
    } else {
           y->left = x->child;
           y->right = x->child->right;
           x->child->right->left = y;
           x->child->right = y;
    }
    x->degree++;
}
void consolidate() {
    Node *A[64] = {NULL};
    int cnt = 0;
    Node *t = min;
    do {
           cnt++;
           t = t->right;
    } while (t != min);
    Node **roots = malloc(cnt * sizeof(Node *));
    t = min;
    for (int i = 0; i < cnt; i++) {
           roots[i] = t;
           t = t->right;
    }
    for (int i = 0; i < cnt; i++) {
           Node *x = roots[i];
           int d = x->degree;
           while (A[d]) {
               Node *y = A[d];
               if (x->key > y->key) {
                      Node *tmp = x;
                      x = y;
                      y = tmp;
               }
               link(y, x);
               A[d] = NULL;
               d++;
           }
           A[d] = x;
    }
    free(roots);
    min = NULL;
    for (int i = 0; i < 64; i++)
        if (A[i])
             addToRoot(A[i]);
}
void extractMin() {
    if (!min) {
        printf("Heap empty\n");
        return;
    }
    Node *z = min;
    if (z->child) {
        Node *c = z->child;
        int k = z->degree;
        for (int i = 0; i < k; i++) {
             Node *next = c->right;
             c->parent = NULL;
             c->left = z;
             c->right = z->right;
             z->right->left = c;
             z->right = c;
             c = next;
        }
    }
    z->left->right = z->right;
    z->right->left = z->left;
    if (z == z->right)
        min = NULL;
    else {
        min = z->right;
        consolidate();
    }
    printf("Extracted min = %d\n", z->key);
    free(z);
}
void printList(Node *x) {
    Node *t = x;
    do {
           printf("%d", t->key);
           if (t->child) {
               printf("(");
               printList(t->child);
               printf(")");
           }
           t = t->right;
           if (t != x)
               printf(" ");
    } while (t != x);
}
void display() {
    if (!min) {
           printf("Heap empty\n");
           return;
    }
    printf("Root List: ");
    printList(min);
    printf("\n");
}
int main() {
    int ch, key;
    while (1) {
           printf("\n1. Insert\n2. Display\n3. Get Min\n");
           printf("4. Extract Min\n5. Exit\n");
           printf("Enter choice: ");
           scanf("%d", &ch);
           if (ch == 1) {
               printf("Enter key: ");
               scanf("%d", &key);
               insert(key);
           } else if (ch == 2) display();
           else if (ch == 3) {
               if (min)
                      printf("Minimum = %d\n", min->key);
               else
                      printf("Heap empty\n");
           } else if (ch == 4) extractMin();
          else if (ch == 5)
             break;
          else
             printf("Invalid choice!\n");
    }
    return 0;
}
