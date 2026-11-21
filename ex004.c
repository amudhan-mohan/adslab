#include <stdio.h>
#define SIZE 50
int heap[SIZE], n = 0;
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
void heapify(int arr[], int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}
void insert(int v) {
    if (n == SIZE) {
        printf("Heap full\n");
        return;
    }
    int i = n++;
    heap[i] = v;
    while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(&heap[(i - 1) / 2], &heap[i]);
        i = (i - 1) / 2;
    }
}
void extractMax() {
    if (n == 0) {
        printf("Heap empty\n");
        return;
    }
    printf("Extracted max = %d\n", heap[0]);
    heap[0] = heap[--n];
    heapify(heap, n, 0);
}
void display() {
    printf("Heap: ");
    for (int i = 0; i < n; i++)
        printf("%d ", heap[i]);
    printf("\n");
}
void heapSort() {
    int t[SIZE], m = n;
    for (int i = 0; i < n; i++)
        t[i] = heap[i];
    for (int i = m / 2 - 1; i >= 0; i--)
        heapify(t, m, i);
    for (int i = m - 1; i > 0; i--) {
        swap(&t[0], &t[i]);
        heapify(t, i, 0);
    }
    printf("Sorted (ascending): ");
    for (int i = 0; i < m; i++)
        printf("%d ", t[i]);
    printf("\n");
}
int main() {
    int ch, v;
    while (1) {
        printf("\n1.Insert 2.Extract Max 3.Display 4.Heap Sort 5.Exit: ");
        scanf("%d", &ch);
        if (ch == 1) {
               printf("Value: ");
               scanf("%d", &v);
               insert(v);
        } else if (ch == 2) extractMax();
        else if (ch == 3)
               display();
        else if (ch == 4)
               heapSort();
        else
            break;
    }
    return 0;
}
