#ifndef SCORE_HTTP_H
#define SCORE_HTTP_H

#include <curl/curl.h>

typedef struct {
    CURL* curl;
} Score_Http;

typedef struct {
    char* data;
    unsigned int size;
} Score_Http_Response;

bool score_http_initialize(Score_Http *http);
bool score_http_perform(Score_Http *http, const char* url, Score_Http_Response* response);
void score_http_dispose_response(Score_Http_Response* response);
void score_http_dispose(Score_Http *http);

#endif