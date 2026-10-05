#include <stdio.h>

#define MAX_VERTICES 20
#define MAX_EDGES 400

typedef struct {
    int u;
    int v;
    int w;
} Edge;

// Find with path compression
int find(int parent[], int i) {
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = find(parent, parent[i]);
}

// Basic Union
void unionSet(int parent[], int x, int y) {
    parent[y] = x;
}

int main() {
    int n, e;

    printf("Enter number of vertices (max %d): ", MAX_VERTICES);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_VERTICES) {
        printf("Invalid number of vertices. Exiting...\n");
        return 1;
    }

    printf("Enter number of edges (max %d): ", MAX_EDGES);
    if (scanf("%d", &e) != 1 || e < 0 || e > MAX_EDGES) {
        printf("Invalid number of edges. Exiting...\n");
        return 1;
    }

    Edge edges[MAX_EDGES];

    printf("Enter edges (u v w):\n");
    for (int i = 0; i < e; i++) {
        if (scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w) != 3) {
            printf("Invalid input detected. Exiting...\n");
            return 1;
        }
        
        // Ensure vertices are within valid graph bounds
        if (edges[i].u < 0 || edges[i].u >= n || edges[i].v < 0 || edges[i].v >= n) {
            printf("Invalid vertex. Must be between 0 and %d.\n", n - 1);
            return 1;
        }
    }

    // Sort edges by weight (Bubble Sort)
    for (int i = 0; i < e - 1; i++) {
        for (int j = i + 1; j < e; j++) {
            if (edges[i].w > edges[j].w) {
                Edge t = edges[i];
                edges[i] = edges[j];
                edges[j] = t;
            }
        }
    }

    int parent[MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    printf("\nEdges in MST:\n");
    int mst_weight = 0;
    int count = 0;

    for (int i = 0; i < e && count < n - 1; i++) {
        int x = find(parent, edges[i].u);
        int y = find(parent, edges[i].v);

        if (x != y) {
            printf("%d - %d (Weight: %d)\n", edges[i].u, edges[i].v, edges[i].w);
            unionSet(parent, x, y);
            mst_weight += edges[i].w;
            count++;
        }
    }

    // Check if the graph is disconnected
    if (count < n - 1) {
        printf("\nGraph is disconnected. A complete Minimum Spanning Tree cannot be formed.\n");
    } else {
        printf("\nTotal MST Weight: %d\n", mst_weight);
    }

    return 0;
}