# Unit 2: Conditional Statements in C++

## Overview

This unit covers **decision-making** in C++: how programs choose different paths of execution based on conditions. The core topics are relational operators, `if` statements (and their variants), logical operators, the `switch` statement, and character/string comparisons.

---

## 1. Relational Operators

Relational operators compare two values and produce a **boolean** result (`true` / `false`, stored internally as `1` / `0`).

| Operator | Meaning                  |
|----------|--------------------------|
| `>`      | Greater than             |
| `<`      | Less than                |
| `>=`     | Greater than or equal to |
| `<=`     | Less than or equal to    |
| `==`     | Equal to                 |
| `!=`     | Not equal to             |

An expression like `num1 > num2` is called a **relational expression**. It does not *assert* that `num1` is greater — it *tests* whether it is, and evaluates to `true` or `false`.

The result can be stored in a variable:

```cpp
bool result = x <= y;  // 1 if true, 0 if false
```

### Assignment (`=`) vs. Equality (`==`)

This is one of the most common bugs in C++. Consider the difference:

```cpp
int years;
years = 6;      // ASSIGNMENT — puts 6 into years
years == 5;     // RELATIONAL EXPRESSION — tests if years equals 5 (false here)
years = years - 1;  // years is now 5
years == 5;     // now this is true
```

The original `initialize.cpp` lab demonstrates this bug directly. The starter code had:

```cpp
if (num1 = num2)   // BUG: assigns num2 to num1, then tests if non-zero
```

This always evaluates to true (as long as `num2` is non-zero) because `=` is assignment, not comparison. The fix:

```cpp
if (num1 == num2)  // CORRECT: tests equality
```

---

## 2. The `if` Statement

Conditional statements let portions of code execute **only when certain conditions are met**. For example, a payroll program should only compute overtime pay if an employee worked more than 40 hours.

```cpp
if (expression)
    statement;
```

If `expression` evaluates to true (non-zero), the statement executes. Otherwise it is skipped.

### Block Bodies

To execute multiple statements conditionally, wrap them in braces:

```cpp
if (score > 90)
{
    grade = 'A';
    cout << "Good Job!" << endl;
}
```

Without braces, only the **first** statement after `if` is conditional — a common source of bugs.

### `if`/`else`

Handles exactly **two** paths. The program can only take one:

```cpp
if (average >= 60)
    cout << "You Pass" << endl;
else
    cout << "You Fail" << endl;
```

This is more elegant than writing two separate `if` statements with opposite conditions (as done in Sample Program 4.1 from the pre-lab), because it guarantees exactly one branch always executes.

### `if`/`else if`/`else`

Chains multiple conditions, evaluated **top to bottom**. The first true branch executes and the rest are skipped:

```cpp
if (bonus < 1000)
    cout << "Another vacation eating hot dogs on the lawn" << endl;
else if (bonus < 10000)
    cout << "Off to Disney World!" << endl;
else if (bonus == 10000)
    cout << "Let's go to Hawaii!" << endl;
```

**Why doesn't the second branch need `>= 1000`?** Because of the top-down evaluation. If we reach `else if (bonus < 10000)`, the first condition (`bonus < 1000`) was already false — meaning `bonus` must be at least 1000. The earlier conditions act as implicit guards.

### The Trailing `else`

A final `else` at the end of an `if`/`else if` chain catches **all remaining cases**. Without it, some inputs produce no output at all:

```cpp
if (bonus < 1000)
    cout << "Hot dogs on the lawn" << endl;
else if (bonus < 10000)
    cout << "Disney World!" << endl;
else if (bonus == 10000)
    cout << "Hawaii!" << endl;
else
{
    cout << bonus << " is not a valid bonus" << endl;
    cout << "Please run the program again with valid data" << endl;
}
```

The `grades.cpp` lab extends this pattern with full grade categories plus invalid-data guards on both ends:

```cpp
if (average > 100)
    cout << "Invalid data" << endl;
else if (average >= 90)
    cout << "'A' category" << endl;
else if (average >= 80)
    cout << "'B' category" << endl;
else if (average >= 60)
    cout << "You Pass" << endl;
else if (average >= 0)
    cout << "You Fail" << endl;
else
    cout << "Invalid data" << endl;   // handles negatives like -12
```

### Nested `if` Statements

An `if` inside another `if`. Useful when a second decision only makes sense after the first:

```cpp
if (programmer == 'Y')
{
    cout << "Do you program in C++?" << endl;
    cin >> cPlusPlus;

    if (cPlusPlus == 'Y')
        cout << "You look like a promising candidate" << endl;
    else if (cPlusPlus == 'N')
        cout << "You need to learn C++" << endl;
    else
        cout << "You must enter Y or N" << endl;
}
else if (programmer == 'N')
    cout << "You are not currently qualified" << endl;
else
    cout << "You must enter Y or N" << endl;
```

