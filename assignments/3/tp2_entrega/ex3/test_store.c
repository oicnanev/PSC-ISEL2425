#include "store.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t n_products, n_users;

    // Get products
    //Product *products = products_get(&n_products);
    //if (products) {
        //printf("Products:\n");
        //for (size_t i = 0; i < n_products; i++) {
        //    printf("ID: %d, Price: %.2f, Description: %s, Category: %s\n",
        //           products[i].id, products[i].price, products[i].description, products[i].category);
        //}
        //free_products(products, n_products);
    //} else {
    //    fprintf(stderr, "Failed to fetch products\n");
    //}

    // Get users
    //User *users = users_get(&n_users);
    //if (users) {
    //    printf("Users:\n");
    //    for (size_t i = 0; i < n_users; i++) {
    //        printf("ID: %d, Name: %s\n", users[i].id, users[i].name);
    //    }
    //    free_users(users, n_users);
    //} else {
    //    fprintf(stderr, "Failed to fetch users\n");
    //}

    // Create and put cart
    Cart cart;
    cart.user_id = 1;  // Assuming user ID 1
    cart.n_products = 1;
    cart.products = malloc(cart.n_products * sizeof(*cart.products));
    if (cart.products == NULL) {
        fprintf(stderr, "Failed to allocate memory for cart products\n");
        return 1;
    }
    cart.products[0].id = 144;
    cart.products[0].quantity = 4;

    if (cart_put(&cart)) {
        printf("Cart successfully added.\n");
    } else {
        fprintf(stderr, "Failed to add cart.\n");
    }

    //free_cart(&cart);

    return 0;
}
