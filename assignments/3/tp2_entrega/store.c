#include "store.h"
#include "http_get_and_post_json.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Function to get products information
Product *products_get(size_t *n_products) {
    const char *url = "https://dummyjson.com/products";
    json_t *json = http_get_json(url);
    if (!json) {
        *n_products = 0;
        return NULL;
    }

    json_t *products_json = json_object_get(json, "products");
    if (!json_is_array(products_json)) {
        json_decref(json);
        *n_products = 0;
        return NULL;
    }

    size_t size = json_array_size(products_json);
    Product *products = malloc(size * sizeof(Product));
    if (!products) {
        fprintf(stderr, "Failed to allocate memory for products\n");
        json_decref(json);
        *n_products = 0;
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        json_t *product_json = json_array_get(products_json, i);
        if (!json_is_object(product_json)) continue;

        products[i].id = json_integer_value(json_object_get(product_json, "id"));
        products[i].price = json_real_value(json_object_get(product_json, "price"));
        products[i].description = strdup(json_string_value(json_object_get(product_json, "description")));
        products[i].category = strdup(json_string_value(json_object_get(product_json, "category")));

        if (!products[i].description || !products[i].category) {
            fprintf(stderr, "Failed to allocate memory for product strings\n");
            free_products(products, i);
            json_decref(json);
            *n_products = 0;
            return NULL;
        }
    }

    json_decref(json);
    *n_products = size;
    return products;
}

// Function to get users information
User *users_get(size_t *n_users) {
    const char *url = "https://dummyjson.com/users";
    json_t *json = http_get_json(url);
    if (!json) {
        *n_users = 0;
        return NULL;
    }

    // Debug: Print the raw JSON response
    char *json_str = json_dumps(json, JSON_INDENT(4));
    printf("Raw JSON response: %s\n", json_str);
    free(json_str);

    // Adjust JSON parsing based on actual structure
    json_t *users_json = json_object_get(json, "users");
    if (!json_is_array(users_json)) {
        json_decref(json);
        *n_users = 0;
        return NULL;
    }

    size_t size = json_array_size(users_json);
    User *users = malloc(size * sizeof(User));
    if (!users) {
        fprintf(stderr, "Failed to allocate memory for users\n");
        json_decref(json);
        *n_users = 0;
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        json_t *user_json = json_array_get(users_json, i);
        if (!json_is_object(user_json)) continue;

        users[i].id = json_integer_value(json_object_get(user_json, "id"));
        printf("User ID: %d\n", users[i].id);

        const char *first_name = json_string_value(json_object_get(user_json, "firstName")); 
        const char *last_name = json_string_value(json_object_get(user_json, "lastName")); 
        if (first_name && last_name) { 
            size_t name_len = strlen(first_name) + strlen(last_name) + 2; // +1 for space, +1 for null terminator 
            users[i].name = malloc(name_len); 
            if (!users[i].name) { 
                fprintf(stderr, "Failed to allocate memory for user names\n"); 
                free_users(users, i); 
                json_decref(json); 
                *n_users = 0; 
                return NULL; 
            } 
            snprintf(users[i].name, name_len, "%s %s", first_name, last_name); 
            printf("User Name: %s\n", users[i].name); 
        } else { 
            users[i].name = NULL; 
            fprintf(stderr, "Name is NULL for user with ID: %d\n", users[i].id);
        }
    }

    json_decref(json);
    *n_users = size;
    return users;
}

// Function to put cart information
bool cart_put(const Cart *cart) {
    const char *url = "https://dummyjson.com/carts/add";
    json_t *cart_json = json_object();
    json_object_set_new(cart_json, "userId", json_integer(cart->user_id));

    json_t *products_json = json_array();
    for (size_t i = 0; i < cart->n_products; i++) {
        json_t *product_json = json_object();
        json_object_set_new(product_json, "id", json_integer(cart->products[i].id));
        json_object_set_new(product_json, "quantity", json_integer(cart->products[i].quantity));
        json_array_append_new(products_json, product_json);
    }
    json_object_set_new(cart_json, "products", products_json);

    bool result = (http_post_json(url, cart_json) != NULL);
    json_decref(cart_json);
    return result;
}

// Function to free dynamically allocated products
void free_products(Product *products, size_t n_products) {
    for (size_t i = 0; i < n_products; i++) {
        free((char *)products[i].description);
        free((char *)products[i].category);
    }
    free(products);
}

// Function to free dynamically allocated users
void free_users(User *users, size_t n_users) {
    for (size_t i = 0; i < n_users; i++) {
        free((char *)users[i].name);
    }
    free(users);
}

// Function to free dynamically allocated cart
void free_cart(Cart *cart) {
    if (cart->products) {
        free(cart->products);
        cart->products = NULL;
    }
    //free(cart);
}
