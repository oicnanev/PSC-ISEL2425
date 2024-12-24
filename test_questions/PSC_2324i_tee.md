# PSC - Teste 2023/24 Época Especial, Inverno

## 1. Programe, em linguagem C, a função find que procura em array, o valor indicado em value. array é um array de valores inteiros, de dimensão array_size, ordenado por ordem crescente. A função devolve a indicação booleana sobre o êxito da procura e assinala, através de place, o local do array onde encontrou, ou deveria ter encontrado, o valor procurado. place aponta para um ponteiro para uma posição de array.

```c
int find(int array[], size_t array_size, int value, int **place);
```


Para implementar a função `find` em C, usamos a busca binária, que é eficiente para arrays ordenados. A busca binária reduz pela metade o espaço de busca a cada iteração, resultando em uma complexidade de tempo de \(O(\log n)\). 

```c
#include <stdio.h>
#include <stdbool.h>

int find(int array[], size_t array_size, int value, int **place) {
    int left = 0;
    int right = array_size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (array[mid] == value) {
            *place = &array[mid];
            return true;
        } else if (array[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Se não encontrado, place aponta para a posição onde deveria estar
    *place = &array[left];
    return false;
}
```

### Explicação do Código:

1. **Inicialização**:
   - `left` e `right` definem os limites do array que estão sendo buscados.
   - `mid` é calculado como o meio do intervalo atual.

2. **Busca Binária**:
   - Se o valor no meio (`array[mid]`) for igual ao valor procurado (`value`), retorna `true` e `place` aponta para a posição encontrada.
   - Se o valor no meio for menor que o valor procurado, ajusta `left` para `mid + 1` para continuar a busca na metade direita.
   - Se o valor no meio for maior que o valor procurado, ajusta `right` para `mid - 1` para continuar a busca na metade esquerda.

3. **Valor Não Encontrado**:
   - Se o valor não for encontrado, `place` aponta para a posição onde o valor deveria estar, que é `left`.
   - Retorna `false` indicando que o valor não foi encontrado.

4. **Função Principal (`main`)**:
   - Demonstra como usar a função `find`.
   - O array é inicializado e a função `find` é chamada com um valor de exemplo (`value`).

Este código implementa a função `find` de forma eficiente para um array ordenado, utilizando busca binária e assegurando a correta manipulação de ponteiros.

## 2. Programe, em linguagem C, a função get_basename que devolve o ponteiro para o nome do ficheiro contido num caminho formado por uma sequência de diretorias. Exemplos: se path for “/usr/bin/zip” devolve “zip”; se path for “a.out” devolve “a.out”; se path for “serie1/exercise1/strcmp.c” devolve “strcmp.c”.

```c
char *get_basename(char *path);
```


```c
#include <string.h>

char *get_basename(char *path) {
    // Procurar a última ocorrência de '/'
    char *basename = strrchr(path, '/');
    
    // Se '/' for encontrado, retornar o próximo caractere após a última '/'
    if (basename) {
        return basename + 1;
    }
    
    // Se '/' não for encontrado, retornar o próprio path
    return path;
}
```

### Explicação do Código

1. **`#include <string.h>`**:
   - Inclui a biblioteca de manipulação de strings.

2. **`char *get_basename(char *path)`**:
   - Define a função `get_basename` que aceita um ponteiro para uma string `path` e retorna um ponteiro para a base do nome do ficheiro.

3. **`char *basename = strrchr(path, '/');`**:
   - Utiliza a função `strrchr` para encontrar a última ocorrência do caractere `'/'` no caminho. `strrchr` retorna um ponteiro para a última ocorrência de `'/'` ou `NULL` se não for encontrada.

4. **Verificação da Presença de `'/'`**:
   - Se `strrchr` encontrou um `'/'`, `basename + 1` retorna o próximo caractere após a última `/`, ou seja, o nome do ficheiro.
   - Se `strrchr` não encontrou um `'/'`, significa que o caminho é apenas o nome do ficheiro, então retorna o próprio `path`.

