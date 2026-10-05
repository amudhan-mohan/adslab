#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10
#define A 0.6180339887

typedef struct {
    int key;
    char val[30];
    int used;
} Entry;

Entry table[SIZE];

int h_div(int k) {
    return k % SIZE;
}

int h_mul(int k) {
    double x = k * A;
    double f = x - (int)x;
    return (int)(SIZE * f);
}

void insert(int k, char *v, int mul) {
    int i = mul ? h_mul(k) : h_div(k);
    int start = i;
    
    while (table[i].used) {
        i = (i + 1) % SIZE;
        if (i == start) {
            printf("Error: Hash Table is Full\n");
            return;
        }
    }
    
    table[i].key = k;
    strcpy(table[i].val, v);
    table[i].used = 1;
}

char* search(int k, int mul) {
    int i = mul ? h_mul(k) : h_div(k);
    int start = i;
    
    while (table[i].used) {
        if (table[i].key == k) return table[i].val;
        
        i = (i + 1) % SIZE;
        if (i == start) break;
    }
    return NULL;
}

void display() {
    printf("\nIndex\tKey\tValue\n");
    for (int i = 0; i < SIZE; i++) {
        if (table[i].used) {
            printf("%d\t%d\t%s\n", i, table[i].key, table[i].val);
        } else {
            printf("%d\t--------\n", i);
        }
    }
}

int main() {
    int choice, k, method;
    char v[30];

    printf("Method? (1=Division, 2=Multiplication): ");
    if (scanf("%d", &method) != 1) return 1;
    
    // Initialize table
    for (int i = 0; i < SIZE; i++) {
        table[i].used = 0;
    }

    while (1) {
        printf("\n1. Insert  2. Search  3. Display  4. Exit: ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            printf("Key: ");
            scanf("%d", &k);
            printf("Value: ");
            scanf("%29s", v); // Limit string input
            insert(k, v, method == 2);
            
        } else if (choice == 2) {
            printf("Key: ");
            scanf("%d", &k);
            char *res = search(k, method == 2);
            
            // Fixed printf logic
            if (res) {
                printf("Found: %s\n", res);
            } else {
                printf("Not found\n");
            }
            
        } else if (choice == 3) {
            display();
        } else {
            break;
        }
    }
    return 0;
}