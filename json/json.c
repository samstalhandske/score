#ifdef SCORE_JSON

#ifdef SCORE_JSON_CJSON
#elif SCORE_JSON_JANSSON
#else
#error "No JSON backend defined, select one: 'SCORE_JSON_CJSON' or 'SCORE_JSON_JANSSON'."
#endif

#endif