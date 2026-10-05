#include <stdio.h>

#define SIZE 20

int visited[SIZE];

void DFS(int adj[SIZE][SIZE], int n, int v) {
    visited[v] = 1;
    printf("%d ", v);
    
    for (int i = 0; i < n; i++) {
        // If there is an edge and the vertex hasn't been visited
        if (adj[v][i] != 0 && !visited[i]) {
            DFS(adj, n, i);
        }
    }
}

int main() {
    int n;
    int adj[SIZE][SIZE];
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

    // Initialize visited array to 0
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("DFS Traversal: ");
    DFS(adj, n, start);
    printf("\n"); // Print newline after traversal finishes

    return 0;
}