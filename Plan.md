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

---

## Cycle 2: All ones

**Goal:** 20 rolls of 1 pin each -> `score() == 20`.

**In scope:**
- One gtest test: roll 1, twenty times; assert `score() == 20`.
- Confirm the existing `Game::score()` (running total of all rolls) already satisfies this, or extend it minimally if it doesn't.

**Explicitly NOT in scope yet:**
- Spare/strike bonus logic, frame boundaries, 10th-frame handling (later cycles).
- Any change to the public API.

**Outcome:** Test passed immediately against the existing running-total `score()` — no code change needed. Kept as a coverage checkpoint before spare/strike logic forces real frame-based scoring in Cycle 3.

---

## Cycle 3: One spare

**Goal:** A spare in frame 1 (5, 5), then a 3, then seventeen gutter rolls (20 rolls total) -> `score() == 16`.

Frame breakdown: frame 1 = 5+5 (spare) + next roll (3) = 13. Frame 2 = 3+0 = 3. Frames 3-10 = 0. Total = 16.

**In scope:**
- One gtest test encoding the roll sequence above and asserting `score() == 16`.
- Real frame-based scoring in `Game::score()`: iterate rolls in frames of two, detect a spare (two rolls summing to 10) and add the next single roll as bonus.

**Explicitly NOT in scope yet:**
- Strike bonus logic (two-roll lookahead) — later cycle.
- 10th-frame special handling — later cycle.
- Multiple spares / perfect game — later cycles.

---

## Cycle 4: One strike

**Goal:** A strike in frame 1 (roll 10), then a 3, then a 4, then sixteen gutter rolls (19 rolls total) -> `score() == 24`.

Frame breakdown: frame 1 = 10 (strike) + next two rolls (3+4) = 17. Frame 2 = 3+4 = 7. Frames 3-10 = 0. Total = 24.

**In scope:**
- One gtest test encoding the roll sequence above and asserting `score() == 24`.
- Real strike-bonus scoring in `Game::score()`: detect a strike (single roll of 10) and add the next two rolls as bonus, advancing only one roll for that frame instead of two.

**Explicitly NOT in scope yet:**
- 10th-frame special handling — later cycle.
- Multiple/consecutive strikes, perfect game — later cycle.
- Mixed strike+spare sequences beyond the single scenario above.

---

## Cycle 5: Perfect game

**Goal:** 12 rolls of 10 pins each (all strikes, including the two bonus rolls used to complete the 10th frame) -> `score() == 300`.

Frame breakdown: each of the 10 frames is a strike worth 10 + next two rolls = 30 (since every roll is 10). 10 frames x 30 = 300. The 10th frame's strike is followed by two more strike rolls (rolls 11 and 12) which serve only as bonus rolls for frame 10 and do not start an 11th frame.

**In scope:**
- One gtest test: roll 10, twelve times; assert `score() == 300`.
- Correct 10th-frame handling in `Game::score()` so the frame loop terminates after exactly 10 frames and does not attempt to read/score an 11th frame or index past the 12 recorded rolls incorrectly.

**Explicitly NOT in scope yet:**
- This is the final planned cycle in this kata plan — no further cycles are scoped after this one.
- Any additional mixed-sequence scenarios (e.g., strike in 9th + spare in 10th, all-spares game) beyond the all-strikes perfect game.
- Input validation or per-frame reporting (still explicitly out of scope per the kata description).

**Outcome (RED observation, pending GREEN/REVIEW confirmation):** The test passed immediately against the existing `Game::score()` from Cycle 4 — no production code change was needed. Reason: the loop always runs exactly 10 iterations (one per frame) regardless of `rollIndex`; it never treats the 10th frame's bonus balls as the start of an 11th frame. For the perfect-game sequence (12 rolls, all 10s), every frame's strike branch reads `rolls[rollIndex+1]` and `rolls[rollIndex+2]`, and for frame 10 (`rollIndex == 9`) those resolve to `rolls[10]` and `rolls[11]` — both valid, in-bounds elements of the 12-roll vector — so the sum is correct (10 frames x 30 = 300) with no out-of-bounds access. This mirrors Cycle 2: kept as a coverage checkpoint confirming the existing algorithm already generalizes correctly to the 10th-frame edge case, rather than forcing an artificial code change.
