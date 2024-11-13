#include <jansson.h>
#include <stdio.h>
#include <stdbool.h>

bool http_post_json(const char *url, json_t *data);

int main() {
    const char *url = "https://dummyjson.com/carts/add";
    json_t *root = json_object();
    json_t *products = json_array();
    json_t *product = json_object();

    json_object_set_new(product, "id", json_integer(144));
    json_object_set_new(product, "quantity", json_integer(4));
    json_array_append_new(products, product);
    json_object_set_new(root, "userId", json_integer(1));
    json_object_set_new(root, "products", products);

    bool success = http_post_json(url, root);

    if (!success) {
        fprintf(stderr, "Failed to post JSON data.\n");
        json_decref(root);
        return 1;
    }

    json_decref(root);
    return 0;
}
