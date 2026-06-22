##1. Match printf/scanf conversion specifiers to the exact argument type
Rule: %u for unsigned int, %d for int — not interchangeable.
Why: %d with unsigned is a type mismatch the standard doesn't guarantee; -Wformat
flags it. Bad: sscanf(line,"%d",&n) / printf("%d",n) with unsigned n.
Good: sscanf(line,"%u",&n) / printf("%u",n).

##2. Validate input against the problem's domain, not just "is it a number"
Rule: after a value parses, separately check it's in the allowed range.
Why: a negative read with %d into unsigned int wraps to a huge positive, giving a
confident wrong answer. Bad: parse only. Good: parse, then `if (n < 0) reject

##3. Prevent signed integer overflow before it happens, not after  (2026-06-11, Tier 3 — 3.2 Reverse the digits)
Rule:Before a signed multiply/add that could exceed the type's range, test whether it would overflow and bail out; never rely on inspecting the result afterward.
Why:Signed overflow in C is undefined behavior (unlike unsigned, which wraps predictably). The compiler may assume it never occurs, so the overflowed value is
meaningless and undetectable after the fact. Operations that grow a value — like building a reversed number — can exceed INT_MAX even for valid input.
**Example — bad:**
```c
reversed = reversed * 10 + digit;   // overflows int for large inputs -> UB
```
**Example — good:**
```c
#include <limits.h>
if (reversed > (INT_MAX - digit) / 10) { /* would overflow */ return 1; } reversed = reversed * 10 + digit; ``` **Source:** Tier 3 — 3.2, input 1999999999
##4. Copy literal output strings from the spec; match spelling and case exactly
Rule: reproduce specified output text character-for-character by copying from the
spec, not typing from memory.
Why: output-matching tasks and auto-graders compare exactly; "Fuzz" vs "fizz" is a
silent failure even when the logic is perfect.
Bad:  printf("Fuzz\n");   // spec said 'fizz'
Good: printf("fizz\n");

##5 Prefer while over do-while unless the body must run at least once
Rule: choose the loop whose natural behavior matches the requirement; use do-while
only when the body genuinely must execute before the first condition test.
Why: do-while always runs the body once before checking, so an excluded value that
reaches the loop gets processed anyway. while tests first and handles the
zero-iteration case on its own.
Bad:  do { /* classify n */ n--; } while (n > 0);   // processes n even if n == 0
Good: while (n > 0) { /* classify n */ n--; }

##6 Return 0 for normal exit; non-zero only for errors
Rule: 0 = success, non-zero = error. Quitting the normal way (typing 'q') is success -> return 0.
Why: scripts and tests check the exit code. return 1 on a normal quit tells them the program failed.
Bad:  if (quit) return 1;
Good: if (quit) return 0;

##7 Check what comes after the integer; reject trailing junk
Rule: after reading a number, check the rest of the line is empty. Reject "42abc".
Why: sscanf("%d") stops at the first non-digit and reports success, so "42abc" passes as 42.
     In a UART/OSDP parser, accepting a broken field is a real bug.
Bad:  if (sscanf(line, "%d", &n) == 1) accept(n);             // "42abc" passes
Good: if (sscanf(line, "%d %c", &n, &extra) == 1) accept(n);  // "42abc" returns 2, rejecte

##8 Reject values outside an inclusive range with (n < lo) || (n > hi)
    Rule: use OR (||), and < / > (not <= / >=) so the endpoints stay valid.
    Why: AND (&&) is always false for a range check, so nothing is rejected.
    Bad:  if ((n <= 0) && (n >= 255)) reject;  // always false; 0 and 255 are valid
    Good: if ((n < 0)  || (n > 255)) reject;

##9 Use a space, not a tab, for a fixed gap
    Rule: a space is always 1 character; a tab jumps to the next tab stop (every 8
    columns), so its width changes with the text before it.
    Why: tabs line up columns at fixed positions, not fixed gaps. For one steady
    space between fields, print a space.
    Bad:  printf("%d 0x%02X\t", n, n);   // gap changes: 255 -> big, 85 -> small
    Good: printf("%d 0x%02X ",  n, n);   // always one space

Note: the hex/decimal format issues are the same "match spec output" and "%X needs
unsigned" rules you already saved — not new

##10 Test/read a bit with & (never &=)
    Rule: to TEST a bit, use reg & (1U << b) -- read only. Never use &= for a test.
    Why: reg &= (1U << b) keeps only bit b and clears every other bit -- it destroys
    the register. A test must not change anything.
    Bad:  reg &= (1U << b);                  // wipes all other bits!
    Good: printf("%d", (reg >> b) & 1);      // reads, does not change reg

##11 Do not retry input after EOF (NULL means stop)
    Rule: when fgets returns NULL, stop the loop (return/break). Do not 'continue'.
    Why: EOF (end of input / Ctrl+D) is permanent. fgets keeps returning NULL, so
    'continue' becomes an infinite loop.
    Bad:  if (fgets(...) == NULL) { printf("error"); continue; }   // infinite loop
    Good: if (fgets(...) == NULL) return 0;                         // stop cleanly

