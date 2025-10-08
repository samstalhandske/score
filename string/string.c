#ifdef SCORE_STRING

#include "string.h"

#include <stdarg.h>
#include <stdio.h>

#include <stdlib.h>

SCORE_BOOL score_string_length(const char *str, uint32_t* out_length) {
    uint32_t length = 0;

    if(str == NULL || out_length == NULL || *out_length != 0) {
        return SCORE_FALSE;
    }

    while(*str != '\0') {
        length += 1;
        str += 1;
    }

    *out_length = length;
    return SCORE_TRUE;
}

SCore_String_Compare_Result score_string_compare(const char *a, const char *b, SCORE_BOOL case_sensitive) {
    uint32_t a_len = 0;
    uint32_t b_len = 0;
    uint32_t i = 0;

    if(a == NULL) return SCore_String_Compare_Result_A_Null;
    if(b == NULL) return SCore_String_Compare_Result_B_Null;

    assert(score_string_length(a, &a_len));
    assert(score_string_length(b, &b_len));

    if(a_len > b_len) {
        return SCore_String_Compare_Result_A_Longer_Than_B;
    }
    else if(b_len > a_len) {
        return SCore_String_Compare_Result_B_Longer_Than_A;
    }

    for(i = 0; i < a_len; i++) {
        char a_char = a[i];
        char b_char = b[i];

        if(a_char != b_char) {
            if(!case_sensitive) {
                SCORE_BOOL same_but_different_casing = a_char == b_char - 32 || a_char == b_char + 32;
                if(!same_but_different_casing) {
                    return SCore_String_Compare_Result_Equal_But_Different_Casing;
                }
            }
            else {
                return SCore_String_Compare_Result_Different;
            }
        }
    }

    return SCore_String_Compare_Result_Equal;
}

uint32_t score_string_snprintf(SCore_Buffer_Writer *writer, const char *format, ...) {
    uint32_t remaining_space_in_writer;
    int32_t bytes_written = 0;
    char *temporary_memory_to_store_bytes = NULL;

    if (writer == NULL || writer->buffer == NULL || format == NULL) {
        return 0;
    }

    remaining_space_in_writer = writer->buffer->capacity - writer->offset;
    if (remaining_space_in_writer == 0) return 0;

    temporary_memory_to_store_bytes = (char *)malloc(remaining_space_in_writer);
    assert(temporary_memory_to_store_bytes != NULL);

    {
        va_list args;
        va_start(args, format);
        bytes_written = vsprintf(temporary_memory_to_store_bytes, format, args);
        va_end(args);

        if (bytes_written < 0) {
            bytes_written = 0;
        }

        if ((uint32_t)bytes_written >= remaining_space_in_writer) {
            bytes_written = remaining_space_in_writer - 1;
            temporary_memory_to_store_bytes[bytes_written] = '\0';
        }

        if (!score_buffer_writer_write(writer, temporary_memory_to_store_bytes, (uint32_t)bytes_written)) {
            free(temporary_memory_to_store_bytes);
            return 0;
        }
    }

    free(temporary_memory_to_store_bytes);
    return (uint32_t)bytes_written;
}

#endif