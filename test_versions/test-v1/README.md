# test-v1: 8-Puzzle Game Development Test Cases

## Overview
This directory contains three iterative test cases that validate the development workflow of an 8-puzzle game in C. Each version tests a specific layer of functionality, building toward a complete automated solver.

The 8-puzzle is a sliding puzzle with a 3×3 grid containing 8 numbered tiles (1-8) and one empty space (0). The goal configuration tested here:
```
1 2 3
8 0 4
7 6 5
```

---

## Test Case Progression

### test_v1.0.c — Foundation Layer Test
**Purpose**: Validate core data structures and board manipulation primitives.

**What it tests:**
- **Board initialization** (`init()`): Random empty-tile placement, remaining cells set to sentinel `-1`
- **Tile population** (`filler()`): Fills `-1` slots with unique random values 1-8 using `search()` for collision detection
- **Position lookup** (`search()`): Returns coordinate for key; special codes `(-1,-1)`=duplicate, `(-2,-2)`=not found, valid `(x,y)` for empty tile (0)
- **Board rendering** (`display()`): Prints 3×3 grid
- **Win detection** (`is_solved()`): Returns `cntXsld` struct with `solved` flag and correct-tile `count` against custom goal pattern
- **Move validation** (`direction()`): Determines legal moves from empty tile position (has logic gaps — see v1.1)
- **Solver scaffold** (`solver()`): Placeholder with iteration structure

**Structs defined:**
```c
typedef struct { bool left, right, up, down; } dir;
typedef struct { bool solved; int count; } cntXsld;
typedef struct { int x, y; } cord;
```

**Run:**
```bash
gcc test_v1.0.c -o test_v1.0 && ./test_v1.0
```
**Expected output**: Random board + direction flags from hardcoded position (1,1) + board display.

---

### test_v1.1.c — Direction Logic & Integration Test
**Purpose**: Fix and validate move-direction logic; integrate empty-tile tracking into main flow.

**Changes from v1.0:**
1. **`direction(cord c)` rewritten**: Initializes all directions `true`, then disables out-of-bounds moves by checking `c.x±1`, `c.y±1` against 0–2. No undefined variables.
2. **`main()` updated**: Calls `direction(search(0))` to pass actual empty-tile coordinates instead of hardcoded `(1,1)`.
3. **`solver()`**: Changed to recursive pseudo-code (intentional infinite recursion — not meant to run).

**What it validates:**
- Direction flags correctly reflect board edges
- Empty-tile position flows through `search(0)` → `direction()` → `main()`
- Win-check still uses custom goal pattern (not standard 8-puzzle goal)

**Run:**
```bash
gcc test_v1.1.c -o test_v1.1 && ./test_v1.1
```
**Expected output**: Random board + correct direction flags for actual empty position + board display.

---

### test_v1.2.c — Automated Solver Workflow Test
**Purpose**: End-to-end test of a greedy best-move solver with tile sliding and visualization.

**Major changes from v1.1:**
- **Renamed/cleaned globals**: `arr` → `tile`, `n,m` → `#define` constants
- **`direc` struct**: `bool dir[4]` array (index 0=right, 1=left, 2=up, 3=down)
- **`count()`**: Heuristic — counts correctly placed tiles (0–8)
- **`is_simplified()`**: Returns `bool` directly
- **`best_move()`**: Greedy algorithm:
  1. Gets empty position + valid directions
  2. For each valid direction: temporarily swaps, calls `count()`, swaps back
  3. Picks move with highest `count()` score
  4. Executes the chosen swap permanently
- **`solver()`**: Loop — displays board, sleeps 1s, calls `best_move()` until `is_solved()`
- **`main()`**: Runs full solve sequence automatically

**What it validates:**
- Tile sliding via `swap()` works in all four directions
- Heuristic evaluation guides move selection
- Automated solve loop runs to completion (or until stuck)
- Visualization with `display()` + `sleep(1)` shows progression

**Known limitations (test boundaries):**
- Greedy `count()` heuristic can reach local optima — not guaranteed to solve all configurations
- `max()` returns index 0 when all moves score `-1` (invalid), may select invalid move
- No solvability check on initial shuffle — ~50% of random boards are unsolvable
- `search()` duplicate detection (`-1,-1`) remains fragile

**Run:**
```bash
gcc test_v1.2.c -o test_v1.2 && ./test_v1.2
```
**Expected output**: Animated board updates every second as solver attempts moves until solved or stuck.

---

## Data Structure Evolution

| Version | Board | Direction Struct | Solved Struct | Coord Struct |
|---------|-------|------------------|---------------|--------------|
| v1.0 | `int arr[3][3]` | `dir {l,r,u,d}` | `cntXsld {solved,count}` | `cord {x,y}` |
| v1.1 | `int arr[3][3]` | `dir {l,r,u,d}` | `cntXsld {solved,count}` | `cord {x,y}` |
| v1.2 | `int tile[3][3]` | `direc {bool dir[4]}` | `bool` return | `cord {x,y}` |

---

## Compile All
```bash
gcc test_v1.0.c -o test_v1.0
gcc test_v1.1.c -o test_v1.1
gcc test_v1.2.c -o test_v1.2
```

## Dependencies
- `stdio.h`, `stdlib.h`, `time.h`, `stdbool.h`
- `unistd.h` (v1.2 only, for `sleep()`)
- C99+ (for `bool`, loop-variable declarations)

---

## Test Workflow Summary

```
v1.0: Board setup → Tile fill → Search → Display → Win-check → Direction (broken) → Solver stub
v1.1: Board setup → Tile fill → Search → Display → Win-check → Direction (fixed) → Solver stub
v1.2: Board setup → Tile fill → Search → Display → Win-check → Direction → Heuristic → Best-move → Swap → Solve loop
```

Each test case isolates and validates one layer before adding the next. Run them in order to observe the workflow progression.