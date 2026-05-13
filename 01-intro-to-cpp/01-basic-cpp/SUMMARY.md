# Unit 1: Basic C++ — Expressions, Input, Output, and Data Types

## Overview

This unit covers the foundational building blocks of C++: writing your first program, declaring variables with various data types, reading user input, producing formatted output, working with expressions and math functions, and understanding how C++ converts between types.

---

## 1. Anatomy of a C++ Program

Every C++ program follows a basic skeleton:

```cpp
#include <iostream>   // preprocessor directive — brings in I/O capabilities

int main() {          // entry point; execution starts here
    std::cout << "Hello, world!" << std::endl;
    return 0;         // 0 signals successful execution to the OS
}
```

### Key Pieces

| Element | Purpose |
|---------|---------|
| `#include <header>` | Preprocessor directive — loads a library before compilation |
| `using namespace std;` | Lets you write `cout` instead of `std::cout` (convenience, not required) |
| `int main()` | The function the OS calls to start your program |
| `return 0;` | Tells the OS the program ended normally |

### Output Basics

- **`cout`** with the **insertion operator `<<`** sends data to the screen.
- **`endl`** flushes the buffer and adds a newline.
- **`\n`** is an escape sequence that adds a newline without flushing.

```cpp
std::cout << "Line one" << std::endl;
std::cout << "Line two\n";
```

---

## 2. Variables and Data Types

A variable is a named memory location. You must **declare** it (give it a type and name) before you use it, and ideally **initialize** it (give it a starting value).

```cpp
int savings = 200;       // declaration + initialization
int checking;            // declaration only (uninitialized — risky!)
checking = 100;          // assignment
```

### Fundamental Types

| Type | What It Holds | Example |
|------|---------------|---------|
| `int` | Whole numbers | `int count = 10;` |
| `double` | Decimal numbers (double precision) | `double pi = 3.14159;` |
| `float` | Decimal numbers (single precision, less common) | `float rate = 8.76f;` |
| `char` | A single character (in single quotes) | `char grade = 'A';` |
| `string` | A sequence of characters (requires `<string>`) | `string name = "Dan";` |
| `bool` | `true` (1) or `false` (0) | `bool passed = true;` |

### The `auto` Keyword

Lets the compiler deduce the type from the initialization value:

```cpp
auto amount = 100;        // int
auto interestRate = 12.0; // double
auto stockCode = 'D';     // char
auto customerNum = 459L;  // long
```

### Named Constants

Values that **cannot change** after initialization. Convention: `ALL_CAPS`.

```cpp
const double TAX_RATE = 0.0675;
const int NUM_STATES = 50;
```

### `sizeof` Operator

Reports how many bytes a type or variable occupies:

```cpp
std::cout << sizeof(double);       // typically 8
std::cout << sizeof(final_money);  // size of the variable
```

### The Modulus Operator `%`

Returns the **remainder** of integer division. Both operands must be integers.

```cpp
std::cout << 13 % 5;  // outputs 3
```

---

## 3. Input with `cin`

`cin` with the **extraction operator `>>`** reads data from the keyboard.

```cpp
int age;
std::cout << "Enter your age: ";   // always prompt before cin
std::cin >> age;
```

### Reading Multiple Values

Separate values with spaces when typing input:

```cpp
double length, width;
std::cin >> length >> width;
```

### How `cin >>` Handles Whitespace

- **Numeric input:** leading whitespace is skipped; reading stops at the first non-numeric character.
- **String input:** leading whitespace is skipped; reading **stops at the first space**. So `"Mary Lou"` would only read `"Mary"`.

### `getline` — Reading Full Lines

Use `getline` to capture an entire line, including spaces:

```cpp
string name;
getline(cin, name);  // reads everything up to the newline
```

### The `cin >>` and `getline` Mixing Problem

`cin >>` leaves a trailing `\n` in the input buffer. A subsequent `getline` immediately consumes that leftover newline and appears to "skip" the input. Fix it with:

```cpp
cin.ignore();  // discard the leftover newline
// or more robust:
cin.ignore(numeric_limits<streamsize>::max(), '\n');
```

### `cin.get()`

Reads the **next character**, including whitespace (unlike `cin >>`):

