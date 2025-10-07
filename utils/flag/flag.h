#ifdef SCORE_UTILS

#ifndef SCORE_FLAGS_H
#define SCORE_FLAGS_H

SCORE_BOOL score_has_any_flag_set(unsigned int flags);
SCORE_BOOL score_flag32_is_set(unsigned int flags, unsigned int flag);
SCORE_BOOL score_flag64_is_set(unsigned long flags, unsigned long flag);

#endif
#else
#error "flag.h included. SCORE_UTILS needs to be defined."
#endif