Notice how the trailing `else` at each level catches invalid input — a good defensive practice.

### `if` Statement Initialization (C++17)

You can declare a variable scoped to the `if`/`else` block:

```cpp
if (int len = password.length(); len < MIN_LENGTH)
    cout << "Too short." << endl;
else
    cout << "Your password has " << len << " characters." << endl;
```

`len` exists only within the `if`/`else` scope, keeping the outer scope clean.

---

## 3. Flags

A **flag** is a variable (usually `bool`) that signals whether a condition has been met:

```cpp
bool isValid = true;
// ...later...
if (isValid)
    // proceed
```

An integer can also serve as a flag: `0` is false, any non-zero value is true.

---

## 4. Logical Operators

Logical operators combine or negate relational expressions to form more complex conditions.

| Operator | Meaning | Notes |
|----------|---------|-------|
| `&&`     | AND     | True only if **both** operands are true |
| `\|\|`  | OR      | True if **at least one** operand is true (**inclusive** OR) |
| `!`      | NOT     | Reverses truth value; wrap the operand in parentheses for clarity |

### Inclusive vs. Exclusive OR

In everyday English, "or" can be exclusive ("concert or ball game" — not both) or inclusive ("ace or king" — could be both). **C++ uses inclusive OR.** `A || B` is true when A is true, B is true, or both are true. There are three scenarios where `if (sunny || warm)` evaluates to true:

1. Sunny but not warm
2. Warm but not sunny
3. Both sunny and warm

### Examples

**AND** — both conditions must hold:

```cpp
if (employed == 'Y' && recentGrad == 'Y')
    cout << "You qualify for the special interest rate." << endl;
```

**NOT with OR** — negating a compound expression:

```cpp
if (!(income >= MIN_INCOME || years > MIN_YEARS))
    cout << "You don't qualify." << endl;
```

**Parenthesizing after `!`** — it is good practice to always enclose the operand after the `!` operator in parentheses. Unexpected results can occur in complex expressions otherwise:

```cpp
if (dollars <= 0 || !(accountActive))
    cout << "You may not withdraw money from the bank";
```

### De Morgan's Law

Useful for simplifying or rewriting conditions:

- `!(A || B)` is equivalent to `(!A && !B)`
- `!(A && B)` is equivalent to `(!A || !B)`

### Equivalences Worth Knowing

- `gpa >= 2.0` is the same as `!(gpa < 2.0)`
- Be careful with data types: if `year` is a `char`, don't compare it with `< 4` — compare it with `< '4'`. Characters are compared by ASCII value, and the character `'4'` (ASCII 52) is not the same as the integer `4`.

### Logical Operator Pitfall: Changing `&&` to `||`

From the `LogicalOp.cpp` lab — replacing `&&` with `||` dramatically changes who "graduates":

```cpp
// Original: must be BOTH a senior AND have GPA >= 2.0
if (gpa >= 2.0 && year == '4')

// Changed: EITHER senior OR GPA >= 2.0 is enough
if (gpa >= 2.0 || year == '4')
```

The second version is far too loose — a freshman with a 2.0 GPA would be told "time to graduate." Understanding the difference between AND and OR is critical.

---

## 5. The `switch` Statement

Another form of conditional statement. Selects among multiple paths based on an **integer or character expression**.

```cpp
switch (expression)
{
    case value1:
        statements;
        break;
    case value2:
        statements;
        break;
    default:
        statements;
}
```

### Rules

1. The `expression` must evaluate to an **integer type** (includes `char` — the compiler automatically converts characters to their integer ASCII values).
2. Each `case` value must be a **constant** and **unique**.
3. `default` is optional but recommended as a catch-all. It executes if none of the case values match.

### The `break` Statement

Without `break`, execution **falls through** to the next case. This is intentional in C++ but usually a bug if unintended.

Removing all `break` statements from a switch means that once a case matches, **every subsequent case's statements also execute** until the end of the switch block or a `break` is reached.

**Fall-through on purpose** — grouping cases that share the same outcome:

```cpp
switch (month) {
    case 12:
    case 1:
    case 2:
        cout << "Winter" << endl;
        break;
    case 3:
    case 4:
    case 5:
        cout << "Spring" << endl;
        break;
    // ...
}
```

Here `case 12`, `case 1`, and `case 2` intentionally fall through to share the "Winter" output.

### Character & String Comparisons with `switch`

Characters and string objects can be compared with the same relational operators used for numbers. A `switch` on a `char` can also modify string variables:

