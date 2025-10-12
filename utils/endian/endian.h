#ifdef SCORE_UTILS

#ifndef SCORE_ENDIAN_H
#define SCORE_ENDIAN_H

typedef enum {
    SCORE_ENDIAN_LITTLE, /* Low byte first. */
    SCORE_ENDIAN_BIG /* High byte first. */
} SCore_Endian;

void score_endian_u16(const SCore_Endian e, const uint16_t v, uint8_t  *out_0, uint8_t  *out_1);
void score_endian_u32(const SCore_Endian e, const uint32_t v, uint16_t *out_0, uint16_t *out_1);

void score_endian_u16_to_u8_array(const SCore_Endian e, const uint16_t v, uint8_t out[2]);
void score_endian_u32_to_u8_array(const SCore_Endian e, const uint32_t v, uint8_t out[4]);

void score_endian_u32_to_u16_array(const SCore_Endian e, const uint32_t v, uint16_t out[2]);

#endif
#else
#error "endian.h included. SCORE_UTILS needs to be defined."
#endif