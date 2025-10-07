#ifdef SCORE_BUFFER

#ifndef SCORE_BUFFER_WRITER_H
#define SCORE_BUFFER_WRITER_H

#include "score/buffer/buffer.h"

typedef struct {
    Score_Buffer *buffer;
    unsigned int offset;
} Score_Buffer_Writer;

Score_Buffer_Writer score_buffer_writer_create(Score_Buffer *buffer);

bool score_buffer_writer_write_unsigned_char(Score_Buffer_Writer *writer, unsigned char value);
bool score_buffer_writer_write_char(Score_Buffer_Writer *writer, char value);
bool score_buffer_writer_write_string(Score_Buffer_Writer *writer, const char *value);
bool score_buffer_writer_write(Score_Buffer_Writer *writer, void *ptr, unsigned int size);

#endif
#else
#error "writer.h included. SCORE_BUFFER needs to be defined."
#endif