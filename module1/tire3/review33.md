# Review — Tier 3, 3.3 Count down with a twist

## 1. Verdict
Logic, count direction (N down to 1), and range (1..50) are all correct. But the
output strings are wrong: spec wants lowercase fizz/buzz/fizzbuzz; code has
"Fuzz"/"FuzzBuzz"/"Buzz" — wrong letter on fizz, wrong case on all three. Plus
"%2d" adds an unrequested leading space on single digits. A transcription bug, not
a logic bug.

## 2. Compilation check
Clean under -Wall -Wextra -Wpedantic. All variables used; %d / %2d match int;
n set by sscanf before use.

## 3. Correctness
Counts down from entered N to 1, classifying each value. Logic verified correct.
Output-string bugs (vs spec):
  "Fuzz"     -> should be "fizz"     (wrong letter and case)
  "FuzzBuzz" -> should be "fizzbuzz" (wrong letter and case)
  "Buzz"     -> should be "buzz"     (wrong case)
  "%2d"      -> should be "%d"       (no padding requested; %2d pads single digits)
Edge cases from the spec (correct after fixes):
  N = 1  -> single line: 1
  N = 15 -> fizzbuzz, 14, 13, fizz, 11, buzz, fizz, 8, 7, fizz, buzz, 4, fizz, 2, 1

## 4. Concept gaps
1. Output-string fidelity: literal output text must match the spec exactly,
   including case. Retyping from memory introduced "Fuzz" for "fizz".
2. Loop-construct choice coupling: the do-while is correct ONLY because the range
   check guarantees n >= 1.

## 5. Mini-teaching
Output strings: when a spec quotes exact text, that text is the expected output,
character for character. Copy it from the spec; don't type from memory. The logic
can be flawless and the program still fails because "Fuzz" != "fizz".

do-while vs while: do-while runs the body once before testing; while tests first.
"Process while positive" is naturally a while. If 0 ever reached the loop, do-while
would run once for 0, and 0 is divisible by 3 and 5 -> it would print fizzbuzz for
zero. while (n > 0) does nothing for 0 on its own.

## 6. Alternative approach
Same logic with while and the corrected literals:

    while (n > 0) {
        if (n % 3 == 0) {
            if (n % 5 == 0) printf("fizzbuzz\n");
            else            printf("fizz\n");
        }
        else if (n % 5 == 0) printf("buzz\n");
        else                 printf("%d\n", n);
        n--;
    }

The nested if (check %3 once, %5 inside) is fine -- keep it.

## 7. Style and good-practice notes
- Lines 21-25: the n < 0 guard is redundant; the range check (n < 1) already
  rejects all negatives. It changes only the error message. Drop it, or keep it
  deliberately for a distinct message.
- Line 8: prompt says "non-negative integer (1-50)" -- contradictory (0 is
  non-negative but out of range). Say "Enter an integer (1-50)".
- Forward note (do NOT fix now): sscanf %d can't safely detect an input that
  overflows int; the range check only contains the damage by luck. strtol is the
  robust tool -- that's what exercise 3.4 (robust integer reader) is for.

## 8. Proposed C_GOOD_PRACTICES.md entries
(Two entries this review. Also copied into C_GOOD_PRACTICES.md, renumbered.)

### Copy literal output strings from the spec; match spelling and case exactly
Rule: reproduce specified output text character-for-character by copying from the
spec, not typing from memory.
Why: output-matching tasks and auto-graders compare exactly; "Fuzz" vs "fizz" is a
silent failure even when the logic is perfect.
Bad:  printf("Fuzz\n");   // spec said 'fizz'
Good: printf("fizz\n");

### Prefer while over do-while unless the body must run at least once
Rule: choose the loop whose natural behavior matches the requirement; use do-while
only when the body genuinely must execute before the first condition test.
Why: do-while always runs the body once before checking, so an excluded value that
reaches the loop gets processed anyway. while tests first and handles the
zero-iteration case on its own.
Bad:  do { /* classify n */ n--; } while (n > 0);   // processes n even if n == 0
Good: while (n > 0) { /* classify n */ n--; }

## 9. Next step
Apply the four string/format fixes, recompile, and run with N = 1 and N = 15 to
confirm the exact outputs above (lowercase words, no leading spaces on numbers).