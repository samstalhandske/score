#ifdef SCORE_HTTP

#include "http.h"
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <stdio.h>
#include <assert.h>

static size_t score_http_response_write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    SCore_Http_Response* response = (SCore_Http_Response*)userp;

    size_t realsize = size * nmemb;
    unsigned int totalSize = response->size + realsize + 1;

    char* ptr = NULL;
    if(response->data == NULL) {
        ptr = (char*)malloc(totalSize);
    }
    else {
        ptr = realloc(response->data, totalSize);
    }

    if(ptr == NULL) {
        return 0;
    }

    response->data = ptr;
    memcpy(&(response->data[response->size]), contents, realsize);
    response->size += realsize;
    response->data[response->size] = 0;

    return realsize;
}

SCORE_BOOL score_http_initialize(SCore_Http* http) {
    http->curl = curl_easy_init();

    if (http->curl == NULL) {
        return SCORE_FALSE;
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_http_perform(SCore_Http* http, const char* url, SCore_Http_Response* response) {
    assert(http != NULL);
    assert(http->curl != NULL);

    curl_easy_setopt(http->curl, CURLOPT_URL, url);
    curl_easy_setopt(http->curl, CURLOPT_WRITEFUNCTION, score_http_response_write_callback);
    curl_easy_setopt(http->curl, CURLOPT_WRITEDATA, (void*)response);

    if (curl_easy_perform(http->curl) != CURLE_OK) {
        return SCORE_FALSE;
    }

    return SCORE_TRUE;
}

void score_http_dispose_response(SCore_Http_Response *response) {
    assert(response != NULL);

    if(response->data != NULL) {
        free(response->data);
        response->data = NULL;
    }
}

void score_http_dispose(SCore_Http *http) {
    assert(http != NULL);

    curl_easy_cleanup(http->curl);
    http->curl = NULL;
}

#endif