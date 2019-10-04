#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>
using namespace std;

#include "gmock/gmock.h"
using namespace testing;

namespace testing {
namespace snip {


uint8_t snip_add_uint8(uint8_t a, uint8_t b, int* error) {
    uint8_t result = (uint8_t)((uint8_t)a + (uint8_t)b);
    if (result < a) {
        *error |= 1;
    }
    return result;
}

int8_t snip_add_int8(int8_t a, int8_t b, int* error) {
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

uint8_t snip_sub_uint8(uint8_t a, uint8_t b, int* error) {
    uint8_t result = 0U;

    if (a < b) {
        *error |= 1;
    } else {
        result = (uint8_t)(a - b);
    }
    return result;
}

int8_t snip_sub_int8(int8_t a, int8_t b, int* error) {
    static const int8_t min_val = (int8_t)(-((int8_t)(1U << (8U - 1U))));
    int8_t result = 0;

    if (((uint8_t)a ^ (uint8_t)b) & (((uint8_t)a - (uint8_t)b) ^ (uint8_t)a) & (uint8_t)min_val) {
        *error |= 1;
    } else {
        result = (int8_t)(a - b);
    }
    return result;
}

#pragma GCC diagnostic warning "-Wsign-conversion"

TEST(snip, YourTest) {
    int error;
    uint8_t u8_result;
    int8_t i8_result;

    /* add */

    error = 0;
    u8_result = snip_add_uint8(42, 2, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(44, u8_result);

    error = 0;
    u8_result = snip_add_uint8(42, 255, &error);
    EXPECT_EQ(1, error);

    error = 0;
    i8_result = snip_add_int8(-2, 2, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(0, i8_result);

    error = 0;
    i8_result = snip_add_int8(-128, 1, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(-127, i8_result);

    /* sub */

    error = 0;
    u8_result = snip_sub_uint8(3, 2, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(1, u8_result);

    error = 0;
    u8_result = snip_sub_uint8(3, 255, &error);
    EXPECT_EQ(1, error);

    error = 0;
    i8_result = snip_sub_int8(3, 10, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(-7, i8_result);

    error = 0;
    i8_result = snip_sub_int8(-3, 10, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(-13, i8_result);

    error = 0;
    i8_result = snip_sub_int8(-3, 10, &error);
    EXPECT_EQ(0, error);
    EXPECT_EQ(-13, i8_result);
}


} // namespace snip
} // namespace testing
