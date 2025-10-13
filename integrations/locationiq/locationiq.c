#if SCORE_INTEGRATIONS_LOCATIONIQ
#include "locationiq.h"

#include "score/http/http.h"
#include "score/json/json.h"
#include "score/buffer/writer/writer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SCORE_BOOL score_locationiq_search(SCore_LocationIQ_Access_Token access_token, const char *location, SCore_LocationIQ_Response *out_response) {
    SCore_Http http;
    (void)access_token;
    if(!score_http_initialize(&http)) {
        return SCORE_FALSE;
    }

    if(location == NULL) {
        return SCORE_FALSE;
    }

    {
        uint8_t url_backing[256];
        SCore_Buffer url_buffer = score_buffer_create_from_backing(&url_backing[0], sizeof(url_backing));
        SCore_Buffer_Writer url_buffer_writer = score_buffer_writer_create(&url_buffer);

        if(!score_buffer_writer_write_string(&url_buffer_writer, "https://")) {
            printf("Failed to write https\n");
            return SCORE_FALSE;
        }
        if(!score_buffer_writer_write_string(&url_buffer_writer, "eu1")) { /* TODO: SS - Switch on region. 'eu1' or 'us1'.*/
            printf("Failed to write region\n");
            return SCORE_FALSE;
        }
        if(!score_buffer_writer_write_string(&url_buffer_writer, ".locationiq.com/v1/search?key=")) {
            printf("Failed to write some of url\n");
            return SCORE_FALSE;
        }
        if(!score_buffer_writer_write_string(&url_buffer_writer, access_token)) {
            printf("Failed to write accesstoken\n");
            return SCORE_FALSE;
        }
        if(!score_buffer_writer_write_string(&url_buffer_writer, "&q=")) {
            printf("Failed to write query\n");
            return SCORE_FALSE;
        }
        if(!score_buffer_writer_write_string(&url_buffer_writer, location)) {
            printf("Failed to write location\n");
            return SCORE_FALSE;
        }
        if(!score_buffer_writer_write_string(&url_buffer_writer, "&format=json")) {
            printf("Failed to write format\n");
            return SCORE_FALSE;
        }

        {
            SCore_Http_Response http_response = {0};
            SCore_JSON_Object root_json_object = {0};
            SCore_JSON_Array json_array_locations = {0};

            char * url_as_string = score_buffer_to_string(&url_buffer);
            if(!score_http_perform(&http, url_as_string, &http_response)) {
                printf("Failed to perform\n");
                free(url_as_string);
                return SCORE_FALSE;
            }

            free(url_as_string);

            /*printf("Got data: '%s'.\n", http_response.data);*/

            if(!score_json_parse(http_response.data, &root_json_object)) {
                score_http_dispose_response(&http_response);
                return SCORE_FALSE;
            }

            assert(score_json_as_array(&root_json_object, &json_array_locations));
            {
                uint32_t i;
                for(i = 0; i < json_array_locations.size; i++) {
                    SCore_JSON_Object *obj = NULL;
                    SCore_LocationIQ_Location *loc = NULL;

                    if(i >= SCORE_LOCATIONIQ_MAX_LOCATIONS) {
                        break;
                    }

                    assert(score_json_get_array_element(&json_array_locations, i, &obj));

                    loc = &out_response->locations[out_response->locations_found];
                    assert(loc != NULL);

                    {
                        { /* Display-name. */
                            SCore_JSON_Object loc_obj;
                            char *v = NULL;
                            SCore_Buffer name_buffer;
                            SCore_Buffer_Writer name_writer;

                            assert(score_json_get_object(obj, "display_name", SCORE_TRUE, &loc_obj));
                            assert(score_json_as_string(&loc_obj, &v));

                            memset(&loc->name[0], 0, SCORE_LOCATIONIQ_MAX_LOCATION_NAME_LENGTH);

                            name_buffer = score_buffer_create_from_backing(&loc->name[0], SCORE_LOCATIONIQ_MAX_LOCATION_NAME_LENGTH);
                            name_writer = score_buffer_writer_create(&name_buffer);
                            score_buffer_writer_write_string(&name_writer, v);
                        }
                        { /* Longitude. */
                            SCore_JSON_Object loc_obj;
                            char *v = NULL;
                            char *end_ptr = NULL;
                            assert(score_json_get_object(obj, "lon", SCORE_TRUE, &loc_obj));
                            assert(score_json_as_string(&loc_obj, &v));

                            loc->coordinate.longitude = (f32)strtod(v, &end_ptr);
                        }
                        { /* Latitude. */
                            SCore_JSON_Object loc_obj;
                            char *v = NULL;
                            char *end_ptr = NULL;
                            assert(score_json_get_object(obj, "lat", SCORE_TRUE, &loc_obj));
                            assert(score_json_as_string(&loc_obj, &v));

                            loc->coordinate.latitude = (f32)strtod(v, &end_ptr);
                        }
                    }

                    out_response->locations_found += 1;
                }
            }

            assert(score_json_array_dispose(&json_array_locations));
            score_http_dispose_response(&http_response);
            score_json_dispose(&root_json_object);
        }
    }

    score_http_dispose(&http);

    return SCORE_TRUE;
}

#endif