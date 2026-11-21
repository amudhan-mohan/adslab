#include <stdio.h>
#define SIZE 20
int q[SIZE], front = 0, rear = 0;
void enqueue(int v) {
    q[rear++] = v;
}
int dequeue() {
    return q[front++];
}
int isEmpty() {
    return front == rear;
}
int main() {
    int n, adj[20][20], visited[20] = {0}, start;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
               scanf("%d", &adj[i][j]);
    printf("Enter start vertex (0-%d): ", n - 1);
    scanf("%d", &start);
    printf("BFS Traversal: ");
    visited[start] = 1;
    enqueue(start);
    while (!isEmpty()) {
        int v = dequeue();
        printf("%d ", v);
        for (int i = 0; i < n; i++)
               if (adj[v][i] && !visited[i]) {
                   visited[i] = 1;
                   enqueue(i);
               }
    }


    for (int s = 0; s < n; s++)
        if (!visited[s]) {
            visited[s] = 1;
            enqueue(s);
            while (!isEmpty()) {
                int v = dequeue();
                printf("%d ", v);
                for (int i = 0; i < n; i++)
                    if (adj[v][i] && !visited[i]) {
                          visited[i] = 1;
                          enqueue(i);
                    }
            }
        }
    printf("\n");
    return 0;
}
