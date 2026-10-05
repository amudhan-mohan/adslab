#include <stdio.h>

#define SIZE 20

int q[SIZE];
int front = 0;
int rear = 0;

void enqueue(int v) {
    if (rear < SIZE) {
        q[rear++] = v;
    } else {
        printf("\nError: Queue overflow.\n");
    }
}

int dequeue() {
    if (front < rear) {
        return q[front++];
    }
    return -1; // Return error value if queue is empty
}

int isEmpty() {
    return front == rear;
}

int main() {
    int n, adj[SIZE][SIZE];
    int visited[SIZE] = {0};
    int start;

    printf("Enter number of vertices (max %d): ", SIZE);
    if (scanf("%d", &n) != 1 || n <= 0 || n > SIZE) {
        printf("Invalid number of vertices. Exiting...\n");
        return 1;
    }

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &adj[i][j]) != 1) {
                printf("Invalid input detected in matrix. Exiting...\n");
                return 1;
            }
        }
    }

    printf("Enter start vertex (0-%d): ", n - 1);
    if (scanf("%d", &start) != 1 || start < 0 || start >= n) {
        printf("Invalid start vertex. Exiting...\n");
        return 1;
    }

    printf("BFS Traversal: ");
    visited[start] = 1;
    enqueue(start);

    while (!isEmpty()) {
        int v = dequeue();
        if (v == -1) break; // Safeguard against underflow
        
        printf("%d ", v);
        
        for (int i = 0; i < n; i++) {
            // If there is an edge and the vertex hasn't been visited
            if (adj[v][i] != 0 && !visited[i]) {
                visited[i] = 1;
                enqueue(i);
            }
        }
    }
    printf("\n");

    return 0;
}