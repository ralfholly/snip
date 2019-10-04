#ifndef SAFE_NUMERIC_INTEGER_PRIMITIVES
#define SAFE_NUMERIC_INTEGER_PRIMITIVES

static uint8_t snip_add_uint8(uint8_t a, uint8_t b, int* error) {
    uint8_t result = (uint8_t)((uint8_t)a + (uint8_t)b);
    if (result < a) {
        *error |= 1;
    }
    return result;
}

static int8_t snip_add_int8(int8_t a, int8_t b, int* error) {
    static const int8_t max_val = (int8_t)(1U << ((8U - 1U) - 1U));
    static const int8_t min_val = (int8_t)(-((int8_t)(1U << (8U - 1U))));
    int8_t result = 0;
    if (   ((b > 0) && (a > max_val - b))
        || ((b < 0) && (a < min_val - b))) {
        *error |= 1;
    } else {
        result = (int8_t)(a + b);
    }
    return result;
}

static uint8_t snip_sub_uint8(uint8_t a, uint8_t b, int* error) {
    uint8_t result = 0U;

    if (a < b) {
        *error |= 1;
    } else {
        result = (uint8_t)(a - b);
    }
    return result;
}

static int8_t snip_sub_int8(int8_t a, int8_t b, int* error) {
    static const int8_t min_val = (int8_t)(-((int8_t)(1U << (8U - 1U))));
    int8_t result = 0;

    if (((uint8_t)a ^ (uint8_t)b) & (((uint8_t)a - (uint8_t)b) ^ (uint8_t)a) & (uint8_t)min_val) {
        *error |= 1;
    } else {
        result = (int8_t)(a - b);
    }
    return result;
}

#endif /* SAFE_NUMERIC_INTEGER_PRIMITIVES */
