#ifdef SCORE_JSON_JANSSON

#include "json/json.h"

#include <stdio.h>

SCORE_BOOL score_json_parse(const char *data, SCore_JSON_Object *out_json_object) {
    (void)data;
    (void)out_json_object;

    printf("TODO: SS - Parse JSON using Jansson.\n");

    return SCORE_FALSE;
}

#endif