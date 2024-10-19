#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

// Definições das estruturas conforme especificado
typedef struct data {
    short flags:6;
    short length:10;
    short vals[];
} data_t;

typedef struct info {
    double ref;
    struct data **data;
    int valid;
} info_t;

// Declaração da função Assembly
extern short* get_val_ptr(info_t items[], size_t item_idx, size_t data_idx, size_t val_idx, short mask);

// Função para criar e inicializar a estrutura data
data_t* create_data(short flags, short length, short vals[]) {
    data_t* d = (data_t*) malloc(sizeof(data_t) + length * sizeof(short));
    d->flags = flags;
    d->length = length;
    for (int i = 0; i < length; i++) {
        d->vals[i] = vals[i];
    }
    return d;
}

// Função principal para testar a função Assembly
int main() {
    // Definir valores
    short vals1[] = {10, 20, 30, 40};
    data_t* data1 = create_data(0x3F, 4, vals1); // flags: 0x3F, length: 4
    data_t* data_array1[] = {data1};
    info_t items[] = {{1.23, data_array1, 1}}; // valid: 1

    // Definir índices e máscara
    size_t item_idx = 0;
    size_t data_idx = 0;
    size_t val_idx = 2;
    short mask = 0x3F;

    // Invocar a função Assembly
    short *result = get_val_ptr(items, item_idx, data_idx, val_idx, mask);

    // Verificar e imprimir o resultado
    if (result) {
        printf("Valor encontrado: %d\n", *result);
    } else {
        printf("Valor não encontrado ou inválido.\n");
    }

    // Liberar memória
    free(data1);

    return 0;
}