```cpp
char letter = 'F';
string word = "passed";

switch (letter)
{
    case 'A': cout << "Your grade is A." << endl; break;
    case 'B': cout << "Your grade is B." << endl; break;
    case 'C': cout << "Your grade is C." << endl; break;
    case 'D': cout << "Your grade is D." << endl; break;
    case 'F': word = "failed"; break;
    default:  cout << "Invalid grade" << endl;
}

if (word == "passed")
    cout << "You passed" << endl;
else
    cout << "You failed" << endl;
// Prints: "You failed" (because letter is 'F', word was changed to "failed")
```

This shows that `switch` cases can do more than just print — they can modify variables that are checked later with `if` statements.

### Switch vs. `if`/`else if`

Any `switch` can be rewritten as an `if`/`else if` chain, and vice versa (when comparing a single value against discrete constants):

```cpp
// switch version
switch (grade) {
    case 'A': cout << "Excellent!"; break;
    case 'B': cout << "Good job";   break;
    default:  cout << "Invalid";
}

// equivalent if/else if version
if (grade == 'A')
    cout << "Excellent!";
else if (grade == 'B')
    cout << "Good job";
else
    cout << "Invalid";
```

The `default` case corresponds to the trailing `else`.

### Menu-Driven Programs

`switch` is a natural fit: display options, read user input, branch on that input.

---

## 6. Key Takeaways

| Concept | When to Use |
|---------|-------------|
| `if` / `else` | Two-way decisions |
| `if` / `else if` / `else` | Multi-way decisions based on ranges or complex conditions |
| Nested `if` | A decision depends on a prior decision |
| `switch` | Multi-way decisions on a single integer/char value with discrete options |
| Logical operators | Combining or negating conditions |
| Trailing `else` / `default` | Catch-all for invalid input or unexpected values |

### Common Mistakes to Avoid

- **`=` vs `==`** — Using assignment instead of equality. `if (x = 5)` assigns 5 to x and always evaluates to true.
- **Forgetting `break`** in a `switch` — causes unintended fall-through to subsequent cases.
- **`char` vs `int` comparisons** — if `year` is a `char`, compare with `'4'` not `4`. The character `'4'` has ASCII value 52.
- **Missing braces** on multi-statement `if` bodies — only the first statement is conditionally executed without braces.
- **Confusing `&&` and `||`** — AND requires both true; OR requires at least one. Swapping them changes logic dramatically.
- **No trailing `else`/`default`** — leaves some inputs silently unhandled.

---

## 7. Pre-Lab Writing Answers

| # | Question | Answer |
|---|----------|--------|
| 1 | Two possible values for a relational expression | **true** and **false** |
| 2 | C++ symbol for AND | **`&&`** |
| 3 | `switch` and `if` are examples of ___ statements | **conditional** |
| 4 | Is C++ OR inclusive or exclusive? | **Inclusive** |
| 5 | C++ symbol for OR | **`\|\|`** |
| 6 | Good practice after the NOT operator | **Enclose the operand in parentheses** |
| 7 | `switch` uses the value of a(n) ___ expression | **integer** |
| 8 | The ___ branch executes when no case matches | **default** |
| 9 | C++ compares numeric values using | **relational operators** |
| 10 | C++ symbol for equality | **`==`** |

---

## 8. Lab Exercises Summary

| Lab | File | What You Practiced |
|-----|------|--------------------|
| 4.1 | `initialize.cpp` | The `=` vs `==` bug — the starter code used assignment inside `if`, always returning true. Fixed to use equality. Extended to have both values user-input and to use `if`/`else`. |
| 4.2 | `grades.cpp` | Went from two separate `if` statements to `if`/`else`, then to full `if`/`else if`/`else` with grade categories (A/B/pass/fail) and invalid-data guards for values > 100 and < 0. |
| 4.3 | `LogicalOp.cpp` | Explored `&&`, `||`, and `!`. Rewrote `gpa >= 2.0` as `!(gpa < 2.0)`. Learned that `year != '4'` cannot be replaced with `year < 4` because `year` is a `char`. Analyzed how swapping `&&`/`||` changes graduation logic. |
| 4.4 | `switch.cpp` | Removed `break` to observe fall-through. Added a "YOU PASSED!" message for grades D or better using intentional fall-through. Rewrote the entire `switch` as `if`/`else if` — the trailing `else` corresponds to `default`. |
| 4.5 | `student_generated_code.cpp` | Option 1: Quarterly water bill calculator — reads 4 quarterly bills, computes average monthly bill, uses `if`/`else if`/`else` to classify water usage (excessive > $75, typical $25–$75, conserving < $25). |
| Auto 1 | `auto_graded_assignment_1.cpp` | Nested `switch` statements: determines meteorological season based on hemisphere (N/S) and month (1–12), using intentional fall-through to group months by season. |
