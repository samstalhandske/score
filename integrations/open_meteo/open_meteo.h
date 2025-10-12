#ifdef SCORE_INTEGRATIONS_OPEN_METEO

#ifndef OPEN_METEO_H
#define OPEN_METEO_H

/* https://open-meteo.com/en/docs */

/*
TODO: SS - Move open_meteo files to SCore.
Replace 'date.h' with score/time/time.h.
*/

#include "score/buffer/writer/writer.h"
#include "score/utils/flag/flag.h"
#include "score/json/json.h"
#include "score/string/string.h"
#include "score/time/time.h"

typedef struct {
    double latitude;
    double longitude;
} Open_Meteo_Coordinate;

typedef enum {
    Open_Meteo_Unit_Celsius,
    Open_Meteo_Unit_Fahrenheit,
    Open_Meteo_Unit_Millimeter,
    Open_Meteo_Unit_Kilometers_Per_Hour
} Open_Meteo_Unit;

SCORE_BOOL open_meteo_string_to_unit(const char *str, Open_Meteo_Unit *unit);

typedef struct {
    SCORE_BOOL temperature_2m;
    SCORE_BOOL temperature_80m;
    SCORE_BOOL temperature_120m;
    SCORE_BOOL temperature_180m;
    SCORE_BOOL relative_humidity_2m;
    SCORE_BOOL dewpoint_2m;
    SCORE_BOOL apparent_temperature;
    SCORE_BOOL precipitation_probability;
    SCORE_BOOL precipitation;
    SCORE_BOOL rain;
    SCORE_BOOL showers;
    SCORE_BOOL snowfall;
    SCORE_BOOL snow_depth;
    SCORE_BOOL weather_code;
    SCORE_BOOL sealevel_pressure;
    SCORE_BOOL surface_pressure;
    SCORE_BOOL cloud_cover_total;
    SCORE_BOOL cloud_cover_low;
    SCORE_BOOL cloud_cover_mid;
    SCORE_BOOL cloud_cover_high;
    SCORE_BOOL visibility;
    SCORE_BOOL evapotranspiration;
    SCORE_BOOL reference_evapotranspiration;
    SCORE_BOOL vapour_pressure_deficit;
    SCORE_BOOL wind_speed_10m;
    SCORE_BOOL wind_speed_80m;
    SCORE_BOOL wind_speed_120m;
    SCORE_BOOL wind_speed_180m;
    SCORE_BOOL wind_direction_10m;
    SCORE_BOOL wind_direction_80m;
    SCORE_BOOL wind_direction_120m;
    SCORE_BOOL wind_direction_180m;
    SCORE_BOOL wind_gusts_10m;
    SCORE_BOOL soil_temperature_0cm;
    SCORE_BOOL soil_temperature_6cm;
    SCORE_BOOL soil_temperature_18cm;
    SCORE_BOOL soil_temperature_54cm;
    SCORE_BOOL soil_moisture_0_1cm;
    SCORE_BOOL soil_moisture_1_3cm;
    SCORE_BOOL soil_moisture_3_9cm;
    SCORE_BOOL soil_moisture_9_27cm;
    SCORE_BOOL soil_moisture_27_81cm;
} Open_Meteo_Hourly_Flags;

typedef struct {
    Open_Meteo_Coordinate coordinate;
    unsigned char past_days;
    unsigned char forecast_days;

    Open_Meteo_Unit temperature_unit;

    SCore_Flags current_flags;
    Open_Meteo_Hourly_Flags hourly_flags;
    SCore_Flags daily_flags;

} Open_Meteo_Data_Request;

typedef struct {
    SCORE_BOOL is_set;
    Open_Meteo_Unit unit; /* Kind of unnecessary cause now every temperature instance will have this with the same value. */
    f32 temperature;
    uint8_t meters_above_ground;
} Open_Meteo_Report_Temperature;

typedef struct {
    SCORE_BOOL is_set;

} Open_Meteo_Report_Wind_Speed;

typedef struct {
    SCORE_BOOL is_set;
    Open_Meteo_Unit unit;
    f32 value;
} Open_Meteo_Report_Rain;

typedef struct {
    SCore_Time date_time; /* TODO: SS - Rename. */

    Open_Meteo_Report_Temperature apparent_temperature;

    Open_Meteo_Report_Temperature temperature_2m;
    Open_Meteo_Report_Temperature temperature_80m;
    Open_Meteo_Report_Temperature temperature_120m;
    Open_Meteo_Report_Temperature temperature_180m;

    Open_Meteo_Report_Wind_Speed wind_speed_10m;
    Open_Meteo_Report_Wind_Speed wind_speed_80m;
    Open_Meteo_Report_Wind_Speed wind_speed_120m;
    Open_Meteo_Report_Wind_Speed wind_speed_180m;

    Open_Meteo_Report_Rain rain;
} Open_Meteo_Report_Hourly_Entry;

typedef struct {
    SCore_Time date_time; /* TODO: SS - Rename. */
} Open_Meteo_Report_Daily_Entry;

/* TODO: SS - Parse the current/hourly/daily_units. */

typedef struct {
    SCore_Time date_time; /* TODO: SS - Rename. */
    uint32_t flags;
} Open_Meteo_Report_Current;

typedef struct {
    Open_Meteo_Hourly_Flags flags;
    Open_Meteo_Report_Hourly_Entry* entries;
    uint32_t entry_count;

} Open_Meteo_Report_Hourly;

typedef struct {
    Open_Meteo_Report_Daily_Entry* entries;
    uint32_t entry_count;
    uint32_t flags;
} Open_Meteo_Report_Daily;


typedef struct {
    uint8_t timezone_abbreviation[8];

    Open_Meteo_Report_Current current;
    Open_Meteo_Report_Hourly hourly;
    Open_Meteo_Report_Daily daily;
} Open_Meteo_Report;

void open_meteo_write_url_to_writer(SCore_Buffer_Writer *writer, const Open_Meteo_Data_Request *data_request);

SCORE_BOOL open_meteo_create_report_from_json_object(const SCore_JSON_Object *json_object, uint32_t current_flags, Open_Meteo_Hourly_Flags hourly_flags, uint32_t daily_flags, Open_Meteo_Report *out_report);

#endif /* OPEN_METEO_H */
#else
#error "open_meteo.h included. SCORE_INTEGRATIONS_OPEN_METEO needs to be defined."
#endif
