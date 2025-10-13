#if SCORE_INTEGRATIONS_LOCATIONIQ
#ifndef SCORE_INTEGRATIONS_LOCATIONIQ_H
#define SCORE_INTEGRATIONS_LOCATIONIQ_H

/*

https://locationiq.com/

Search for locations and get their longitude and latitude,
or the other way around.

*/

#include "score/json/json.h"

#ifndef SCORE_LOCATIONIQ_MAX_LOCATION_NAME_LENGTH
#define SCORE_LOCATIONIQ_MAX_LOCATION_NAME_LENGTH 128
#endif

typedef const char * SCore_LocationIQ_Access_Token;

typedef struct {
    f32 longitude;
    f32 latitude;
} SCore_LocationIQ_Coordinate;

typedef struct {
    uint8_t name[SCORE_LOCATIONIQ_MAX_LOCATION_NAME_LENGTH];
    SCore_LocationIQ_Coordinate coordinate;
} SCore_LocationIQ_Location;

#ifndef SCORE_LOCATIONIQ_MAX_LOCATIONS
#define SCORE_LOCATIONIQ_MAX_LOCATIONS 8
#endif

typedef struct {
    SCore_LocationIQ_Location locations[SCORE_LOCATIONIQ_MAX_LOCATIONS];
    uint8_t locations_found;
} SCore_LocationIQ_Response;

SCORE_BOOL score_locationiq_search(SCore_LocationIQ_Access_Token access_token, const char *location, SCore_LocationIQ_Response *out_response);

#endif
#else
#error "locationiq.h included. SCORE_INTEGRATIONS_LOCATIONIQ needs to be defined."
#endif