#include "flag.h"

SCORE_BOOL score_flag_add(SCore_Flags *flags, SCore_Flag flag) {
    if(score_flag_is_set(*flags, flag)) {
        return SCORE_FALSE; /* Already set. */
    }

    *flags |= flag;
    return SCORE_TRUE;
}

SCORE_BOOL score_flag_remove(SCore_Flags *flags, SCore_Flag flag) {
    if(!score_flag_is_set(*flags, flag)) {
        return SCORE_FALSE; /* Not set. */
    }

    *flags &= ~flag;
    return SCORE_TRUE;
}

SCORE_BOOL score_flag_is_set(const SCore_Flags flags, SCore_Flag flag) {
    if((flags & flag) == 0) {
        return SCORE_FALSE;
    }

    return SCORE_TRUE;
}

SCORE_BOOL score_flag_has_any(const SCore_Flags flags) {
    if(flags == 0) {
        return SCORE_FALSE;
    }

    return SCORE_TRUE;
}