#ifdef SCORE_BUFFER

#ifndef SCORE_BUFFER_WRITER_H
#define SCORE_BUFFER_WRITER_H

#include "score/buffer/buffer.h"

typedef struct {
    SCore_Buffer *buffer;
    unsigned int offset;
} SCore_Buffer_Writer;

SCore_Buffer_Writer score_buffer_writer_create(SCore_Buffer *buffer);

SCORE_BOOL score_buffer_writer_write_unsigned_char(SCore_Buffer_Writer *writer, unsigned char value);
SCORE_BOOL score_buffer_writer_write_char(SCore_Buffer_Writer *writer, char value);
SCORE_BOOL score_buffer_writer_write_string(SCore_Buffer_Writer *writer, const char *value);
SCORE_BOOL score_buffer_writer_write(SCore_Buffer_Writer *writer, void *ptr, unsigned int size);

#endif
#else
#error "writer.h included. SCORE_BUFFER needs to be defined."
#endif