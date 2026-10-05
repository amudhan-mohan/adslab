#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

// Helper to get height of a node
int h(Node *n) {
    return n ? n->height : 0;
}

// Helper to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new AVL node
Node* newNode(int key) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (n == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    n->height = 1; // New node is initially added at leaf
    
    return n;
}

// Right rotate
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T;
    
    // Update heights
    y->height = 1 + max(h(y->left), h(y->right));
    x->height = 1 + max(h(x->left), h(x->right));
    
    return x;
}

// Left rotate
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T;
    
    // Update heights
    x->height = 1 + max(h(x->left), h(x->right));
    y->height = 1 + max(h(y->left), h(y->right));
    
    return y;
}

// Get balance factor of node N
int getBalance(Node* n) {
    return n ? h(n->left) - h(n->right) : 0;
}

// Insert a key into the AVL tree
Node* insert(Node* node, int key) {
    // 1. Perform the normal BST insertion
    if (!node) return newNode(key);
    
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Equal keys are not allowed in BST
    }
    
    // 2. Update height of this ancestor node
    node->height = 1 + max(h(node->left), h(node->right));
    
    // 3. Get the balance factor
    int bal = getBalance(node);
    
    // If the node becomes unbalanced, there are 4 cases
    
    // Left Left Case
    if (bal > 1 && key < node->left->key) {
        return rotateRight(node);
    }
    
    // Right Right Case
    if (bal < -1 && key > node->right->key) {
        return rotateLeft(node);
    }
    
    // Left Right Case
    if (bal > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Right Left Case
    if (bal < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

// Print inorder traversal
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int n, x;
    
    printf("Enter number of nodes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Exiting...\n");
        return 1;
    }
    
    printf("Enter %d values: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &x) == 1) {
            root = insert(root, x);
        } else {
            printf("\nInvalid input detected. Stopping insertion.\n");
            break;
        }
    }
    
    printf("Inorder Traversal (Balanced Tree): ");
    inorder(root);
    printf("\n"); // Clear newline at the end of program
    
    return 0;
}