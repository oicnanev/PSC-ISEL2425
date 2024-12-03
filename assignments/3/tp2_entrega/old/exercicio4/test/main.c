#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include "types.h"

extern Products *products_get();
extern Users *users_get();
extern bool cart_put(Cart *cart);

int main() {
    Products *products = products_get();
    if (!products) {
        fprintf(stderr, "Erro ao obter produtos.\n");
        return 1;
    }

    // Exibir alguns produtos para teste
    printf("Produtos obtidos:\n");
    for (size_t i = 0; i < products->count; i++) {
        printf("ID: %d, Preço: %.2f, Descrição: %s, Categoria: %s\n",
               products->items[i].id, products->items[i].price,
               products->items[i].description, products->items[i].category);
    }
    // Libera a memória dos produtos
    free(products->items);
    free(products);

    Users *users = users_get();
    if (!users) {
        fprintf(stderr, "Erro ao obter utilizadores.\n");
        return 1;
    }

    // Exibir alguns utilizadores para teste
    printf("\nUtilizadores obtidos:\n");
    for (size_t i = 0; i < users->count; i++) {
        printf("ID: %d, Nome: %s\n", users->items[i].id, users->items[i].name);
    }
    // Libera a memória dos utilizadores
    free(users->items);
    free(users);

    // Carrinho de compras
    Cart *cart = malloc(sizeof(Cart) + sizeof(cart->products[0]) * 1);  // Aloca espaço para 1 produto
    if (!cart) {
        fprintf(stderr, "Erro de alocação de memória para o carrinho.\n");
        return 1;
    }

    cart->user_id = 1;
    cart->n_products = 1;
    cart->products[0].id = 144;
    cart->products[0].quantity = 4;

    if (!cart_put(cart)) {
        fprintf(stderr, "Erro ao enviar carrinho de compras.\n");
        free(cart);
        return 1;
    }

    printf("\nCarrinho de compras enviado com sucesso.\n");

    free(cart);  // Libera a memória alocada para o carrinho
    return 0;
}
