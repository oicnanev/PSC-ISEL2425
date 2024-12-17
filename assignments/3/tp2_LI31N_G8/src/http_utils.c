// src/http_utils.c
#include <curl/curl.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_utils.h"


struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    // printf("Received %zu bytes of data\n", realsize); // DEBUG LINE

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        fprintf(stderr, "Not enough memory (realloc returned NULL)\n");
        return 0; // Out of memory!
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}


json_t *http_get_json(const char *url) {
    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

    res = curl_easy_perform(curl_handle);

    json_t *json = NULL;
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        json_error_t error;
        json = json_loads(chunk.memory, 0, &error);
        if (!json) {
            fprintf(stderr, "json_loads() failed: %s\n", error.text);
        }
    }

    curl_easy_cleanup(curl_handle);
    curl_global_cleanup();
    free(chunk.memory);

    return json;
}

bool http_post_json(const char *url, json_t *data) {
    CURL *curl_handle;
    CURLcode res;
    struct curl_slist *headers = NULL;
    char *json_data = json_dumps(data, 0);
    struct MemoryStruct response;
    response.memory = malloc(1);  // Inicialização mínima
    response.size = 0;

    if (!json_data) {
        fprintf(stderr, "Failed to convert JSON data to string.\n");
        return false;
    }

    // printf("Generated JSON data: %s\n", json_data); // DEBUG LINE

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    if (curl_handle) {
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, json_data);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&response);

        res = curl_easy_perform(curl_handle);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(json_data);
            curl_slist_free_all(headers);  // Libertar a lista de headers
            curl_easy_cleanup(curl_handle);
            curl_global_cleanup();
            free(response.memory);  // Libertar a memória alocada para a resposta
            return false;
        }

        // printf("Response: %s\n", response.memory);  // DEBUG LINE

        // Limpeza
        curl_easy_cleanup(curl_handle);
        curl_global_cleanup();
        curl_slist_free_all(headers);  // Libertar a lista de headers
        free(response.memory);  // Libertar a memória alocada para a resposta
        free(json_data);
        return true;
    }

    fprintf(stderr, "Failed to initialize CURL.\n");
    free(json_data);
    curl_global_cleanup();
    return false;
}
