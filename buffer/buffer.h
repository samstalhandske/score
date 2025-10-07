#ifdef SCORE_BUFFER

#ifndef SCORE_BUFFER_H
#define SCORE_BUFFER_H

typedef struct {
    const void *data;
    unsigned int capacity;
    unsigned int length;
} SCore_Buffer;

void score_buffer_init_using_backing(SCore_Buffer *buffer, void *ptr_to_backing, unsigned int capacity);
SCore_Buffer score_buffer_create_from_backing(const void *ptr_to_backing, unsigned int capacity);

SCORE_BOOL score_buffer_has_data(SCore_Buffer *buffer);

#endif
#else
#error "buffer.h included. SCORE_BUFFER needs to be defined."
#endif