# Projeto de Simulação de Loja

## Instituto Superior de Engenharia de Lisboa
### Licenciatura em Engenharia Informática e de Computadores
### Programação de Sistemas Computacionais
### Inverno de 2024/2025 - Segundo Trabalho Prático

---

Este projeto é uma implementação de um programa de simulação de uma loja, que interage com a API web do site dummyJSON para trocar dados fictícios. A implementação foi realizada em linguagem C, utilizando as bibliotecas libcurl e jansson.

## Estrutura do Projeto

O projeto está organizado em seis diretórios, um para cada exercício descrito na Parte II do enunciado. Cada diretório contém o código fonte, makefile e bibliotecas necessárias para gerar os programas executáveis especificados.

## Requisitos de Instalação

### Bibliotecas Necessárias
- **libcurl**: Para suportar comunicações com o servidor usando o protocolo HTTP.

```bash
  sudo apt install libcurl4-gnutls-dev
```

- **Jansson**: Para interpretar as respostas do servidor em formato JSON

```bash
  sudo apt install libjansson-dev
```

- **Valgrind**: Para verificar se o programa liberta toda a memória alocada dinâmicamente
```bash
  sudo apt install valgrind
```

## Parte 1 - Preparação do Ambiente de desenvolvimento

O acesso à informação utiliza o protocolo HTTP para acessar os serviços definidos por uma API REST. A resposta ao pedido é codificada no formato JSON. A documentação da API está disponível em [dummyJSON API Documentation](https://dummyjson.com/docs).

## Parte 2 - Realização

### 1. Funções `json_t *http_get_json(const char *url)` e `bool http_post_json(const char *url, json_t *data)`

Juntamos estas 2 funções num ficheiro apenas, `http_utils.c`, que para além destas funções, tem ainda
a função `static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)` como auxiliar de operações com a memória.

A função `json_t *http_get_json(const char *url)` implementa um pedido HTTP GET ao URL especificado, retornando o ponteiro para uma instância do tipo `json_t` com o conteúdo da resposta. Em caso de erro, retorna `NULL` e mostra a razão do erro no `stderr`.

A função `bool http_post_json(const char *url, json_t *data)` implementa um pedido HTTP POST ao URL especificado, enviando dados no formato JSON. Em caso de erro, retorna `false` e mostra a razão do erro no `stderr`.

### 2. Funções `Products* products_get()`, `Users* users_get()` e `bool cart_put(Cart *cart)`

Para a implementação desta funções criamos 2 ficheiros:

- `types.h` - que contém as estruturas usadas durante o projeto
- `api.c` - que para além destas funções contém ainda duas funções de auxilio na libertação da memoria alocada
  - `free_products(Products *products)`
  - `free_users(Users *users)`

Como estruturas deste projeto usamos:

```c
typedef struct {
    int id;
    float price;
    const char *title;
    const char *description;
    const char *category;
    double discountPercentage;
    long stock;
} Product;

typedef struct {
    int id;
    const char *name;
    struct {
        size_t n_products;
        struct {
            int id;
            size_t quantity;
        } products[100]; // Supondo um limite de 100 produtos por carrinho
    } cart;
} User;

typedef struct {
    int user_id;
    size_t n_products;
    struct {
        int id;
        size_t quantity;
    } *products;
} Cart;

typedef struct {
    size_t count;
    Product *items;
} Products;

typedef struct {
    size_t count;
    User *items;
} Users;
```
### 3. Biblioteca de ligação dinâmica

Todas as funções implementadas foram organizadas em uma biblioteca de ligação dinâmica para evitar repetições de código e facilitar a manutenção.

### 4. Programa de comandos - psc_store

Desenvolve um programa que permanece em execução, aceitando e processando comandos para apresentação de informação na consola. Os comandos incluem listagem de utilizadores, gestão de produtos, carrinho de compras e finalização de compras.

### 5. Suporte a plug-ins

Modifica o programa de modo que possam ser acrescentados novos comandos na forma de plug-ins, incluindo um exemplo de comando que lista as categorias de produtos no carrinho, através do carregamento de bibliotecas em tempo de execução.

### 6. Construção do Makefile

Para construir o projeto em C que inclui tanto o executável principal `psc_store` bem como um programa de testes à API, `test_api`, além da biblioteca compartilhada, organizamos o Makefile em várias secções para facilitar a compilação, teste, intalação e limpeza do projeto.

#### Variáveis

- **TARGET**: Nome do executável principal (`psc_store`)
- **TEST_TARGET**: Nome do executável de teste à API (`test_api`)
- **CC**: Compilador a ser usado (`gcc`)
- **CFLAGS**: Flags de compilação (`-Wall -g`), ativando todos os avisos e a depuração.
- **LDFLAGS**: Flags de *linkagem* (`-lcurl -ljansson`), especificando as bibliotecas a serem linkadas.
- **SRC_DIR**: Pasta dos arquivos fonte (`src`)
- **OBJ_DIR**: Pasta dos arquivos objeto (`obj`)
- **BIN_DIR**: Pasta dos executáveis (`bin`)
- **INCLUDE_DIR**: Pasta dos arquivos de inclusão (`include`)
- **TEST_DIR**: Pasta dos arquivos fonte de teste (`tests`)
- **LIB_DIR**: Pasta da biblioteca (`lib`)

#### Ficheiros fonte e objetos

- **SRC**: Lista de ficheiros código fonte na pasta `src` (`$(wildcard $(SRC_DIR)/*.c)`)
- **OBJ**: Lista de ficheiros objeto correspondentes aos arquivos fonte `($(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o))`.
- **TEST_SRC**: Lista de ficheiros código fonte de teste na pasta tests `($(wildcard $(TEST_DIR)/*.c))`.
- **TEST_OBJ**: Lista de ficheiros objeto correspondentes aos arquivos de teste `($(TEST_SRC:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o))`.

#### Biblioteca Compartihada

- **LIBRARY**: Caminho para a biblioteca compartilhada `($(LIB_DIR)/libpsc.so)`.

#### Regras de compilação

- **all**: Regra principal que compila o executável principal, o executável de teste e a biblioteca compartilhada, além de instalar a biblioteca no sistema.
- **Compilar o Executável Principal**: Compila o executável principal a partir dos ficheiros objeto.
- **Compilar os Testes**: Compila o executável de teste a partir dos ficheiros objeto de teste.
- **Compilar a Biblioteca Compartilhada**: Compila a biblioteca compartilhada a partir dos ficheiros objeto.
- **Compilar os Ficheiros Objeto**: Compila os ficheiros objeto a partir dos ficheiros fonte.
- **Compilar os Ficheiros de Teste**: Compila os ficheiros objeto de teste a partir dos ficheiros fonte de teste.

#### Instalação

- **install**: Instala a biblioteca em `/usr/lib` e atualiza o cache do linker.

#### Limpeza

- **clean**: Remove os ficheiros objeto, executáveis e a biblioteca.

#### Phony targets

- **.PHONY**: Declara que `all`, `clean` e `install` são alvos de compilação e que não correspondem a ficheiros reais.

### Estrutura final do projeto

```txt
.
├── bin
│   ├── psc_store
│   └── test_api
├── include
│    ├── http_utils.h
│    └── types.h
├── lib
│    └── libpsc.so
├── Makefile
├── obj
│    ├── api.o
│    ├── http_utils.o
│    ├── main.o
│    └── test_api.o
├── README.md
├── src
│    ├── api.c
│    ├── http_utils.c
│    └── main.c
└── tests
    └── test_api.c

```

### Testes

Todos os programas e funções foram testados rigorosamente para assegurar a ausência de perdas de memória utilizando o utilitário **Valgrind**. O código foi desenvolvido para emitir todos os avisos com a opção `-Wall` do compilador.

### Conclusão

Este projeto simula uma loja que interage com uma API web para troca de dados fictícios. Asseguramos que o código é eficiente, claro, e livre de perdas de memória.



