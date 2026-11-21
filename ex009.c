#include <stdio.h>
#define INF 9999
void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j);
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}
int main() {
    int n, adj[20][20], dist[20], parent[20], visited[20] = {0}, start;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
               scanf("%d", &adj[i][j]);
    printf("Enter start vertex: ");
    scanf("%d", &start);
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[start] = 0;
    for (int count = 0; count < n; count++) {
        int u = -1, min = INF;
        for (int i = 0; i < n; i++)
               if (!visited[i] && dist[i] < min) {
                   min = dist[i];
                   u = i;
               }
        if (u == -1)
               break;
        visited[u] = 1;
        int *w = adj[u];
        for (int i = 0; i < n; i++)
              if (w[i] && !visited[i] && dist[u] + w[i] < dist[i]) {
                    dist[i] = dist[u] + w[i];
                    parent[i] = u;
              }
    }
    printf("Shortest distances from %d:\n", start);
    for (int i = 0; i < n; i++) {
          if (dist[i] == INF)
              printf("%d -> %d : unreachable\n", start, i);
          else {
              printf("%d -> %d : %d     Path: ", start, i, dist[i]);
              printPath(parent, i);
              printf("\n");
          }
    }
    return 0;
}
