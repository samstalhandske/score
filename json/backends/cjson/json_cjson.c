#ifdef SCORE_JSON_CJSON

#include "json/json.h"
#include "cJSON/cJSON.h"

#include <stdio.h>
#include <stdlib.h>

SCORE_BOOL score_json_parse(const char *data, SCore_JSON_Object *out_json_object) {
    if(data == NULL) {
        return SCORE_FALSE;
    }

    out_json_object->data = (void *)cJSON_Parse(data);
    return SCORE_TRUE;
}

SCORE_BOOL score_json_get_object(const SCore_JSON_Object *json_object, const char *item_name, SCORE_BOOL case_sensitive, SCore_JSON_Object *out_json_object) {
    if(json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_object->data == NULL) {
        return SCORE_FALSE;
    }
    if(item_name == NULL) {
        return SCORE_FALSE;
    }
    if(out_json_object == NULL) {
        return SCORE_FALSE;
    }

    cJSON *cjson_data = (cJSON *)json_object->data;

    if(case_sensitive == SCORE_TRUE) {
        out_json_object->data = (void *)cJSON_GetObjectItemCaseSensitive(cjson_data, item_name);
    }
    else {
        out_json_object->data = (void *)cJSON_GetObjectItem(cjson_data, item_name);
    }

    if(out_json_object->data == NULL) {
        return SCORE_FALSE;
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_json_as_double(const SCore_JSON_Object *json_object, double *out_value) {
    if(json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_object->data == NULL) {
        return SCORE_FALSE;
    }
    if(out_value == NULL) {
        return SCORE_FALSE;
    }

    if(!cJSON_IsNumber(json_object)) {
        return SCORE_FALSE;
    }

    *out_value = cJSON_GetNumberValue((cJSON *)json_object->data);

    return SCORE_TRUE;
}

SCORE_BOOL score_json_as_string(const SCore_JSON_Object *json_object, char **out_string) {
    if(json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_object->data == NULL) {
        return SCORE_FALSE;
    }
    if(out_string == NULL) {
        return SCORE_FALSE;
    }
    if(*out_string == NULL) {
        return SCORE_FALSE;
    }

    if(!cJSON_IsString(json_object)) {
        return SCORE_FALSE;
    }

    char *v = cJSON_GetStringValue((cJSON *)json_object->data);
    if(v == NULL) {
        return SCORE_FALSE;
    }

    *out_string = v;

    return SCORE_TRUE;
}

SCORE_BOOL score_json_as_array(const SCore_JSON_Object *json_object, SCore_Json_Array *out_value) {
    (json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_object->data == NULL) {
        return SCORE_FALSE;
    }
    if(out_value == NULL) {
        return SCORE_FALSE;
    }

    if(!cJSON_IsArray(json_object)) {
        return SCORE_FALSE;
    }

    cJSON* json_array_object = (cJSON *)json_object->data;

    int32_t array_size = cJSON_GetArraySize(json_array_object);
    assert(array_size >= 0);
    out_value->size = (uint32_t)array_size;
    out_value->data = malloc(out_value->size * sizeof(SCore_Json_Array));

    uint32_t i;
    for(i = 0; i < out_value->size; i++) {
        out_value->data[i].data = (void *)cJSON_GetArrayItem(json_array_object, i);
    }

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

SCORE_BOOL score_json_dispose(SCore_JSON_Object *json_object) {
    if(json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_object->data == NULL) {
        return SCORE_FALSE;
    }

    cJSON *data = (cJSON *)json_object->data;
    cJSON_Delete(data);

    json_object->data = NULL;

    return SCORE_TRUE;
}

#endif