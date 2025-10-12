#ifdef SCORE_BUFFER

#include "writer.h"
#include "score/string/string.h"
#include "score/utils/endian/endian.h"
#include <stdio.h>
#include <string.h>

SCore_Buffer_Writer score_buffer_writer_create(SCore_Buffer *buffer) {
    SCore_Buffer_Writer w = {0};
    w.buffer = buffer;
    w.offset = 0;
    return w;
}

void score_buffer_writer_reset_offset(SCore_Buffer_Writer *writer) {
    assert(writer != NULL);
    writer->offset = 0;
}


SCORE_BOOL score_buffer_writer_write_u8(SCore_Buffer_Writer *writer, uint8_t value) {
    if(writer == NULL) {
        return SCORE_FALSE;
    }
    if(writer->buffer == NULL) {
        return SCORE_FALSE;
    }
    if(!score_buffer_has_data(writer->buffer)) {
        return SCORE_FALSE;
    }
    if(score_buffer_space_left(writer->buffer) == 0) {
        return SCORE_FALSE;
    }
    if(writer->offset >= writer->buffer->capacity) {
        return SCORE_FALSE;
    }

    ((uint8_t*)writer->buffer->data)[writer->offset] = value;

    writer->offset += 1;

    if(writer->offset > writer->buffer->length) {
        writer->buffer->length = writer->offset;
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_buffer_writer_write_u16(SCore_Buffer_Writer *writer, uint16_t value) {
    uint8_t bytes[2];

    if(writer == NULL) return SCORE_FALSE;
    if(writer->buffer == NULL) return SCORE_FALSE;
    if(!score_buffer_has_data(writer->buffer)) return SCORE_FALSE;
    if(score_buffer_space_left(writer->buffer) == 0) return SCORE_FALSE;
    if(writer->offset >= writer->buffer->capacity) return SCORE_FALSE;

    score_endian_u16_to_u8_array(SCORE_ENDIAN_LITTLE, value, bytes);

    {
        uint32_t i;
        for(i = 0; i < sizeof(bytes); i++) {
            if(!score_buffer_writer_write_u8(writer, bytes[i])) {
                return SCORE_FALSE;
            }
        }
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_buffer_writer_write_u32(SCore_Buffer_Writer *writer, uint32_t value) {
    uint8_t bytes[4];

    if(writer == NULL) return SCORE_FALSE;
    if(writer->buffer == NULL) return SCORE_FALSE;
    if(!score_buffer_has_data(writer->buffer)) return SCORE_FALSE;
    if(score_buffer_space_left(writer->buffer) == 0) return SCORE_FALSE;
    if(writer->offset >= writer->buffer->capacity) return SCORE_FALSE;

    score_endian_u32_to_u8_array(SCORE_ENDIAN_LITTLE, value, bytes);

    if(score_buffer_space_left(writer->buffer) < sizeof(bytes)) {
        return SCORE_FALSE;
    }

    {
        uint32_t i;
        for(i = 0; i < sizeof(bytes); i++) {
            if(!score_buffer_writer_write_u8(writer, bytes[i])) {
                return SCORE_FALSE;
            }
        }
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_buffer_writer_write_u8_ascii(SCore_Buffer_Writer *writer, uint8_t value) {
    char temp[4];
    int len;

    memset(&temp[0], '\0', sizeof(temp));
    sprintf(temp, "%u", value);

    for (len = 0; temp[len] != '\0'; len++) {
        if (!score_buffer_writer_write_u8(writer, (uint8_t)temp[len])) {
            return SCORE_FALSE;
        }
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_buffer_writer_write_u16_ascii(SCore_Buffer_Writer *writer, uint16_t value) {
    char temp[5 + 1];
    int len;

    memset(&temp[0], '\0', sizeof(temp));
    sprintf(temp, "%u", value);

    for (len = 0; temp[len] != '\0'; len++) {
        if (!score_buffer_writer_write_u8(writer, (uint8_t)temp[len])) {
            return SCORE_FALSE;
        }
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_buffer_writer_write_u32_ascii(SCore_Buffer_Writer *writer, uint32_t value) {
    char temp[10];
    int len;

    memset(&temp[0], '\0', sizeof(temp));
    sprintf(temp, "%u", (uint32_t)value);

    for (len = 0; temp[len] != '\0'; len++) {
        if (!score_buffer_writer_write_u8(writer, (uint8_t)temp[len])) {
            return SCORE_FALSE;
        }
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_buffer_writer_write_string(SCore_Buffer_Writer *writer, const char *value) {
    uint32_t len = 0;
    uint32_t i = 0;

    if(!score_string_length(value, &len)) {
        return SCORE_FALSE;
    }

    for(i = 0; i < len; i++) {
        if(!score_buffer_writer_write_u8(writer, value[i])) {
            break;
        }
    }

    return SCORE_TRUE;
}



SCORE_BOOL score_buffer_writer_write(SCore_Buffer_Writer *writer, void *ptr, uint32_t size) {
    unsigned char *char_data = NULL;

    if(ptr == NULL) {
        return SCORE_FALSE;
    }

    char_data = (unsigned char*)ptr;
    assert(char_data != NULL);

    {
        uint32_t i;
        for(i = 0; i < size; i++) {
            if(!score_buffer_writer_write_u8(writer, char_data[i])) {
                return SCORE_FALSE;
            }
        }
    }

    return SCORE_TRUE;
}

#endif