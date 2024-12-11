#include "store.h"
#include <curl/curl.h>
#include <jansson.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef HAVE_STRDUP
char *strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d == NULL) return NULL;
    return (char *)memcpy(d, s, len);
}
#endif

#ifndef HAVE_STRNDUP
char *strndup(const char *s, size_t n) {
    size_t len = strlen(s);
    if (len > n)
        len = n;
    char *result = (char *)malloc(len + 1);
    if (!result) return NULL;
    result[len] = '\0';
    return (char *)memcpy(result, s, len);
}
#endif

// Write callback function for libcurl
static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    char **response = (char **)userp;

    *response = realloc(*response, strlen(*response) + realsize + 1);
    if (*response == NULL) {
        fprintf(stderr, "Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    strncat(*response, data, realsize);
    return realsize;
}

// Helper function to perform HTTP GET request and return JSON response
json_t *http_get_json(const char *url) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return NULL;
    }

    CURLcode res;
    char *response = calloc(1, sizeof(char));

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "CURL error: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        free(response);
        return NULL;
    }

    // Print raw response for debugging
    printf("Raw response: %s\n", response);

    json_error_t error;
    json_t *json = json_loads(response, 0, &error);
    if (!json) {
        fprintf(stderr, "JSON error: %s\n", error.text);
    }

    curl_easy_cleanup(curl);
    free(response);
    return json;
}

// Helper function to perform HTTP POST request and return success/failure
bool http_post_json(const char *url, json_t *data) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return false;
    }

    CURLcode res;
    char *json_data = json_dumps(data, 0);
    if (!json_data) {
        fprintf(stderr, "Failed to serialize JSON data\n");
        curl_easy_cleanup(curl);
        return false;
    }

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "CURL error: %s\n", curl_easy_strerror(res));
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    free(json_data);
    return res == CURLE_OK;
}

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
        json_decref(json);
        *n_products = 0;
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        json_t *product_json = json_array_get(products_json, i);
        products[i].id = json_integer_value(json_object_get(product_json, "id"));
        products[i].price = json_real_value(json_object_get(product_json, "price"));
        products[i].description = strdup(json_string_value(json_object_get(product_json, "description")));
        products[i].category = strdup(json_string_value(json_object_get(product_json, "category")));
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

    json_t *users_json = json_object_get(json, "users");
    if (!json_is_array(users_json)) {
        json_decref(json);
        *n_users = 0;
        return NULL;
    }

    size_t size = json_array_size(users_json);
    User *users = malloc(size * sizeof(User));
    if (!users) {
        json_decref(json);
        *n_users = 0;
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        json_t *user_json = json_array_get(users_json, i);
        users[i].id = json_integer_value(json_object_get(user_json, "id"));
        users[i].name = strdup(json_string_value(json_object_get(user_json, "name")));
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

    bool result = http_post_json(url, cart_json);
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
    free(cart->products);
    free(cart);
}
