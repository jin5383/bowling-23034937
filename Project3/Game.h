#pragma once

class Game
{
public:
    void roll(int pins);
    int score();

private:
    int total = 0;
};
