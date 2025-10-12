#ifdef SCORE_TIME_NOW

#ifndef TIME_NOW_H
#define TIME_NOW_H

#include "score/time/time.h"
#include <string.h>

SCore_Time score_time_now();

#endif

#else
#error "now.h included. SCORE_TIME_NOW needs to be defined."
#endif