#ifdef SCORE_BUFFER

#ifndef SCORE_BUFFER_H
#define SCORE_BUFFER_H

#include <stdlib.h>

typedef struct {
    const uint8_t *data;
    uint32_t capacity;
    uint32_t length;
} SCore_Buffer;

SCore_Buffer score_buffer_create_from_backing(const uint8_t *ptr_to_backing, unsigned int capacity);
void score_buffer_init_using_backing(SCore_Buffer *buffer, uint8_t *ptr_to_backing, unsigned int capacity);

SCORE_BOOL score_buffer_clear(SCore_Buffer *buffer);

SCORE_BOOL score_buffer_has_data(SCore_Buffer *buffer);
uint32_t score_buffer_space_left(SCore_Buffer *buffer);

char *score_buffer_to_string(SCore_Buffer *buffer);

#endif
#else
#error "buffer.h included. SCORE_BUFFER needs to be defined."
#endif