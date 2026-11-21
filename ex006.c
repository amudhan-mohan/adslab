#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int key, height;
    struct Node *left, *right;
} Node;
int h(Node *n) {
    return n ? n->height : 0;
}
int max(int a, int b) {
    return (a > b) ? a : b;
}
Node *newNode(int key) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->key = key;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}
Node *rotateRight(Node *y) {
    Node *x = y->left;
    Node *T = x->right;
    x->right = y;
    y->left = T;
    y->height = 1 + max(h(y->left), h(y->right));
    x->height = 1 + max(h(x->left), h(x->right));
    return x;
}
Node *rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T = y->left;
    y->left = x;
    x->right = T;
    x->height = 1 + max(h(x->left), h(x->right));
    y->height = 1 + max(h(y->left), h(y->right));
    return y;
}
int getBalance(Node *n) {
    return n ? h(n->left) - h(n->right) : 0;
}
Node *insert(Node *node, int key) {
    if (!node)
           return newNode(key);
    if (key < node->key)
           node->left = insert(node->left, key);
    else if (key > node->key)
           node->right = insert(node->right, key);
    else
           return node;
    node->height = 1 + max(h(node->left), h(node->right));
    int bal = getBalance(node);
    if (bal > 1 && key < node->left->key)
           return rotateRight(node);
    if (bal < -1 && key > node->right->key)
           return rotateLeft(node);
    if (bal > 1 && key > node->left->key) {
           node->left = rotateLeft(node->left);
           return rotateRight(node);
    }
    if (bal < -1 && key < node->right->key) {
           node->right = rotateRight(node->right);
           return rotateLeft(node);
    }
    return node;
}
void inorder(Node *r) {
    if (r) {
           inorder(r->left);
           printf("%d ", r->key);
           inorder(r->right);
    }
}
void preorder(Node *r) {
    if (r) {
           printf("%d ", r->key);
           preorder(r->left);
        preorder(r->right);
    }
}
int main() {
    Node *root = NULL;
    int n, x;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter %d values: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        root = insert(root, x);
    }
    printf("Inorder Traversal (Balanced Tree): ");
    inorder(root);
    printf("\nPreorder Traversal: ");
    preorder(root);
    printf("\n");
    return 0;
}
