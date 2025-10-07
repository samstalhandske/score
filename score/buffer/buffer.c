#ifdef SCORE_BUFFER

#include "buffer.h"

bool score_buffer_has_data(Score_Buffer *buffer) {
    if(buffer == NULL) {
        return false;
    }
    if(buffer->data == NULL) {
        return false;
    }

    return true;
}

Score_Buffer score_buffer_create_from_backing(const void *ptr_to_backing, unsigned int capacity) {
    Score_Buffer b;
    b.data = ptr_to_backing;
    b.capacity = capacity;
    b.length = 0;

    return b;
}

void score_buffer_init_using_backing(Score_Buffer *buffer, void *ptr_to_backing, unsigned int capacity) {
    *buffer = score_buffer_create_from_backing(ptr_to_backing, capacity);
}

#endif