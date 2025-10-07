#ifdef SCORE_JSON_CJSON

#include "json/json.h"
#include "cJSON/cJSON.h"

#include <stdio.h>
#include <stdlib.h>

SCORE_BOOL score_json_parse(const char *data, SCore_JSON_Object *out_json_object) {
    (void)data;
    (void)out_json_object;

    printf("TODO: SS - Parse JSON using cJSON.\n");

    out_json_object->data = (void *)cJSON_CreateObject();
    cJSON_AddStringToObject((cJSON*)out_json_object->data, "Hello", "World");

    return SCORE_TRUE;
}

SCORE_BOOL score_json_write_to_buffer(SCore_Buffer_Writer *writer, const SCore_JSON_Object json_object) {
    char *printed_json = cJSON_Print((cJSON *)json_object.data);
    if(!score_buffer_writer_write_string(writer, printed_json)) {
        free(printed_json);
        return SCORE_FALSE; /* Maybe we shouldn't return SCORE_FALSE here. Maybe an enum is better. */
    }

    free(printed_json);
    return SCORE_TRUE;
}

#endif