# Review — Tier 3, 3.2 Reverse the digits  (2026-06-11)

## 1. Verdict
Works correctly for typical inputs and all guarded edge cases (zero, negatives,
trailing zeros), but reversing a large value (e.g. 1999999999) overflows int,
which is undefined behavior.

## 2. Compilation check
Clean under -Wall -Wextra -Wpedantic. Types match specifiers, no unused includes,
no uninitialized reads — a step up from 3.1's two -Wformat warnings.
Caveat: the compiler will NOT warn about the overflow below. Signed overflow is a
runtime issue on values the compiler can't see, so -Wall is no help — reason about
it yourself.

## 3. Correctness
Reverse loop is right: n % 10 peels the lowest digit, n /= 10 drops it,
reversed = reversed * 10 + digit shifts the accumulator left and drops the digit in.
- Normal (123) -> 321. Correct.
- Zero (0) -> loop skipped, prints 0. Correct.
- Trailing zero (120) -> 21 (not 021). Correct/expected.
- Negative (-5) -> rejected. Correct.
- Large (1999999999) -> BUG. Parses fine (below INT_MAX) and passes all guards,
  but its reverse 9999999991 far exceeds INT_MAX; reversed * 10 + digit overflows
  signed int -> undefined behavior.

## 4. Concept gaps
Signed integer overflow is undefined behavior (integer overflow risks category).
Reversing can yield a value larger than the original, so valid input can still
push reversed past INT_MAX.

## 5. Mini-teaching
On STM32F407/MSP432, int tops out at 2147483647. reverse(1999999999) = 9999999991,
~5x too big.
8051 contrast: an 8-bit accumulator past 255 wraps to 0 and sets the carry flag —
defined and detectable. C guarantees that wrap behavior ONLY for unsigned types.
Signed overflow is undefined: the compiler may assume it never happens, so the
result is meaningless and can't be reliably detected afterward. Therefore: with
signed types, prevent overflow BEFORE it happens, not after.

## 6. Alternative approach
Check whether the next multiply-add would overflow, before doing it:

    #include <stdio.h>
    #include <limits.h>   // INT_MAX

    while (n > 0) {
        digit = n % 10;
        n /= 10;
        if (reversed > (INT_MAX - digit) / 10) {
            printf("Reversed value overflows int\n");
            return 1;
        }
        reversed = reversed * 10 + digit;
    }

Why before, not after: we want reversed * 10 + digit <= INT_MAX, i.e.
reversed <= (INT_MAX - digit) / 10. If reversed already exceeds that, the op would
overflow, so bail first. Checking after is impossible — once overflow occurs the
value is undefined.
INT_MAX (<limits.h>) is the portable "biggest int on this target", which matters
because that limit differs across MCUs. This is the right time to use limits.h,
unlike the speculative stdint.h include in 3.1.

## 7. Style and good-practice notes
- Line 11: comment "// Handle Non numeric garbage" is on the wrong guard. The
  fgets() == NULL check handles no-input / EOF / read error, not garbage. Garbage
  is caught by the sscanf != 1 check below. Fix to "// No input (EOF or read error)".
- Line 9: prompt says "positive integer" but 0 is accepted (n < 0 lets 0 through).
  Say "non-negative" or reject 0, per intent.
- Line 1: "Tire" -> "Tier", "digit" -> "digits". Cosmetic.

## 8. Next step
Add the overflow guard, recompile to confirm it's still clean, then run with
1999999999 and confirm it reports the overflow instead of printing nonsense.