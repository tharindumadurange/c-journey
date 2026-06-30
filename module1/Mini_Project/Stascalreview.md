# Tier 5 Review — Statistics Calculator (Short)  (2026-06-21)

**Verdict:** Good structure — menu, validation, robust input, and switch all work.
But 3 real bugs: "count above mean" counts the WRONG side, and two arrays are
written past their end (memory corruption). Fix these before it goes in your portfolio.

**Compiles?** Likely clean, but two array-overflow bugs are runtime, so -Wall will
NOT catch them. You must fix them by hand.

---

## ✓ Good
- Robust input everywhere (fgets + sscanf + return check). Re-prompts on bad value.
- Stops on EOF instead of looping (your 3.6 lesson — applied).
- switch for the menu, as the spec asked.
- mean / min / max reset correctly at the top of each menu turn.
- Quit count is correct (4 actions for 3,5,7,8 — matches the sample).

---

## ✗ Fix these

**1. "Count above mean" counts BELOW the mean.** ← most important

    if(values[x] < mean){ cntAbvMean++; }   // < counts the wrong side

Spec wants count ABOVE the mean, and ties (equal to mean) are NOT above.
Use `>`:

    if(values[x] > mean){ cntAbvMean++; }

**2. `menuHistory[31]` is too small → writes past the end.**
You keep 32 actions, but `int menuHistory[31]` has only slots 0..30. When menuCnt
reaches 31 you write `menuHistory[31]` — out of bounds (memory corruption).
Make it size 32:

    int menuHistory[32];

**3. 1-based indexing → `values[n]` overflow at n = 100.**
You use indices 1..n (`values[j++]` with j=1, loops `x = 1; x <= n`).
C arrays start at 0. `double values[100]` has valid slots 0..99. For n = 100 you
read/write `values[100]` — out of bounds.
Fix: use 0-based everywhere. Store `values[i]` for i = 0..n-1, init min/max from
`values[0]`, and loop `for(x = 0; x < n; x++)`.

---

## Notes (smaller)
- **History order after wrap:** when overflowflag is set, you print slots 0..31 in
  array order. After the buffer wraps, the oldest item is NOT at slot 0, so the
  history prints out of time order. (This is the SAME ring-buffer idea as a UART RX
  buffer — worth getting right.) Print starting from the oldest slot (`menuCnt`),
  wrapping around.
- **Output text** (your recurring lesson): spec says `== Statistics Calculator ==`
  (you wrote "Static"); value prompt is `value [k of N]: ` (same line, with colon);
  menu prompt is `Choice: `. Match them — this is the rule you already saved.
- **Style:** `printf("range = %.2lf\n", range = max - min);` hides an assignment
  inside printf. Compute first, then print:
      range = max - min;
      printf("range = %.2lf\n", range);