## 3. Programe em assembly x86-64 a função data_equal, cuja definição em linguagem C se apresenta a seguir.

```c
typedef struct { 
	char label[16]; 
	short value; 
} Data;

typedef struct { 
	const char *set_id; 
	unsigned set_len; 
	Data **data; 
} Data_set;

int data_equal(Data_set *s1, Data_set *s2, unsigned index) {
	if (index > s1‐>set_len || index > s2‐>set_len)
		return 0;
	return s1‐>data[index]‐>value == s2‐>data[index]‐>value;
}
```

Claro! Vamos detalhar a função `data_equal` em assembly x86-64 e desenhar as estruturas em memória para entender melhor os endereços. Começaremos com um esboço das estruturas:

### Estruturas em Memória

#### Estrutura `Data`
```c
typedef struct {
    char label[16]; // 16 bytes
    short value;    // 2 bytes
} Data;
```

#### Estrutura `Data_set`
```c
typedef struct {
    const char *set_id; // 8 bytes (ponteiro)
    unsigned set_len;   // 4 bytes
    Data **data;        // 8 bytes (ponteiro para ponteiro)
} Data_set;
```

### Função `data_equal` em C
Vamos fazer um esboço da função `data_equal` em C antes de passar para assembly:

```c
int data_equal(Data_set *s1, Data_set *s2, unsigned index) {
    if (index > s1->set_len || index > s2->set_len)
        return 0;
    return s1->data[index]->value == s2->data[index]->value;
}
```

### Função `data_equal` em Assembly x86-64

A função em assembly x86-64:

```assembly
section .text
    global data_equal

data_equal:
    ; Prologue
    push rbp
    mov rbp, rsp
    sub rsp, 32 ; espaço para variáveis locais

    ; Parâmetros
    ; s1 -> rdi
    ; s2 -> rsi
    ; index -> edx

    ; Carregar s1->set_len em eax
    mov eax, [rdi + 8]
    ; Comparar index com s1->set_len
    cmp edx, eax
    ; Se index > s1->set_len, retornar 0
    ja  .not_equal

    ; Carregar s2->set_len em eax
    mov eax, [rsi + 8]
    ; Comparar index com s2->set_len
    cmp edx, eax
    ; Se index > s2->set_len, retornar 0
    ja  .not_equal

    ; Carregar s1->data[index] em rax
    mov rax, [rdi + 16]    ; rax = s1->data
    mov rax, [rax + rdx*8] ; rax = s1->data[index]

    ; Carregar s2->data[index] em rcx
    mov rcx, [rsi + 16]    ; rcx = s2->data
    mov rcx, [rcx + rdx*8] ; rcx = s2->data[index]

    ; Comparar s1->data[index]->value com s2->data[index]->value
    movzx eax, word [rax + 16] ; eax = s1->data[index]->value
    movzx ecx, word [rcx + 16] ; ecx = s2->data[index]->value
    cmp eax, ecx
    jne .not_equal

    ; Se os valores forem iguais, retornar 1
    mov eax, 1
    jmp .end

.not_equal:
    ; Se os valores não forem iguais, retornar 0
    xor eax, eax

.end:
    ; Epilogue
    mov rsp, rbp
    pop rbp
    ret
```

### Desenho das Estruturas em Memória

#### `Data` Estrutura em Memória

| Offset | Campo   | Tamanho |
|--------|---------|---------|
| 0      | label   | 16 bytes|
| 16     | value   | 2 bytes |
| 18	 | [dummy] | 6 bytes |

#### `Data_set` Estrutura em Memória

| Offset | Campo   | Tamanho |
|--------|---------|---------|
| 0      | set_id  | 8 bytes |
| 8      | set_len | 4 bytes |
| 12	 | [dummy] | 4 bytes |
| 16     | data    | 8 bytes |

