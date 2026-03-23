# Unit 4: Functions in C++

## Table of Contents

1. [What is a Function?](#1-what-is-a-function)
2. [Void Functions (Procedures)](#2-void-functions-procedures)
3. [Function Prototypes](#3-function-prototypes)
4. [Parameters vs. Arguments](#4-parameters-vs-arguments)
5. [Pass by Value](#5-pass-by-value)
6. [Pass by Reference](#6-pass-by-reference)
7. [Value-Returning Functions](#7-value-returning-functions)
8. [Scope](#8-scope)
9. [Static Local Variables](#9-static-local-variables)
10. [Default Arguments](#10-default-arguments)
11. [Function Overloading](#11-function-overloading)
12. [Stubs and Drivers](#12-stubs-and-drivers)
13. [The `exit()` Function](#13-the-exit-function)
14. [Key Takeaways](#14-key-takeaways)

---

## 1. What is a Function?

A function is a self-contained block of code that performs a specific task. Every C++ program has at least one function: `main()`.

**Anatomy of a function:**

```
ReturnType FunctionName(ParameterList) {
    // Function body
}
```

| Component        | Example         | Description                          |
| ---------------- | --------------- | ------------------------------------ |
| Return type      | `int`           | The data type of the value returned  |
| Function name    | `main`          | Identifier used to call the function |
| Parameter list   | `()`            | Inputs the function accepts          |
| Function body    | `{ ... }`       | The statements that execute          |
| Function header  | `int main()`    | The first line (return type + name + params) |

---

## 2. Void Functions (Procedures)

If a function **does not return a value**, its return type is `void`. These are sometimes called **procedures** in other languages.

```cpp
void printDescription() {
    cout << "This program takes two numbers (pay rate and hours)" << endl;
    cout << "and outputs gross pay." << endl;
}
```

- No `return` statement is required (though `return;` with no value is allowed).
- Called as a standalone statement: `printDescription();`

---

## 3. Function Prototypes

A **prototype** is a declaration that tells the compiler a function exists before its full definition appears. It acts as a *contract* or *promise* that the function will be defined later.

```cpp
void printDescription();            // no parameters
void calPaycheck(float, int);      // two pass-by-value parameters
void calPaycheck(float, int, float &); // includes a reference parameter
```

**Rules:**

- A prototype **must** list data types for all parameters.
- Parameter **names** in the prototype are optional (but allowed).
- The program must include either a prototype or the full function definition **before** any call to that function — otherwise you get a compiler error.
- Most C++ programs place prototypes near the top so `main()` can be the first function.

---

## 4. Parameters vs. Arguments

These two terms are related but distinct:

| Term | Also Called | Where It Lives | Example |
|------|-------------|----------------|---------|
| **Argument** | Actual parameter | In the **function call** | `calPaycheck(payRate, hours);` |
| **Parameter** | Formal parameter | In the **function heading** | `void calPaycheck(float rate, int time)` |

**Comparison across all three locations:**

```
Prototype:          void calPaycheck(float, int);
Function heading:   void calPaycheck(float rate, int time)
Function call:      calPaycheck(payRate, hours);
```

- The **heading** must have both the data type and the name for each parameter.
- The **prototype** must have the data type; names are optional.
- The **call** must have argument names only — **no data types**.

---

## 5. Pass by Value

When an argument is passed **by value**, a *copy* of the actual parameter's value is placed into the formal parameter. Changes to the formal parameter inside the function **do not** affect the original variable.

```cpp
void calPaycheck(float rate, int time) {
    float gross = rate * time;       // rate and time are local copies
    cout << "The pay is " << gross << endl;
}

// In main:
calPaycheck(payRate, hours);  // payRate and hours are unchanged after the call
```

Use pass by value when the function only needs to **read** the data, not modify the caller's variable.

---

## 6. Pass by Reference

When an argument is passed **by reference** (using `&`), the formal parameter and the actual parameter refer to the **same memory location**. Changes inside the function **do** affect the original variable.

```cpp
void calPaycheck(float rate, int time, float &gross) {
    gross = rate * time;  // modifies the caller's variable directly
}

// In main:
float grossPay;
calPaycheck(payRate, hours, grossPay);
// grossPay now holds the computed value
```

**Declaring reference parameters in the prototype:**

In the prototype, the `&` goes **after the data type** — just like in the function heading. Since parameter names are optional in prototypes, you'll often see just the type followed by `&`:

```
Prototype (no names):    void calPaycheck(float, int, float &);
Prototype (with names):  void calPaycheck(float rate, int time, float &gross);
Function heading:        void calPaycheck(float rate, int time, float &gross)
Function call:           calPaycheck(payRate, hours, grossPay);
```

Notice the `&` **never** appears in the function call — only in the prototype and the heading. The caller doesn't need to do anything special; the compiler already knows from the prototype that the third parameter is a reference.

**When to use pass by reference:**

- When the function needs to **send data back** to the caller through a parameter.
- When a void function needs to modify multiple values (since it can't use `return` for more than one value).

**Example: computing both gross and net pay**

```cpp
void computePaycheck(float rate, int time, float &gross, float &net) {
    gross = rate * time;
    net = gross - (gross * 0.15);
}
```

Here `rate` and `time` are pass by value (input only), while `gross` and `net` are pass by reference (output).

---

## 7. Value-Returning Functions

Instead of `void`, specify the return type. The function uses a `return` statement to send a single value back to the caller.

```cpp
float convertToYen(float dollars) {
    float yen = dollars * 124.35;
    return yen;
}

// Called as part of an expression:
yen = convertToYen(dollars);
```

**Guidelines:**

- Every function with a data type (not `void`) in the heading **must** have a `return` statement.
- The call is typically part of an assignment or expression — not a standalone statement.
- Value-returning functions should use **pass by value only** for all parameters. Nothing in C++ prevents pass by reference here, but it should be avoided by convention.

---

## 8. Scope

**Scope** refers to the region of a program where a variable is "active" (accessible).

### Global Scope

Identifiers declared outside all functions. Accessible from any function in the file.

```cpp
const double PI = 3.14;      // global constant
const double RATE = 0.25;    // global constant
```

### Local Scope

Identifiers declared inside a block `{ }`. They are active only within that block.

```cpp
int main() {
    float radius = 12;          // local to main

    {
        float area;             // local to this inner block
        findArea(radius, area); // radius (12) is accessible here
    }
    // area is NOT accessible here

    {
        float radius = 10;     // NEW local variable — shadows outer radius
        float circumference;
        findCircumference(radius, circumference);  // uses radius = 10
    }
    // radius is back to 12 here
}
```

### Name Precedence

When two or more variables share the same name, the **most recently defined** (innermost scope) variable takes precedence.

### Lifetime vs. Scope

- **Scope**: where a variable is accessible.
- **Lifetime**: how long a variable has storage allocated. They are similar but not identical (see static variables below).

### Scope Summary Table

| Scope Level | What's Active |
|---|---|
| Global | `PI`, `RATE`, all function names |
| `main` outer | `radius` (12), plus all globals |
| `main` inner block 1 | `area`, `radius` (12), plus all globals |
| `main` inner block 2 | `radius` (10, shadows outer), `circumference`, plus globals |
| `findArea` function | `rad`, `answer`, plus all globals |
| `findCircumference` function | `length`, `distance`, plus all globals |

> In C++, **all functions have global scope** — they can be called from anywhere (assuming a prototype or prior definition).

---

## 9. Static Local Variables

Normally, local variables are destroyed when their function returns. A **static** local variable retains its value between function calls.

```cpp
void normalizeMoney(float &dollars, int cents) {
    float total = 0;              // reset to 0 every call
    static float sum = 0.0;      // initialized ONCE, persists across calls

    dollars = static_cast<float>(cents) / 100;
    total = total + dollars;
    sum = sum + dollars;

    cout << "Running total (static): $" << sum << endl;
    cout << "Local total (non-static): $" << total << endl;
}
```

**Calling this 3 times with 95, 193, and 150 cents:**

| Call | `total` (local) | `sum` (static) |
|------|------------------|----------------|
| 1    | 0.95             | 0.95           |
| 2    | 1.93             | 2.88           |
| 3    | 1.50             | 4.38           |

- `total` resets to 0 each call.
- `sum` accumulates across calls.
- If no initializer is given, static variables are automatically initialized to 0.

---

## 10. Default Arguments

You can assign **default values** to parameters in the prototype. If the caller omits those arguments, the defaults are used.

```cpp
void calNetPay(float &net, int hours = 40, float rate = 6.00);  // prototype
```

```cpp
calNetPay(pay);               // uses hours=40, rate=6.00
calNetPay(pay, 20);           // uses hours=20, rate=6.00
calNetPay(pay, 20, 8.50);    // uses hours=20, rate=8.50
```

**Rules:**

- Default values are usually specified in the **prototype** (not the function definition).
- If a parameter is omitted, **all parameters after it** must also be omitted.
- Pass-by-reference parameters should be placed **first** (since they must always be provided).
- Default values are generally not given for pass-by-reference parameters.

---

## 11. Function Overloading

Two or more functions can share the **same name** as long as their parameter lists differ in **quantity or data type**.

```cpp
int square(int num)       { return num * num; }
double square(double num) { return num * num; }
```

The compiler determines which version to call based on the argument types:

```cpp
square(5);       // calls int version  → 25
square(2.5);     // calls double version → 6.25
```

### Real-World Example: Currency Converter

```cpp
void convertMulti(float dollars, float &euros, float &pesos);
void convertMulti(float dollars, float &euros, float &pesos, float &yen);
```

Both functions are named `convertMulti`, but one converts to 2 currencies and the other to 3. The compiler picks the right one based on how many arguments you pass.

### Another Example: Ordering Values

```cpp
void order(char &input1, char &input2);
void order(int &input1, int &input2);
void order(double &input1, double &input2);
```

All three `order` functions swap two values so the smaller comes first, but each works on a different data type.

---

## 12. Stubs and Drivers

These are testing techniques used during incremental development.

### Stubs

A **stub** is a dummy function that stands in for a function not yet written. It confirms the function was called correctly without implementing the real logic.

```cpp
int findSqrRoot(int x) {
    cout << "findSqrRoot was called with " << x << " as its argument" << endl;
    return 0;  // placeholder
}
```

Use stubs to test that `main()` and the function calls work correctly before writing the actual function body.

### Drivers

A **driver** is a small `main()` whose sole purpose is to test a specific function.

```cpp
int main() {
    cout << "Calling findSqrRoot with 4" << endl;
    cout << "The result is " << findSqrRoot(4) << endl;
    return 0;
}
```

Use drivers to verify that a function produces correct output, independent of the rest of the program.

---

## 13. The `exit()` Function

Terminates program execution immediately. Requires `#include <cstdlib>`.

```cpp
#include <cstdlib>

exit(0);               // normal termination
exit(EXIT_SUCCESS);    // same as exit(0)
exit(EXIT_FAILURE);    // indicates abnormal termination
```

- Can be called from **any** function, not just `main()`.
- Usually reserved for **abnormal termination** (unrecoverable errors).
- The integer argument is passed to the operating system as a status code.

---

## 14. Key Takeaways

| Concept | Quick Summary |
|---|---|
| `void` functions | Don't return a value; called as standalone statements |
| Prototypes | Declare a function before its definition; must include parameter data types |
| Pass by value | Copies the value; original is safe from modification |
| Pass by reference (`&`) | Shares the memory location; changes affect the original |
| Value-returning functions | Use `return` to send back one value; call is part of an expression |
| Scope | Global = everywhere; Local = within `{ }` block only |
| Name precedence | Innermost variable with a given name wins |
| Static locals | Persist across function calls; initialized only once |
| Default arguments | Provide fallback values in the prototype; omitted args use defaults |
| Overloading | Same function name, different parameter lists |
| Stubs | Placeholder functions for testing call structure |
| Drivers | Minimal `main()` programs for testing a single function |
| `exit()` | Immediately terminates the program from any function |

### Pre-Lab Definitions (Lab 6.1)

1. `void` precedes every function that does not return a value.
2. **Pass by value** copies the actual parameter into the formal parameter.
3. **Actual parameters** (arguments) are found in the function call.
4. A prototype must give the **data type** of its parameters; names are optional.
5. `&` after a data type indicates **pass by reference**.
6. Non-returning functions are called **procedures** in other languages.
7. **Pass by reference** passes the *location*, not just a copy of the value.
8. A call must have argument **names** only — no data types.
9. **Scope** = the region where a variable is active.
10. **Names and data types** of formal parameters are found in the function heading.

### Pre-Lab Definitions (Lab 6.2)

1. **Static variables** retain their value across multiple function calls.
2. In C++, all functions have **global scope**.
3. **Default arguments** are usually defined in the prototype.
4. A value-returning function should **never** use pass by reference.
5. Every non-void function **must** have a `return` statement.
6. A **driver** tests a function by calling it.
7. A **block** is defined by `{ }`.
8. A **stub** is a dummy function indicating the function was called properly.
9. Default values are generally **not** given for pass-by-reference parameters.
10. **Overloaded functions** share a name but have different parameter lists.
