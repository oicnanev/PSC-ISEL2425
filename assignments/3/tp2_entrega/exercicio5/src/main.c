#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dlfcn.h>
#include "types.h"

// Declaração das funções da biblioteca libpsc.so
extern Products *products_get();
extern Users *users_get();
extern bool cart_put(Cart *cart);

void listar_utilizadores(Users *users) {
    printf("\nUtilizadores:\n");
    for (size_t i = 0; i < users->count; i++) {
        printf("ID: %d, Nome: %s\n", users->items[i].id, users->items[i].name);
    }
}

int comparar_preco_asc(const void *a, const void *b) {
    double diff = ((Product *)a)->price - ((Product *)b)->price;
    return (diff > 0) - (diff < 0);
}

int comparar_preco_desc(const void *a, const void *b) {
    double diff = ((Product *)b)->price - ((Product *)a)->price;
    return (diff > 0) - (diff < 0);
}

void listar_produtos(Products *products, const char *categoria, const char *criterio) {
    Product *produtos_filtrados = malloc(products->count * sizeof(Product));
    size_t count = 0;

    for (size_t i = 0; i < products->count; i++) {
        if (strcmp(products->items[i].category, categoria) == 0 || strcmp(categoria, "todos") == 0) {
            produtos_filtrados[count++] = products->items[i];
        }
    }

    if (count == 0) {
        // Se a categoria não for encontrada, listar todos os produtos
        for (size_t i = 0; i < products->count; i++) {
            produtos_filtrados[i] = products->items[i];
        }
        count = products->count;
    }
    char *msg;
    if (strcmp(criterio, "<") == 0) {
        qsort(produtos_filtrados, count, sizeof(Product), comparar_preco_asc);
        msg = "preço crescente";
    } else if (strcmp(criterio, ">") == 0) {
        qsort(produtos_filtrados, count, sizeof(Product), comparar_preco_desc);
        msg = "preço decrescente";
    }

    printf("\nProdutos na categoria '%s' (%s):\n", categoria, msg);
    for (size_t i = 0; i < count; i++) {
        printf("ID: %d, Descrição: %s, Preço: %.2f, Categoria: %s\n",
               produtos_filtrados[i].id, produtos_filtrados[i].description,
               produtos_filtrados[i].price, produtos_filtrados[i].category);
    }

    free(produtos_filtrados);
}

