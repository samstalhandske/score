#ifdef SCORE_JSON
#ifndef SCORE_JSON_H
#define SCORE_JSON_H

#include "score/buffer/writer/writer.h"

typedef struct {
    void *data;
} SCore_JSON_Object;

typedef struct {
    SCore_JSON_Object *data;
    uint32_t size;
} SCore_JSON_Array;

SCORE_BOOL score_json_parse(const char *data, SCore_JSON_Object *out_json_object);

SCORE_BOOL score_json_get_object(const SCore_JSON_Object *json_object, const char *item_name, SCORE_BOOL case_sensitive, SCore_JSON_Object *out_json_object);

SCORE_BOOL score_json_as_number(const SCore_JSON_Object *json_object, double *out_value);
SCORE_BOOL score_json_as_string(const SCore_JSON_Object *json_object, char **out_value);
SCORE_BOOL score_json_as_array(const SCore_JSON_Object *json_object, SCore_JSON_Array *out_value);
SCORE_BOOL score_json_as_array_to_buffer(const SCore_JSON_Object *json_object, SCore_Buffer_Writer *writer);

SCORE_BOOL score_json_is_number(const SCore_JSON_Object *json_object);
SCORE_BOOL score_json_is_string(const SCore_JSON_Object *json_object);
SCORE_BOOL score_json_is_array(const SCore_JSON_Object *json_object);

SCORE_BOOL score_json_write_to_buffer(SCore_Buffer_Writer *writer, const SCore_JSON_Object json_object);

SCORE_BOOL score_json_dispose(SCore_JSON_Object *json_object);
SCORE_BOOL score_json_array_dispose(SCore_JSON_Array *json_array);

#endif
#else
#error "json.h included. SCORE_JSON needs to be defined."
#endif