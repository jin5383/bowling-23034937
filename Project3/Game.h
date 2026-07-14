#pragma once

#include <vector>

class Game
{
public:
    void roll(int pins);
    int score();

private:
    std::vector<int> rolls;
};
