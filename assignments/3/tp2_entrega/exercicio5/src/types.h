#ifndef TYPES_H
#define TYPES_H

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
    } products[];
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
