#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int degree;
    int mark;
    struct Node *parent;
    struct Node *child;
    struct Node *left;
    struct Node *right;
} Node;

Node *min = NULL;

// Create new node
Node* newNode(int key) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (n == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    
    n->key = key;
    n->degree = 0;
    n->mark = 0;
    n->parent = NULL;
    n->child = NULL;
    n->left = n;
    n->right = n;
    
    return n;
}

// Insert node
void insert(int key) {
    Node *n = newNode(key);
    
    if (!min) {
        min = n;
    } else {
        // Insert node to the right of min
        n->left = min;
        n->right = min->right;
        min->right->left = n;
        min->right = n;
        
        // Update min pointer if necessary
        if (n->key < min->key) {
            min = n;
        }
    }
}

// Display root list
void display() {
    if (!min) {
        printf("Heap empty\n");
        return;
    }
    
    Node *t = min;
    printf("Root List: ");
    do {
        printf("%d ", t->key);
        t = t->right;
    } while (t != min);
    printf("\n");
}

int main() {
    int choice, key;
    
    while (1) {
        printf("\n1. Insert\n2. Display\n3. Get Min\n4. Exit\nEnter choice: ");
        
        // Prevent infinite loop on non-integer input
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Exiting...\n");
            break;
        }

        if (choice == 1) {
            printf("Enter key: ");
            if (scanf("%d", &key) == 1) {
                insert(key);
            } else {
                printf("Invalid key. Please enter a number.\n");
                while (getchar() != '\n'); // Clear input buffer
            }
        } 
        else if (choice == 2) {
            display();
        } 
        else if (choice == 3) {
            if (min) {
                printf("Minimum = %d\n", min->key);
            } else {
                printf("Heap empty\n");
            }
        } 
        else if (choice == 4) {
            break;
        } 
        else {
            printf("Invalid choice!\n");
        }
    }
    
    return 0;
}