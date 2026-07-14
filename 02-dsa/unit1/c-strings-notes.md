# C-Strings in C++ — Comprehensive Notes

> Reference code: `lab1/functions.h`, `lab1/functions.cpp`, `lab1/functions_test.cpp`

---

## 1. What Is a C-String?

A **C-string** (C-style string) is simply an **array of `char`** that ends with a special
**null terminator** character `'\0'` (ASCII value `0`).

There is no separate "string" type in C — a C-string is just bytes in memory plus a
*convention*: "the string continues until you hit a `'\0'`."

```cpp
char word[] = "hello";
```

In memory this is **6 bytes**, not 5:

```
index:     0    1    2    3    4    5
value:    'h'  'e'  'l'  'l'  'o'  '\0'
ascii:    104  101  108  108  111   0
```

That trailing `'\0'` is the entire reason functions like `strlen` know where to stop.
If it is missing, code keeps reading memory past the array → **undefined behavior**.

### Key vocabulary

| Term | Meaning |
|------|---------|
| `char` | a single character (1 byte) |
| `char[]` | an array of characters (a buffer you can modify) |
| `char *` | a pointer to the first character |
| `const char *` | a pointer to characters you promise **not** to modify |
| `'\0'` | the null terminator that ends every C-string |
| `"hello"` | a **string literal** (read-only, already null-terminated) |

---

## 2. Declaring C-Strings (and the `char[]` vs `char *` trap)

```cpp
char a[] = "hello";        // modifiable copy in this array (6 bytes)
const char *b = "hello";   // pointer to a read-only string literal
char c[20] = "hi";         // 20-byte buffer, "hi\0" + leftover space
```

### Why `char[]` vs `const char *` matters

- `char a[] = "hello";` copies the literal into a **local, writable** array.
  You can do `a[0] = 'H';`.
- `const char *b = "hello";` points at the literal stored in **read-only memory**.
  Writing `b[0] = 'H';` is **undefined behavior** (often a crash).

This is exactly why your test driver uses **arrays** when it needs to modify, but
**pointers** when it only reads:

```38:46:02-data-structures/unit1/lab1/functions_test.cpp
    char test1[] = "hello";
    char test2[] = "racecar";
    char test3[] = "A";
    char test4[] = "data structures";

    reverse(test1);
    reverse(test2);
```

`reverse` *modifies in place*, so it must receive a real writable array (`char[]`),
not a string literal. Meanwhile read-only tests use `const char *`:

```22:23:02-data-structures/unit1/lab1/functions_test.cpp
    const char *tests[] = {"12345", "0012", "12a45", "", "0", "987654321"};
    const bool expected[] = {true, true, false, false, true, true};
```

**Rule of thumb:** if a function changes the characters, take `char *`.
If it only reads them, take `const char *` (this is the `const`-correct choice and
lets callers pass literals safely).

---

## 3. Accessing Each Character

There are two equivalent ways to reach element `i`:

```cpp
theString[i]      // subscript / index notation
*(theString + i)  // pointer arithmetic (identical meaning)
```

`theString[i]` is literally shorthand for `*(theString + i)`. Arrays "decay" into a
pointer to their first element, so indexing and pointer math are the same operation.

### Looping until the null terminator

The most common C-string loop walks forward until it sees `'\0'`. You see this pattern
throughout your lab:

```37:43:02-data-structures/unit1/lab1/functions.cpp
void printASCII(const char *theString) {
  // TODO: Output the ASCII decimal value of each character in the string.
  for (int i = 0; theString[i] != '\0'; i++) {
    std::cout << int(theString[i]) << " ";
  }
  std::cout << std::endl;
}
```

The loop condition `theString[i] != '\0'` is the heart of nearly every C-string
algorithm. You do **not** need to know the length in advance — the terminator tells you
when to stop.

The same idea drives counting and conversion:

```45:54:02-data-structures/unit1/lab1/functions.cpp
int countOccurrences(const char *theString, char target) {
  // TODO: Count and return how many times target appears in the string.
  int num = 0;
  for (int i = 0; theString[i] != '\0'; i++) {
    if (theString[i] == target) {
      num += 1;
    }
  }
  return num;
}
```

---

## 4. Characters Are Just Numbers (ASCII)

Every `char` is stored as a small integer (its ASCII code). This unlocks two
fundamental tricks.

### Trick 1: Range checks with character literals

`'0'` through `'9'` are **consecutive** ASCII codes (48–57). So "is this a digit?" is a
simple range comparison — no library needed:

