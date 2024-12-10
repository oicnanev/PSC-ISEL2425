// include/http_utils.h
#ifndef HTTP_UTILS_H
#define HTTP_UTILS_H

#include <jansson.h>
#include <stdbool.h>

// Declaração da função para realizar o pedido HTTP GET
json_t *http_get_json(const char *url);

// Declaração da função para realizar o pedido HTTP POST
bool http_post_json(const char *url, json_t *data);

#endif // HTTP_UTILS_H
