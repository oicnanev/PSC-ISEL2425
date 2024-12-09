#include <stdio.h>

#define INC_BAD(x)      x+1
#define INC_GOOD(x)     ((x)+1)
#define DOUBLE_BAD(x)   (x * x)
#define DOUBLE_GOOD(x)  ((x) * (x))
#define PRINT_EXP(exp1, exp2)	\
    printf(#exp1" = %d\n", c##exp2)

int main() {
    int c1 = INC_BAD(2) * 3;
    int c2 = INC_GOOD(2) * 3;
    int c3 = DOUBLE_BAD(c2 + 1);
    int c4 = DOUBLE_GOOD(c2 + 1);
    PRINT_EXP(c1, 1);
    PRINT_EXP(c2, 2);
    PRINT_EXP(c3, 3);
    PRINT_EXP(c4, 4);
    return 0;
}