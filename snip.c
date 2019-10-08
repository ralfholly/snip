#include "snip.h"

#define SNIP_DEFINE_ADD_UINT(bits) \
SNIP_INLINE uint##bits##_t snip_add_uint##bits(uint##bits##_t a, uint##bits##_t b, uint8_t* error) { \
    uint##bits##_t result = (uint##bits##_t)((uint##bits##_t)a + (uint##bits##_t)b); \
    if (result < a) { \
        *error = 1U; \
    } \
    return result; \
}

#define SNIP_DEFINE_ADD_INT(bits) \
SNIP_INLINE int##bits##_t snip_add_int##bits(int##bits##_t a, int##bits##_t b, uint8_t* error) { \
    int##bits##_t result = 0; \
    if (   ((b > 0) && (a > SNIP_INT_MAX(bits) - b)) \
        || ((b < 0) && (a < SNIP_INT_MIN(bits) - b))) { \
        *error = 1U; \
    } else { \
        result = (int##bits##_t)(a + b); \
    } \
    return result; \
}

#define SNIP_DEFINE_SUB_UINT(bits) \
SNIP_INLINE uint##bits##_t snip_sub_uint##bits(uint##bits##_t a, uint##bits##_t b, uint8_t* error) { \
    uint##bits##_t result = 0U; \
    if (a < b) { \
        *error = 1U; \
    } else { \
        result = (uint##bits##_t)(a - b); \
    } \
    return result; \
}

#define SNIP_DEFINE_SUB_INT(bits) \
SNIP_INLINE int##bits##_t snip_sub_int##bits(int##bits##_t a, int##bits##_t b, uint8_t* error) { \
    int##bits##_t result = 0; \
    if (   (b > 0 && a < SNIP_INT_MIN(bits) + b) \
        || (b < 0 && a > SNIP_INT_MAX(bits) + b)) { \
        *error = 1U; \
    } else { \
        result = (int##bits##_t)(a - b); \
    } \
    return result; \
}

#define SNIP_DEFINE_MUL_UINT(bits) \
SNIP_INLINE uint##bits##_t snip_mul_uint##bits(uint##bits##_t a, uint##bits##_t b, uint8_t* error) { \
    uint##bits##_t result = 0U; \
    if ((b != 0) && (a > (SNIP_UINT_MAX(bits) / b))) { \
        *error = 1U; \
    } else { \
        result = (uint##bits##_t)(a * b); \
    } \
    return result; \
}

#define SNIP_DEFINE_MUL_INT(bits) \
SNIP_INLINE int##bits##_t snip_mul_int##bits(int##bits##_t a, int##bits##_t b, uint8_t* error) { \
    int##bits##_t result = 0; \
    do { \
        if (a > 0) { \
            if (b > 0) { \
                if (a > (SNIP_INT_MAX(bits) / b)) { \
                    *error = 1U; \
                    break; \
                } \
            } else { \
                if (b < (SNIP_INT_MIN(bits) / a)) { \
                    *error = 1U; \
                    break; \
                } \
            } \
        } else { \
            if (b > 0) { \
                if (a < (SNIP_INT_MIN(bits) / b)) { \
                    *error = 1U; \
                    break; \
                } \
            } else { \
                if ( (a != 0) && (b < (SNIP_INT_MAX(bits) / a))) { \
                    *error = 1U; \
                    break; \
                } \
            } \
        } \
        result = (int##bits##_t)(a * b); \
    } while (0); \
    return result; \
}

#define SNIP_DEFINE_DIV_UINT(bits) \
SNIP_INLINE uint##bits##_t snip_div_uint##bits(uint##bits##_t a, uint##bits##_t b, uint8_t* error) { \
    uint##bits##_t result = 0U; \
    if (b == 0U) { \
        *error = 1U; \
    } else { \
        result = (uint##bits##_t)(a / b); \
    } \
    return result; \
}

#define SNIP_DEFINE_DIV_INT(bits) \
SNIP_INLINE int##bits##_t snip_div_int##bits(int##bits##_t a, int##bits##_t b, uint8_t* error) { \
    int##bits##_t result = 0; \
    if (((a == SNIP_INT_MIN(bits)) && (b == -1)) || (b == 0)) { \
        *error = 1U; \
    } else { \
        result = (int##bits##_t)(a / b); \
    } \
    return result; \
}

SNIP_DEFINE_ADD_UINT(8)
SNIP_DEFINE_ADD_INT(8)
SNIP_DEFINE_SUB_UINT(8)
SNIP_DEFINE_SUB_INT(8)
SNIP_DEFINE_MUL_UINT(8)
SNIP_DEFINE_MUL_INT(8)
SNIP_DEFINE_DIV_UINT(8)
SNIP_DEFINE_DIV_INT(8)

SNIP_DEFINE_ADD_UINT(16)
SNIP_DEFINE_ADD_INT(16)
SNIP_DEFINE_SUB_UINT(16)
SNIP_DEFINE_SUB_INT(16)
SNIP_DEFINE_MUL_UINT(16)
SNIP_DEFINE_MUL_INT(16)
SNIP_DEFINE_DIV_UINT(16)
SNIP_DEFINE_DIV_INT(16)

SNIP_DEFINE_ADD_UINT(32)
SNIP_DEFINE_ADD_INT(32)
SNIP_DEFINE_SUB_UINT(32)
SNIP_DEFINE_SUB_INT(32)
SNIP_DEFINE_MUL_UINT(32)
SNIP_DEFINE_MUL_INT(32)
SNIP_DEFINE_DIV_UINT(32)
SNIP_DEFINE_DIV_INT(32)

SNIP_DEFINE_ADD_UINT(64)
SNIP_DEFINE_ADD_INT(64)
SNIP_DEFINE_SUB_UINT(64)
SNIP_DEFINE_SUB_INT(64)
SNIP_DEFINE_MUL_UINT(64)
SNIP_DEFINE_MUL_INT(64)
SNIP_DEFINE_DIV_UINT(64)
SNIP_DEFINE_DIV_INT(64)

