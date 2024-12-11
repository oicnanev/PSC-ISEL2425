// http_post_json.c
#include <curl/curl.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Incluído para declarar bool

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    char **response_ptr = (char **)userp;

    // Libera a memória anteriormente alocada, se houver
    if (*response_ptr) {
        free(*response_ptr);
    }

    *response_ptr = strndup(contents, realsize);
    
    return realsize;
}

bool http_post_json(const char *url, json_t *data) {
    CURL *curl_handle;
    CURLcode res;
    struct curl_slist *headers = NULL;
    char *json_data = json_dumps(data, 0);
    char *response = NULL;

    if (!json_data) {
        fprintf(stderr, "Failed to convert JSON data to string.\n");
        return false;
    }

    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();

    if (curl_handle) {
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, json_data);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl_handle);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(json_data);
            curl_slist_free_all(headers);  // Liberando a lista de headers
            curl_easy_cleanup(curl_handle);
            curl_global_cleanup();
            return false;
        }

        printf("Response: %s\n", response);

        // Limpeza
        curl_easy_cleanup(curl_handle);
        curl_global_cleanup();
        curl_slist_free_all(headers);  // Liberando a lista de headers
        free(response);
        free(json_data);
        return true;
    }

    fprintf(stderr, "Failed to initialize CURL.\n");
    free(json_data);
    curl_global_cleanup();
    return false;
}
