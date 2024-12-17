#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>

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

#endif // TYPES_H
