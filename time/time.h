#ifdef SCORE_TIME

#ifndef TIME_H
#define TIME_H

#include "score/buffer/writer/writer.h"

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    f32 second;
} SCore_Time_ISO_8601;

typedef struct {
    uint32_t seconds_since_1970_01_01; /* Seconds since 1970-01-01. */
    uint16_t milliseconds;
} SCore_Time_UNIX;

typedef struct {
    SCore_Time_ISO_8601 iso;
    SCore_Time_UNIX unix;
} SCore_Time;

SCORE_BOOL score_time_set_iso_8601(SCore_Time *time, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, f32 second);
SCORE_BOOL score_time_set_unix(SCore_Time *time, uint32_t seconds_since_1970_01_01, uint16_t milliseconds);

SCORE_BOOL score_time_iso_8601_to_unix(const SCore_Time_ISO_8601 iso_time, SCore_Time_UNIX *out_unix_time);
SCORE_BOOL score_time_unix_to_iso_8601(const SCore_Time_UNIX unix_time, SCore_Time_ISO_8601 *out_iso_time);

SCORE_BOOL score_time_write_iso_8601_to_buffer(const SCore_Time *time, SCore_Buffer_Writer *writer);
SCORE_BOOL score_time_write_unix_to_buffer(const SCore_Time *time, SCore_Buffer_Writer *writer);

#endif

#else
#error "time.h included. SCORE_TIME needs to be defined."
#endif