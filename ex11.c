#include <stdio.h>
#include <stdlib.h>

#define ORDER 4

struct BPlusNode {
    int keys[ORDER];
    struct BPlusNode *child[ORDER + 1];
    struct BPlusNode *next;
    int count;
    int isLeaf;
};

struct BPlusNode *root = NULL;

struct BPlusNode* createNode(int isLeaf) {
    struct BPlusNode *newNode = (struct BPlusNode*)malloc(sizeof(struct BPlusNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    newNode->count = 0;
    newNode->isLeaf = isLeaf;
    newNode->next = NULL;
    
    for (int i = 0; i <= ORDER; i++) {
        newNode->child[i] = NULL;
    }
    
    return newNode;
}

void insert(int key) {
    if (root == NULL) {
        root = createNode(1);
        root->keys[0] = key;
        root->count = 1;
        return;
    }
    
    struct BPlusNode *leaf = root;
    
    // Traverse internal nodes
    while (!leaf->isLeaf) {
        int i = 0;
        while (i < leaf->count && key >= leaf->keys[i]) {
            i++;
        }
        leaf = leaf->child[i];
    }
    
    // TOY IMPLEMENTATION FIX: Since this basic demonstration doesn't 
    // promote keys to internal nodes upon splitting, we must traverse 
    // the leaf linked-list to find the correct insertion node.
    while (leaf->next != NULL && key >= leaf->next->keys[0]) {
        leaf = leaf->next;
    }
    
    // Find correct position and shift keys
    int i = leaf->count - 1;
    while (i >= 0 && leaf->keys[i] > key) {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }
    
    leaf->keys[i + 1] = key;
    leaf->count++;
    
    // Simple split for demonstration
    if (leaf->count == ORDER) {
        struct BPlusNode *newLeaf = createNode(1);
        int mid = ORDER / 2;
        
        for (i = mid; i < leaf->count; i++) {
            newLeaf->keys[i - mid] = leaf->keys[i];
        }
        
        newLeaf->count = leaf->count - mid;
        leaf->count = mid;
        
        newLeaf->next = leaf->next;
        leaf->next = newLeaf;
    }
}

void display() {
    struct BPlusNode *temp = root;
    
    if (temp == NULL) {
        printf("B+ Tree is empty.\n");
        return;
    }
    
    // Drop down to the first leaf
    while (!temp->isLeaf) {
        temp = temp->child[0];
    }
    
    printf("B+ Tree Leaf Nodes:\n");
    while (temp != NULL) {
        printf("[ ");
        for (int i = 0; i < temp->count; i++) {
            printf("%d ", temp->keys[i]);
        }
        printf("] ");
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n, key;
    
    printf("Enter number of keys: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Exiting...\n");
        return 1;
    }
    
    printf("Enter %d keys:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &key) == 1) {
            insert(key);
        } else {
            printf("Invalid key input detected. Stopping insertion.\n");
            break;
        }
    }
    
    display();
    return 0;
}