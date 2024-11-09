#include <stdio.h>
#include <stdlib.h>

// Definição das estruturas
typedef struct data {
    short flags:6;      // 6 bits para flags
    short length:10;    // 10 bits para length
    short *vals;        // array de valores
} data;

typedef struct info {
    double ref;          // ref (não utilizada aqui)
    struct data **data;  // ponteiro para array de ponteiros para `data`
    int valid;           // valid
} info;

// Declaração da função assembly
extern short *get_val_ptr(struct info items[], size_t item_idx, size_t data_idx, size_t val_idx, short mask);

// Alocar memória para os vals
short vals1[] = {10, 20, 30, 40, 50};
short vals2[] = {5, 15, 25};

// Criar array de structs 'data' e alocar memória para 'vals'
data data1 = {0b000001, 5, vals1};  // flags = 0b000001, length = 5
data data2 = {0b000010, 3, vals2};  // flags = 0b000010, length = 3
    
// Criar estrutura info com array de ponteiros para 'data'
data *data_arr[] = {&data1, &data2};
info items[1] = {
    { 1.0, data_arr, 1 }  // ref = 1.0, dados válidos e apontando para 'data_arr'
};


int main() {
    // Parâmetros para testar a função
    size_t item_idx = 0;
    size_t data_idx = 0;
    size_t val_idx = 2;     // Acessar o índice 2 de vals (valor = 30)
    short mask = 0b000001;  // Testar o bit 0 das flags (que é 1 em data1)
    
    // Chamar função assembly
    short *val_ptr = get_val_ptr(items, item_idx, data_idx, val_idx, mask);
    
    if (val_ptr != NULL) {
        printf("Valor encontrado: %d\n", *val_ptr);  // Deve imprimir 30
    } else {
        printf("Valor não encontrado ou condição falhou.\n");
    }
    
    // Teste com um valor inválido
    val_idx = 10;  // Índice fora do limite, deve retornar NULL
    val_ptr = get_val_ptr(items, item_idx, data_idx, val_idx, mask);
    
    if (val_ptr != NULL) {
        printf("Valor encontrado: %d\n", *val_ptr);
    } else {
        printf("Valor não encontrado ou condição falhou.\n");  // Esperado: "Valor não encontrado"
    }

    return 0;
}
