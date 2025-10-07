#ifdef SCORE_BUFFER

#include "writer.h"
#include "score/string/string.h"

Score_Buffer_Writer score_buffer_writer_create(Score_Buffer *buffer) {
    Score_Buffer_Writer w = {0};
    w.buffer = buffer;
    w.offset = 0;
    return w;
}

bool score_buffer_writer_write_unsigned_char(Score_Buffer_Writer *writer, unsigned char value) {
    if(writer == NULL) return false;
    if(writer->buffer == NULL) return false;
    if(!score_buffer_has_data(writer->buffer)) return false;
    if(writer->offset >= writer->buffer->capacity) return false;

    ((unsigned char*)writer->buffer->data)[writer->offset] = value;

    writer->offset += 1;

    if(writer->offset > writer->buffer->length) {
        writer->buffer->length = writer->offset;
    }

    return true;
}

bool score_buffer_writer_write_char(Score_Buffer_Writer *writer, char value) {
    if(writer == NULL) return false;
    if(writer->buffer == NULL) return false;
    if(!score_buffer_has_data(writer->buffer)) return false;
    if(writer->offset >= writer->buffer->capacity) return false;

    ((char*)writer->buffer->data)[writer->offset] = value;

    writer->offset += 1;

    if (writer->offset > writer->buffer->length) {
        writer->buffer->length = writer->offset;
    }

    return true;
}

bool score_buffer_writer_write_string(Score_Buffer_Writer *writer, const char *value) {
    unsigned int len = 0;
    if(!score_string_length(value, &len)) {
        return false;
    }

    unsigned int i;
    for(i = 0; i < len; i++) {
        if(!score_buffer_writer_write_char(writer, value[i])) {
            break;;
        }
    }

    return true;
}

bool score_buffer_writer_write(Score_Buffer_Writer *writer, void *ptr, unsigned int size) {
    if(ptr == NULL) {
        return false;
    }

    unsigned char *data = (unsigned char*)ptr;

    unsigned int i;
    for(i = 0; i < size; i++) {
        if(!score_buffer_writer_write_unsigned_char(writer, data[i])) {
            return false;
        }
    }

    return true;
}

#endif