#include "common.h"

void f0_count_ones();
void f1_alignment_and_endianness();
void f2_struct_fields_addr();
void f3_jmpxx();
void f4_arithmetics();
void f5_shifts();

int main() {
    printf("f0_count_ones() output:\n");
    f0_count_ones();
    printf("f4_arithmetics() output:\n");
    f4_arithmetics();
    printf("f5_logics() output:\n");
    f5_shifts();
    printf("f3_jmpxx() output:\n");
    f3_jmpxx();
    printf("f1_alignment_and_endianness() output:\n");
    f1_alignment_and_endianness();
    printf("f2_struct_fields_addr() output:\n");
    f2_struct_fields_addr();
    return 0;
}

int count_ones(ulong v) {
    // Conta o número de bits a 1 num inteiro do tipo long
    int cnt = 0;
    while (v) {
        cnt += v & 1;
        v >>= 1;
    }
    return cnt;
}
void f0_count_ones() {
    int n = count_ones(0x1234567890abcdef); // 32 bits a 1
    printf("count_ones(0x1234567890abcdef) return %d bit%s with value one\n", n, n==1 ? "": "s");
}

int v1 = 0x12345678;
long v2 = 0x1234567890abcdef;
void print_int_long_alignment(int * pv1, long * pv2) {
    printf("pv1=%p\n", (void*)pv1);
    printf("pv2=%p\n", (void*)pv2);
}
void print_int_long_lsb(int * pv1, long * pv2) {
    uchar * pc1 = (uchar *)pv1, *pc2 = (uchar*)pv2;
    printf("*pv1=0x%x\n", *pc1);
    printf("*pv2=0x%x\n", *pc2);
}
void f1_alignment_and_endianness() {
    // Representação de dados em memória: little-endian ou big-endian
    // Alinhamento de tipos de dados em memória
    int * pv1 = &v1;
    long * pv2 = &v2;

    print_int_long_alignment(pv1, pv2);
    print_int_long_lsb(pv1, pv2);
}

void print_struct_fields_addr(long * pa, int * pb, char * pc, char * pd, long * pe) {
    printf("Struct fields address:\n"
           "\t.a = %p\n"
           "\t.b = %p\n"
           "\t.c = %p\n"
           "\t.d = %p\n"
           "\t.e = %p\n"
           , (void*)pa, (void*)pb, (void*)pc, (void*)pd, (void*)pe);
}
struct {
    long a;
    int  b;
    char c;
    char d;
    long e;
} struct_ex = { 0x1, 0x2, 0x3, 0x4, 0x5 };
void f2_struct_fields_addr() {
    // Alinhamento dos campos de uma estrutura em memória
    long * pa = &struct_ex.a;
    int *  pb = &struct_ex.b;
    char * pc = &struct_ex.c;
    char * pd = &struct_ex.d;
    long * pe = &struct_ex.e;

    print_struct_fields_addr(pa, pb, pc, pd, pe);
}
/* Comparação de inteiros com sinal */
int int_cmp(int v1, int v2) {
    if (v1 < v2)
        return -1;
    if (v1 > v2)
        return 1;
    return 0;
}
/* Comparação de inteiros sem sinal */
int uint_cmp(uint v1, uint v2) {
    if (v1 < v2)
        return -1;
    if (v1 > v2)
        return 1;
    return 0;
}
void f3_jmpxx() {
    int r1 = int_cmp(-1, 20);
    int r2 = uint_cmp(-1, 20);
    printf("r1=%d, r2=%d\n", r1, r2);
}

/* Expressão aritmética com valores inteiros de diferentes tipos a produzir um valor do tipo long. */
long calc_expression_and_ret_long(int a, long b, char c) {
    long res = a + b + c;
    return res;
}
/* Expressão aritmética com valores inteiros de diferentes tipos a produzir um valor do tipo int. */
int calc_expression_and_ret_int(int a, long b, char c) {
    int res = (int)(a + b + c);
    return res;
}
/* Expressão aritmética com valores inteiros de diferentes tipos a produzir um valor do tipo short. */
short calc_expression_and_ret_short(int a, long b, char c) {
    short res = (short)(a + b + c);
    return res;
}
void f4_arithmetics() {
    long lres = calc_expression_and_ret_long(1, -3, 1);
    int  ires = calc_expression_and_ret_int(1, -3, 1);
    char cres = calc_expression_and_ret_short(1, -3, 1);

    printf("calc_expression_and_ret_long(1, -3, 1) = %ld\n", lres);
    printf("calc_expression_and_ret_int(1, -3, 1) = %d\n", ires);
    printf("calc_expression_and_ret_short(1, -3, 1) = %d\n", cres);
}

/* Deslocamento para a direita sem sinal */
int shift_right_uint(uint v, int n) {
    return v >> n;
}
/* Deslocamento para a direita com sinal */
int shift_right_int(int v, int n) {
    return v >> n;
}
/* Divisão inteira sem sinal implementada com deslocamento */
int divide_by_four_uint(uint v) {
    return v / 4;
}
/* Divisão inteira com sinal implementada com deslocamento */
int divide_by_four_int(int v) {
    return v / 4;
}
void f5_shifts() {
    int r1u = shift_right_uint(0x71234567, 12);
    int r1i = shift_right_int(0x71234567, 12);
    int r2u = shift_right_uint(0xC1234567, 12);
    int r2i = shift_right_int(0xC1234567, 12);
    printf("shift_right_uint(0x71234567, 12) return %d\n", r1u);
    printf("shift_right_int(0x71234567, 12) return %d\n", r1i);
    printf("shift_right_uint(0xC1234567, 12) return %d\n", r2u);
    printf("shift_right_int(0xC1234567, 12) return %d\n", r2i);

    int v1 = divide_by_four_uint(-8);
    int vints[] = {-8, 0xFFFFF01A, 0xFFFFFFFA, 0xFFFFFFFB, 0xFFFFFFFC, 0xFFFFFFFD, 0xFFFFFFFE, 0xFFFFFFFF };
    int vintsr[sizeof(vints) /sizeof (vints[0])];
    for (int i = 0; i < sizeof(vints) /sizeof (vints[0]); i++)
        vintsr[i] = divide_by_four_int(vints[i]);

    printf("divide_by_four_uint(-8) = %d\n", v1);
    for (int i = 0; i < sizeof(vints) /sizeof (vints[0]); i++)
        printf("divide_by_four_int(%d) = %d\n", vints[i], vintsr[i]);

}
