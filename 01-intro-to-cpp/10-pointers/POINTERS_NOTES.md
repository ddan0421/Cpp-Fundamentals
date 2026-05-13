# C++ Pointers — Comprehensive Notes

These notes consolidate everything from this unit's source files (`01-pointer-variables.cpp`, `02-arrays-and-pointers.cpp`, `03-dynamic-variables.cpp`), the `Unit10_Assignment_Dan/` lab files, the auto-graded assignment, the textbook chapter (`SOW_C++_CSO_Chapter_09_10e.pdf` — Chapter 9), and the pre-lab reading from `Unit10-Lab09_Instructions.pdf`.

---

## Table of Contents

1. [What Is a Pointer?](#1-what-is-a-pointer)
2. [The `&` (Address-Of) Operator](#2-the--address-of-operator)
3. [The `*` (Indirection / Dereference) Operator](#3-the--indirection--dereference-operator)
4. [Defining and Initializing Pointers](#4-defining-and-initializing-pointers)
5. [The Relationship Between Arrays and Pointers](#5-the-relationship-between-arrays-and-pointers)
6. [Pointer Arithmetic](#6-pointer-arithmetic)
7. [Comparing Pointers](#7-comparing-pointers)
8. [Pointers as Function Parameters](#8-pointers-as-function-parameters)
9. [`const` and Pointers](#9-const-and-pointers)
10. [Dynamic Memory Allocation: `new` and `delete`](#10-dynamic-memory-allocation-new-and-delete)
11. [Returning Pointers from Functions](#11-returning-pointers-from-functions)
12. [Smart Pointers — Avoiding Memory Leaks](#12-smart-pointers--avoiding-memory-leaks)
13. [Quick Reference Cheat Sheet](#13-quick-reference-cheat-sheet)
14. [Pre-Lab Q&A Recap](#14-pre-lab-qa-recap)
15. [Quiz Concept Recap](#15-quiz-concept-recap)

---

## 1. What Is a Pointer?

- Every variable lives at a **unique memory address**.
- A **pointer** is a variable whose value *is* an address — it "points to" another piece of data.
- Pointers are more *low-level* than arrays or reference variables: **you** are responsible for getting the address, storing it correctly, and (if dynamic) freeing it.

```cpp
int sum;                    // sum holds an integer value
int *sumPtr = nullptr;      // sumPtr holds an *address* of an int
```

`sumPtr` is **not** an int. It is "a variable that can hold the address of an int."

### Things that already act like pointers
You've already touched pointer-like behavior:

- **Arrays passed to functions** — the array name decays to a pointer to its first element.
- **Reference parameters (`&`)** — the compiler stores the *address* of the argument and auto-dereferences it.

Pointers make this explicit instead of implicit.

---

## 2. The `&` (Address-Of) Operator

`&` has two distinct uses:

### Use 1: Reference parameter in a function header / prototype
The `&` between the type and parameter name says "pass by reference" — the address of the argument is sent to the function and the compiler auto-dereferences it.

```cpp
void swap(int &first, int &second) {
    int temp = first;
    first   = second;
    second  = temp;
}
```

### Use 2: Get the address of a variable
When `&` is placed *in front of a variable name in an expression*, it yields that variable's address.

```cpp
cout << sum;   // prints the value stored in sum
cout << &sum;  // prints the address (e.g. 0x006AF0F4)
```

This is how we feed an address into a pointer:

```cpp
int *ptr = &sum;
```

---

## 3. The `*` (Indirection / Dereference) Operator

`*` also has two uses:

### Use 1: Define a pointer variable
```cpp
int *ptr = nullptr;   // "ptr can hold the address of an int"
```
Spacing doesn't matter: `int* ptr;`, `int *ptr;`, and `int * ptr;` all mean the same.

### Use 2: Dereference a pointer (the indirection operator)
When `*` is placed in front of an *already defined* pointer in an expression, it accesses the **value at the address** the pointer holds.

```cpp
int x = 25;
int *intptr = &x;
cout << *intptr;   // prints 25
*intptr = 30;      // changes x to 30 through the pointer
```

### Worked example — putting `*` and `&` together

From `01-pointer-variables.cpp`:

```1:124:01-pointer-variables.cpp
int main() {
  int one = 10;
  int *ptr1 = nullptr; // ptr1 is a pointer variable that points to an int
  ptr1 = &one;         // &one indicates that the address, not the
                       // contents, of one is being assigned to ptr1.
  cout << "The value of one is " << one << endl << endl;
  cout << "The value of &one is " << &one << endl << endl;
  cout << "The value of ptr1 is " << ptr1 << endl << endl;
  cout << "The value of *ptr1 is " << *ptr1 << endl << endl;
  return 0;
}
```

If `&one` is `0x006AF0F4`, the output is:

```
The value of one is 10
The value of &one is 006AF0F4
The value of ptr1 is 006AF0F4
The value of *ptr1 is 10
```

**Mnemonic:** `*` and `&` are *opposites*. `&x` gives you the address; `*ptr` gives you back the value at that address.

---

## 4. Defining and Initializing Pointers

```cpp
int *p1 = nullptr;          // null pointer (recommended starting state)
int  num = 42;
int *p2 = &num;             // initialize at definition time
int  vals[3], *vp = vals;   // pointer to an array
```

Rules:

- A pointer's type must match what it points to. `int *p = &someDouble;` does **not** compile.
- `nullptr` (C++11) replaces the older `0` / `NULL`. It represents "points to nothing."
- You can test validity with `if (!ptr) { ... }` or `if (ptr == nullptr) { ... }`.

---

## 5. The Relationship Between Arrays and Pointers

> An **array name is (essentially) a pointer to its first element**.

```cpp
int vals[] = {4, 7, 11};

cout << vals;      // address of vals[0]   e.g. 0x4a00
cout << *vals;     // 4   (dereference -> first element)
cout << vals[0];   // 4   (same thing)
```

A pointer can be used like an array name:

```cpp
int *valptr = vals;
cout << valptr[1]; // 7
```

### The four equivalent ways to access an array element

| Method | Example |
|---|---|
| array name + `[]` | `vals[2] = 17;` |
| pointer + `[]` | `valptr[2] = 17;` |
| array name + arithmetic | `*(vals + 2) = 17;` |
| pointer + arithmetic | `*(valptr + 2) = 17;` |

The fundamental identity:

```
vals[i]  ≡  *(vals + i)
```

`grades[i]` is just **pointer arithmetic + dereference** under the hood. C++ moves `i * sizeof(element)` bytes forward from the base address, then dereferences.

> ⚠ **No bounds checking** is performed — neither with `[]` nor with pointer arithmetic.

### `sizeof` gotcha — array decay

Arrays are not pointers, but in most expressions they **decay** into pointers to their first element.

```cpp
int arr[10];
sizeof(arr);    // 40   (10 ints * 4 bytes)  -- still a real array here

void func(int arr[]) {
    cout << sizeof(arr);   // size of a pointer (e.g. 8), NOT 40
}
```

Inside a parameter list, `int arr[]` is silently rewritten to `int *arr`.

### What you cannot do with an array name

The array name is a *pointer constant* — it always points to the start of the array.

```cpp
int grades[5];
grades = grades + 1;   // ❌ illegal — can't reassign an array name

int *p = grades;
p = p + 1;             // ✅ fine — moves p forward by one int
```

---

## 6. Pointer Arithmetic

Pointer arithmetic is **scaled by the size of the pointed-to type**. `p + 1` advances by `sizeof(*p)` bytes, not 1 byte.

```cpp
int vals[] = {4, 7, 11};
int *valptr = vals;
```

| Operation | Example | Result |
|---|---|---|
| `++`, `--` | `valptr++;` | now points at `7` |
| `+`, `-` (pointer + int) | `*(valptr + 2)` | `11` |
| `+=`, `-=` | `valptr += 2;` | points at `11` |
| pointer − pointer | `valptr - vals` | distance in elements |

From `02-arrays-and-pointers.cpp`:

```88:113:02-arrays-and-pointers.cpp
int main() {
  int grades[] = {90, 88, 76, 54, 34};

  cout << "The first grade is " << *grades << endl;
  cout << "The second grade is " << *(grades + 1) << endl;
  cout << "The third grade is " << *(grades + 2) << endl;
  cout << "The fourth grade is " << *(grades + 3) << endl;
  cout << "The fifth grade is " << *(grades + 4) << endl;
  return 0;
}
```

---

## 7. Comparing Pointers

Relational operators (`<`, `>`, `==`, `!=`, etc.) compare the *addresses* the pointers hold — **not** the values they point to.

```cpp
if (ptr1 == ptr2)      // do they point to the same location?
if (*ptr1 == *ptr2)    // do the pointed-to values match?
```

These are very different questions. Mixing them up is a classic bug.

---

## 8. Pointers as Function Parameters

A pointer parameter behaves like a reference parameter — the function can modify the caller's variable — but the syntax is more explicit:

1. `*` on the parameter in the prototype/header.
2. `*` in the body to dereference it.
3. Pass the **address** at the call site with `&`.

```cpp
void getNum(int *ptr) {   // (1) prototype
    cin >> *ptr;          // (2) dereference
}

int num;
getNum(&num);             // (3) pass address
```

### Swap with pointers (vs. references)

```cpp
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int num1 = 2, num2 = -3;
swap(&num1, &num2);
```

### Passing an array
Because an array name *is* a pointer to its first element, these two prototypes are equivalent:

```cpp
void sortIt(float *grades, int numOfGrades);
void sortIt(float grades[], int numOfGrades);   // identical to compiler
```

You also pass the size separately because the function cannot recover it from a decayed pointer.

From `Unit10_Assignment_Dan/student_generated_code.cpp`:

```56:66:Unit10_Assignment_Dan/student_generated_code.cpp
void sort(int *score, int num_scores) {
  for (int i = num_scores - 1; i > 0; i--) {
    for (int j = 0; j < i; j++) {
      if (score[j] > score[j + 1]) {
        int temp = score[j];
        score[j] = score[j + 1];
        score[j + 1] = temp;
      }
    }
  }
}
```

---

## 9. `const` and Pointers

The position of `const` matters. Read declarations *right-to-left*.

### (a) Pointer to a `const` — `const T *p` or `T const *p`
The **value** can't be changed through the pointer, but the pointer itself can be redirected.

```cpp
int a = 10, b = 20;
const int *p = &a;
cout << *p;     // ✅ 10
p = &b;         // ✅ retarget — fine
*p = 30;        // ❌ compile error — can't modify *p
```

Use this when a function should *read* but not modify caller data:

```cpp
void displayPayRates(const double *rates, int size) {
    for (int i = 0; i < size; ++i)
        cout << *(rates + i) << endl;
}
```

### (b) `const` Pointer — `T * const p`
The **address** can't change, but the value at that address can.

```cpp
int a = 10, b = 20;
int * const p = &a;   // must be initialized at declaration!
*p = 15;              // ✅ a is now 15
p = &b;               // ❌ compile error — can't retarget
```

### (c) `const` Pointer to `const` — `const T * const p`
Neither the address nor the value can change.

```cpp
int value = 22;
const int * const ptr = &value;   // can't retarget; can't modify *ptr
```

---

## 10. Dynamic Memory Allocation: `new` and `delete`

Static arrays force you to guess the maximum size up front. **Dynamic allocation** lets you allocate memory at *runtime*, sized exactly to what you need.

### Lifetime
Normal variables have lifetimes tied to their scope. Dynamically allocated objects exist on the **heap** until you explicitly destroy them.

### Allocating
```cpp
int    *p   = new int;          // single int
double *dp  = new double;       // single double
int    *arr = new int[n];       // array of n ints (n known at runtime)
```

`new` returns the address of the newly allocated memory.

### Deallocating
```cpp
delete p;        // for a single object
delete[] arr;    // for an array — note the []
```

> ⚠ Use `delete[]` for arrays and plain `delete` for single objects. Mismatching is undefined behavior.

> ⚠ Only call `delete` on memory that came from `new`.

> ✅ `delete` on `nullptr` is a safe no-op. A common pattern:
> ```cpp
> delete[] grades;
> grades = nullptr;
> ```

### Single-variable example

From `03-dynamic-variables.cpp`:

```cpp
int *one = nullptr;
int *two = nullptr;
int  result;

one = new int;
two = new int;

*one = 10;
*two = 20;
result = *one + *two;       // 30

delete one;
delete two;
```

### Dynamic array example

From `03-dynamic-variables.cpp`:

```75:123:03-dynamic-variables.cpp
int main() {
  float *grades = nullptr;
  float total = 0;
  float average;
  int numOfGrades;
  int count;

  cout << fixed << showpoint << setprecision(2);

  cout << "How many grades will be processed " << endl;
  cin >> numOfGrades;

  while (numOfGrades <= 0) {
    cout << "There must be at least one grade. Please reenter.\n";
    cout << "How many grades will be processed " << endl;
    cin >> numOfGrades;
  }
  grades = new float[numOfGrades];
  if (grades == nullptr) {
    cout << "Error allocating memory!\n";
    return 1;
  }
  cout << "Enter the grades below\n";

  for (count = 0; count < numOfGrades; count++) {
    cout << "Grade " << (count + 1) << ": " << endl;
    cin >> grades[count];
    total = total + grades[count];
  }
  average = total / numOfGrades;
  cout << "Average Grade is " << average << "%" << endl;
  sortIt(grades, numOfGrades);
  displayGrades(grades, numOfGrades);
  delete[] grades;
  return 0;
}
```

### Reading/writing a dynamic array *without* `[]`

From `Unit10_Assignment_Dan/dynamic.cpp` — proves that `name[pos]` is just sugar for `*(name + pos)`:

```40:52:Unit10_Assignment_Dan/dynamic.cpp
  name = new char[MAXNAME];
  ...
  for (pos = 0; pos < MAXNAME; pos++)
    cin >> *(name + pos);
  ...
  for (pos = 0; pos < MAXNAME; pos++)
    cout << *(name + pos);
```

### Memory leaks
A **memory leak** happens when you allocate with `new` and never `delete`. The memory stays "in use" with no way to reach it. In long-running programs this eats RAM until the process is killed. Always pair every `new` with a `delete` (or use a smart pointer — see §12).

---

## 11. Returning Pointers from Functions

A function can return a pointer:

```cpp
int* newNum();
```

### The Golden Rule
A function should **only** return a pointer to:

1. Memory that was **passed in** as an argument, or
2. Memory that was **dynamically allocated** inside the function (with `new`).

**Never** return a pointer to a local variable — that variable is destroyed when the function returns, leaving you with a dangling pointer to garbage.

```cpp
int* bad() {
    int x = 5;
    return &x;     // ❌ x dies when bad() returns
}

int* good() {
    int *x = new int(5);
    return x;      // ✅ heap memory survives; caller must delete it
}
```

### Worked example — `expandArray` from the auto-graded assignment

> Create a new int array twice the size of the input, copy the contents, zero the unused half, and return a pointer to it. Return `nullptr` if input size ≤ 0.

```17:35:auto_graded_assignment_1.cpp
int *expandArray(int[], int);

int *expandArray(int inputArray[], int inputSize) {
  if (inputSize <= 0)
    return nullptr;

  int *newArray = nullptr;
  int newSize = inputSize * 2;
  newArray = new int[newSize];

  for (int i = 0; i < newSize; i++) {
    if (i < inputSize)
      newArray[i] = inputArray[i];
    else
      newArray[i] = 0;
  }

  return newArray;
}
```

The caller now owns that memory and is responsible for `delete[]`-ing it.

---

## 12. Smart Pointers — Avoiding Memory Leaks

C++11 added **smart pointers**, which manage the lifetime of dynamically allocated memory automatically. When the smart pointer goes out of scope, it deletes the memory for you. **You don't call `delete`.** This is the modern, recommended way to use the heap.

```cpp
#include <memory>
```

### Three flavors

| Smart pointer | Purpose |
|---|---|
| `unique_ptr<T>` | Sole owner. Cannot be copied, only moved. The default choice. |
| `shared_ptr<T>` | Shared ownership via reference counting. Memory freed when the last `shared_ptr` is destroyed. |
| `weak_ptr<T>`   | Non-owning observer of a `shared_ptr`. Used to break reference cycles. |

This course focuses on `unique_ptr`.

### `unique_ptr` basics

```cpp
#include <memory>
#include <iostream>
using namespace std;

int main() {
    unique_ptr<int> ptr(new int);   // allocates an int on the heap
    *ptr = 100;
    cout << *ptr << endl;           // 100
    return 0;
    // No delete needed. When ptr goes out of scope here,
    // its destructor runs delete on the underlying memory.
}
```

Decoding `unique_ptr<int> ptr( new int );`:

- `<int>` — the smart pointer points to an `int`.
- `ptr` — the variable name.
- `new int` — allocates the heap memory.
- The address is stored inside `ptr`. When `ptr` dies, the heap memory dies with it.

### Why smart pointers solve memory leaks
With raw `new` / `delete`:

```cpp
int *p = new int(42);
if (something) return;     // ❌ leaked! never delete'd
delete p;
```

With `unique_ptr`:

```cpp
unique_ptr<int> p(new int(42));
if (something) return;     // ✅ destructor of p runs -> automatic delete
```

Even on exceptions, the destructor still runs. This is called **RAII** (Resource Acquisition Is Initialization) and it's the foundational idiom of modern C++.

### Preferred: `make_unique` (C++14+)

```cpp
auto p = std::make_unique<int>(42);          // single int
auto a = std::make_unique<int[]>(n);         // dynamic array of n ints
```

`make_unique` is exception-safe and avoids the bare `new`. Many codebases ban raw `new` entirely in favor of these factories.

### Quick rules of thumb

- Default to `unique_ptr` for owning heap memory.
- Use `shared_ptr` only when ownership is genuinely shared.
- Never mix raw `delete` with smart pointers on the same object.
- Smart pointers replace `new`/`delete`, **not** every pointer — you can still use raw pointers as non-owning "observers."

---

## 13. Quick Reference Cheat Sheet

```cpp
// --- declaration & address ---
int  x = 42;
int *p = &x;            // p holds address of x
cout << p;              // address
cout << *p;             // 42  (dereference)

// --- null pointer ---
int *q = nullptr;
if (!q) { /* q is null */ }

// --- arrays decay ---
int a[5];
int *r = a;             // r == &a[0]
a[i] == *(a + i);       // identity

// --- pointer arithmetic ---
r++;        // advances by sizeof(int)
r += 2;
ptrdiff_t d = r - a;    // element distance

// --- function parameter (out-parameter) ---
void fill(int *out) { *out = 99; }
int v; fill(&v);

// --- const positions ---
const int *cp;          // can't modify *cp
int * const cp2 = &x;   // can't retarget
const int * const cp3 = &x;  // both locked

// --- new / delete ---
int    *one = new int;          delete one;
double *arr = new double[n];    delete[] arr;
arr = nullptr;                  // good hygiene

// --- returning a pointer ---
int* makeArr(int n) { return new int[n]; }   // caller deletes[]

// --- smart pointer ---
#include <memory>
auto sp = std::make_unique<int>(7);          // auto-deleted
```

---

## 14. Pre-Lab Q&A Recap

Direct answers to the pre-lab fill-in-the-blanks (from `Unit10_Assignment_Dan/pre_lab_writing.txt`):

1. The **`*`** symbol is the dereferencing operator.
2. The **`&`** symbol means "address of."
3. The name of an array, without any brackets, acts as a **pointer** to the starting address of the array.
4. An operator that allocates a dynamic variable is **`new`**.
5. An operator that deallocates a dynamic variable is **`delete`**.
6. Parameters that are passed by **reference** are similar to a pointer variable in that they can contain the address of another variable.

Given:
```cpp
float *pointer;
float pay = 3.75;
pointer = &pay;
```

7. `cout << pointer;` → **an address**
8. `cout << *pointer;` → **3.75**
9. `cout << &pay;` → **an address**
10. `cout << pay;` → **3.75**

---

## 15. Quiz Concept Recap

A distilled review of the key concepts tested on the Unit 10 quiz. Each item lists the concept, the correct answer, and the *why* behind it.

### True/False fundamentals

1. **No bounds checking.** C++ does **not** perform array bounds checking, so a pointer can legally hold the address of an element outside an array — the compiler will not stop you, but you'll get undefined behavior at runtime. (*True*)
2. **Subscript ↔ pointer arithmetic.** `myValues[index]` and `*(myValues + index)` are exactly the same expression. The subscript operator is just sugar for "add `index * sizeof(element)` to the base address, then dereference." (*True*)
3. **Smart pointers manage memory for you.** A smart pointer dynamically allocates memory and automatically deletes it when the smart pointer goes out of scope — you do not call `delete` yourself. (*True*)
4. **`weak_ptr` does NOT share ownership.** `weak_ptr` is a *non-owning* observer of a `shared_ptr`. Only `shared_ptr` shares ownership via reference counting. (*False*)
5. **`unique_ptr` is the sole owner.** Exactly one `unique_ptr` owns its memory at a time; it cannot be copied, only moved. (*True*)

### Operators and terminology

6. **Address-of operator.** The **ampersand (`&`)**, also called the address operator, returns the memory address of a variable.
7. **Indirect manipulation.** With pointer variables you can **indirectly** manipulate data stored in other variables — you reach the variable through its address.
8. **Dereferencing.** When you work with a *dereferenced* pointer (`*ptr`), you are working with **the actual value of the variable whose address is stored in the pointer** — not a copy.

### Functions returning pointers

9. **Safe return rule.** A function may return a pointer, but the programmer must ensure the pointer **still points to a valid object after the function ends**. That means: return a pointer to memory that was passed in *or* dynamically allocated with `new` — **never** to a local variable.

### Declarations

10. **`double *num2;`** — this **declares a pointer variable named `num2`** that can point to a `double`. It does *not* initialize it (the pointer holds garbage until you assign it).
11. **Spotting invalid pointer code.** Of these, all are invalid:
    - `int ptr = int *num1;` — syntax garbage.
    - `float num1 = &ptr2;` — assigning an address to a `float`.
    - `int ptr = &num1;` — assigning an address to a non-pointer `int`.

    The correct form would be `int *ptr = &num1;` (note the `*`).

### `new` / `delete`

12. **Deleting a dynamic array.** Use **`delete [] array;`** — the `[]` is required so the runtime calls the destructor for each element and frees the whole block.
13. **Printing an address.** **`cout << &numb;`** — the address-of operator yields the variable's address. (`cout << numb;` prints the value; `cout << *numb;` only works if `numb` is itself a pointer.)

### Smart pointers as leak prevention

14. **Definition.** A **smart pointer** automatically deletes a chunk of dynamically allocated memory when that memory is no longer being used, helping prevent memory leaks.
17. **Declaring a `unique_ptr`.** **`unique_ptr<int> uniq( new int );`** — angle brackets specify the pointed-to type, and `new int` supplies the heap memory. (Watch for typos like `neww` or missing `<int>` in distractors.)

### Pointer arithmetic / array equivalence

15. **Output of the loop.**
    ```cpp
    int *numbers = new int[5];
    for (int i = 0; i <= 4; i++)
        *(numbers + i) = i;
    cout << numbers[2] << endl;
    ```
    Prints **`2`**. The loop assigns `numbers[i] = i`, so element 2 is `2`.
16. **`ptr++` on an `int*`.** Given `int *ptr = numbers; ptr++;`, `ptr` now holds **the address of `numbers[1]`**. `++` on a pointer advances by `sizeof(*ptr)` bytes — one full element, not one byte.

### "Select all that apply"

18. **Things usable as pointers:** **array names**. Keywords and numeric constants cannot be used as pointers — only an array name (which decays to the address of its first element) acts like one.
19. **Valid pointer arithmetic operations:** **addition** and **subtraction**. You can `++`, `--`, `+= n`, `-= n`, or subtract two pointers. **Multiplication, division, and modulus are not allowed on pointers.**
20. **Equivalent pointer declarations:** **`int *ptr = nullptr;`** and **`int* ptr = nullptr;`** — whitespace around `*` is irrelevant. `int ptr = nullptr;`, `*int ptr = nullptr;`, and `int ptr* = nullptr;` are all invalid.

### Common quiz traps to remember

- `ptr++` moves by **one element**, not one byte.
- `cout << ptr;` prints an **address**; `cout << *ptr;` prints the **value**.
- `delete` vs `delete[]` — match it to how you allocated.
- `weak_ptr` ≠ shared ownership — it just *observes* a `shared_ptr`.
- Pointer math allows only `+` and `-` (and `++` / `--`). No `*`, `/`, `%`.
- The `*` in `int *p;` is part of the *declaration*; the `*` in `*p = 5;` is the *dereference operator*. Same symbol, different jobs.

---

## Big Picture

- A pointer is just a variable that stores an address.
- `&` gets an address. `*` follows an address back to a value.
- Arrays and pointers are deeply intertwined: `a[i]` ≡ `*(a + i)`.
- `new` / `delete` (and `new[]` / `delete[]`) let you manage memory at runtime — but you become responsible for freeing it.
- Functions can return pointers, but only to caller-provided data or heap-allocated data — **never** to locals.
- Modern C++ prefers **smart pointers** (`unique_ptr`, `shared_ptr`) so memory is freed automatically and leaks become structurally hard to write.
