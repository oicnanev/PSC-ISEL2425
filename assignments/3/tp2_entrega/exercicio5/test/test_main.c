#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"

// Declaração das funções da biblioteca libpsc.so
extern Products *products_get();
extern Users *users_get();
extern bool cart_put(Cart *cart);

void listar_utilizadores(Users *users) {
    printf("\nListando utilizadores:\n");
    for (size_t i = 0; i < users->count; i++) {
        printf("ID: %d, Nome: %s\n", users->items[i].id, users->items[i].name);
    }
}

void listar_produtos(Products *products, const char *categoria, const char *criterio) {
    printf("\nListando produtos na categoria '%s' (%s):\n", categoria, criterio);
    for (size_t i = 0; i < products->count; i++) {
        if (strcmp(products->items[i].category, categoria) == 0 || strcmp(categoria, "todos") == 0) {
            printf("ID: %d, Descrição: %s, Preço: %.2f, Categoria: %s\n",
                   products->items[i].id, products->items[i].description,
                   products->items[i].price, products->items[i].category);
        }
    }
}

int main() {
    // Obter utilizadores e produtos
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

    // Testar a funcionalidade: Listar Utilizadores
    listar_utilizadores(users);

    // Testar a funcionalidade: Definir o utilizador corrente (usuário 1)
    printf("\nDefinindo o utilizador corrente como o usuário de ID 1:\n");
    cart.user_id = 1;
    printf("Utilizador corrente definido: %s\n", users->items[0].name);

    // Testar a funcionalidade: Listar produtos por categoria e critério
    printf("\nListando produtos na categoria 'eletrônicos' (por preço crescente):\n");
    listar_produtos(products, "eletrônicos", "preço crescente");

    // Testar a funcionalidade: Exibir carrinho de compras vazio
    printf("\nCarrinho de compras (vazio):\n");
    for (size_t i = 0; i < cart.n_products; i++) {
        printf("Produto ID: %d, Quantidade: %ld\n", cart.products[i].id, cart.products[i].quantity);
    }

    // Testar a funcionalidade: Adicionar produtos ao carrinho
    printf("\nAdicionando produtos ao carrinho:\n");
    cart.products[cart.n_products].id = 1;  // Produto 1
    cart.products[cart.n_products].quantity = 2; // Quantidade 2
    cart.n_products++;
    cart.products[cart.n_products].id = 3;  // Produto 3
    cart.products[cart.n_products].quantity = 1; // Quantidade 1
    cart.n_products++;

    // Testar a funcionalidade: Exibir carrinho com produtos
    printf("\nCarrinho de compras com produtos:\n");
    for (size_t i = 0; i < cart.n_products; i++) {
        printf("Produto ID: %d, Quantidade: %ld\n", cart.products[i].id, cart.products[i].quantity);
    }

    // Testar a funcionalidade: Finalizar a compra
    printf("\nFinalizando a compra...\n");
    if (cart.n_products > 0) {
        if (cart_put(&cart)) {
            printf("Compra finalizada com sucesso!\n");
        } else {
            printf("Erro ao finalizar a compra.\n");
        }
    } else {
        printf("Carrinho vazio! Não é possível finalizar a compra.\n");
    }

    // Limpeza da memória
    free(products->items);
    free(products);
    free(users->items);
    free(users);

    return 0;
}
