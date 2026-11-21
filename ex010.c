#include <stdio.h>
typedef struct {
    int u, v, w;
} Edge;
int find(int parent[], int i) {
    return (parent[i] == i) ? i : (parent[i] = find(parent, parent[i]));
}
void unionSet(int parent[], int x, int y) {
    parent[y] = x;
}
int main() {
    int n, e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);
    Edge edges[e];
    printf("Enter edges (u v w):\n");
    for (int i = 0; i < e; i++)
          scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    for (int i = 0; i < e - 1; i++)
          for (int j = i + 1; j < e; j++)
               if (edges[i].w > edges[j].w) {
                   Edge t = edges[i];
                   edges[i] = edges[j];
                   edges[j] = t;
               }
    int parent[n];
    for (int i = 0; i < n; i++)
          parent[i] = i;
    int total = 0, count = 0;
    printf("Edges in MST:\n");
    for (int i = 0; i < e && count < n - 1; i++) {
          int x = find(parent, edges[i].u), y = find(parent, edges[i].v);
          if (x != y) {
               printf("%d - %d (%d)\n", edges[i].u, edges[i].v, edges[i].w);
               unionSet(parent, x, y);
               total += edges[i].w;
               count++;
           }
    }
    if (count < n - 1)
           printf("Graph is not connected, no spanning tree.\n");
    else
           printf("Total cost = %d\n", total);
    return 0;
}
