#include "Game.h"

void Game::roll(int pins)
{
    total += pins;
}

int Game::score()
{
    return total;
}
