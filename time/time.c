#ifdef SCORE_TIME
#include "time.h"

#include <stdio.h>
#include <string.h>

static SCORE_BOOL is_leap_year(const uint16_t year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

static uint16_t get_days_in_year(const uint16_t year) {
    if(is_leap_year(year)) {
        return 366;
    }

    return 365;
}

static void get_length_of_months_for_year(const uint16_t year, uint8_t out_month_lengths[12]) {
    out_month_lengths[0]  = 31;
    out_month_lengths[1]  = is_leap_year(year) ? 29 : 28;
    out_month_lengths[2]  = 31;
    out_month_lengths[3]  = 30;
    out_month_lengths[4]  = 31;
    out_month_lengths[5]  = 30;
    out_month_lengths[6]  = 31;
    out_month_lengths[7]  = 31;
    out_month_lengths[8]  = 30;
    out_month_lengths[9]  = 31;
    out_month_lengths[10] = 30;
    out_month_lengths[11] = 31;
}

SCORE_BOOL score_time_set_iso_8601(SCore_Time *time, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, f32 second) {
    SCore_Time_ISO_8601 iso;
    iso.year = year;
    iso.month = month;
    iso.day = day;
    iso.hour = hour;
    iso.minute = minute;
    iso.second = second;

    time->iso = iso;

    return score_time_iso_8601_to_unix(time->iso, &time->unix);
}

SCORE_BOOL score_time_set_unix(SCore_Time *time, uint32_t seconds_since_1970_01_01, uint16_t milliseconds) {
    SCore_Time_UNIX unix;
    unix.seconds_since_1970_01_01 = seconds_since_1970_01_01;
    unix.milliseconds = milliseconds;

    time->unix = unix;

    return score_time_unix_to_iso_8601(time->unix, &time->iso);
}

SCORE_BOOL score_time_iso_8601_to_unix(const SCore_Time_ISO_8601 iso, SCore_Time_UNIX *out_unix_time) {
    if (iso.year < 1970 || iso.month < 1 || iso.month > 12 || iso.day < 1) {
        return SCORE_FALSE;
    }

    {
        uint32_t days = 0;
        uint8_t month_lengths[12];
        get_length_of_months_for_year(iso.year, month_lengths);

        if (iso.day > month_lengths[iso.month - 1]) {
            return SCORE_FALSE;
        }

        {
            uint16_t year;
            for (year = 1970; year < iso.year; ++year) {
                days += get_days_in_year(year);
            }
        }

        {
            uint8_t month;
            for (month = 0; month < iso.month - 1; ++month) {
                days += month_lengths[month];
            }
        }

        days += (iso.day - 1);

        {
            uint32_t total_seconds =
                    days * 86400UL +
                    (uint32_t)iso.hour * 3600UL +
                    (uint32_t)iso.minute * 60UL +
                    (uint32_t)iso.second;

            double fractional = iso.second - (uint32_t)iso.second;
            uint16_t ms = (uint16_t)(fractional * 1000.0 + 0.5);

            out_unix_time->seconds_since_1970_01_01 = total_seconds;
            out_unix_time->milliseconds = ms;
        }
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_time_unix_to_iso_8601(const SCore_Time_UNIX unix_time, SCore_Time_ISO_8601 *out_iso_time) {
    uint32_t seconds = unix_time.seconds_since_1970_01_01;
    uint32_t days = seconds / 86400UL;
    uint32_t rem  = seconds % 86400UL;
    const uint16_t start_year = 1970;
    uint16_t target_year = start_year;
    uint8_t month_lengths[12];
    memset(&month_lengths, 0, sizeof(month_lengths));

    out_iso_time->hour   = (uint8_t)(rem / 3600UL);
    rem %= 3600UL;
    out_iso_time->minute = (uint8_t)(rem / 60UL);
    out_iso_time->second = (double)(rem % 60UL) + unix_time.milliseconds / 1000.0;

    while (1) {
        uint16_t year_days = get_days_in_year(target_year);
        if (days < year_days) {
            break;
        }
        days -= year_days;
        target_year++;
    }
    out_iso_time->year = target_year;

    get_length_of_months_for_year(target_year, month_lengths);

    {
        uint8_t month = 0;
        while (days >= (uint32_t)month_lengths[month]) {
            days -= month_lengths[month];
            month++;
            if (month >= 12) { month = 11; break; }
        }

        out_iso_time->month = (uint8_t)(month + 1);
        out_iso_time->day   = (uint8_t)(days + 1);
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_time_write_iso_8601_to_buffer(const SCore_Time *time, SCore_Buffer_Writer *writer) {
    if(time == NULL) {
        return SCORE_FALSE;
    }
    if(writer == NULL) {
        return SCORE_FALSE;
    }

    if(!score_buffer_writer_write_u16_ascii(writer, time->iso.year)) {
        return SCORE_FALSE;
    }
    if(!score_buffer_writer_write_u8(writer, '-')) {
        return SCORE_FALSE;
    }
    if(!score_buffer_writer_write_u8_ascii(writer, time->iso.month)) {
        return SCORE_FALSE;
    }
    if(!score_buffer_writer_write_u8(writer, '-')) {
        return SCORE_FALSE;
    }
    if(!score_buffer_writer_write_u8_ascii(writer, time->iso.day)) {
        return SCORE_FALSE;
    }
    if(!score_buffer_writer_write_u8(writer, ' ')) {
        return SCORE_FALSE;
    }
    if(!score_buffer_writer_write_u8_ascii(writer, time->iso.hour)) {
        return SCORE_FALSE;
    }
    if(!score_buffer_writer_write_u8(writer, ':')) {
        return SCORE_FALSE;
    }
    if(!score_buffer_writer_write_u8_ascii(writer, time->iso.minute)) {
        return SCORE_FALSE;
    }
    if(!score_buffer_writer_write_u8(writer, ':')) {
        return SCORE_FALSE;
    }
    if(!score_buffer_writer_write_u8_ascii(writer, time->iso.second)) { /* Seconds gets truncated. */
        return SCORE_FALSE;
    }

    if(!score_buffer_writer_write_u8(writer, '\0')) {
        return SCORE_FALSE;
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_time_write_unix_to_buffer(const SCore_Time *time, SCore_Buffer_Writer *writer) {
    if(time == NULL) {
        return SCORE_FALSE;
    }
    if(writer == NULL) {
        return SCORE_FALSE;
    }

    if(!score_buffer_writer_write_u32_ascii(writer, time->unix.seconds_since_1970_01_01)) {
        return SCORE_FALSE;
    }

    /*
    NOTE: SS - This works but I'm not sure that I want to display it
    because ISO doesn't show ms.

    if(!score_buffer_writer_write_u8(writer, '.')) {
        return SCORE_FALSE;
    }
    if(!score_buffer_writer_write_u16_ascii(writer, time->unix.milliseconds)) {
        return SCORE_FALSE;
    }
    */

    if(!score_buffer_writer_write_u8(writer, '\0')) {
        return SCORE_FALSE;
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_time_from_json(const SCore_JSON_Object *json_object, SCore_Time *out_time) {
    char *time_format = NULL;

    if(!score_json_is_string(json_object)) {
        return SCORE_FALSE;
    }

    assert(score_json_as_string(json_object, &time_format));

    {
        uint32_t year = 0;
        uint32_t month = 0;
        uint32_t day = 0;

        uint32_t hour = 0;
        uint32_t minute = 0;

        int32_t result = sscanf(time_format,
            "%u-%u-%u"
            "T"
            "%u:%u",
            &year, &month, &day,
            &hour, &minute
        );
        if(result == 0) {
            return SCORE_FALSE;
        }

        score_time_set_iso_8601(
            out_time,
            (uint16_t)year, (uint8_t)month, (uint8_t)day,
            (uint8_t)hour, (uint8_t)minute, 0
        );
    }

    return SCORE_TRUE;
}

#endif