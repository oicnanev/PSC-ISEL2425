#include <curl/curl.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"

// Reutilizando o WriteMemoryCallback do exemplo anterior
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    char **response_ptr = (char **)userp;

    if (*response_ptr) {
        free(*response_ptr);
    }

    *response_ptr = strndup(contents, realsize);
    return realsize;
}

// Função HTTP GET reutilizada do exemplo anterior
json_t *http_get_json(const char *url);

// Função HTTP POST reutilizada do exemplo anterior
bool http_post_json(const char *url, json_t *data);

Products *products_get() {
    const char *url = "https://dummyjson.com/products";
    json_t *json = http_get_json(url);

    if (!json) {
        return NULL;
    }

    json_t *products_array = json_object_get(json, "products");
    if (!json_is_array(products_array)) {
        json_decref(json);
        return NULL;
    }

    size_t count = json_array_size(products_array);
    Products *products = malloc(sizeof(Products));
    products->count = count;
    products->items = malloc(count * sizeof(Product));

    for (size_t i = 0; i < count; i++) {
        json_t *product_json = json_array_get(products_array, i);
        products->items[i].id = json_integer_value(json_object_get(product_json, "id"));
        products->items[i].price = json_real_value(json_object_get(product_json, "price"));
        const char *description = json_string_value(json_object_get(product_json, "description"));
        const char *category = json_string_value(json_object_get(product_json, "category"));
        products->items[i].description = description ? strdup(description) : NULL;
        products->items[i].category = category ? strdup(category) : NULL;
    }

    json_decref(json);
    return products;
}

Users *users_get() {
    const char *url = "https://dummyjson.com/users";
    json_t *json = http_get_json(url);

    if (!json) {
        return NULL;
    }

    json_t *users_array = json_object_get(json, "users");
    if (!json_is_array(users_array)) {
        json_decref(json);
        return NULL;
    }

    size_t count = json_array_size(users_array);
    Users *users = malloc(sizeof(Users));
    users->count = count;
    users->items = malloc(count * sizeof(User));

    for (size_t i = 0; i < count; i++) {
        json_t *user_json = json_array_get(users_array, i);
        users->items[i].id = json_integer_value(json_object_get(user_json, "id"));
        const char *name = json_string_value(json_object_get(user_json, "name"));
        users->items[i].name = name ? strdup(name) : NULL;
    }

    json_decref(json);
    return users;
}

bool cart_put(Cart *cart) {
    const char *url = "https://dummyjson.com/carts/add";
    json_t *root = json_object();
    json_t *products_array = json_array();

    json_object_set_new(root, "userId", json_integer(cart->user_id));

    for (size_t i = 0; i < cart->n_products; i++) {
        json_t *product = json_object();
        json_object_set_new(product, "id", json_integer(cart->products[i].id));
        json_object_set_new(product, "quantity", json_integer(cart->products[i].quantity));
        json_array_append_new(products_array, product);
    }

    json_object_set_new(root, "products", products_array);

    bool success = http_post_json(url, root);

    json_decref(root);
    return success;
}
