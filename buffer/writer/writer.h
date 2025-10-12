#ifdef SCORE_BUFFER

#ifndef SCORE_BUFFER_WRITER_H
#define SCORE_BUFFER_WRITER_H

#include "score/buffer/buffer.h"

typedef struct {
    SCore_Buffer *buffer;
    uint32_t offset;
} SCore_Buffer_Writer;

SCore_Buffer_Writer score_buffer_writer_create(SCore_Buffer *buffer);
void score_buffer_writer_reset_offset(SCore_Buffer_Writer *writer);

SCORE_BOOL score_buffer_writer_write_u8(SCore_Buffer_Writer *writer, uint8_t value);
SCORE_BOOL score_buffer_writer_write_u16(SCore_Buffer_Writer *writer, uint16_t value);
SCORE_BOOL score_buffer_writer_write_u32(SCore_Buffer_Writer *writer, uint32_t value);

SCORE_BOOL score_buffer_writer_write_u8_ascii(SCore_Buffer_Writer *writer, uint8_t value);
SCORE_BOOL score_buffer_writer_write_u16_ascii(SCore_Buffer_Writer *writer, uint16_t value);
SCORE_BOOL score_buffer_writer_write_u32_ascii(SCore_Buffer_Writer *writer, uint32_t value);

SCORE_BOOL score_buffer_writer_write_string(SCore_Buffer_Writer *writer, const char *value);
SCORE_BOOL score_buffer_writer_write(SCore_Buffer_Writer *writer, void *ptr, unsigned int size);

#endif
#else
#error "writer.h included. SCORE_BUFFER needs to be defined."
#endif