#ifdef SCORE_STRING

#ifndef SCORE_STRING_H
#define SCORE_STRING_H

#include "score/buffer/writer/writer.h"

typedef enum {
    Score_String_Compare_Result_Equal,
    Score_String_Compare_Result_Equal_But_Different_Casing,
    Score_String_Compare_Result_A_Longer_Than_B,
    Score_String_Compare_Result_B_Longer_Than_A,
    Score_String_Compare_Result_A_Null,
    Score_String_Compare_Result_B_Null,
    Score_String_Compare_Result_Different,
} Score_String_Compare_Result;

Score_String_Compare_Result score_string_compare(const char *a, const char *b, bool case_sensitive);
bool score_string_length(const char *str, unsigned int *out_length);

unsigned int score_string_snprintf(Score_Buffer_Writer *writer, const char *format, ...);

#endif
#else
#error "string.h included. SCORE_STRING needs to be defined."
#endif
