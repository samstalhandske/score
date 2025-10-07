#ifndef SCORE_BUFFER_READER_H
#define SCORE_BUFFER_READER_H

#include "score/buffer/buffer.h"

typedef struct {
    Score_Buffer *buffer;
    unsigned int offset;
} Score_Buffer_Reader;

#endif