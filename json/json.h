#ifdef SCORE_JSON
#ifndef SCORE_JSON_H
#define SCORE_JSON_H

#include "score/buffer/writer/writer.h"

typedef struct {
    void *data;
} SCore_JSON_Object;

SCORE_BOOL score_json_parse(const char *data, SCore_JSON_Object *out_json_object);

SCORE_BOOL score_json_write_to_buffer(SCore_Buffer_Writer *writer, const SCore_JSON_Object json_object);

#endif
#else
#error "json.h included. SCORE_JSON needs to be defined."
#endif