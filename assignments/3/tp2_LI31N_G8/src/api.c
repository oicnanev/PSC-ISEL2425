#include "types.h"
#include <curl/curl.h>
#include <jansson.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função HTTP GET 
json_t *http_get_json(const char *url);

// Função HTTP POST 
bool http_post_json(const char *url, json_t *data);


Products* products_get() {
    const char *url = "https://dummyjson.com/products?limit=0";
    json_t *root = http_get_json(url);

    if (!root) {
        return NULL;
    }

    Products *products = malloc(sizeof(Products));
    if (!products) {
        json_decref(root);
        return NULL;
    }

    json_t *products_array = json_object_get(root, "products");
    if (!products_array || !json_is_array(products_array)) {
        json_decref(root);
        free(products);
        return NULL;
    }

    size_t count = json_array_size(products_array);
    products->count = count;
    products->items = malloc(count * sizeof(Product));
    if (!products->items) {
        json_decref(root);
        free(products);
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        json_t *product_json = json_array_get(products_array, i);        
        
        const char *title = json_string_value(json_object_get(product_json, "title"));        
        const char *description = json_string_value(json_object_get(product_json, "description"));
        const char *category = json_string_value(json_object_get(product_json, "category"));
        double discountPercentage = json_real_value(json_object_get(product_json, "discountPercentage"));
        long stock = json_integer_value(json_object_get(product_json, "stock")); 

        products->items[i].id = json_integer_value(json_object_get(product_json, "id"));
        products->items[i].title = title ? strdup(title) : NULL;
        products->items[i].price = json_real_value(json_object_get(product_json, "price"));
        products->items[i].description = description ? strdup(description) : NULL;
        products->items[i].category = category ? strdup(category) : NULL;
        products->items[i].discountPercentage = discountPercentage ? discountPercentage : 0;
        products->items[i].stock = stock ? stock : 0;

    }

    json_decref(root);
    return products;
}

// Função para liberar memória alocada para Products
void free_products(Products *products) {
    if (products) {
        for (size_t i = 0; i < products->count; i++) {
            free((void *)products->items[i].description); // Cast explícito para void *
            free((void *)products->items[i].title);
            free((void *)products->items[i].category);
        }
        free(products->items);
        free(products);
    }
}

Users* users_get() {
    const char *url = "https://dummyjson.com/users?limit=0";
    json_t *root = http_get_json(url);

    if (!root) {
        return NULL;
    }

    Users *users = malloc(sizeof(Users));
    if (!users) {
        json_decref(root);
        return NULL;
    }

    json_t *users_array = json_object_get(root, "users");
    if (!users_array || !json_is_array(users_array)) {
        json_decref(root);
        free(users);
        return NULL;
    }

    size_t count = json_array_size(users_array);
    users->count = count;
    users->items = malloc(count * sizeof(User));
    if (!users->items) {
        json_decref(root);
        free(users);
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        json_t *user_json = json_array_get(users_array, i);
        users->items[i].id = json_integer_value(json_object_get(user_json, "id"));

        // Inicializar o carrinho do usuário 
        users->items[i].cart.n_products = 0; 
        memset(users->items[i].cart.products, 0, sizeof(users->items[i].cart.products));
        
        const char *first_name = json_string_value(json_object_get(user_json, "firstName"));
        const char *last_name = json_string_value(json_object_get(user_json, "lastName"));

        if (first_name && last_name) {
            size_t name_len = strlen(first_name) + strlen(last_name) + 2;
            char *full_name = (char *)malloc(name_len);
            snprintf(full_name, name_len, "%s %s", first_name, last_name);
            users->items[i].name = full_name;
        } else if (first_name) {
            users->items[i].name = strdup(first_name);
        } else if (last_name) {
            users->items[i].name = strdup(last_name);
        } else {
            users->items[i].name = NULL;
        }
    }

    json_decref(root);
    return users;
}

// Função para liberar memória alocada para Users
void free_users(Users *users) {
    if (users) {
        for (size_t i = 0; i < users->count; i++) {
            free((void *)users->items[i].name);  // Cast explícito para void *
        }
        free(users->items);
        free(users);
    }
}

bool cart_put(Cart *cart) {
  const char *url = "https://dummyjson.com/carts/add";
  json_t *root = json_object();
  json_t *products_array = json_array();

  json_object_set_new(root, "userId", json_integer(cart->user_id));

  for (size_t i = 0; i < cart->n_products; i++) {
    json_t *product = json_object();
    json_object_set_new(product, "id", json_integer(cart->products[i].id));
    json_object_set_new(product, "quantity",
                        json_integer(cart->products[i].quantity));
    json_array_append_new(products_array, product);
  }

  json_object_set_new(root, "products", products_array);

  bool success = http_post_json(url, root);

  json_decref(root);
  return success;
}
