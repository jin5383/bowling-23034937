#include "Game.h"

void Game::roll(int pins)
{
    rolls.push_back(pins);
}

namespace
{
    constexpr int kPinsPerFrame = 10;
}

int Game::score()
{
    int total = 0;
    size_t rollIndex = 0;
    for (int frame = 0; frame < 10; ++frame)
    {
        int firstRoll = rolls[rollIndex];
        if (firstRoll == kPinsPerFrame)
        {
            // Strike: frame is a single roll worth 10 + next two rolls.
            total += firstRoll + rolls[rollIndex + 1] + rolls[rollIndex + 2];
            rollIndex += 1;
            continue;
        }

        int secondRoll = rolls[rollIndex + 1];
        total += firstRoll + secondRoll;
        if (firstRoll + secondRoll == kPinsPerFrame)
        {
            // Spare: frame's two rolls plus the next single roll.
            total += rolls[rollIndex + 2];
        }
        rollIndex += 2;
    }
    return total;
}