```9:23:02-data-structures/unit1/lab1/functions.cpp
bool isDigitString(const char *theString) {
  // TODO: Return true only if the string is non-empty
  // and every character is a digit.

  // handling empty string
  if (theString[0] == '\0') {
    return false;
  }
  for (int i = 0; theString[i] != '\0'; i++) {
    if (theString[i] < '0' || theString[i] > '9') {
      return false;
    }
  }
  return true;
}
```

### The library way: `std::isdigit(static_cast<unsigned char>(c))`

The manual range check works, but the standard, portable way to test a character is the
`<cctype>` family: `std::isdigit`, `std::isalpha`, `std::isspace`, `std::isupper`, etc.
Instead of `theString[i] < '0' || theString[i] > '9'`, you write:

```cpp
#include <cctype>

if (!std::isdigit(static_cast<unsigned char>(theString[i]))) {
    return false;
}
```

`std::isdigit` returns a non-zero (truthy) value if the character is `'0'`–`'9'`, and `0`
otherwise — so `!std::isdigit(...)` means "not a digit."

#### Why the `static_cast<unsigned char>` is required (this is the important part)

The `<cctype>` functions take an `int`, and the standard says the value you pass **must
be representable as `unsigned char` or be `EOF`**. Otherwise the behavior is *undefined*.