```cpp
char ch;
cin.get(ch);     // reads even spaces, tabs, newlines
ch = cin.get();  // alternative syntax
cin.get();       // discard one character
```

---

## 4. Formatted Output

Requires `#include <iomanip>`.

### Stream Manipulators

| Manipulator | Effect |
|-------------|--------|
| `fixed` | Display floats in decimal notation (not scientific) |
| `setprecision(n)` | With `fixed`: show `n` digits **after** the decimal. Without `fixed`: show `n` **significant** digits total. |
| `showpoint` | Always show the decimal point, even for whole numbers |
| `setw(n)` | Print the next value in a field at least `n` characters wide (right-justified) |

### Common Pattern

```cpp
cout << setprecision(2) << fixed << showpoint;
```

This is typically placed once, early in the program. It makes all subsequent float output show exactly 2 decimal places.

### Aligning Data in Columns with `setw`

```cpp
cout << setw(15) << "PRICE" << setw(12) << "QUANTITY" << endl;
cout << setw(15) << 9.50   << setw(12) << 4         << endl;
```

Output is **right-justified** within the specified width. `setw` only applies to the **very next** value printed — it resets after each use.

### Turning Off `fixed`

```cpp
cout.unsetf(ios::floatfield);
```

---

## 5. Expressions and Operator Precedence

An expression combines variables, constants, and literals with operators. C++ evaluates them using precedence rules:

| Priority | Operators | Direction |
|----------|-----------|-----------|
| 1 (highest) | `()` parentheses | Inner to outer |
| 2 | Unary `-` (negation) | Right to left |
| 3 | `*`, `/`, `%` | Left to right |
| 4 (lowest) | `+`, `-` | Left to right |

### Worked Example

```
(5 - 16 / 2 * 3 + (3 + 2 / 2) - 5)
= (5 - 16/2*3 + (3 + 1) - 5)
= (5 - 8*3 + 4 - 5)
= (5 - 24 + 4 - 5)
= -20
```

### Converting Algebra to C++

Algebraic notation must be made explicit:

| Algebra | C++ |
|---------|-----|
| \(2x + 3^4\) | `2 * x + pow(3, 4)` |
| \(\sqrt{a^2 + b^2}\) | `sqrt(pow(a,2) + pow(b,2))` |
| \(\frac{-b + \sqrt{b^2 - 4ac}}{2a}\) | `(-b + sqrt(pow(b,2) - 4*a*c)) / (2*a)` |

### Combined Assignment Operators

Shorthand for modifying a variable in place:

```cpp
x += 5;   // same as x = x + 5
x -= 3;   // same as x = x - 3
x *= 2;   // same as x = x * 2
x /= 4;   // same as x = x / 4
```

---

## 6. Math Library Functions

Require `#include <cmath>`.

| Function | Purpose | Example |
|----------|---------|---------|
| `pow(base, exp)` | Raise `base` to the power `exp` | `pow(2, 3)` = 8 |
| `sqrt(n)` | Square root of `n` | `sqrt(9)` = 3.0 |
| `abs(n)` | Absolute value | `abs(-7)` = 7 |
| `sin(n)`, `cos(n)`, `tan(n)` | Trig functions (radians) | `sin(3.14159)` ≈ 0 |
| `log(n)` | Natural logarithm | `log(2.718)` ≈ 1 |

---

## 7. Type Conversions

### Type Hierarchy (lowest to highest)

```
int → unsigned int → long → unsigned long → float → double → long double
```

### Implicit Coercion (Automatic)

When an operation mixes types, the **lower** type is **promoted** to the higher type:

```cpp
int x = 5;
double y = 2.5;
double result = x + y;  // x is promoted to 5.0
```

**Demotion** (higher to lower) causes **truncation**, not rounding:

```cpp
int count = 7.8;  // count is 7, not 8 — fractional part is chopped off
```

### The Integer Division Trap

When both operands are integers, the result is an integer (truncated):

```cpp
int hits = 123;
int atBat = 421;
float avg = hits / atBat;  // 0, not 0.292 — integer division!
```

Changing `avg` to `float` does **not** help; the division already happened as integer math.

### Explicit Type Casting (The Fix)

Force one operand to a floating-point type before division:

