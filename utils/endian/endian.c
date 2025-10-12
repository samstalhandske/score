#ifdef SCORE_UTILS
#include "endian.h"

void score_endian_u16(const SCore_Endian e, const uint16_t v, uint8_t *out_0, uint8_t *out_1) {
    const uint8_t mask = 0xFF;
    if (e == SCORE_ENDIAN_LITTLE) {
        *out_1 = (uint8_t)(v & mask);
        *out_0 = (uint8_t)((v >> 8) & mask);
    } else {
        *out_0 = (uint8_t)(v & mask);
        *out_1 = (uint8_t)((v >> 8) & mask);
    }
}

void score_endian_u32(const SCore_Endian e, const uint32_t v, uint16_t *out_0, uint16_t *out_1) {
    const uint32_t mask = 0xFFFF;
    if (e == SCORE_ENDIAN_LITTLE) {
        *out_1 = (uint16_t)(v & mask);
        *out_0 = (uint16_t)((v >> 16) & mask);
    } else {
        *out_0 = (uint16_t)(v & mask);
        *out_1 = (uint16_t)((v >> 16) & mask);
    }
}

void score_endian_u16_to_u8_array(const SCore_Endian e, const uint16_t v, uint8_t out[2]) {
    score_endian_u16(e, v, &out[0], &out[1]);
}

void score_endian_u32_to_u8_array(const SCore_Endian e, const uint32_t v, uint8_t out[4]) {
    uint16_t high16, low16;
    score_endian_u32(e, v, &high16, &low16);

    score_endian_u16(e, high16, &out[0], &out[1]);
    score_endian_u16(e, low16,  &out[2], &out[3]);
}

void score_endian_u32_to_u16_array(const SCore_Endian e, const uint32_t v, uint16_t out[2]) {
    score_endian_u32(e, v, &out[0], &out[1]);
}

#endif