Here's the trap: plain `char` may be **signed** on many compilers. If a string contains a
byte with the high bit set (value ≥ 128, e.g. an accented or non-ASCII character), a
signed `char` holds a **negative** value like `-61`. Passing that negative number
directly to `std::isdigit` is undefined behavior (it can index out of bounds inside the
library's internal lookup table) and may crash or misbehave.

```cpp
char c = theString[i];                 // could be negative if char is signed
std::isdigit(c);                       // UB if c < 0 (and not EOF)
std::isdigit(static_cast<unsigned char>(c));   // SAFE: always 0..255
```

Casting to `unsigned char` first **reinterprets the byte as 0–255**, which is always a
legal argument. So the idiom is always:

```cpp
std::isdigit(static_cast<unsigned char>(c))
```

> Note: this is a *different* reason from the `static_cast<const void *>` in Section 6.
> - `static_cast<unsigned char>` → make the byte a **valid value** for `<cctype>`.
> - `static_cast<const void *>` → make `cout` print an **address, not text**.
> Both are casts, but they solve unrelated problems.

#### Manual check vs `std::isdigit` — trade-offs

| Approach | Pros | Cons |
|----------|------|------|
| `c >= '0' && c <= '9'` | no header, transparent, fine for plain ASCII | you must remember it's ASCII-only logic |
| `std::isdigit(static_cast<unsigned char>(c))` | standard, readable, locale-aware, handles signedness safely | must remember the `unsigned char` cast |

For learning the mechanics, the manual range check is great. For production code, prefer
`std::isdigit(static_cast<unsigned char>(c))` — it states intent clearly and is safe for
all byte values. The same `unsigned char` cast applies to every `<cctype>` function
(`std::isalpha`, `std::toupper`, `std::tolower`, …).

### Trick 2: `char - '0'` converts a digit character to its numeric value

Because digits are consecutive, `'7' - '0'` == `55 - 48` == `7`. This is how you turn a
string of digits into an actual integer, digit by digit (Horner's method):

```73:82:02-data-structures/unit1/lab1/functions.cpp
int stringToInt(const char *theString) {
  // TODO: Assume the string contains digits only.
  // Convert the C-string to its integer value and return it.
  int num = 0;
  for (int i = 0; theString[i] != '\0'; i++) {
    int currentNum = theString[i] - '0';
    num = currentNum + (10 * num);
  }
  return num;
}
```

Walkthrough for `"105"`:

| char | `char - '0'` | `num = currentNum + 10*num` |
|------|--------------|------------------------------|
| `'1'` | 1 | `1 + 10*0  = 1`   |
| `'0'` | 0 | `0 + 10*1  = 10`  |
| `'5'` | 5 | `5 + 10*10 = 105` |

The reverse trick also exists: `int(theString[i])` (used in `printASCII`) converts a
character **to** its ASCII number.

---

## 5. Pointers, Addresses, and Memory

### A C-string variable is (or decays to) an address

When you pass `char *theString`, you are not copying the whole string — you are passing
the **memory address of the first character**. The function then reads forward from that
address. This is cheap and is why C-strings are passed around as pointers.

### `strlen` — finding the length by scanning

`strlen` (from `<cstring>`) walks from the first byte and counts until `'\0'`, **not**
including the terminator. `strlen("hello")` is `5`. It is an O(n) scan every time you
call it, which is why you often store it once.

You use it to set up the two-pointer technique:

```25:35:02-data-structures/unit1/lab1/functions.cpp
void reverse(char *theString) {
  // TODO: Reverse the contents of the modifiable C-string in place.
  int first = 0;
  int last = strlen(theString) - 1;

  while (first < last) {
    swapIt(theString[first], theString[last]);
    first++;
    last--;
  }
}
```

### The two-pointer technique

Both `reverse` and `isPalindrome` use the same idea: one index starts at the front,
another at the back, and they move toward each other.

- **`reverse`**: swap the two ends, then step inward — reverses the array in place.
- **`isPalindrome`**: compare the two ends; if any pair differs, it's not a palindrome.

```56:71:02-data-structures/unit1/lab1/functions.cpp
bool isPalindrome(const char *theString) {
  // TODO: Return true if the string reads the same forward and backward.

  int left = 0;
  int right = strlen(theString) - 1;

  while (left < right) {
    if (theString[left] != theString[right]) {
      return false;
    }
    left++;
    right--;
  }

  return true;
}
```

Note: the empty string never enters the loop (`left < right` is false immediately), so
it correctly returns `true` — an empty string is a palindrome.

### "In place" means no extra buffer

`reverse` rearranges the existing bytes using `swapIt`; it allocates no new array. That's
why it needs a *writable* `char *` argument. The generic swap comes from your template:

```64:70:02-data-structures/unit1/lab1/functions.h
template <class type> void swapIt(type &a, type &b) {
  type stored = a;
  a = b;
  b = stored;
}
```

### Pointer arithmetic on addresses

`item + i` advances the pointer by `i` **elements** (the compiler multiplies by the
element size for you). For a `char` array that's `i` bytes; for an `int` array it's
`i * 4` bytes. Your `printAddresses` template prints the address of each element:

```75:79:02-data-structures/unit1/lab1/functions.h
template <class type> void printAddresses(type *item, int n) {
  for (int i = 0; i < n; i++) {
    std::cout << static_cast<const void *>(item + i) << std::endl;
  }
}
```

Running this on a `char[]` shows addresses **1 apart** (chars are 1 byte). On an
`int[]` you'd see them **4 apart** — a great way to *see* that array elements are
contiguous in memory.

---

## 6. Why `static_cast<const void *>` Is Needed

This is the subtle part of your lab and worth understanding deeply.

### The problem: `char *` has a special overload in `cout`

`std::cout` is overloaded so that when you give it a `char *` or `const char *`, it
assumes you want to **print the string** (the text), not the address:

```cpp
char str[] = "test";
std::cout << str;        // prints: test   (NOT an address!)
std::cout << &str[0];    // also prints: test
```

So if `printAddresses` were instantiated with `char`, then `item + i` is a `char *`, and
`cout` would happily print the *characters* instead of the *address* you actually want.

### The fix: cast to `void *` so `cout` prints the address

For **any other** pointer type, `cout` prints the raw memory address (in hex). The
generic "pointer to anything" type is `void *`. Casting to it forces `cout` to use the
address-printing overload instead of the string-printing one:

```cpp
std::cout << static_cast<const void *>(item + i);  // prints e.g. 0x7ffd...
```

Your test driver does the exact same thing when labeling addresses:

```125:130:02-data-structures/unit1/lab1/functions_test.cpp
    for (int i = 0; i < len; i++)
    {
        std::cout << "str[" << i << "] = "
                  << static_cast<const void*>(&sample[i])
                  << std::endl;
    }
```

### Two equivalent ways to get the address of element `i`

Notice the template (`printAddresses`) uses `item + i`, while the test driver uses
`&sample[i]`. **These produce the exact same address** — they are interchangeable:

```cpp
item + i      // pointer math: start pointer advanced by i elements
&item[i]      // "address of" the i-th element
```

Why they're identical: `item[i]` means `*(item + i)`, so taking its address with `&`
gives `&*(item + i)`, and the `&` and `*` cancel out → `item + i`. Use whichever reads
more clearly. Both still need the `static_cast<const void *>` wrapper when the element
type is `char`, otherwise `cout` prints text instead of the address:

```cpp
std::cout << static_cast<const void *>(item + i);    // works
std::cout << static_cast<const void *>(&item[i]);    // identical result
```

### Why `static_cast` (and why `const`)

- **`static_cast<const void *>`** is the C++ way to do this conversion. It's safer and
  more visible than a C-style cast `(const void *)`. `static_cast` is checked at compile
  time and is easy to search for.
- The **`const`** is kept because `printAddresses` may receive a `const char *`. You
  cannot legally cast away `const` with `static_cast`, so the target type must also be
  `const void *`. Keeping `const` preserves the promise "I won't modify what this points
  to — I just want its address."

### Summary table

| You write | What `cout` prints | Why |
|-----------|--------------------|-----|
| `cout << charPtr` | the text characters | special `char*` overload |
| `cout << intPtr` | the hex address | normal pointer overload |
| `cout << static_cast<const void*>(charPtr)` | the hex address | forces the pointer overload |

**One-line answer:** `static_cast<const void *>` is needed so the address of a
`char`/`const char` is printed as a memory address instead of being interpreted as text.

---

## 7. Additional Fundamentals (Important Beyond the Lab)

### 7.1 Common `<cstring>` library functions

You implemented many of these by hand in the lab, but in real code you'd reach for:

| Function | Purpose | Note |
|----------|---------|------|
| `strlen(s)` | length (excludes `'\0'`) | O(n) scan |
| `strcpy(dst, src)` | copy string | **no bounds check** — dst must be big enough |
| `strncpy(dst, src, n)` | copy up to n chars | safer, but may not null-terminate |
| `strcmp(a, b)` | compare; 0 if equal | returns <0 / 0 / >0 |
| `strcat(dst, src)` | append src onto dst | dst must have room |
| `strchr(s, c)` | find first `c` | returns pointer or `nullptr` |

### 7.2 You cannot compare or assign C-strings with `==` or `=`

```cpp
char a[] = "hi";
char b[] = "hi";
if (a == b) { ... }   // BUG: compares ADDRESSES, not contents (almost always false)
a = b;                // ERROR: cannot assign to an array
```

Use `strcmp(a, b) == 0` to compare contents, and `strcpy` to copy contents.

### 7.3 Buffer size and off-by-one errors

A buffer must always have room for the `'\0'`. To hold an `n`-character string you need
`n + 1` bytes:

```cpp
char name[6] = "hello";   // OK: 5 chars + '\0' = 6
char bad[5]  = "hello";   // DANGER: no room for terminator
```

Writing past the end of a buffer (buffer overflow) is one of the most common and
dangerous bugs in C/C++.

### 7.4 The null terminator vs the digit `'0'` vs the number `0`

These are three different things — a frequent beginner confusion:

| Symbol | Meaning | ASCII value |
|--------|---------|-------------|
| `'\0'` | null terminator (ends a string) | 0 |
| `'0'` | the character zero | 48 |
| `0` | the integer zero | 0 |

So `'\0' == 0` is `true`, but `'\0' == '0'` is `false`.

### 7.5 `char` is 1 byte; signedness can bite you

`char` is exactly 1 byte but may be **signed or unsigned** depending on the compiler.
For plain ASCII (0–127) it doesn't matter, but for bytes ≥ 128 it can. When in doubt,
the `<cctype>` functions (`isdigit`, `isalpha`, `toupper`, …) handle this more portably
than manual comparisons.

### 7.6 C-strings vs `std::string`

In modern C++ you'd usually prefer `std::string`, which manages its own memory, knows its
length in O(1), supports `==`, `+`, and resizing, and is far safer. Your lab deliberately
avoids it so you learn the underlying mechanics — but know that `std::string` exists and
is the production default. You can always get a C-string back with `myString.c_str()`.

---

## 8. How C-Strings Differ From Modern String Types

C-strings are the original, lowest-level option. Modern C++ offers safer, more convenient
alternatives. Here's how they compare and when to reach for each.

### The contenders

| Type | Header | What it is |
|------|--------|------------|
| `char *` / `char[]` (C-string) | `<cstring>` | raw `char` array ending in `'\0'` |
| `std::string` | `<string>` | owning, growable, self-managing string class |
| `std::string_view` | `<string_view>` | non-owning *view* (pointer + length) over existing chars |
| `std::array<char, N>` | `<array>` | fixed-size char buffer with bounds info (less common for text) |

### Side-by-side comparison

| Feature | C-string (`char *`) | `std::string` | `std::string_view` |
|---------|---------------------|---------------|--------------------|
| Knows its length | No — must scan for `'\0'` (O(n)) | Yes, O(1) `.size()` | Yes, O(1) `.size()` |
| Owns / manages memory | No (you manage it) | Yes (auto grow/free) | No (just borrows) |
| Can grow / resize | No (fixed buffer) | Yes | No |
| `==` compares contents | No (compares addresses!) | Yes | Yes |
| `+` concatenation | No (use `strcat`) | Yes | No |
| Can contain embedded `'\0'` | No (terminator ends it) | Yes | Yes |
| Bounds safety | None — easy to overflow | `.at()` throws on bad index | view can dangle |
| Copy cost | cheap pointer, but manual | allocates + copies | cheap (no copy) |
| Best for | C APIs, learning fundamentals | general string work | read-only params, no copying |

### What makes a C-string fundamentally different

1. **It carries no length.** A C-string is *just* the bytes; its end is discovered by
   scanning for `'\0'`. `std::string` and `string_view` store the length explicitly, so
   they don't need a terminator and can even hold `'\0'` inside the text.

2. **It doesn't manage its own memory.** You decide where the buffer lives and how big it
   is. `std::string` allocates and frees automatically and grows on demand.

3. **It has no built-in operators.** `==`, `=`, `+`, `<` either don't compile or do the
   wrong thing (comparing pointers). You must call `strcmp`, `strcpy`, `strcat`, etc.

4. **It is unsafe by default.** Nothing stops you from writing past the buffer or
   forgetting the terminator. The modern types add bounds checking and ownership.

### Quick examples of the difference

```cpp
// --- C-string ---
char a[] = "hi";
char b[] = "hi";
bool same = (a == b);              // WRONG: compares addresses (false)
bool ok   = (strcmp(a, b) == 0);   // correct

// --- std::string ---
std::string s = "hi";
std::string t = "hi";
bool eq = (s == t);                // correct, compares contents (true)
s += " there";                     // grows automatically -> "hi there"
std::cout << s.size();             // O(1), no scanning

// --- std::string_view (read-only, no copy) ---
std::string_view v = s;            // borrows s's characters, copies nothing
std::cout << v.size();             // O(1)
// v does NOT own the data: if s is destroyed/modified, v can dangle
```

### When to use which (rule of thumb)

- **`std::string`** — default choice for owning and modifying text.
- **`std::string_view`** — read-only function parameters where you don't need a copy
  (accepts both `std::string` and C-strings).
- **C-string (`const char *`)** — interfacing with C libraries / OS APIs, string
  literals, embedded systems, or (like this lab) learning how strings work underneath.

### Interop: converting between them

```cpp
std::string s = "hello";
const char *c = s.c_str();         // std::string -> C-string (null-terminated)

const char *raw = "world";
std::string s2 = raw;              // C-string -> std::string (copies)

std::string_view sv = "view";      // works from C-string or std::string
```

**Bottom line:** A C-string is the bare metal — an unmanaged array plus the `'\0'`
convention. `std::string` adds ownership, length, safety, and operators; `string_view`
adds a cheap, length-aware read-only window. Knowing the C-string mechanics (this lab)
is what makes the convenience of the modern types make sense.

---

## 9. Quick Reference Cheat Sheet

```cpp
// Declaration
char buf[] = "hello";          // writable copy (6 bytes incl. '\0')
const char *p = "hello";       // pointer to read-only literal

// Access
buf[i]            // i-th char
*(buf + i)        // same thing via pointer math

// Standard loop
for (int i = 0; s[i] != '\0'; ++i) { /* use s[i] */ }

// Length
int n = strlen(s);             // excludes '\0'

// Char <-> number
int  v = s[i] - '0';           // digit char -> int  ('7' -> 7)
char c = char(v + '0');        // int -> digit char  (7 -> '7')
int  a = int(s[i]);            // char -> ASCII code

// Two-pointer template
int lo = 0, hi = strlen(s) - 1;
while (lo < hi) { /* compare or swap s[lo], s[hi] */ lo++; hi--; }

// Print an address (not the text!)
std::cout << static_cast<const void *>(s);
```

### Mental model to remember

1. A C-string is **an array of chars ending in `'\0'`**.
2. The variable usually behaves as a **pointer to the first char**.
3. `s[i]` and `*(s + i)` are the **same** thing.
4. **Chars are numbers** (ASCII) — exploit that for digit checks and conversions.
5. To print a `char*`'s **address**, cast to `const void *`, or `cout` prints the text.
```
