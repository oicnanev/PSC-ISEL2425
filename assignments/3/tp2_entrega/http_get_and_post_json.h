#ifndef _HTTP_GET_AND_PUT_JSON_H
#define _HTTP_GET_AND_PUT_JSON_H

#include <jansson.h>

json_t *http_get_json(const char *url);
json_t *http_post_json(const char *uri, json_t *data);

#endif /*_HTTP_GET_AND_PUT_JSON_H*/