int main() {
    Users *users = users_get();
    if (!users) {
        fprintf(stderr, "Erro ao obter utilizadores.\n");
        return 1;
    }

    Products *products = products_get();
    if (!products) {
        fprintf(stderr, "Erro ao obter produtos.\n");
        free(users->items);
        free(users);
        return 1;
    }

    Cart cart = { .user_id = 0, .n_products = 0 };

    char command[256];
    char categoria[100], criterio[2];
    int user_id, produto_id, quantidade;

    printf("\n\n");
    printf(" ooooooooo.   .oooooo..o   .oooooo.         .oooooo..o     .      \n"); 
    printf("`888   `Y88. d8P'    `Y8  d8P'  `Y8b       d8P'    `Y8   .o8   \n");
    printf(" 888   .d88' Y88bo.      888               Y88bo.      .o888oo  .ooooo.   ooo d8b  .ooooo. \n");
    printf(" 888ooo88P'   `'Y8888o.  888                `'Y8888o.    888   d88' `88b `888''8P d88' `88b \n");
    printf(" 888              `'Y88b 888                    `'Y88b   888   888   888  888     888ooo888 \n");
    printf(" 888         oo     .d8P `88b    ooo       oo     .d8P   888 . 888   888  888     888    .o \n");
    printf("o888o        8''88888P'   `Y8bood8P'       8''88888P'   '888'  `Y8bod8P' d888b    `Y8bod8P'\n");
    printf("\n");
    
    while (1) {
        printf("\nComandos:");
        printf("\nUtilizadores \t\t\t - listar utilizadores");
        printf("\nuTilizadore <id> \t\t - usar utilizador com o id escolhido");
        printf("\nProdutos <categoria> <criterio>  - listar produtos, < (preço crescente), > (preço decrescente)");
        if (cart.user_id != 0) {
            printf("\nCarrinho \t\t\t - listar produtos que estão no carrinho");
            printf("\nCategoriasCarrinho \t\t - listar categorias de produtos que estão no carrinho");
            printf("\ncOmprar <produto> <quantidade> \t - adicionar produto ao carrinho");
            printf("\nFinalizar \t\t\t - finalizar compra");
        }
        printf("\nTerminar \t\t\t - terminar programa\n");
        printf("\nDigite um comando: ");

        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';  // Remove o newline no final da string

        if (strcmp(command, "Terminar") == 0) {
            break;
        }
        else if (strcmp(command, "Utilizadores") == 0) {
            listar_utilizadores(users);
        }
        else if (sscanf(command, "uTilizador %d", &user_id) == 1) {
            if (user_id > 0 && user_id <= users->count) {
                cart.user_id = user_id;
                printf("Bem vindo %s\n", users->items[user_id - 1].name);
            } else {
                printf("Utilizador com ID %d não encontrado.\n", user_id);
            }
        }
        else if (sscanf(command, "Produtos %s %s", categoria, criterio) == 2) {
            listar_produtos(products, categoria, criterio);
        }
        else if (strcmp(command, "Carrinho") == 0) {
            if (cart.user_id != 0) {
                printf("\nCarrinho de compras:\n");
                double total_a_pagar = 0.0;
                for (size_t i = 0; i < cart.n_products; i++) {
                    int produto_id = cart.products[i].id;
                    int quantidade = cart.products[i].quantity;
                    double preco = 0.0;

                    // Encontrar o preço do produto no array de produtos
                    for (size_t j = 0; j < products->count; j++) {
                        if (products->items[j].id == produto_id) {
                            preco = products->items[j].price;
                            break;
                        }
                    }

                    double preco_total = preco * quantidade;
                    printf("Produto ID: %d, Preço: %.2f$, Quantidade: %d, Preço total: %.2f$\n", produto_id, preco, quantidade, preco_total);
                    total_a_pagar += preco_total;
                }
                printf("\nTotal a pagar: %.2f$\n", total_a_pagar);
            } else {
                printf("Por favor, faça login primeiro usando o comando 'uTilizador <id>'.\n");
            }
        }
        else if (strcmp(command, "CategoriasCarrinho") == 0) {
            if (cart.user_id != 0) {
                void *handler = dlopen("./plugins/libcatcard.so", RTLD_NOW);
                if (!handler) {
                    fprintf(stderr, "Erro ao carregar plugin/ ou função ainda em desenvolvimento\n");
                } else {
                    void (*categcard)() = (void (*)())dlsym(handler, "categcard"); 
                    const char *dlsym_error = dlerror(); 
                    if (dlsym_error) { 
                        fprintf(stderr, "Erro ao localizar símbolo: %s\n", dlsym_error); 
                    } else {
                        (*categcard)();
                    }
                    dlclose(handler);
                }
            } else {
                printf("Por favor, faça login primeiro usando o comando 'uTilizador <id>'.\n");
            }
        }
        else if (sscanf(command, "cOmprar %d %d", &produto_id, &quantidade) == 2) {
            if (cart.user_id != 0) {
                if (produto_id > 0 && produto_id <= products->count) {
                    cart.products[cart.n_products].id = produto_id;
                    cart.products[cart.n_products].quantity = quantidade;
                    cart.n_products++;
                    printf("Produto adicionado ao carrinho.\n");
                } else {
                    printf("Produto com ID %d não encontrado.\n", produto_id);
                }
            } else {
                printf("Por favor, faça login primeiro usando o comando 'uTilizador <id>'.\n");
            }
        }
        else if (strcmp(command, "Finalizar") == 0) {
            if (cart.user_id != 0) {
                if (cart.n_products > 0) {
                    double total_a_pagar = 0.0;
                    for (size_t i = 0; i < cart.n_products; i++) {
                        int produto_id = cart.products[i].id;
                        int quantidade = cart.products[i].quantity;
                        double preco = 0.0;

                        // Encontrar o preço do produto no array de produtos
                        for (size_t j = 0; j < products->count; j++) {
                            if (products->items[j].id == produto_id) {
                                preco = products->items[j].price;
                                break;
                            }
                        }

                        double preco_total = preco * quantidade;
                        total_a_pagar += preco_total;
                    }
                    printf("Compra finalizada com sucesso! O utilizador %s pagou um total de %.2f$.\n", users->items[cart.user_id - 1].name, total_a_pagar);
                    // Limpar o carrinho
                    cart.n_products = 0;
                } else {
                    printf("Carrinho vazio! Não é possível finalizar a compra.\n");
                }
            } else {
                printf("Por favor, faça login primeiro usando o comando 'uTilizador <id>'.\n");
            }
        }
        else {
            printf("Comando inválido!\n");
        }
    }

    // Libertar a memória alocada
    free(products->items);
    free(products);
    free(users->items);
    free(users);

    return 0;
}
