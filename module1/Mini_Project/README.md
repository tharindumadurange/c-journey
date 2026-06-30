# Statistics Calculator

A single-file C program that reads a set of numeric measurements and lets the user
explore them through an interactive menu (min, max, mean, range, count above mean,
print all, and a session history of menu actions).

Built as the Module 1 capstone of my structured C learning path, focused on robust
input handling, bitwise/array fundamentals, and clean, warning-free C.

## What it does

- Prompts for **N** measurements (1–100) and reads N floating-point values.
- Validates every input: rejects non-numbers and out-of-range values, and re-prompts
  instead of crashing.
- Offers a menu:
  1. minimum
  2. maximum
  3. mean
  4. range (max − min)
  5. count of values above the mean
  6. print all values
  7. print history of menu actions this session
  8. quit
- Keeps a **circular history** of the last 32 menu actions (oldest entries are
  forgotten gracefully once more than 32 actions are taken).
- On quit, prints a one-line session summary.

## Build

Requires `gcc` (or any C11 compiler).

    gcc -Wall -Wextra -Wpedantic -std=c11 -o statistics main.c

Compiles with **zero warnings** under those flags.

## Run

    ./statistics

Then follow the prompts.

### Example session

== Statistics Calculator ==
Enter up to 100 numeric measurements: then explore them via the menu
Please enter number of measurements
5
Number of values = 5
value [1 of 5]:65.32
value [2 of 5]:12.56
value [3 of 5]:71.35
value [4 of 5]:50.5
value [5 of 5]:96.32
------ Menu ------
1).min     5).count above mean
2).max     6).print all
3).mean    7).print history
4).range   8).quit
Please enter a valid menu number
1
Choice 1
min = 12.56
Please enter a valid menu number
2
Choice 2
max = 96.32
Please enter a valid menu number
3
Choice 3
mean = 59.21
Please enter a valid menu number
4
Choice 4
range = 83.76
Please enter a valid menu number
5
Choice 5
Count above mean = 3
Please enter a valid menu number
6
Choice 6
65.32   12.56   71.35   50.50   96.32
Please enter a valid menu number
7
Choice 7
1       2       3       4       5       6       7
Please enter a valid menu number
8
Choice 8
Session ended. 5 values processed, 8 menu action performed

## Notes

- Single source file; all logic in `main` (no functions yet — this is a Module 1
  exercise; a later module refactors into functions).
- Fixed-size array `double values[100]`; no dynamic allocation.
- Values are stored and processed using 0-based indexing (valid slots 0..N-1).
- The menu-action history uses a circular buffer read from the oldest slot, the
  same pattern used by a UART receive buffer in embedded firmware.

## Author

Tharindu Madhurange