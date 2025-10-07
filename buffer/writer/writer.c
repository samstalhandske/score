#ifdef SCORE_BUFFER

#include "writer.h"
#include "score/string/string.h"

SCore_Buffer_Writer score_buffer_writer_create(SCore_Buffer *buffer) {
    SCore_Buffer_Writer w = {0};
    w.buffer = buffer;
    w.offset = 0;
    return w;
}

SCORE_BOOL score_buffer_writer_write_unsigned_char(SCore_Buffer_Writer *writer, unsigned char value) {
    if(writer == NULL) return SCORE_FALSE;
    if(writer->buffer == NULL) return SCORE_FALSE;
    if(!score_buffer_has_data(writer->buffer)) return SCORE_FALSE;
    if(writer->offset >= writer->buffer->capacity) return SCORE_FALSE;

    ((unsigned char*)writer->buffer->data)[writer->offset] = value;

    writer->offset += 1;

    if(writer->offset > writer->buffer->length) {
        writer->buffer->length = writer->offset;
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_buffer_writer_write_char(SCore_Buffer_Writer *writer, char value) {
    if(writer == NULL) return SCORE_FALSE;
    if(writer->buffer == NULL) return SCORE_FALSE;
    if(!score_buffer_has_data(writer->buffer)) return SCORE_FALSE;
    if(writer->offset >= writer->buffer->capacity) return SCORE_FALSE;

    ((char*)writer->buffer->data)[writer->offset] = value;

    writer->offset += 1;

    if (writer->offset > writer->buffer->length) {
        writer->buffer->length = writer->offset;
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_buffer_writer_write_string(SCore_Buffer_Writer *writer, const char *value) {
    unsigned int len = 0;
    if(!score_string_length(value, &len)) {
        return SCORE_FALSE;
    }

    unsigned int i;
    for(i = 0; i < len; i++) {
        if(!score_buffer_writer_write_char(writer, value[i])) {
            break;;
        }
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_buffer_writer_write(SCore_Buffer_Writer *writer, void *ptr, unsigned int size) {
    if(ptr == NULL) {
        return SCORE_FALSE;
    }

    unsigned char *data = (unsigned char*)ptr;

    unsigned int i;
    for(i = 0; i < size; i++) {
        if(!score_buffer_writer_write_unsigned_char(writer, data[i])) {
            return SCORE_FALSE;
        }
    }

    return SCORE_TRUE;
}

#endif