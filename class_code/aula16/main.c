#include "../common.h"

void aprint(int a[], int size);
int asum(int a[], int size);

int main() {
    int a1[] = {1, 2, 3, 4};
    int sum = asum(a1, ARRAY_SIZE(a1));
    aprint(a1, ARRAY_SIZE(a1));
    printf("Sum of a1=%d\n", sum);    
    return 0;
}