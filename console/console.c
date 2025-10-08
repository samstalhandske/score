#include "console.h"

#include <stdio.h>
#include "score/string/string.h"

SCORE_BOOL score_console_read_from_stdin(char *buffer, unsigned int buffer_length) {
    char *read = NULL;
    uint32_t read_length = 0;

    if(buffer == NULL) {
        return SCORE_FALSE;
    }
    if(buffer_length == 0) {
        return SCORE_FALSE;
    }

    read = fgets(buffer, buffer_length, stdin);
    if(read == NULL) {
        return SCORE_FALSE;
    }

    if(score_string_length(read, &read_length)) {
        read[read_length - 1] = '\0';
    }

    return read == buffer;
}