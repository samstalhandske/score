#ifndef SCORE_TYPES_H
#define SCORE_TYPES_H

#ifdef SCORE_ENABLE_ASSERTS
    #include <assert.h>
#endif

#ifdef SCORE_USE_STDINT
    #include <stdint.h>
#else
    typedef signed char         int8_t;
    typedef unsigned char       uint8_t;
    typedef signed short        int16_t;
    typedef unsigned short      uint16_t;
    typedef signed int          int32_t;
    typedef unsigned int        uint32_t;

    #if defined(__GNUC__) || defined(_MSC_VER)
        #ifndef i64_DEFINED
            typedef signed long long int64_t;
            #define i64_DEFINED
        #endif
        #ifndef u64_DEFINED
            typedef unsigned long long  uint64_t;
            #define u64_DEFINED
        #endif
    #endif
#endif

typedef uint8_t  u8;
typedef int8_t   i8;
typedef uint16_t u16;
typedef int16_t  i16;
typedef uint32_t u32;
typedef int32_t  i32;
typedef uint64_t u64;
typedef int64_t  i64;

#ifndef NULL
#define NULL 0
#endif

#ifndef __bool_true_false_are_defined
    typedef uint8_t bool;
    #define TRUE  1
    #define FALSE 0
    #define true  1
    #define false 0
#endif

#endif /* SCORE_TYPES_H */