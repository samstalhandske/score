#ifndef SCORE_TYPES_H
#define SCORE_TYPES_H

#include <limits.h>
#include <assert.h>

typedef unsigned char uint8_t;
typedef signed char int8_t;

#if USHRT_MAX == 0xFFFF
typedef unsigned short uint16_t;
typedef signed short int16_t;
#else
#error "No suitable 16-bit type"
#endif

#if UINT_MAX == 0xFFFFFFFF
typedef unsigned int uint32_t;
typedef signed int int32_t;
#elif ULONG_MAX == 0xFFFFFFFF
typedef unsigned long uint32_t;
typedef signed long int32_t;
#else
#error "No suitable 32-bit type"
#endif

typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint32_t u32;
typedef int32_t i32;
typedef float f32;

#ifndef NULL
#define NULL 0
#endif

typedef uint8_t SCORE_BOOL;
#define SCORE_TRUE 1
#define SCORE_FALSE 0

#endif /* SCORE_TYPES_H */