### Resumo
A função `data_equal` compara o valor de dois elementos em um array de estruturas `Data`, indexados pelo campo `data` de duas estruturas `Data_set`. Utiliza-se a busca e comparação de valores em memória para determinar se os valores são iguais ou não, e retorna 1 (igual) ou 0 (diferente).

## 4 Considere a função comb_sort e o tipo Student, cujas definições, em linguagem C, se apresentam a seguir.

```c
void comb_sort(void *items[], size_t nelems, int (*compar)(const void *, const void *)) {
size_t i, gap = nelems * 10 / 13;
for (i = 0; gap > 0 && i < nelems; gap = gap * 10 / 13)
for (i = 0; i + gap < nelems; i++)
if ((*compar)(items[i], items[gap + i]) > 0) {
void *tmp = items[i];
items[i] = items[i + gap];
items[i + gap] = tmp;
}
}
typedef struct student { int number; const char *name; } Student;
```

**a. Programe a função comb_sort em assembly x86-64.**

Vamos começar pela implementação da função `comb_sort` em assembly x86-64.

### Parte a: Implementação da função `comb_sort` em Assembly x86-64

A função `comb_sort` em assembly x86-64 é bastante desafiadora devido à manipulação de ponteiros e à necessidade de chamadas para funções de comparação. Abaixo está a implementação dessa função:

```assembly
section .data
section .bss
section .text
    global comb_sort

comb_sort:
    ; Prologue
    push rbp
    mov rbp, rsp
    sub rsp, 32

    ; Parâmetros
    ; items -> rdi
    ; nelems -> rsi
    ; compar -> rdx

    mov rcx, rsi               ; rcx = nelems
    imul rcx, rcx, 10
    idiv rcx, 13               ; gap = nelems * 10 / 13
    mov r8, rcx                ; r8 = gap

.outer_loop:
    cmp r8, 0
    jle .end_outer_loop

    xor r9, r9                 ; i = 0
.inner_loop:
    lea r10, [r9 + r8]
    cmp r10, rsi
    jge .next_gap

    ; Call compar(items[i], items[i + gap])
    mov rax, [rdi + r9*8]
    mov rbx, [rdi + r10*8]
    mov rdi, rax
    mov rsi, rbx
    call rdx

    cmp rax, 0
    jle .skip_swap

    ; Swap items[i] and items[i + gap]
    mov rax, [rdi + r9*8]
    mov rbx, [rdi + r10*8]
    mov [rdi + r9*8], rbx
    mov [rdi + r10*8], rax

.skip_swap:
    inc r9
    jmp .inner_loop

.next_gap:
    imul r8, r8, 10
    idiv r8, 13
    jmp .outer_loop

.end_outer_loop:
    ; Epilogue
    mov rsp, rbp
    pop rbp
    ret
```

**b. Escreva, em linguagem C, um programa de teste da função comb_sort que ordena um array de ponteiros para instâncias do tipo Student, por ordem alfabética dos respectivos nomes. No programa, deve explicitar a iniciação do array, a definição da função de comparação, a chamada à função comb_sort, assim como o código para mostrar o array ordenado na consola. **

Função `comb_sort` que ordena um array de ponteiros para instâncias do tipo `Student` por ordem alfabética dos respectivos nomes.

```c
#include <stdio.h>
#include <string.h>

typedef struct student {
    int number;
    const char *name;
} Student;

int compare_students(const void *a, const void *b) {
    Student *student_a = *(Student **)a;
    Student *student_b = *(Student **)b;
    return strcmp(student_a->name, student_b->name);
}

void comb_sort(void *items[], size_t nelems, int (*compar)(const void *, const void *));

int main() {
    Student s1 = {1, "Charlie"};
    Student s2 = {2, "Alice"};
    Student s3 = {3, "Bob"};
    Student *students[] = {&s1, &s2, &s3};
    size_t nelems = sizeof(students) / sizeof(students[0]);

    // Ordenar o array de estudantes
    comb_sort((void **)students, nelems, compare_students);

    // Mostrar o array ordenado
    printf("Students sorted by name:\n");
    for (size_t i = 0; i < nelems; i++) {
        printf("Number: %d, Name: %s\n", students[i]->number, students[i]->name);
    }

    return 0;
}
```

