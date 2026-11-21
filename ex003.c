#include <stdio.h>
#include <string.h>
#define SIZE 10
#define A 0.6180339887
typedef struct {
    int key;
    char val[30];
    int state;
} Entry;


Entry table[SIZE];
int h_div(int k) {
    return k % SIZE;
}
int h_mul(int k) {
    double x = k * A;
    return (int)(SIZE * (x - (int)x));
}
int hash(int k, int mul) {
    return mul ? h_mul(k) : h_div(k);
}
void insert(int k, char *v, int mul) {
    int i = hash(k, mul), start = i, firstFree = -1;
    do {
           if (table[i].state == 1 && table[i].key == k) {
               printf("Key already exists\n");
               return;
           }
           if (table[i].state != 1 && firstFree == -1)
               firstFree = i;


           if (table[i].state == 0)
               break;


           i = (i + 1) % SIZE;
    } while (i != start);
    if (firstFree == -1) {
           printf("Table full\n");
           return;
    }
    table[firstFree].key = k;
    strcpy(table[firstFree].val, v);
    table[firstFree].state = 1;
}
char *search(int k, int mul) {
    int i = hash(k, mul), start = i;
    do {
           if (table[i].state == 0)
               return NULL;
           if (table[i].state == 1 && table[i].key == k)
               return table[i].val;
           i = (i + 1) % SIZE;
    } while (i != start);
    return NULL;
}
void removeKey(int k, int mul) {
    int i = hash(k, mul), start = i;
    do {
           if (table[i].state == 0)
               break;
           if (table[i].state == 1 && table[i].key == k) {
               table[i].state = 2;
               printf("Deleted\n");
               return;
           }
           i = (i + 1) % SIZE;
    } while (i != start);
    printf("Key not found\n");
}
void display() {
    printf("\nIndex      Key   Value\n");
    for (int i = 0; i < SIZE; i++) {
           if (table[i].state == 1)
               printf("%-6d %-4d %s\n", i, table[i].key, table[i].val);
           else
               printf("%-6d ---    ---\n", i);
    }
}
int main() {
    int choice, k, method;
    char v[30];
    printf("Method? 1=Div 2=Mul: ");
    scanf("%d", &method);
    while (1) {
        printf("\n1.Insert 2.Search 3.Delete 4.Display 5.Exit: ");
        scanf("%d", &choice);
        if (choice == 1) {
               printf("Key: ");
               scanf("%d", &k);
               printf("Value: ");
               scanf("%s", v);
               insert(k, v, method == 2);
        } else if (choice == 2) {
               printf("Key: ");
               scanf("%d", &k);
               char *r = search(k, method == 2);
               if (r)
                      printf("Found %s\n", r);
               else
                      printf("Not found\n");
        } else if (choice == 3) {
               printf("Key: ");
               scanf("%d", &k);
               removeKey(k, method == 2);
        } else if (choice == 4) display();
        else
               break;
    }
    return 0;
}
