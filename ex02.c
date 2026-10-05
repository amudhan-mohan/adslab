#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(char *arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    char **L = malloc(n1 * sizeof(char *));
    char **R = malloc(n2 * sizeof(char *));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) > 0) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    free(L);
    free(R);
}

void mergeSort(char *arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    int n;
    
    printf("Enter number of names: ");
    if (scanf("%d", &n) != 1) return 1;
    getchar(); // Consume the newline character

    printf("Enter %d names:\n", n);
    char **names = malloc(n * sizeof(char *));
    
    for (int i = 0; i < n; i++) {
        char buf[100];
        if (fgets(buf, sizeof(buf), stdin)) {
            buf[strcspn(buf, "\n")] = 0; // Remove trailing newline
            
            // Standard C equivalent of strdup
            names[i] = malloc(strlen(buf) + 1);
            strcpy(names[i], buf);
        }
    }

    mergeSort(names, 0, n - 1);

    printf("\nNames in descending order:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", names[i]);
        free(names[i]);
    }
    
    free(names);
    return 0;
}