### Explicação do Código em C

1. **Estrutura `Student`**:
   - Define uma estrutura para representar os estudantes.

2. **Função `compare_students`**:
   - Função de comparação para comparar os nomes dos estudantes.

3. **Função `comb_sort`**:
   - Declaração da função `comb_sort` para ser usada no código.

4. **Função `main`**:
   - Inicializa um array de ponteiros para instâncias de `Student`.
   - Chama a função `comb_sort` para ordenar o array.
   - Exibe o array ordenado na consola.

### Conclusão

A função `comb_sort` foi programada em assembly x86-64, e um programa de teste em C foi escrito para ordenar um array de ponteiros para instâncias do tipo `Student` por ordem alfabética dos respectivos nomes. A solução cobre a inicialização do array, a definição da função de comparação, a chamada à função `comb_sort` e o código para mostrar o array ordenado.

## 5. Considere o conteúdo dos ficheiros fonte f1.c e f2.c.

```c
/* f1.c */
int a = 2;
static int b;
extern int c;
void y(int);
void d(int);

void x(int x, int y) {
	a += x;
	b += y;
	d(c);
}

int main() {
	y(a);
}
```


```c
/* f2.c */
int a = 2;
int b = 1;
int d;

void x(int, int, int);

void y(int c) {
	a += b;
	x(a, b, c);
	b += 1;
}
```

### a. Indique o conteúdo das tabelas de símbolos dos ficheiros objecto relocáveis resultantes da compilação de f1.c e f2.c. Para cada símbolo, indique o nome, a secção e o respectivo âmbito (local ou global). Pode usar as convenções do utilitário nm.

### a. Tabelas de Símbolos

#### Tabela de Símbolos para f1.o

| Nome | Secção       | Âmbito   |
|------|--------------|----------|
| a    | .data        | Global   |
| b    | .bss         | Local    |
| c    | U (undefined)| Global   |
| y    | U (undefined)| Global   |
| d    | U (undefined)| Global   |
| x    | .text        | Global   |
| main | .text        | Global   |

Explicação:
- `a`: Variável global inicializada na secção `.data`.
- `b`: Variável estática (local) não inicializada na secção `.bss`.
- `c`: Variável externa (undefined) referenciada.
- `y`: Função externa (undefined) referenciada.
- `d`: Função externa (undefined) referenciada.
- `x`: Função definida globalmente na secção `.text`.
- `main`: Função definida globalmente na secção `.text`.

#### Tabela de Símbolos para f2.o

| Nome | Secção       | Âmbito   |
|------|--------------|----------|
| a    | .data        | Global   |
| b    | .data        | Global   |
| d    | .bss         | Global   |
| x    | U (undefined)| Global   |
| y    | .text        | Global   |

Explicação:
- `a`: Variável global inicializada na secção `.data`.
- `b`: Variável global inicializada na secção `.data`.
- `d`: Variável global não inicializada na secção `.bss`.
- `x`: Função externa (undefined) referenciada.
- `y`: Função definida globalmente na secção `.text`.

### b. Identifique e justifique erros de ligação entre os módulos f1.o e f2.o.

Erros de Ligação

1. **Duplicação de Variáveis Globais `a`**:
   - Ambos os módulos, `f1.o` e `f2.o`, definem a variável global `a` na secção `.data`. Isso resulta em um conflito de múltiplas definições de `a` durante a ligação.

2. **Referências Externas Não Satisfeitas**:
   - Em `f1.o`, as variáveis `c` e as funções `y` e `d` são referenciadas externamente, mas não são definidas em nenhum dos módulos. 
   - Em `f2.o`, a função `x` é referenciada externamente, mas não é definida em nenhum dos módulos.

