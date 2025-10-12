#ifdef SCORE_ALLOCATOR

#ifndef SCORE_ALLOCATOR_H
#define SCORE_ALLOCATOR_H

typedef bool (*score_allocator_alloc)(uint32_t size);

typedef struct {
    const char *name;

    score_allocator_alloc allocate;
} SCore_Allocator;

#endif
#error "allocator.h included. SCORE_ALLOCATOR needs to be defined."
#endif