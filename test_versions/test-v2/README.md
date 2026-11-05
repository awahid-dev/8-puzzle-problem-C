# test-v2: 8-Puzzle Heuristic Search Test Cases

## Overview
This directory contains iterative test cases that continue the 8-puzzle development workflow from test-v1. Version 2 focuses on replacing the correct-tile-count heuristic with a Manhattan-distance heuristic, then using that distance to choose moves that bring the board closer to the goal.

The 8-puzzle is a sliding puzzle with a 3×3 grid containing 8 numbered tiles (1-8) and one empty space (0). The goal configuration tested here:
```
1 2 3
8 0 4
7 6 5
```

---

## Test Case Progression

### test-v2.1.c — Manhattan Distance Heuristic Test
**Purpose**: Validate a distance-based heuristic and greedy distance-reducing move selection as an improvement over v1.2's correct-tile count.

**What it tests:**
- **Board initialization** (`init()`): Random empty-tile placement, remaining cells set to sentinel `-1`
- **Tile population** (`filler()`): Fills `-1` slots with unique random values 1-8 using `search()` for collision detection
- **Position lookup** (`search()`): Returns coordinates for a key; special codes `(-1,?)`=duplicate, `(-2,-2)`=not found, valid `(x,y)` for the empty tile (0)
- **Board rendering** (`display()`): Prints the 3×3 grid
- **Move validation** (`direction()`): Determines legal moves from the empty tile's position
- **Goal lookup** (`correct_position(key)`): Maps each tile 1-8 to its target coordinate in the custom goal pattern
- **Manhattan distance** (`distance()`): Sums `|x - target_x| + |y - target_y|` over all tiles, skipping the empty tile
- **Win detection** (`is_solved()`): Early-exit check against the custom goal pattern
- **Move scoring** (`min()`): Returns the index of the legal move with the smallest distance
- **Move selection** (`best_move()`): Evaluates all legal moves, then commits only the move that strictly reduces the current Manhattan distance
- **Solver loop** (`solver()`): Displays the board, waits 1 second, and repeats `best_move()` until solved

**Structs defined:**
```c
typedef struct { bool dir[4]; } direc_t;  // 0=right, 1=left, 2=up, 3=down
typedef struct { int x, y; } cord_t;
```

**Run:**
```bash
gcc test-v2.1.c -o test-v2.1 && ./test-v2.1
```
**Expected output**: Animated board frames every second as the solver makes Manhattan-distance-reducing moves until the board is solved or no improving move remains.

---

## Changes from v1.2

| Area | v1.2 | v2.1 |
|------|------|------|
| Heuristic | `count()` — number of correctly placed tiles (higher is better) | `distance()` — total Manhattan distance (lower is better) |
| Goal mapping | Hardcoded conditions inside `count()` / `is_solved()` | `correct_position()` helper used by `distance()` |
| Selection helper | `max()` | `min()` |
| Move rule | Execute the highest-scoring move | Execute a move only if it strictly lowers the current distance (`prev_dist > dist[i]`) |
| Struct names | `direc`, `cord` | `direc_t`, `cord_t` |
| Includes | `stdio.h`, `stdlib.h`, `time.h`, `unistd.h` | Adds `math.h` |
| Solver loop | `display()` → `sleep()` → `best_move()` (shows initial board) | `best_move()` → `display()` → `sleep()` (first frame is after the first move) |

**Unchanged from v1.2:**
- Custom goal pattern (not the standard 8-puzzle goal)
- `init()`, `filler()`, `search()`, `display()`, `swap()`, and `direction()` behavior
- Random shuffle with no solvability check
- `main()`: `srand(time(NULL))` → `init()` → `filler()` → `solver()`

---

## Heuristic Comparison

| | v1.2 `count()` | v2.1 `distance()` |
|---|---|---|
| Score meaning | Tiles already in the correct position | Steps each tile is away from its correct position |
| Better direction | Higher score | Lower score |
| Move acceptance | Best score, ties resolved by direction index | Must be strictly lower than the current distance |
| Plateau handling | Equal-score moves are allowed | Equal-distance moves are rejected |

---

## Known Limitations (test boundaries)
- `distance()` uses `break` when it finds the empty tile, which exits only the inner `j` loop — tiles after the empty tile in that row are skipped, underestimating the distance
- `best_move()` requires strict improvement, so equal-distance (plateau) moves are rejected; the solver can get stuck at a local minimum
- `solver()` loops until `is_solved()`, but a stuck `best_move()` performs no swap, so the loop can run forever without progress
- No solvability check on the initial shuffle — roughly half of all random boards are unsolvable
- `correct_position()` has no return path for key `0` or values outside 1-8; it relies on `distance()` skipping the empty tile
- `search()` duplicate detection sets only `c.x = -1`, leaving `c.y` uninitialized (same fragility as v1.x)
- `min()` returns index 0 if every option is `-1` (unlikely here because the empty tile always has at least one legal move)

**Build note:** The file uses `bool` without including `<stdbool.h>`. It compiles as C23, where `bool` is a keyword; for C99-C17, add `#include <stdbool.h>`.

---

## Compile
```bash
gcc test-v2.1.c -o test-v2.1
```

## Dependencies
- `stdio.h`, `stdlib.h`, `time.h`, `unistd.h`, `math.h`
- `bool` — native in C23; include `stdbool.h` on C99-C17
- C99+ (C23 recommended for this file as written)

---

## Test Workflow Summary

```
v2.1: Board setup → Tile fill → Search → Display → Win-check → Direction → Goal-coordinate lookup → Manhattan distance → Min selection → Best-move → Swap → Solve loop
```

Each test case isolates and validates one layer before adding the next. Read test-v1's README first to understand the foundation that v2 builds on.

## Next Step
Next I will try to implement searching algorithms to solve the problem.
