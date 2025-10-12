#ifdef SCORE_TIME_NOW

#if !defined(SCORE_TIME_NOW_LINUX) && !defined(SCORE_TIME_NOW_WINDOWS)
#error "No backend defined. Define 'SCORE_TIME_NOW_LINUX' or 'SCORE_TIME_NOW_WINDOWS'."
#endif

#include "now.h"
#include <stdio.h>

#if defined(SCORE_TIME_NOW_LINUX)

#define _POSIX_C_SOURCE 200809L
#include <time.h>
#include <sys/time.h>

SCore_Time score_time_now() {
    struct timeval tv;
    struct tm *tm_ptr;
    SCore_Time time;

    memset(&time, 0, sizeof(SCore_Time));

    assert(gettimeofday(&tv, NULL) == 0);

    tm_ptr = gmtime(&tv.tv_sec);
    assert(tm_ptr != NULL);

    score_time_set_iso_8601(&time,
        (uint16_t)(tm_ptr->tm_year + 1900),
        (uint8_t)(tm_ptr->tm_mon + 1),
        (uint8_t)(tm_ptr->tm_mday),
        (uint8_t)(tm_ptr->tm_hour),
        (uint8_t)(tm_ptr->tm_min),
        (double)tm_ptr->tm_sec + ((double)tv.tv_usec / 1e6)
    );

    return time;
}
#else

#endif

#endif