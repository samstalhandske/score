#ifdef SCORE_BUFFER

#include "buffer.h"
#include <stdio.h>

SCore_Buffer score_buffer_create_from_backing(const uint8_t *ptr_to_backing, unsigned int capacity) {
    SCore_Buffer b;
    b.data = ptr_to_backing;
    b.capacity = capacity;
    b.length = 0;

    return b;
}

void score_buffer_init_using_backing(SCore_Buffer *buffer, uint8_t *ptr_to_backing, unsigned int capacity) {
    *buffer = score_buffer_create_from_backing(ptr_to_backing, capacity);
}

SCORE_BOOL score_buffer_clear(SCore_Buffer *buffer) {
    if(!score_buffer_has_data(buffer)) {
        return SCORE_FALSE;
    }

    buffer->length = 0;
    return SCORE_TRUE;
}

SCORE_BOOL score_buffer_has_data(SCore_Buffer *buffer) {
    if(buffer == NULL) {
        return SCORE_FALSE;
    }
    if(buffer->data == NULL) {
        return SCORE_FALSE;
    }

    return SCORE_TRUE;
}

uint32_t score_buffer_space_left(SCore_Buffer *buffer) {
    assert(buffer != NULL);
    return buffer->capacity - buffer->length;
}

char *score_buffer_to_string(SCore_Buffer *buffer) {
    char *str_ptr;

    assert(buffer != NULL);
    assert(score_buffer_has_data(buffer));

    if (buffer == NULL || buffer->data == NULL) {
        return NULL;
    }

    str_ptr = calloc(buffer->length + 1, sizeof(char)); /* TODO: SS - Get an allocator and use it here. */
    assert(str_ptr != NULL);

    {
        uint32_t i;
        for (i = 0; i < buffer->length; i++) {
            uint8_t byte = ((uint8_t*)buffer->data)[i];

            str_ptr[i] = byte;
        }

        str_ptr[i] = '\0';
    }

    return str_ptr;
}

#endif