## 6. Considere um programa que manipula um array de valores do tipo float, com 1024 elementos. Se este programa executar num sistema com uma cache de 32 KiByte de capacidade, 64 bytes de bloco e organização 16-way, indique a posição do array em que o sistema repete a utilização do mesmo set da cache que utiliza no acesso à primeira posição. Justifique

Vamos analisar o problema com base nas características da cache fornecidas:

1. **Capacidade da Cache**: 32 KiB (32 * 1024 bytes = 32,768 bytes)
2. **Tamanho do Bloco**: 64 bytes
3. **Organização**: 16-way set associative

### Cálculos:

1. **Número de Blocos na Cache**:
   - \( \frac{32,768 \text{ bytes}}{64 \text{ bytes por bloco}} = 512 \text{ blocos} \)

2. **Número de Sets na Cache**:
   - \( \frac{512 \text{ blocos}}{16 \text{ vias}} = 32 \text{ sets} \)

### Acesso à Primeira Posição:

- O primeiro elemento do array está no endereço 0 (considerando um endereço base de 0).
- Como cada posição do array `float` ocupa 4 bytes, 1024 elementos ocupam \( 1024 \times 4 = 4096 \text{ bytes} \).

### Determinação do Set:

Para determinar o set utilizado por um endereço, usamos o índice do set, que é dado por:

\[ \text{Set index} = \left( \frac{\text{Endereço} \, \text{do} \, \text{array}}{\text{Tamanho do bloco}} \right) \mod \text{Número de sets} \]

#### Endereço da Primeira Posição (Elemento 0):

- Endereço = 0
- Set index = \( \left( \frac{0}{64} \right) \mod 32 = 0 \)

#### Endereço de Posição \(i\) (Elemento \(i\)):

Para encontrar quando o mesmo set é reutilizado, precisamos encontrar o menor valor de \(i\) tal que:

\[ \left( \frac{i \times 4}{64} \right) \mod 32 = 0 \]

\[ \left( \frac{i}{16} \right) \mod 32 = 0 \]

Isso nos dá o menor valor de \(i\) que resulta em um inteiro múltiplo de 32 vezes o número de blocos por set (64/4 = 16):

\[ i = 32 \times 16 = 512 \]

### Justificação:

Ao acessar a posição 512 do array de `float`:
- O endereço é \( 512 \times 4 = 2048 \)
- O set index é \( \left( \frac{2048}{64} \right) \mod 32 = 32 \mod 32 = 0 \)

Portanto, a posição 512 do array reutiliza o mesmo set da cache que a primeira posição (posição 0) utiliza.

Em resumo, o sistema repete a utilização do mesmo set da cache que é usado no acesso à primeira posição do array na posição 512 do array. Isso ocorre devido ao alinhamento da memória e à organização da cache. 

## 7. Considere o tipo Vector como base para suportar a implementação de um vetor dinâmico de valores inteiros. Os dados do vetor - valores inteiros - são guardados em blocos de 100 elementos. O campo data aponta para um array de ponteiros. O primeiro ponteiro desse array aponta para o bloco que aloja os valores dos índices de 0 a 99, o segundo ponteiro aponta para o bloco qua aloja os valores dos índices de 100 a 199 e assim sucessivamente. Os blocos de suporte aos dados só devem ser alocados à medida que vão sendo necessários.

## A função vector_set_at afeta a posição indicada pelo parâmetro index com o valor value. Se o índice indicado estiver para além da capacidade atual do vetor, essa capacidade deve ser aumentada até à necessária, com a eventual alocação de memória.

## A função vector_shrink encolhe o vetor até ao índice indicado pelo parâmetro index. Se esse índice estiver aquém da capacidade atual, devem ser libertados os recursos de memória desnecessários.

## Implemente em linguagem C as funções descritas, acrescentando a struct vector os campos que considerar necessários para suportar a implementação dessas funções no cumprimento dos requisitos especificados.

```c
typedef struct vector { int **data; ... ; } Vector;
void vector_set_at(Vector *vector, int index, int value);
void vector_shrink(Vector *vector, int index);
```

