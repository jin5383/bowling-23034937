#include "Game.h"

void Game::roll(int pins)
{
    rolls.push_back(pins);
}

int Game::score()
{
    int total = 0;
    size_t rollIndex = 0;
    for (int frame = 0; frame < 10; ++frame)
    {
        int first = rolls[rollIndex];
        int second = rolls[rollIndex + 1];
        total += first + second;
        if (first + second == 10)
        {
            total += rolls[rollIndex + 2];
        }
        rollIndex += 2;
    }
    return total;
}
