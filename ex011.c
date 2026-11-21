#include <stdio.h>
#include <stdlib.h>
#define ORDER 4
#define MAXK (ORDER - 1)
typedef struct Node {
    int keys[MAXK + 1];
    struct Node *child[ORDER + 2];
    struct Node *next;
    int count, isLeaf;
} Node;
Node *root = NULL;
Node *createNode(int isLeaf) {
    Node *n = (Node *)calloc(1, sizeof(Node));
    n->isLeaf = isLeaf;
    return n;
}
int search(int key) {
    Node *n = root;
    if (!n)
          return 0;
    while (!n->isLeaf) {
          int i = 0;
          while (i < n->count && key >= n->keys[i])
              i++;
          n = n->child[i];
    }
    for (int i = 0; i < n->count; i++)
          if (n->keys[i] == key)
              return 1;
    return 0;
}
Node *insertRec(Node *node, int key, int *up) {
    int i;
    if (node->isLeaf) {
          i = node->count - 1;
          while (i >= 0 && node->keys[i] > key) {
              node->keys[i + 1] = node->keys[i];
         i--;
    }
    node->keys[i + 1] = key;
    node->count++;
    if (node->count <= MAXK)
         return NULL;
    Node *right = createNode(1);
    int mid = node->count / 2;
    for (i = mid; i < node->count; i++)
         right->keys[i - mid] = node->keys[i];
    right->count = node->count - mid;
    node->count = mid;
    right->next = node->next;
    node->next = right;
    *up = right->keys[0];
    return right;
}
i = 0;
while (i < node->count && key >= node->keys[i])
    i++;
int k;
Node *nc = insertRec(node->child[i], key, &k);
if (!nc)
    return NULL;
for (int j = node->count; j > i; j--) {
    node->keys[j] = node->keys[j - 1];
    node->child[j + 1] = node->child[j];
}
node->keys[i] = k;
node->child[i + 1] = nc;
node->count++;
if (node->count <= MAXK)
    return NULL;
Node *right = createNode(0);
int mid = node->count / 2, r = 0;
*up = node->keys[mid];
for (i = mid + 1; i < node->count; i++) {
    right->keys[r] = node->keys[i];
    right->child[r] = node->child[i];
        r++;
    }
    right->child[r] = node->child[node->count];
    right->count = r;
    node->count = mid;
    return right;
}
void insert(int key) {
    if (!root) {
        root = createNode(1);
        root->keys[0] = key;
        root->count = 1;
        return;
    }
    if (search(key)) {
        printf("Duplicate %d ignored\n", key);
        return;
    }
    int up;
    Node *right = insertRec(root, key, &up);
    if (right) {
        Node *nr = createNode(0);
        nr->keys[0] = up;
        nr->child[0] = root;
        nr->child[1] = right;
        nr->count = 1;
        root = nr;
    }
}
void printTree(Node *n, int lvl) {
    if (!n)
        return;
    for (int i = 0; i < lvl; i++)
        printf("      ");
    printf("[ ");
    for (int i = 0; i < n->count; i++)
        printf("%d ", n->keys[i]);
    printf("]\n");
    if (!n->isLeaf)
        for (int i = 0; i <= n->count; i++)
               printTree(n->child[i], lvl + 1);
}
void display() {
    if (!root) {
        printf("B+ Tree is empty.\n");
        return;
    }
    printf("B+ Tree Structure:\n");
    printTree(root, 0);
    Node *t = root;
    while (!t->isLeaf)
        t = t->child[0];
    printf("Leaf nodes (linked): ");
    while (t) {
        printf("[ ");
        for (int i = 0; i < t->count; i++)
               printf("%d ", t->keys[i]);
        printf("] ");
        t = t->next;
    }
    printf("\n");
}
int main() {
    int n, key;
    printf("Enter number of keys: ");
    scanf("%d", &n);
    printf("Enter the keys:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(key);
    }
    display();
    printf("Enter key to search: ");
    scanf("%d", &key);
    printf(search(key) ? "%d found\n" : "%d not found\n", key);
    return 0;
}