Vamos implementar as funções `vector_set_at` e `vector_shrink` em linguagem C, utilizando uma estrutura `Vector` que suporte a alocação dinâmica dos blocos de memória conforme necessário. 

### Definição da Estrutura `Vector`
Vamos primeiro definir a estrutura `Vector`:

```c
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 100

typedef struct vector {
    int **data;      // Array de ponteiros para blocos de dados
    size_t size;     // Número total de elementos armazenados
    size_t capacity; // Capacidade atual em termos de blocos
} Vector;
```

### Implementação da Função `vector_set_at`

A função `vector_set_at` define o valor de um elemento no índice especificado e aumenta a capacidade do vetor se necessário:

```c
void vector_set_at(Vector *vector, int index, int value) {
    size_t block_index = index / BLOCK_SIZE;
    size_t element_index = index % BLOCK_SIZE;

    // Expandir a capacidade se necessário
    if (block_index >= vector->capacity) {
        size_t new_capacity = block_index + 1;
        vector->data = realloc(vector->data, new_capacity * sizeof(int *));
        for (size_t i = vector->capacity; i < new_capacity; ++i) {
            vector->data[i] = NULL;
        }
        vector->capacity = new_capacity;
    }

    // Alocar bloco se necessário
    if (vector->data[block_index] == NULL) {
        vector->data[block_index] = malloc(BLOCK_SIZE * sizeof(int));
        for (size_t i = 0; i < BLOCK_SIZE; ++i) {
            vector->data[block_index][i] = 0; // Inicializar com 0
        }
    }

    // Definir o valor
    vector->data[block_index][element_index] = value;

    // Atualizar o tamanho se necessário
    if (index >= vector->size) {
        vector->size = index + 1;
    }
}
```

### Implementação da Função `vector_shrink`

A função `vector_shrink` libera a memória desnecessária e ajusta a capacidade do vetor conforme especificado pelo índice:

```c
void vector_shrink(Vector *vector, int index) {
    if (index < 0 || index >= vector->size) {
        return; // Índice inválido
    }

    size_t block_index = index / BLOCK_SIZE + 1;

    // Liberar blocos desnecessários
    for (size_t i = block_index; i < vector->capacity; ++i) {
        if (vector->data[i] != NULL) {
            free(vector->data[i]);
            vector->data[i] = NULL;
        }
    }

    // Reduzir a capacidade
    vector->data = realloc(vector->data, block_index * sizeof(int *));
    vector->capacity = block_index;
    vector->size = index + 1;
}
```

### Exemplo de Uso

Aqui está um exemplo de como usar as funções `vector_set_at` e `vector_shrink`:

```c
int main() {
    Vector vector = {NULL, 0, 0};

    vector_set_at(&vector, 150, 42);
    vector_set_at(&vector, 250, 84);

    printf("Valor no índice 150: %d\n", vector.data[1][50]); // Deve imprimir 42
    printf("Valor no índice 250: %d\n", vector.data[2][50]); // Deve imprimir 84

    vector_shrink(&vector, 50);

    printf("Capacidade após encolher: %zu\n", vector.capacity); // Deve ser 1
    printf("Tamanho após encolher: %zu\n", vector.size); // Deve ser 51

    // Liberar memória restante
    for (size_t i = 0; i < vector.capacity; ++i) {
        free(vector.data[i]);
    }
    free(vector.data);

    return 0;
}
```

### Resumo

1. **Estrutura `Vector`**:
   - Define um vetor dinâmico com blocos de 100 elementos.

2. **Função `vector_set_at`**:
   - Define o valor de um elemento no índice especificado, aumentando a capacidade do vetor se necessário.

3. **Função `vector_shrink`**:
   - Encolhe o vetor até o índice especificado e libera a memória desnecessária.

4. **Exemplo de Uso**:
   - Demonstra como usar as funções `vector_set_at` e `vector_shrink`.

Essas implementações cumprem os requisitos especificados e suportam a alocação dinâmica de blocos de memória conforme necessário.
