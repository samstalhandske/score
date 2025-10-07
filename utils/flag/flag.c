#include "flag.h"

SCORE_BOOL score_has_any_flag_set(unsigned int flags) {
    return flags > 0;
}

SCORE_BOOL score_flag32_is_set(unsigned int flags, unsigned int flag) {
    return (flags & flag) != 0;
}
SCORE_BOOL score_flag64_is_set(unsigned long flags, unsigned long flag) {
    return (flags & flag) != 0;
}