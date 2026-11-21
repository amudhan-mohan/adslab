#include <stdio.h>
#define SIZE 20
int visited[SIZE];
void DFS(int adj[SIZE][SIZE], int n, int v) {
    visited[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < n; i++)
        if (adj[v][i] && !visited[i])
               DFS(adj, n, i);
}
int main() {
    int n, adj[SIZE][SIZE], start;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
               scanf("%d", &adj[i][j]);
    printf("Enter start vertex (0-%d): ", n - 1);
    scanf("%d", &start);
    printf("DFS Traversal: ");
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    DFS(adj, n, start);
    printf("\n");
    return 0;
}
