#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>
using namespace std;

#include "gmock/gmock.h"
using namespace testing;

// TODO: Remove, once all families have been tested.
#pragma GCC diagnostic ignored "-Wunused-function"

#include "snip.h"

namespace testing {
namespace snip {

#pragma GCC diagnostic warning "-Wsign-conversion"

TEST(snip, simple) {
    uint8_t error;
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
