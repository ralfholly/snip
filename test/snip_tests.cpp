#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>
using namespace std;

#include "gmock/gmock.h"
using namespace testing;

// Use inline version of SNIP.
#define SNIP_INLINE inline
#include "snip.c"

namespace testing {
namespace snip {

#pragma GCC diagnostic warning "-Wsign-conversion"

#define ASIZE(a) ( sizeof(a) / sizeof(a[0]) )

TEST(snip, add_unsigned) {
    uint8_t error;

    // .. No overflow.
    { error = 0; uint8_t result = snip_add_uint8(42, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(44U, result); }
    { error = 0; uint16_t result = snip_add_uint16(42, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(44U, result); }
    { error = 0; uint32_t result = snip_add_uint32(42, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(44U, result); }
    { error = 0; uint64_t result = snip_add_uint64(42, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(44U, result); }

    // .. Overflow.
    { error = 0; snip_add_uint8(1, SNIP_UINT_MAX(8), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_add_uint16(1, SNIP_UINT_MAX(16), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_add_uint32(1, SNIP_UINT_MAX(32), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_add_uint64(1, SNIP_UINT_MAX(64), &error); EXPECT_EQ(1, error); }
}

TEST(snip, add_signed) {
    uint8_t error;

    // .. No overflow.
    { error = 0; int8_t result = snip_add_int8(-2, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(0, result); }
    { error = 0; int16_t result = snip_add_int16(-2, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(0, result); }
    { error = 0; int32_t result = snip_add_int32(-2, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(0, result); }
    { error = 0; int64_t result = snip_add_int64(-2, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(0, result); }

    { error = 0; int8_t result = snip_add_int8(SNIP_INT_MIN(8), 1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_INT_MIN(8) + 1, result); }
    { error = 0; int16_t result = snip_add_int16(SNIP_INT_MIN(16), 1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_INT_MIN(16) + 1, result); }
    { error = 0; int32_t result = snip_add_int32(SNIP_INT_MIN(32), 1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_INT_MIN(32) + 1, result); }
    { error = 0; int64_t result = snip_add_int64(SNIP_INT_MIN(64), 1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_INT_MIN(64) + 1, result); }

    // .. Overflow
    { error = 0; snip_add_int8(SNIP_INT_MAX(8), 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_add_int16(SNIP_INT_MAX(16), 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_add_int32(SNIP_INT_MAX(32), 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_add_int64(SNIP_INT_MAX(64), 1, &error); EXPECT_EQ(1, error); }

    { error = 0; snip_add_int8(SNIP_INT_MIN(8), -1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_add_int16(SNIP_INT_MIN(16), -1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_add_int32(SNIP_INT_MIN(32), -1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_add_int64(SNIP_INT_MIN(64), -1, &error); EXPECT_EQ(1, error); }
}

TEST(snip, sub_unsigned) {
    uint8_t error;

    // ... No overflow.
    { error = 0; uint8_t result = snip_sub_uint8(4, 3, &error); EXPECT_EQ(0, error); EXPECT_EQ(1U, result); }
    { error = 0; uint16_t result = snip_sub_uint16(4, 3, &error); EXPECT_EQ(0, error); EXPECT_EQ(1U, result); }
    { error = 0; uint32_t result = snip_sub_uint32(4, 3, &error); EXPECT_EQ(0, error); EXPECT_EQ(1U, result); }
    { error = 0; uint64_t result = snip_sub_uint64(4, 3, &error); EXPECT_EQ(0, error); EXPECT_EQ(1U, result); }

    // ... Overflow
    { error = 0; snip_sub_uint8(0, 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_sub_uint16(0, 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_sub_uint32(0, 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_sub_uint64(0, 1, &error); EXPECT_EQ(1, error); }
}

TEST(snip, sub_signed) {
    uint8_t error;

    // ... No overflow.
    { error = 0; int8_t result = snip_sub_int8(3, 10, &error); EXPECT_EQ(0, error); EXPECT_EQ(-7, result); }
    { error = 0; int16_t result = snip_sub_int16(3, 10, &error); EXPECT_EQ(0, error); EXPECT_EQ(-7, result); }
    { error = 0; int32_t result = snip_sub_int32(3, 10, &error); EXPECT_EQ(0, error); EXPECT_EQ(-7, result); }
    { error = 0; int64_t result = snip_sub_int64(3, 10, &error); EXPECT_EQ(0, error); EXPECT_EQ(-7, result); }

    { error = 0; int8_t result = snip_sub_int8(0, SNIP_INT_MAX(8), &error); EXPECT_EQ(0, error); EXPECT_EQ(-SNIP_INT_MAX(8), result); }
    { error = 0; int16_t result = snip_sub_int16(0, SNIP_INT_MAX(16), &error); EXPECT_EQ(0, error); EXPECT_EQ(-SNIP_INT_MAX(16), result); }
    { error = 0; int32_t result = snip_sub_int32(0, SNIP_INT_MAX(32), &error); EXPECT_EQ(0, error); EXPECT_EQ(-SNIP_INT_MAX(32), result); }
    { error = 0; int64_t result = snip_sub_int64(0, SNIP_INT_MAX(64), &error); EXPECT_EQ(0, error); EXPECT_EQ(-SNIP_INT_MAX(64), result); }

    // ... Overflow.
    { error = 0; snip_sub_int8(SNIP_INT_MIN(8), 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_sub_int16(SNIP_INT_MIN(16), 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_sub_int32(SNIP_INT_MIN(32), 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_sub_int64(SNIP_INT_MIN(64), 1, &error); EXPECT_EQ(1, error); }

    { error = 0; snip_sub_int8(SNIP_INT_MIN(8), SNIP_INT_MAX(8), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_sub_int16(SNIP_INT_MIN(16), SNIP_INT_MAX(16), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_sub_int32(SNIP_INT_MIN(32), SNIP_INT_MAX(32), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_sub_int64(SNIP_INT_MIN(64), SNIP_INT_MAX(64), &error); EXPECT_EQ(1, error); }
}

TEST(snip, ensure_error_not_reset) {
    uint8_t error;

    error = 0;
    snip_add_int32(17, 4, &error); EXPECT_EQ(0, error);
    snip_add_int32(SNIP_INT_MAX(32), 1, &error); EXPECT_EQ(1, error);
    snip_add_int32(17, 4, &error); EXPECT_EQ(1, error); // Error still set.
}

TEST(snip, chaining) {
    uint8_t error;
    uint32_t result;

    error = 0;
    result = snip_add_uint32(100,
        snip_add_uint32(50,
            snip_sub_uint32(100, 50, &error), &error), &error);
    EXPECT_EQ(200U, result);
    EXPECT_EQ(0, error);

    error = 0;
    result = snip_add_uint32(100,
        snip_add_uint32(50,
            // 50 - (50 + 50) -> Overflow, error set.
            snip_sub_uint32(50,
                snip_add_uint32(50, 50, &error), &error), &error), &error);
    EXPECT_EQ(1, error);
}

TEST(snip, mul_unsigned) {
    uint8_t error;

    // ... No overflow.
    { error = 0; uint8_t result = snip_mul_uint8(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20U, result); }
    { error = 0; uint16_t result = snip_mul_uint16(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20U, result); }
    { error = 0; uint32_t result = snip_mul_uint32(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20U, result); }
    { error = 0; uint64_t result = snip_mul_uint64(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20U, result); }

    { error = 0; uint8_t result = snip_mul_uint8(10, 0, &error); EXPECT_EQ(0, error); EXPECT_EQ(0U, result); }
    { error = 0; uint16_t result = snip_mul_uint16(10, 0, &error); EXPECT_EQ(0, error); EXPECT_EQ(0U, result); }
    { error = 0; uint32_t result = snip_mul_uint32(10, 0, &error); EXPECT_EQ(0, error); EXPECT_EQ(0U, result); }
    { error = 0; uint64_t result = snip_mul_uint64(10, 0, &error); EXPECT_EQ(0, error); EXPECT_EQ(0U, result); }

    { error = 0; uint8_t result = snip_mul_uint8(1, SNIP_UINT_MAX(8), &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_UINT_MAX(8), result); }
    { error = 0; uint16_t result = snip_mul_uint16(1, SNIP_UINT_MAX(16), &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_UINT_MAX(16), result); }
    { error = 0; uint32_t result = snip_mul_uint32(1, SNIP_UINT_MAX(32), &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_UINT_MAX(32), result); }
    { error = 0; uint64_t result = snip_mul_uint64(1, SNIP_UINT_MAX(64), &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_UINT_MAX(64), result); }

    { error = 0; uint8_t result = snip_mul_uint8(2, SNIP_UINT_MAX(8) / 2, &error); EXPECT_EQ(0, error); EXPECT_EQ((SNIP_UINT_MAX(8) / 2) * 2, result); }
    { error = 0; uint16_t result = snip_mul_uint16(2, SNIP_UINT_MAX(16) / 2, &error); EXPECT_EQ(0, error); EXPECT_EQ((SNIP_UINT_MAX(16) / 2) * 2, result); }
    { error = 0; uint32_t result = snip_mul_uint32(2, SNIP_UINT_MAX(32) / 2, &error); EXPECT_EQ(0, error); EXPECT_EQ((SNIP_UINT_MAX(32) / 2) * 2, result); }
    { error = 0; uint64_t result = snip_mul_uint64(2, SNIP_UINT_MAX(64) / 2, &error); EXPECT_EQ(0, error); EXPECT_EQ((SNIP_UINT_MAX(64) / 2) * 2, result); }

    // ... Overflow.
    { error = 0; snip_mul_uint8(SNIP_UINT_MAX(8), SNIP_UINT_MAX(8), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_uint16(SNIP_UINT_MAX(16), SNIP_UINT_MAX(16), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_uint32(SNIP_UINT_MAX(32), SNIP_UINT_MAX(32), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_uint64(SNIP_UINT_MAX(64), SNIP_UINT_MAX(64), &error); EXPECT_EQ(1, error); }

    { error = 0; snip_mul_uint8(2, (SNIP_UINT_MAX(8) / 2) + 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_uint16(2, (SNIP_UINT_MAX(16) / 2) + 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_uint32(2, (SNIP_UINT_MAX(32) / 2) + 1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_uint64(2, (SNIP_UINT_MAX(64) / 2) + 1, &error); EXPECT_EQ(1, error); }
}

TEST(snip, mul_signed) {
    uint8_t error;

    // ... No overflow.
    { error = 0; int8_t result = snip_mul_int8(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20, result); }
    { error = 0; int16_t result = snip_mul_int16(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20, result); }
    { error = 0; int32_t result = snip_mul_int32(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20, result); }
    { error = 0; int64_t result = snip_mul_int64(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20, result); }

    { error = 0; int8_t result = snip_mul_int8(-10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(-20, result); }
    { error = 0; int16_t result = snip_mul_int16(-10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(-20, result); }
    { error = 0; int32_t result = snip_mul_int32(-10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(-20, result); }
    { error = 0; int64_t result = snip_mul_int64(-10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(-20, result); }

    { error = 0; int8_t result = snip_mul_int8(10, -2, &error); EXPECT_EQ(0, error); EXPECT_EQ(-20, result); }
    { error = 0; int16_t result = snip_mul_int16(10, -2, &error); EXPECT_EQ(0, error); EXPECT_EQ(-20, result); }
    { error = 0; int32_t result = snip_mul_int32(10, -2, &error); EXPECT_EQ(0, error); EXPECT_EQ(-20, result); }
    { error = 0; int64_t result = snip_mul_int64(10, -2, &error); EXPECT_EQ(0, error); EXPECT_EQ(-20, result); }

    { error = 0; int8_t result = snip_mul_int8(-10, -2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20, result); }
    { error = 0; int16_t result = snip_mul_int16(-10, -2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20, result); }
    { error = 0; int32_t result = snip_mul_int32(-10, -2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20, result); }
    { error = 0; int64_t result = snip_mul_int64(-10, -2, &error); EXPECT_EQ(0, error); EXPECT_EQ(20, result); }

    // ... Overflow.
    { error = 0; snip_mul_int8(SNIP_INT_MAX(8), SNIP_INT_MAX(8), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_int16(SNIP_INT_MAX(16), SNIP_INT_MAX(16), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_int32(SNIP_INT_MAX(32), SNIP_INT_MAX(32), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_int64(SNIP_INT_MAX(64), SNIP_INT_MAX(64), &error); EXPECT_EQ(1, error); }

    { error = 0; snip_mul_int8(SNIP_INT_MIN(8), SNIP_INT_MIN(8), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_int16(SNIP_INT_MIN(16), SNIP_INT_MIN(16), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_int32(SNIP_INT_MIN(32), SNIP_INT_MIN(32), &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_int64(SNIP_INT_MIN(64), SNIP_INT_MIN(64), &error); EXPECT_EQ(1, error); }

    { error = 0; snip_mul_int8(SNIP_INT_MIN(8), -1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_int16(SNIP_INT_MIN(16), -1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_int32(SNIP_INT_MIN(32), -1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_mul_int64(SNIP_INT_MIN(64), -1, &error); EXPECT_EQ(1, error); }
}

TEST(snip, div_unsigned) {
    uint8_t error;

    // ... No overflow.
    { error = 0; uint8_t result = snip_div_uint8(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5U, result); }
    { error = 0; uint16_t result = snip_div_uint16(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5U, result); }
    { error = 0; uint32_t result = snip_div_uint32(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5U, result); }
    { error = 0; uint64_t result = snip_div_uint64(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5U, result); }

    { error = 0; uint8_t result = snip_div_uint8(11, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5U, result); }
    { error = 0; uint16_t result = snip_div_uint16(11, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5U, result); }
    { error = 0; uint32_t result = snip_div_uint32(11, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5U, result); }
    { error = 0; uint64_t result = snip_div_uint64(11, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5U, result); }

    { error = 0; uint8_t result = snip_div_uint8(0, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(0U, result); }
    { error = 0; uint16_t result = snip_div_uint16(0, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(0U, result); }
    { error = 0; uint32_t result = snip_div_uint32(0, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(0U, result); }
    { error = 0; uint64_t result = snip_div_uint64(0, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(0U, result); }

    { error = 0; uint8_t result = snip_div_uint8(SNIP_UINT_MAX(8), 1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_UINT_MAX(8), result); }
    { error = 0; uint16_t result = snip_div_uint16(SNIP_UINT_MAX(16), 1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_UINT_MAX(16), result); }
    { error = 0; uint32_t result = snip_div_uint32(SNIP_UINT_MAX(32), 1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_UINT_MAX(32), result); }
    { error = 0; uint64_t result = snip_div_uint64(SNIP_UINT_MAX(64), 1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_UINT_MAX(64), result); }

    // ... Overflow.
    { error = 0; snip_div_int8(10, 0, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_div_int16(10, 0, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_div_int32(10, 0, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_div_int64(10, 0, &error); EXPECT_EQ(1, error); }
}

TEST(snip, div_signed) {
    uint8_t error;

    // ... No overflow.
    { error = 0; int8_t result = snip_div_int8(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5, result); }
    { error = 0; int16_t result = snip_div_int16(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5, result); }
    { error = 0; int32_t result = snip_div_int32(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5, result); }
    { error = 0; int64_t result = snip_div_int64(10, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5, result); }

    { error = 0; int8_t result = snip_div_int8(11, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5, result); }
    { error = 0; int16_t result = snip_div_int16(11, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5, result); }
    { error = 0; int32_t result = snip_div_int32(11, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5, result); }
    { error = 0; int64_t result = snip_div_int64(11, 2, &error); EXPECT_EQ(0, error); EXPECT_EQ(5, result); }

    { error = 0; int8_t result = snip_div_int8(SNIP_INT_MAX(8), -1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_INT_MIN(8) + 1, result); }
    { error = 0; int16_t result = snip_div_int16(SNIP_INT_MAX(16), -1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_INT_MIN(16) + 1, result); }
    { error = 0; int32_t result = snip_div_int32(SNIP_INT_MAX(32), -1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_INT_MIN(32) + 1, result); }
    { error = 0; int64_t result = snip_div_int64(SNIP_INT_MAX(64), -1, &error); EXPECT_EQ(0, error); EXPECT_EQ(SNIP_INT_MIN(64) + 1, result); }

    // ... Overflow.
    { error = 0; snip_div_int8(SNIP_INT_MAX(8), 0, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_div_int16(SNIP_INT_MAX(16), 0, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_div_int32(SNIP_INT_MAX(32), 0, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_div_int64(SNIP_INT_MAX(64), 0, &error); EXPECT_EQ(1, error); }

    { error = 0; snip_div_int8(SNIP_INT_MIN(8), -1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_div_int16(SNIP_INT_MIN(16), -1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_div_int32(SNIP_INT_MIN(32), -1, &error); EXPECT_EQ(1, error); }
    { error = 0; snip_div_int64(SNIP_INT_MIN(64), -1, &error); EXPECT_EQ(1, error); }
}

} // namespace snip
} // namespace testing
