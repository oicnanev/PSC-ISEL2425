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

void listar_produtos(Products *products, const char *categoria, const char *criterio) {
    printf("\nProdutos na categoria '%s' (%s):\n", categoria, criterio);
    for (size_t i = 0; i < products->count; i++) {
        if (strcmp(products->items[i].category, categoria) == 0 || strcmp(categoria, "todos") == 0) {
            printf("ID: %d, Descrição: %s, Preço: %.2f, Categoria: %s\n",
                   products->items[i].id, products->items[i].description,
                   products->items[i].price, products->items[i].category);
        }
    }
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

    printf("\n--- Dummy Json Store ---\n")
    
    while (1) {
        printf("\nComandos:");
        printf("\nUtilizadores - listar utilizadores");
        printf("\nuTilizadore <id> - usar utilizador com o id escolhido");
        printf("\nProdutos <categoria> <criterio> - listar produtos, < (preço crescente), > (preço decrescente)");
        printf("\nCarrinho - listar produtos que estão no carrinho");
        printf("\nCategoriasCarrinho - listar categorias de produtos que estão no carrinho");
        printf("\n cOmprar <produto> <quantidade>");
        printf("\nFinalizar - finalizar comprar");
        printf("\nTerminar - terminar programa\n");
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
                printf("Utilizador corrente definido como: %s\n", users->items[user_id - 1].name);
            } else {
                printf("Utilizador com ID %d não encontrado.\n", user_id);
            }
        }
        else if (sscanf(command, "Produtos %s %s", categoria, criterio) == 2) {
            listar_produtos(products, categoria, criterio);
        }
        else if (strcmp(command, "Carrinho") == 0) {
            printf("\nCarrinho de compras:\n");
            for (size_t i = 0; i < cart.n_products; i++) {
                printf("Produto ID: %d, Quantidade: %d\n", cart.products[i].id, cart.products[i].quantity);
            }
        }
        else if (sscanf(command, "CategoriasCarrinho") == 0) {
            void *handler = dlopen("./pulgins/libcatcard.so", RTLD_NOW);
            if (!handler) {
                printf("Função ainda não implementada\n");
            } else {
                void (*categcard)() = (void (*)())dlsym(handle, "categcard"); 
                const char *dlsym_error = dlerror(); 
                if (dlsym_error) { 
                    fprintf(stderr, "Erro ao localizar símbolo: %s\n", dlsym_error); 
                    dlclose(handle);
                } else {
                    (*categcard)();
                }
            }
            dlclose(handle);
        }
        else if (sscanf(command, "cOmprar %d %d", &produto_id, &quantidade) == 2) {
            if (produto_id > 0 && produto_id <= products->count) {
                if (cart.n_products < 10) {
                    cart.products[cart.n_products].id = produto_id;
                    cart.products[cart.n_products].quantity = quantidade;
                    cart.n_products++;
                    printf("Produto adicionado ao carrinho.\n");
                } else {
                    printf("Carrinho de compras cheio!\n");
                }
            } else {
                printf("Produto com ID %d não encontrado.\n", produto_id);
            }
        }
        else if (strcmp(command, "Finalizar") == 0) {
            if (cart.n_products > 0) {
                printf("Compra finalizada com sucesso!\n");
                // TODO:apagar cart
                free(cart);
            } else {
                printf("Carrinho vazio! Não é possível finalizar a compra.\n");
            }
        }
        else {
            printf("Comando inválido!\n");
        }
    }

    // Liberando a memória alocada
    free(products->items);
    free(products);
    free(users->items);
    free(users);

    return 0;
}
