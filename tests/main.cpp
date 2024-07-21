#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <cstdint>

#include "../include/game.hpp"

TEST(stringRangeTestSuite, zeroToFourNoFactorTest) {
    auto result = Magma::string_range(0,4);
    auto compare = std::vector<uint32_t> {0,1,2,3};

    EXPECT_EQ(result,compare);
}

TEST(stringRangeTestSuite, oneToSixTwoFactorTest) {
    auto result = Magma::string_range(1,6,2);
    auto compare = std::vector<uint32_t> {2,4,6,8,10};

    EXPECT_EQ(result,compare);
}
