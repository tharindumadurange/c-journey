# 3.6 Review — Set, Clear, Toggle, Test (Short)  (2026-06-21)

**Verdict:** Menu, validation, and the set/clear/toggle idioms are correct — nice.
But "test bit" is wrong: it CHANGES the register instead of just reading it.
Also EOF makes the program loop forever, and one error message shows the wrong number.

**Compiles?** Clean.

---

## ✓ Good
- `uint8_t reg` — exactly as the task asked.
- set / clear / toggle are all correct firmware idioms:
  - set:    `reg |= 1U << b;`
  - clear:  `reg &= ~(1U << b);`
  - toggle: `reg ^= 1U << b;`
- Used `1U` for the shift — safe.
- Menu range (1-6) and bit range (0-7) checks use `||` and `< / >` correctly
  (you applied the 3.5 lesson).

---

## ✗ Fix these

**1. "Test bit" is broken.** ← most important
You wrote:

    case 4:
        reg &= (1U << bitsel);   // this CHANGES reg

`reg &= (1U << b)` keeps only bit b and clears all the others. It destroys the
register. A test must only READ and report — use `&`, not `&=`.

    case 4:
        printf("bit %d = %d\n", bitsel, (reg >> bitsel) & 1);
        break;

**2. EOF makes an infinite loop.**
When input ends (Ctrl+D), `fgets` returns NULL. You print an error and `continue`
— but EOF is permanent, so fgets returns NULL again, forever. On NULL, stop instead
of retrying (both the outer and inner loops):

    if (fgets(line, sizeof line, stdin) == NULL) return 0;

**3. Wrong number in the bit-range error.**
`printf("%d is out of bit range\n", opsel);` prints `opsel` (the menu choice).
It should print `bitsel` (the bad bit number).

---

## Small notes
- Typo: "Progrm Exit" → "Program Exit".
- After option 5 (print register), the menu is not shown again, but it IS shown
  after options 1-4. Reprint it consistently (or print it once at the top of the loop).
- The `switch` is indented as if it is inside the inner `while`, but it is not.
  Fix the indentation so the structure is clear.