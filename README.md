# 8-Puzzle Game (C Implementation)

A sliding puzzle game implementation in C with iterative development test cases.

## Project Structure

```
8P_game/
├── test_versions/
│   ├── test-v0/      # Warm-up: ASCII rendering & basic C primitives
│   └── test-v1/      # 8-Puzzle: 3 iterative test cases (v1.0 → v1.1 → v1.2)
└── workstation/
    └── main.c        # Latest working implementation (based on test_v1.2.c)
```

## Overview

The 8-puzzle is a 3×3 grid with 8 numbered tiles (1-8) and one empty space (0). Goal configuration:
```
1 2 3
8 0 4
7 6 5
```

## Development Progression

| Version | Purpose |
|---------|---------|
| **test-v0** | Compiler validation, basic I/O, random numbers, ASCII grid rendering |
| **test-v1.0** | Board init, tile population, position lookup, win detection, move validation (stub) |
| **test-v1.1** | Fixed direction logic, integrated empty-tile tracking |
| **test-v1.2** | Greedy best-move solver with heuristic (`count()`), automated solve loop, visualization |
| **workstation/main.c** | Current working version (matches test_v1.2.c) |

## Quick Start

```bash
# Run latest version
cd workstation
gcc main.c -o puzzle && ./puzzle

# Run test cases in order
cd ../test_versions/test-v0
gcc test_v0.c -o test_v0 && ./test_v0

cd ../test-v1
gcc test_v1.0.c -o test_v1.0 && ./test_v1.0
gcc test_v1.1.c -o test_v1.1 && ./test_v1.1
gcc test_v1.2.c -o test_v1.2 && ./test_v1.2
```

## Detailed Documentation

- **[test-v0/README.md](test_versions/test-v0/README.md)** — Warm-up test details
- **[test-v1/README.md](test_versions/test-v1/README.md)** — Complete 8-puzzle test case progression

## Current Limitations (test-v1.2 / workstation)

- Greedy heuristic can reach local optima (not guaranteed to solve all configurations)
- No solvability check on initial shuffle (~50% of random boards unsolvable)
- `max()` returns index 0 when all moves invalid
- `search()` duplicate detection is fragile

## Dependencies

- `stdio.h`, `stdlib.h`, `time.h`, `stdbool.h`
- `unistd.h` (for `sleep()`)
- C99+ compiler (gcc/clang)