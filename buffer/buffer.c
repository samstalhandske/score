#ifdef SCORE_BUFFER

#include "buffer.h"

SCORE_BOOL score_buffer_has_data(SCore_Buffer *buffer) {
    if(buffer == NULL) {
        return SCORE_FALSE;
    }
    if(buffer->data == NULL) {
        return SCORE_FALSE;
    }

    return SCORE_TRUE;
}

SCore_Buffer score_buffer_create_from_backing(const void *ptr_to_backing, unsigned int capacity) {
    SCore_Buffer b;
    b.data = ptr_to_backing;
    b.capacity = capacity;
    b.length = 0;

    return b;
}

void score_buffer_init_using_backing(SCore_Buffer *buffer, void *ptr_to_backing, unsigned int capacity) {
    *buffer = score_buffer_create_from_backing(ptr_to_backing, capacity);
}

#endif