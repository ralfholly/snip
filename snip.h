#ifndef SAFE_NUMERIC_INTEGER_PRIMITIVES
#define SAFE_NUMERIC_INTEGER_PRIMITIVES

#define SNIP_DEFINE_ADD_UINT(bits) \
static uint##bits##_t snip_add_uint##bits(uint##bits##_t a, uint##bits##_t b, int* error) { \
    uint##bits##_t result = (uint##bits##_t)((uint##bits##_t)a + (uint##bits##_t)b); \
    if (result < a) { \
        *error |= 1; \
    } \
    return result; \
}

#define SNIP_DEFINE_ADD_INT(bits) \
static int##bits##_t snip_add_int8(int##bits##_t a, int##bits##_t b, int* error) { \
    static const int##bits##_t max_val = (int##bits##_t)(1U << ((bits##U - 1U) - 1U)); \
    static const int##bits##_t min_val = (int##bits##_t)(-((int##bits##_t)(1U << (bits##U - 1U)))); \
    int##bits##_t result = 0; \
    if (   ((b > 0) && (a > max_val - b)) \
        || ((b < 0) && (a < min_val - b))) { \
        *error |= 1; \
    } else { \
        result = (int##bits##_t)(a + b); \
    } \
    return result; \
}


#define SNIP_DEFINE_SUB_UINT(bits) \
static uint##bits##_t snip_sub_uint8(uint##bits##_t a, uint##bits##_t b, int* error) { \
    uint##bits##_t result = 0U; \
    if (a < b) { \
        *error |= 1; \
    } else { \
        result = (uint##bits##_t)(a - b); \
    } \
    return result; \
}

#define SNIP_DEFINE_SUB_INT(bits) \
static int##bits##_t snip_sub_int8(int##bits##_t a, int##bits##_t b, int* error) { \
    static const int##bits##_t min_val = (int##bits##_t)(-((int##bits##_t)(1U << (bits##U - 1U)))); \
    int##bits##_t result = 0; \
    if (((uint##bits##_t)a ^ (uint##bits##_t)b) & (((uint##bits##_t)a - (uint##bits##_t)b) ^ (uint##bits##_t)a) & (uint##bits##_t)min_val) { \
        *error |= 1; \
    } else { \
        result = (int##bits##_t)(a - b); \
    } \
    return result; \
}

SNIP_DEFINE_ADD_UINT(8)
SNIP_DEFINE_ADD_INT(8)
SNIP_DEFINE_SUB_UINT(8)
SNIP_DEFINE_SUB_INT(8)


#endif /* SAFE_NUMERIC_INTEGER_PRIMITIVES */
