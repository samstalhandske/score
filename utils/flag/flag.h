#ifdef SCORE_UTILS

#ifndef SCORE_FLAGS_H
#define SCORE_FLAGS_H

typedef uint32_t SCore_Flags;
typedef uint32_t SCore_Flag;

SCORE_BOOL score_flag_add(SCore_Flags *flags, SCore_Flag flag);
SCORE_BOOL score_flag_remove(SCore_Flags *flags, SCore_Flag flag);
SCORE_BOOL score_flag_is_set(const SCore_Flags flags, SCore_Flag flag);
SCORE_BOOL score_flag_has_any(const SCore_Flags flags);

#endif
#else
#error "flag.h included. SCORE_UTILS needs to be defined."
#endif