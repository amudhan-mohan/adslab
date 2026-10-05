#include <stdio.h>

#define INF 999
#define SIZE 20

int main() {
    int n;
    int adj[SIZE][SIZE];
    int dist[SIZE];
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

    // Initialize all distances to infinity
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
    }
    dist[start] = 0;

    // Dijkstra's Algorithm
    for (int count = 0; count < n - 1; count++) {
        int min = INF;
        int u = -1;

        // Find the unvisited vertex with the smallest distance
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        // If no reachable vertex is found (disconnected graph), stop early
        if (u == -1) break;

        visited[u] = 1;

        // Update the distance of the adjacent vertices
        for (int i = 0; i < n; i++) {
            // Check if there is an edge, it's unvisited, and the new path is shorter
            if (adj[u][i] != 0 && !visited[i] && dist[u] != INF && dist[u] + adj[u][i] < dist[i]) {
                dist[i] = dist[u] + adj[u][i];
            }
        }
    }

    printf("\nShortest distances from vertex %d:\n", start);
    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            printf("%d -> %d : INF (Unreachable)\n", start, i);
        } else {
            printf("%d -> %d : %d\n", start, i, dist[i]);
        }
    }

    return 0;
}