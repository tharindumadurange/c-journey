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
