# 3.4 Review — Short Version

**Verdict:** Your code runs and the adding works. But it is not "robust" yet. There are 4 things to fix.

**Compiles clean?** Yes. No warnings.

## ✓ What is good
- You used `fgets` + `sscanf`, like the spec asked.
- You accept negative numbers. Correct — negatives are integers too.
- The loop and the sum are clean.

## ✗ What to fix (4 things)

**1. It accepts `"42abc"` as `42`.** ← most important
`sscanf("%d")` reads the `42` part and stops. It does not see the `abc`. So your code thinks the input is fine. But this exercise is about robust reading. `"42abc"` is not a real integer. Your code should say no.

**2. Wrong output text.**
Spec wants: `sum so far: X`
You wrote: `Sum of entered integers = X`
This is the same rule you saved last review (copy the exact words from the spec). It happened again here.

**3. `'q'` exits with an error code.**
Typing `q` is the normal way to quit. That is success. But you wrote `return 1`, and `1` means "error" to the computer. Use `return 0`.

**4. Bad input is dropped silently.**
When the user types `"abc"`, your code just ignores it. No message. The spec says reject input gracefully — that means: show a message like "that was not a number." Do not stay silent.

**Bonus problem:** `"quit"` or `"queen"` will also exit, because your check only looks at the first letter `q`. Only `q` by itself should exit.