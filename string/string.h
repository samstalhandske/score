#ifdef SCORE_STRING

#ifndef SCORE_STRING_H
#define SCORE_STRING_H

#include "score/buffer/writer/writer.h"

typedef enum {
    SCore_String_Compare_Result_Equal,
    SCore_String_Compare_Result_Equal_But_Different_Casing,
    SCore_String_Compare_Result_A_Longer_Than_B,
    SCore_String_Compare_Result_B_Longer_Than_A,
    SCore_String_Compare_Result_A_Null,
    SCore_String_Compare_Result_B_Null,
    SCore_String_Compare_Result_Different
} SCore_String_Compare_Result;

SCore_String_Compare_Result score_string_compare(const char *a, const char *b, SCORE_BOOL case_sensitive);
SCORE_BOOL score_string_length(const char *str, unsigned int *out_length);

unsigned int score_string_snprintf(SCore_Buffer_Writer *writer, const char *format, ...);

#endif
#else
#error "string.h included. SCORE_STRING needs to be defined."
#endif
