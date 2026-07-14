#include "gtest/gtest.h"
#include "Game.h"

TEST(GameTest, AllGuttersScoresZero)
{
    Game game;
    for (int i = 0; i < 20; ++i)
    {
        game.roll(0);
    }
    EXPECT_EQ(0, game.score());
}

TEST(GameTest, AllOnesScoresTwenty)
{
    Game game;
    for (int i = 0; i < 20; ++i)
    {
        game.roll(1);
    }
    EXPECT_EQ(20, game.score());
}

TEST(GameTest, OneSpare)
{
    Game game;
    game.roll(5);
    game.roll(5);
    game.roll(3);
    for (int i = 0; i < 17; ++i)
    {
        game.roll(0);
    }
    EXPECT_EQ(16, game.score());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
