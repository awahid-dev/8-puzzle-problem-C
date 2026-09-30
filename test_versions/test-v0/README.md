# test-v0: Warm-up / ASCII Rendering Test

## Overview
Simple warm-up exercise to verify basic C compilation, random number generation, and console output formatting. This is not an 8-puzzle implementation — it's a foundational test of the development environment and basic rendering primitives.

## What It Tests
- **Basic I/O**: `printf`, loops, functions
- **Random numbers**: `rand() % MAX` with `srand(time(NULL))` (though `srand` not called here — output deterministic per run)
- **ASCII grid rendering**: Three helper functions to draw a 3×3 grid pattern:
  - `dash(n)` — prints `n` dashes (`-`)
  - `undscr(n)` — prints `n` underscores (`_`)
  - `pipe(n)` — alternating `|` and random digit (0-7)

## Code Structure
```c
#define MAX 8

void dash(int n)      // horizontal border
void undscr(int n)    // top border
void pipe(int n)      // row with separators + random cells

int main() {
    // Draws 3-row grid:
    // _______
    // |n|n|n|
    // -------
    // |n|n|n|
    // -------
    // |n|n|n|
    // -------
}
```

## Compile & Run
```bash
gcc test_v0.c -o test_v0 && ./test_v0
```

## Sample Output
```
_______
|3|5|2|
-------
|7|1|6|
-------
|4|0|8|
-------
```
(Values vary per run since no `srand()` called — same sequence each execution)

## Purpose in Workflow
This warm-up validates:
1. Compiler toolchain works
2. Basic C syntax and functions work
3. Console rendering approach for grid-based games
4. Random number integration (later used for tile shuffling in v1+)

## Next Step
See `../test-v1/` for the actual 8-puzzle implementation test cases.