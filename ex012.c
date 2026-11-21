#include <stdio.h>
#include <string.h>
#define SIZE 29
int bitArray[SIZE] = {0};
unsigned int hash1(char *s) {
    unsigned long h = 5381;
    for (; *s; s++)
        h = (h * 33 + (unsigned char)*s) % SIZE;
    return h;
}
unsigned int hash2(char *s) {
    unsigned long h = 0;
    for (; *s; s++)
        h = (h * 31 + (unsigned char)*s) % SIZE;
    return h;
}
unsigned int hash3(char *s) {
    unsigned long h = 0;
    for (; *s; s++)
        h = (h * 131 + (unsigned char)*s) % SIZE;
    return h;
}
void insert(char *s) {
    bitArray[hash1(s)] = 1;
    bitArray[hash2(s)] = 1;
    bitArray[hash3(s)] = 1;
}
int search(char *s) {
    return bitArray[hash1(s)] && bitArray[hash2(s)] && bitArray[hash3(s)];
}
void display() {
    printf("\nBloom Filter:\n");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", bitArray[i]);
    printf("\n");
}
int main() {
    int n;
    char str[50];
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
           scanf("%s", str);
           insert(str);
    }
    display();
    printf("\nEnter element to search: ");
    scanf("%s", str);
    if (search(str))
           printf("%s may be present in the set.\n", str);
    else
           printf("%s is definitely not present in the set.\n", str);
    return 0;
}
