# Plan: Bowling Game Kata (TDD)

This plan is built incrementally — each RED stage appends its own section below for the cycle it's starting. It is not written all at once up front.

## Goal
Implement a `Game` class (C++17/20, gtest/gmock via existing NuGet package) with:

```cpp
class Game {
public:
    void roll(int pins);
    int score();
};
```

`roll(pins)` records one ball thrown (0-10 pins). `score()` returns the
total game score computed per standard American ten-pin bowling rules
(open frame = sum of two rolls; spare = 10 + next roll; strike = 10 +
next two rolls; 10th frame gets extra rolls to complete a final
spare/strike). No input validation is required (kata explicitly waives
it) and no per-frame/intermediate score reporting is required — only
the final total from `score()`.

## Public API (final, does not change across cycles)
- `void Game::roll(int pins)`
- `int Game::score()`

## Planned upcoming cycles (rough sketch only — each gets its own detailed section below when its RED stage starts)
1. Gutter game
2. All ones
3. One spare
4. One strike
5. Perfect game

---

## Cycle 1: Gutter game

**Goal:** 20 rolls of 0 pins -> `score() == 0`.

**In scope:**
- `Game.h` / `Game.cpp` compiling stub with the two methods above.
- One gtest test: roll 0, twenty times; assert `score() == 0`.
- Wiring the new files into `Project3.vcxproj` / `.vcxproj.filters` so the project builds and the test runs (and is observed failing) as a standalone console app running `RUN_ALL_TESTS()` from `main()`.

**Explicitly NOT in scope yet:**
- Any real scoring logic (frame iteration, spare/strike bonus lookahead, 10th-frame handling). The stub `score()` intentionally returns an obviously-wrong sentinel value so the test fails for the right reason.
- Spare, strike, and perfect-game tests (later cycles).
- Input validation, per-frame score reporting (explicitly out of scope per the kata description).
- Linking gtest_main — this project builds its own `main()` calling `InitGoogleTest` + `RUN_ALL_TESTS()`.
