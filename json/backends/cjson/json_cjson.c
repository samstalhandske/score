#ifdef SCORE_JSON_CJSON

#include "json/json.h"
#include "cJSON/cJSON.h"

#include <stdio.h>
#include <stdlib.h>

cJSON *cast_score_json_to_cjson(const SCore_JSON_Object *json_object) {
    assert(json_object != NULL);
    assert(json_object->data != NULL);

    return (cJSON *)json_object->data;
}

SCORE_BOOL score_json_parse(const char *data, SCore_JSON_Object *out_json_object) {
    if(data == NULL) {
        return SCORE_FALSE;
    }

    out_json_object->data = (void *)cJSON_Parse(data);
    return SCORE_TRUE;
}

SCORE_BOOL score_json_get_object(const SCore_JSON_Object *json_object, const char *item_name, SCORE_BOOL case_sensitive, SCore_JSON_Object *out_json_object) {
    cJSON *cjson_data = NULL;

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

    cjson_data = cast_score_json_to_cjson(json_object);

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

SCORE_BOOL score_json_get_array_element(const SCore_JSON_Array *json_array, const uint32_t index, SCore_JSON_Object **out_json_object) {
    SCore_JSON_Object *obj = NULL;

    if(json_array == NULL) {
        return SCORE_FALSE;
    }
    if(out_json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_array->size == 0) {
        return SCORE_FALSE;
    }
    if(json_array->size <= index) {
        return SCORE_FALSE;
    }
    if(json_array->data == NULL) {
        return SCORE_FALSE;
    }

    obj = &json_array->data[index];
    assert(obj != NULL);

    *out_json_object = obj;
    return SCORE_TRUE;
}


SCORE_BOOL score_json_as_number(const SCore_JSON_Object *json_object, double *out_value) {
    cJSON *json_number_object = NULL;

    if(json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_object->data == NULL) {
        return SCORE_FALSE;
    }
    if(out_value == NULL) {
        return SCORE_FALSE;
    }

    if(!score_json_is_number(json_object)) {
        return SCORE_FALSE;
    }

    json_number_object = cast_score_json_to_cjson(json_object);

    *out_value = cJSON_GetNumberValue(json_number_object);

    return SCORE_TRUE;
}

SCORE_BOOL score_json_as_string(const SCore_JSON_Object *json_object, char **out_string) {
    char *json_string_value = NULL;

    if(json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_object->data == NULL) {
        return SCORE_FALSE;
    }
    if(out_string == NULL) {
        return SCORE_FALSE;
    }

    if(!score_json_is_string(json_object)) {
        return SCORE_FALSE;
    }

    json_string_value = cJSON_GetStringValue(cast_score_json_to_cjson(json_object));
    if(json_string_value == NULL) {
        return SCORE_FALSE;
    }

    *out_string = json_string_value;

    return SCORE_TRUE;
}

SCORE_BOOL score_json_as_array(const SCore_JSON_Object *json_object, SCore_JSON_Array *out_value) {
    cJSON* json_array_object = NULL;
    int32_t array_size = 0;

    if(json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_object->data == NULL) {
        return SCORE_FALSE;
    }
    if(out_value == NULL) {
        return SCORE_FALSE;
    }

    if(!score_json_is_array(json_object)) {
        return SCORE_FALSE;
    }

    json_array_object = cast_score_json_to_cjson(json_object);

    array_size = cJSON_GetArraySize(json_array_object);
    assert(array_size >= 0);

    out_value->size = (uint32_t)array_size;
    out_value->data = calloc(out_value->size, sizeof(SCore_JSON_Object));

    {
        uint32_t i;
        for(i = 0; i < out_value->size; i++) {
            out_value->data[i].data = (void *)cJSON_GetArrayItem(json_array_object, i);
        }
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_json_is_number(const SCore_JSON_Object *json_object) {
    if(json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_object->data == NULL) {
        return SCORE_FALSE;
    }

    if(!cJSON_IsNumber(cast_score_json_to_cjson(json_object))) {
        return SCORE_FALSE;
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_json_is_string(const SCore_JSON_Object *json_object) {
    if(json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_object->data == NULL) {
        return SCORE_FALSE;
    }

    if(!cJSON_IsString(cast_score_json_to_cjson(json_object))) {
        return SCORE_FALSE;
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_json_is_array(const SCore_JSON_Object *json_object) {
    if(json_object == NULL) {
        return SCORE_FALSE;
    }
    if(json_object->data == NULL) {
        return SCORE_FALSE;
    }

    if(!cJSON_IsArray(cast_score_json_to_cjson(json_object))) {
        return SCORE_FALSE;
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

    cJSON_Delete((cJSON *)json_object->data);

    json_object->data = NULL;

    return SCORE_TRUE;
}

SCORE_BOOL score_json_array_dispose(SCore_JSON_Array *json_array) {
    if(json_array == NULL) {
        return SCORE_FALSE;
    }

    /*
        We're not allowed to dispse the json objects in the array cause we don't own them.
    */
    free(json_array->data);
    json_array->size = 0;
    json_array->data = NULL;

    return SCORE_FALSE;
}

#endif