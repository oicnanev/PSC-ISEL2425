#include <stdio.h>
#include <jansson.h>

json_t *http_get_json(const char *url);

int main() {
    const char *url = "https://dummyjson.com/products/1";
    json_t *json = http_get_json(url);

    if (!json) {
        fprintf(stderr, "Failed to get JSON data.\n");
        return 1;
    }

    json_t *title = json_object_get(json, "title");
    if (json_is_string(title)) {
        printf("Title: %s\n", json_string_value(title));
    } else {
        printf("Title not found or not a string.\n");
    }

    json_decref(json);
    return 0;
}
