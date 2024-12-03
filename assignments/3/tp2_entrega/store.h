#ifndef _STORE_H
#define _STORE_H

#include <stdbool.h>
#include <jansson.h>
#include <stddef.h>

// Structures
typedef struct {
    int id;
    float price;
    const char *description;
    const char *category;
} Product;

typedef struct {
    int id;
    const char *name;
} User;

typedef struct {
    int user_id;
    size_t n_products;
    struct {
        int id;
        size_t quantity;
    } *products;
} Cart;

// Functions
Product *products_get(size_t *n_products);
User *users_get(size_t *n_users);
bool cart_put(const Cart *cart);

void free_products(Product *products, size_t n_products);
void free_users(User *users, size_t n_users);
void free_cart(Cart *cart);

#endif /* _STORE_H */