```cpp
float avg = static_cast<float>(hits) / atBat;  // 0.292162
```

The general form: `static_cast<TargetType>(value)`

Other uses:

```cpp
char ch = 'C';
cout << static_cast<int>(ch);  // prints 67 (ASCII value)
```

---

## 8. Strings

### Declaring Strings

```cpp
#include <string>

string firstName = "Dan";
string lastName = "Li";
```

### String Operations

| Operation | Syntax | Example |
|-----------|--------|---------|
| Length | `str.length()` | `"Texas".length()` → 5 |
| Concatenation | `str1 + str2` | `"Hi" + "Dan"` → `"HiDan"` |
| Input (no spaces) | `cin >> str` | Reads one word |
| Input (with spaces) | `getline(cin, str)` | Reads entire line |

### C-Strings vs. String Objects

| C-String | String Object |
|----------|---------------|
| `char name[12];` | `string name;` |
| Fixed size, null-terminated (`'\0'`) | Dynamic size, managed automatically |
| Read full line: `cin.getline(name, 12);` | Read full line: `getline(cin, name);` |

For this course, **string objects** are preferred.

---

## 9. Random Number Generation

### Modern C++ Approach (requires `<random>`)

```cpp
#include <random>

std::random_device engine;
std::uniform_int_distribution<int> dist(1, 6);  // range [1, 6]

cout << dist(engine) << endl;  // random number between 1 and 6
```

### Legacy Approach (requires `<cstdlib>`)

- `rand()` returns a pseudo-random int.
- `srand(seed)` seeds the generator (same seed = same sequence).

The modern `<random>` approach is more flexible and produces better randomness.

---

## 10. Pre-Lab Writing Answers (Quick Reference)

| # | Question | Answer |
|---|----------|--------|
| 1 | `(5 - 16/2*3 + (3 + 2/2) - 5)` | **-20** |
| 2 | \(2x + 3^4\) in C++ | `2 * x + pow(3, 4)` |
| 3 | Implicit conversion is also known as... | **type coercion** |
| 4 | Explicit type conversion is also known as... | **type casting** |
| 5 | Directive needed for `cin`/`cout` | `#include <iostream>` |
| 6 | Blank spaces / unseen control chars | **whitespace** |
| 7 | `<<` in `cout` is called the... | **insertion operator** |
| 8 | Header needed for formatted output | `#include <iomanip>` |
| 9 | `'\n'` is a special character that... | **creates a new line (escape sequence)** |

---

## 11. Lab Exercises Summary

| Lab | File | What You Practiced |
|-----|------|--------------------|
| 3.1 | `bill.cpp` | `cin` for input, `setprecision`/`fixed`/`showpoint`, `getline` for item name with spaces, computing a total bill |
| 3.2 | `tabledata.cpp` | `setw()` for column alignment, reading multiple values, formatted table output |
| 3.3 | `righttrig.cpp` | `sqrt()` and `pow()` from `<cmath>`, computing the Pythagorean theorem: `hyp = sqrt(pow(a,2) + pow(b,2))` |
| 3.4 | `batavg.cpp` | Integer division trap, `static_cast<float>()` to fix it — batting average goes from `0` to `0.292162` |
| 3.5 | `student_generated_code.cpp` | Original program: reads 3 grades, computes and displays the average to 2 decimal places |
| Auto 1 | `auto_graded_assignment_1.cpp` | Circle area with `pow()` and `PI` constant, formatted to 2 decimal places |
| Auto 3 | `auto_graded_assignment_3.cpp` | `getline` for multi-word string input, building a formatted event summary |

---

## 12. Common Mistakes to Avoid

- **Forgetting `#include`** — `<iostream>` for I/O, `<iomanip>` for formatting, `<cmath>` for math, `<string>` for string objects.
- **Using `=` instead of `==`** — `=` assigns, `==` compares (more relevant in Unit 2, but the habit starts here).
- **Integer division** — `10 / 50` gives `0`, not `0.2`. Use `static_cast` or make one operand a float (e.g., `/ 3.0` instead of `/ 3`).
- **Mixing `cin >>` and `getline`** — always call `cin.ignore()` after `cin >>` if `getline` follows.
- **Uninitialized variables** — always give variables a value before reading them.
