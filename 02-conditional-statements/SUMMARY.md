# Unit 2: Conditional Statements in C++

## Overview

This unit covers **decision-making** in C++: how programs choose different paths of execution based on conditions. The core topics are relational operators, `if` statements (and their variants), logical operators, and `switch` statements.

---

## 1. Relational Operators

Relational operators compare two values and produce a boolean result (`true` / `false`, stored as `1` / `0`).

| Operator | Meaning                  |
|----------|--------------------------|
| `>`      | Greater than             |
| `<`      | Less than                |
| `>=`     | Greater than or equal to |
| `<=`     | Less than or equal to    |
| `==`     | Equal to                 |
| `!=`     | Not equal to             |

The result can be stored in a variable:

```cpp
bool result = x <= y;  // 1 if true, 0 if false
```

**Common pitfall:** `==` is equality; `=` is assignment. Mixing them up is a classic bug.

---

## 2. The `if` Statement

The simplest form of conditional execution.

```cpp
if (expression)
    statement;
```

If `expression` evaluates to true (non-zero), the statement executes. Otherwise it is skipped.

### Block Bodies

To execute multiple statements, wrap them in braces:

```cpp
if (score > 90)
{
    grade = 'A';
    cout << "Good Job!" << endl;
}
```

### `if`/`else`

Handles exactly two paths:

```cpp
if (average >= 60)
    cout << "You Pass" << endl;
else
    cout << "You Fail" << endl;
```

### `if`/`else if`/`else`

Chains multiple conditions, evaluated top to bottom. The first true branch executes and the rest are skipped:

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
    cout << "Invalid data" << endl;
```

The trailing `else` acts as a catch-all for anything that didn't match.

### Nested `if` Statements

An `if` inside another `if`. Useful when a second decision only makes sense after the first:

```cpp
if (programmer == 'Y')
{
    cout << "Do you program in C++?" << endl;
    cin >> cPlusPlus;

    if (cPlusPlus == 'Y')
        cout << "You look like a promising candidate" << endl;
    else
        cout << "You need to learn C++" << endl;
}
else
    cout << "Not currently qualified" << endl;
```

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

Combine or negate relational expressions.

| Operator | Meaning | Notes |
|----------|---------|-------|
| `&&`     | AND     | True only if **both** operands are true |
| `\|\|`  | OR      | True if **at least one** operand is true (inclusive OR) |
| `!`      | NOT     | Reverses truth value; wrap the operand in parentheses for clarity |

### Examples

**AND** -- both conditions must hold:

```cpp
if (employed == 'Y' && recentGrad == 'Y')
    cout << "You qualify for the special interest rate." << endl;
```

**NOT with OR** -- negating a compound expression:

```cpp
if (!(income >= MIN_INCOME || years > MIN_YEARS))
    cout << "You don't qualify." << endl;
```

By De Morgan's Law, `!(A || B)` is equivalent to `(!A && !B)`.

### Equivalences Worth Knowing

- `gpa >= 2.0` is the same as `!(gpa < 2.0)`
- Be careful with data types: if `year` is a `char`, don't compare it with `< 4` -- compare it with `< '4'`.

---

## 5. The `switch` Statement

Selects among multiple paths based on an **integer or character expression**.

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

1. The `expression` must evaluate to an integer type (includes `char`).
2. Each `case` value must be a **constant** and **unique**.
3. `default` is optional but recommended as a catch-all.

### The `break` Statement

Without `break`, execution **falls through** to the next case. This is intentional in C++ but usually a bug if unintended.

**Fall-through on purpose** -- grouping cases that share the same outcome:

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

### Switch vs. `if`/`else if`

A `switch` on grade letters can be rewritten as an `if`/`else if` chain:

```cpp
// switch version
switch (grade) {
    case 'A': cout << "Excellent!"; break;
    case 'B': cout << "Good job";   break;
    // ...
}

// equivalent if/else if version
if (grade == 'A')
    cout << "Excellent!";
else if (grade == 'B')
    cout << "Good job";
// ...
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

### Common Mistakes to Avoid

- Using `=` (assignment) instead of `==` (equality).
- Forgetting `break` in a `switch`, causing unintended fall-through.
- Comparing a `char` variable with an integer literal instead of a character literal (e.g., `year < 4` vs. `year < '4'`).
- Omitting braces on multi-statement `if` bodies -- only the first statement is conditionally executed without braces.

---

## Lab Exercises Covered

| File | Topic |
|------|-------|
| `initialize.cpp` | Equality (`==`) vs. assignment (`=`), comparing user input |
| `grades.cpp` | Multi-branch `if`/`else if` for grade categories with input validation |
| `LogicalOp.cpp` | Logical operators (`&&`, `\|\|`, `!`), char comparison subtleties |
| `switch.cpp` | Rewriting a `switch` as `if`/`else if`; understanding fall-through and `default` |
| `student_generated_code.cpp` | Original program: water bill average with `if`/`else if` for usage categories |
| `auto_graded_assignment_1.cpp` | Nested `switch` statements: meteorological seasons by hemisphere and month |
