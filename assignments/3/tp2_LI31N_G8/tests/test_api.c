#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "types.h"

Products *products_get();
Users *users_get();
bool cart_put(Cart *cart);
void free_products(Products *products);
void free_users(Users *users);

void save_products_to_csv(const Products *products, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("fopen");
        return;
    }

    fprintf(file, "id,price,description,category\n");
    for (size_t i = 0; i < products->count; i++) {
        fprintf(file, "%d,%.2f,%s,%s\n",
                products->items[i].id,
                products->items[i].price,
                products->items[i].description,
                products->items[i].category);
    }

    fclose(file);
}


void save_users_to_csv(const Users *users, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("fopen");
        return;
    }

    fprintf(file, "id,name\n");
    for (size_t i = 0; i < users->count; i++) {
        fprintf(file, "%d,%s\n", users->items[i].id, users->items[i].name);
    }

    fclose(file);
}

int main() {
    // Obter e salvar produtos
    Products *products = products_get();
    if (products) {
        save_products_to_csv(products, "products.csv");
        printf("Products saved with success.\n");
        free_products(products);  // Liberando memória alocada para products
    } else {
        fprintf(stderr, "Failed to get products.\n");
    }

    // Obter e salvar utilizadores
    Users *users = users_get();
    if (users) {
        save_users_to_csv(users, "users.csv");
        printf("Users saved with success.\n");
        free_users(users);  // Liberando memória alocada para users
    } else {
        fprintf(stderr, "Failed to get users.\n");
    }

    // Testar cart_put
    size_t n_products = 1;
    Cart *cart = malloc(sizeof(Cart));
    if (!cart) {
        fprintf(stderr, "Failed to allocate memory for cart.\n");
        return 1;
    }

    cart->products = malloc(n_products * sizeof(*cart->products));
    if (!cart->products) {
        fprintf(stderr, "Failed to allocate memory for cart products.\n");
        free(cart);
        return 1;
    }

    cart->user_id = 1;
    cart->n_products = n_products;
    cart->products[0].id = 144;
    cart->products[0].quantity = 4;

    if (!cart_put(cart)) {
        fprintf(stderr, "Failed to put cart.\n");
    }

    free(cart->products);
    free(cart);

    return 0;
}
