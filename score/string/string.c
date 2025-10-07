#ifdef SCORE_STRING

#include "string.h"

#include <stdarg.h>
#include <stdio.h>

#include <stdlib.h>

bool score_string_length(const char *str, unsigned int* out_length) {
    if(str == NULL || out_length == NULL || *out_length != 0) {
        return false;
    }

    unsigned int length = 0;
    while(*str != '\0') {
        length += 1;
        str += 1;
    }

    *out_length = length;
    return true;
}

Score_String_Compare_Result score_string_compare(const char *a, const char *b, bool case_sensitive) {
    if(a == NULL) return Score_String_Compare_Result_A_Null;
    if(b == NULL) return Score_String_Compare_Result_B_Null;

    unsigned int a_len = 0;
    unsigned int b_len = 0;

    assert(score_string_length(a, &a_len));
    assert(score_string_length(b, &b_len));

    if(a_len > b_len) {
        return Score_String_Compare_Result_A_Longer_Than_B;
    }
    else if(b_len > a_len) {
        return Score_String_Compare_Result_B_Longer_Than_A;
    }

    unsigned int i;
    for(i = 0; i < a_len; i++) {
        char a_char = a[i];
        char b_char = b[i];

        if(a_char != b_char) {
            if(!case_sensitive) {
                bool same_but_different_casing = a_char == b_char - 32 || a_char == b_char + 32;
                if(!same_but_different_casing) {
                    return Score_String_Compare_Result_Equal_But_Different_Casing;
                }
            }
            else {
                return Score_String_Compare_Result_Different;
            }
        }
    }

    return Score_String_Compare_Result_Equal;
}

unsigned int score_string_snprintf(Score_Buffer_Writer *writer, const char *format, ...) {
    if (writer == NULL || writer->buffer == NULL || format == NULL) {
        return 0;
    }

    unsigned int remaining = writer->buffer->capacity - writer->offset;
    if (remaining == 0) return 0;

    char *temp = (char *)malloc(remaining);
    if (!temp) {
        return 0;
    }

    va_list args;
    va_start(args, format);
    int n = vsprintf(temp, format, args);
    va_end(args);

    if (n < 0) {
        n = 0;
    }

    if ((unsigned int)n >= remaining) {
        n = remaining - 1;
        temp[n] = '\0';
    }

    if (!score_buffer_writer_write(writer, temp, (unsigned int)n)) {
        free(temp);
        return 0;
    }

    free(temp);
    return (unsigned int)n;
}

#endif