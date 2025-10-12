#ifdef SCORE_HTTP
#ifndef SCORE_HTTP_H
#define SCORE_HTTP_H

#include <curl/curl.h>

typedef struct {
    CURL* curl;
} SCore_Http;

typedef struct {
    char* data;
    unsigned int size;
} SCore_Http_Response;

SCORE_BOOL score_http_initialize(SCore_Http *http);
SCORE_BOOL score_http_perform(SCore_Http *http, const char* url, SCore_Http_Response* response);
void score_http_dispose_response(SCore_Http_Response* response);
void score_http_dispose(SCore_Http *http);

#endif
#else
#error "http.h included. SCORE_HTTP needs to be defined."
#endif