# 3.5 Review — Hex Dump of a Byte (Short)  (2026-06-21)

**Verdict:** Binary loop is correct (the hard part — good). But the range check
does nothing, and the decimal/hex output do not match the spec.

**Compiles?** One likely warning: `%X` wants an *unsigned* value, but `n` is `int`
(your 3.1 lesson).

---

## ✓ Good
- Binary loop is correct (42 → `00101010`).
- Used `1U << i` — the safe way to shift.
- Input reading (fgets + sscanf) is solid.

---

## ✗ Fix these

**1. Range check is broken.** ← most important
`if ((n <= 0) && (n >= 255))` is ALWAYS false → nothing is rejected (try 1000).
`&&` must be `||`, and `<= / >=` must be `< / >` (0 and 255 are valid).

    if ((n < 0) || (n > 255))

**2. Hex is wrong.**
`%#0X` prints `0X2A` (capital X) and does not pad (5 → `0X5`). Spec wants `0x2A` / `0x05`.

    printf("0x%02X", (unsigned)n);

**3. Decimal is wrong for small numbers.**
`%02d` prints `05` for 5. Spec wants `5`. Use `%d`.

**4. Tab gives uneven gaps.**
You used `\t`. A tab jumps to the next tab stop (every 8 columns), so the gap
changes with the text length (255 → big gap, 85 → tiny gap). Use ONE space instead,
inside the format string after `%02X` — the binary loop has no space in front.

---

## Corrected output part

    printf("%d 0x%02X ", n, (unsigned)n);   // space after X
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);          // clean way to read a bit
    }
    printf("\n");

Result is always one space: `5 0x05 00000101`, `255 0xFF 11111111`.
