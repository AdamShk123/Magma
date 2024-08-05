#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/game.hpp"

TEST(utilityTestSuite, loadTextureTest)
{
    std::optional<Magma::Texture> resultOne = Magma::loadTexture("textures/awesomeface.png");
    EXPECT_EQ(resultOne.has_value(), true);

    std::optional<Magma::Texture> resultTwo = Magma::loadTexture("textures/container.jpg");
    EXPECT_EQ(resultTwo.has_value(), true);
}
