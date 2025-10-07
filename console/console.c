#include "console.h"

#include <stdio.h>
#include "score/string/string.h"

bool score_console_read(char *buffer, unsigned int buffer_length) {
    if(buffer == NULL) {
        return false;
    }
    if(buffer_length == 0) {
        return false;
    }

    char *read = fgets(buffer, buffer_length, stdin);
    if(read == NULL) {
        return false;
    }

    unsigned int read_length = 0;
    if(score_string_length(read, &read_length)) {
        read[read_length - 1] = '\0';
    }

    return read == buffer;
}