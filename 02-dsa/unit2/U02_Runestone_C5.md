# Unit 02 — Runestone Chapter 5: Recursion (C++)

> Study notes & summary based on *Problem Solving with Algorithms and Data
> Structures using C++* (Runestone Academy), Chapter 5.
> Source: https://runestone.academy/ns/books/published/cppds/Recursion/toctree.html

---

## Table of Contents
1. [Objectives](#51-objectives)
2. [What Is Recursion?](#52-what-is-recursion)
3. [Calculating the Sum of a Vector of Numbers](#53-calculating-the-sum-of-a-vector-of-numbers)
4. [The Three Laws of Recursion](#54-the-three-laws-of-recursion)
5. [Converting an Integer to a String in Any Base](#55-converting-an-integer-to-a-string-in-any-base)
6. [Stack Frames: Implementing Recursion](#56-stack-frames-implementing-recursion)
7. [Visualizing Recursion (Turtle Graphics)](#57-visualizing-recursion)
8. [Sierpinski Triangle](#58-sierpinski-triangle)
9. [Complex Recursive Problems (Fibonacci)](#59-complex-recursive-problems)
10. [Tower of Hanoi](#510-tower-of-hanoi)
11. [Exploring a Maze](#511-exploring-a-maze)
12. [Dynamic Programming](#512-dynamic-programming)
13. [Chapter Summary](#513-summary)
14. [Self-Check Answers](#514-self-check-answers)
15. [Glossary](#517-glossary)
16. [Summary](#summary)

---

## 5.1 Objectives

By the end of this chapter you should be able to:

- Understand that **complex problems can be expressed simply using recursion**.
- Understand and apply the **three laws of recursion**.
- Write a problem as a **recursive definition** (a definition in terms of itself).
- Understand how recursion is implemented by the computer using a **call stack /
  stack frames**.
- Convert iterative algorithms into recursive ones (and recognize when *not* to).
- Recognize that recursion is sometimes more elegant but **not always more efficient**.

---

## 5.2 What Is Recursion?

**Recursion** is a method of solving problems by breaking a problem down into
smaller and smaller subproblems until you reach a subproblem small enough to be
solved trivially. Recursion involves **a function calling itself**.

> Key idea: it *seems* circular ("solve a problem by calling the same function")
> but it is not — each call works on a **smaller** version of the problem until a
> trivially solvable **base case** is reached.

---

## 5.3 Calculating the Sum of a Vector of Numbers

A warm-up problem: sum the numbers in `[1, 3, 5, 7, 9]`.

### Iterative version (no recursion)

Uses an **accumulator** variable (`theSum`) and a loop.

```cpp
//Example of summing up a vector without using recursion.
#include <iostream>
using namespace std;

int vectsum(int numVect[]){
    int theSum = 0;
    for (int i = 0; i < 5; i++){
        theSum += numVect[i];
    }
    return theSum;
}

int main() {
    int numVect[5] = {1, 3, 5, 7, 9};
    cout << vectsum(numVect) << endl;   // prints 25
    return 0;
}
```

### Thinking recursively

Pretend you have **no loops**. Addition is defined for *pairs* of numbers, so we
can fully parenthesize the sum:

```
((((1 + 3) + 5) + 7) + 9)        // or, the other direction:
(1 + (3 + (5 + (7 + 9))))
```

The innermost pair `(7 + 9)` can be solved with no loop. This gives a chain of
simplifications:

```
total = (1 + (3 + (5 + (7 + 9))))
total = (1 + (3 + (5 + 16)))
total = (1 + (3 + 21))
total = (1 + 24)
total = 25
```

The recursive insight:

> `sum(vec)` = **first element** + `sum(rest of the vector)`

### Recursive version

```cpp
//Example of summing a vector by using recursion.
#include <iostream>
#include <vector>
using namespace std;

int vectsum(vector<int> numVect){
    if (numVect.size() == 0)
        return 0;
    if (numVect.size() <= 1)        // <-- escape clause / base case
        return numVect[0];

    // make a copy of the vector WITHOUT the first element ("rest")
    vector<int> remaining(numVect.begin() + 1, numVect.end());

    return numVect[0] + vectsum(remaining);   // <-- recursive call ("first + rest")
}

int main() {
    vector<int> numVect = {1, 3, 5, 7, 9};
    cout << vectsum(numVect) << endl;   // prints 25
    return 0;
}
```

**Why this works:**
- The base case (a vector of length ≤ 1) is our **escape clause**.
- Each recursive call solves a **smaller** problem (a shorter vector).
- Calls "stack up" on the way down (simplification), then results are pieced back
  together on the way back up (addition).

---

## 5.4 The Three Laws of Recursion

Like Asimov's robots, every recursive algorithm must obey **three laws**:

1. **A recursive algorithm must have a base case.**
   The condition that lets the algorithm stop recursing — a problem small enough
   to solve directly. (For `vectsum`, the base case is a vector of length 1.)

2. **A recursive algorithm must change its state and move toward the base case.**
   Some data must be modified so the problem gets *smaller*. (For `vectsum`, we
   shorten the vector on each call.)

3. **A recursive algorithm must call itself.**
   This is the literal definition of recursion.

### Caution: obeying the laws ≠ efficient

A recursive function can follow all three laws and still be hopelessly slow.
The classic example is the **Ackermann function**, which expands explosively.
`ackermann(4,3)` calls itself **over 100 billion** times — it would finish long
after the predicted end of the universe.

```cpp
//ackermann function example
#include <iostream>
using namespace std;

unsigned int ackermann(unsigned int m, unsigned int n) {
    if (m == 0) {                       // Base case
        return n + 1;
    }
    if (n == 0) {
        return ackermann(m - 1, 1);     // subtract, move to base case
    }
    // A call to ackermann used as a parameter to another call to ackermann.
    // This is where it gets unrealistically complicated.
    return ackermann(m - 1, ackermann(m, n - 1));   // subtract here too
}

int main(){
    // Try replacing 1,2 with 4,3 and see what happens (it won't finish!)
    cout << ackermann(1,2) << endl;
    return 0;
}
```

**Takeaway:** efficiency depends heavily on *how* recursion is implemented, not
just on whether it is "correct."

### Worked example: Factorial

The factorial is the canonical "first" recursion example. By definition:

```
n! = n * (n-1) * (n-2) * ... * 1        and        0! = 1
```

This has a naturally recursive structure: **`n! = n * (n-1)!`**.

- **Law 1 — base case:** `n <= 1` returns `1` (covers both `1!` and `0!`, and
  guards against negative input causing infinite recursion).
- **Law 2 — change state:** each call uses `n - 1`, shrinking toward the base case.
- **Law 3 — calls itself:** `return n * factorial(n - 1)`.

```cpp
//Recursive factorial: n! = n * (n-1)!
#include <iostream>
using namespace std;

long factorial(int n) {
    if (n <= 1)                       // base case: 0! = 1 and 1! = 1
        return 1;
    return n * factorial(n - 1);      // recursive call on a smaller problem
}

int main() {
    cout << factorial(5) << endl;     // prints 120
    return 0;
}
```

**Trace of `factorial(5)`** (note how each call *waits* for the one below it,
then multiplies on the way back up — classic stack/LIFO behavior):

```
factorial(5) = 5 * factorial(4)
             = 5 * (4 * factorial(3))
             = 5 * (4 * (3 * factorial(2)))
             = 5 * (4 * (3 * (2 * factorial(1))))   // base case hit: returns 1
             = 5 * (4 * (3 * (2 * 1)))
             = 5 * (4 * (3 * 2))
             = 5 * (4 * 6)
             = 5 * 24
             = 120
```

> Unlike Ackermann, factorial makes exactly **`n` calls** — recursion here is
> clean and efficient (`O(n)`). Watch out for **overflow**: `int` overflows
> around `13!`, so use a wider type like `long`/`long long` for bigger inputs.

---

## 5.5 Converting an Integer to a String in Any Base

**Goal:** convert an integer to its string representation in any base from 2
(binary) to 16 (hexadecimal). e.g. `10` → `"10"` (decimal) or `"1010"` (binary).

### The idea (base 10 example with 769)

With a lookup string `convString = "0123456789"`, any number **< base** is a
single character we can look up directly → that's the **base case**.

To reduce a number, use **integer division + remainder**:

```
769 / 10 = 76 remainder 9   -> remember 9
 76 / 10 =  7 remainder 6   -> remember 6
  7 < 10                    -> base case, return "7"
```

Reading the remembered digits gives `"769"`.

Algorithm has three components:
1. **Reduce** the number to single digits (integer division).
2. **Convert** each single digit to a string via lookup.
3. **Concatenate** the single-digit strings into the final result.

### Recursive version

```cpp
//Recursive example of converting from int to string.
#include <iostream>
#include <string>
using namespace std;

string toStr(int n, int base) {
    string convertString = "0123456789ABCDEF";
    if (n < base) {                                  // base case
        return string(1, convertString[n]);         // convert char -> string
    } else {
        return toStr(n/base, base) + convertString[n%base];  // recursive call
    }
}

int main() {
    cout << toStr(1453, 16);   // prints 5AD
}
```

### Why the digit order comes out correct

When converting `10` to base 2 (`"1010"`), notice we make the **recursive call
first**, *then* append `convertString[n%base]`. By delaying the concatenation
until after the recursive call returns, the digits land in the proper order.
If you reversed those two operations, the string would be **backward**.

> This "delay until the call returns" behavior is exactly **stack** (LIFO)
> behavior — the deepest call finishes first.

---

## 5.6 Stack Frames: Implementing Recursion

What if, instead of concatenating results from recursive calls, we **pushed the
characters onto an explicit stack**? This mirrors what recursion does internally.

```cpp
//Example of the toStr function using a stack instead of recursion.
#include <iostream>
#include <string>
#include <stack>
using namespace std;

stack<char> rStack;

string toStr(int n, int base) {
    string convertString = "0123456789ABCDEF";
    while (n > 0) {
        if (n < base) {
            rStack.push(convertString[n]);          // push digit
        } else {
            rStack.push(convertString[n % base]);   // push n mod base
        }
        n = n/base;
    }
    string res;
    while (!rStack.empty()) {                        // pop everything back off
        res = res + (string(1, rStack.top()));
        rStack.pop();
    }
    return res;
}

int main() {
    cout << toStr(1453, 16);
}
```

### How this connects to "real" recursion

- When a function is called, a **stack frame** is allocated to hold its local
  variables. When it returns, the **return value is left on top of the stack**
  for the caller to use.
- For `toStr(10,2)`, the call `toStr(2/2, 2)` leaves `"1"` on the stack; that value
  is then used in place of the call inside `"1" + convertString[2%2]`, leaving
  `"10"` on top, and so on.
- The **call stack** takes the place of the explicit stack we built above.
- Stack frames also provide **scope**: even though it's the same function called
  over and over, each call gets a fresh, separate set of local variables.

---

## 5.7 Visualizing Recursion

Recursion can be hard to picture. Drawing **fractals** with turtle graphics makes
the recursive process visible. The C++ examples use **C-Turtle**
(https://github.com/walkerje/C-Turtle/), a C++ port of Python's `turtle` module.

The chapter walks through two drawings:

- **Recursive spiral** — base case is when the line length drops to `0`; each step
  draws forward, turns 90°, then recurses with a smaller length.
- **Fractal tree** — a tree is *a trunk with a smaller tree to the right and a
  smaller tree to the left* (two recursive calls). It is drawn **right side first**,
  all the way down to the smallest twig, then works back up the trunk and draws the
  left side.

> Full code and figures: https://runestone.academy/ns/books/published/cppds/Recursion/pythondsintro-VisualizingRecursion.html

---

## 5.8 Sierpinski Triangle

Another self-similar fractal — and a great example of a **three-way recursive**
algorithm.

**Hand procedure:** start with a large triangle, connect the midpoints of the
three sides to make three corner triangles (ignore the middle one), then apply
the same procedure to each of the three corner triangles, forever.

- **Base case:** the **degree** of the fractal (how many times we subdivide).
  Each recursive call subtracts 1 from `degree`; when `degree == 0`, stop.
- The `sierpinski` function makes **three recursive calls** — one per corner —
  using midpoints of the current triangle's sides.

> Full code and figures: https://runestone.academy/ns/books/published/cppds/Recursion/pythondsSierpinskiTriangle.html

---

## 5.9 Complex Recursive Problems

Some problems are **hard to solve iteratively but elegant with recursion**. The
following sections (Tower of Hanoi, Exploring a Maze) are such problems. The
chapter also warns of a "deceptive" problem (making change) that *looks* like it
has an elegant recursive solution but is actually inefficient without extra
techniques (see Dynamic Programming).

### Worked example: Fibonacci sequence

The Fibonacci sequence is `0, 1, 1, 2, 3, 5, 8, 13, 21, ...` — each number is the
sum of the previous two. Its mathematical definition is **already recursive**:

```
fib(0) = 0
fib(1) = 1
fib(n) = fib(n-1) + fib(n-2)     for n >= 2
```

- **Base cases:** `fib(0) = 0` and `fib(1) = 1` (this problem needs **two** base
  cases, because the recursive step reaches back two steps).
- **Change state:** the two recursive calls use `n-1` and `n-2`.
- **Calls itself:** twice per call.

```cpp
//Naive recursive Fibonacci -- elegant, but slow (exponential time).
#include <iostream>
using namespace std;

long fib(int n) {
    if (n < 2)                        // base cases: fib(0)=0, fib(1)=1
        return n;
    return fib(n - 1) + fib(n - 2);   // two recursive calls
}

int main() {
    for (int i = 0; i < 10; i++)
        cout << fib(i) << " ";        // prints 0 1 1 2 3 5 8 13 21 34
    cout << endl;
    return 0;
}
```

#### Why this is a *complex* / deceptive recursive problem

The naive version is beautiful but **terribly inefficient** — it runs in roughly
`O(2^n)` time because it **recomputes the same subproblems** over and over. For
example, computing `fib(5)` recomputes `fib(3)` twice, `fib(2)` three times, and
so on:

```
                      fib(5)
              /                    \
          fib(4)                   fib(3)
         /      \                 /      \
     fib(3)    fib(2)         fib(2)    fib(1)
     /    \    /    \         /    \
  fib(2) fib(1) ...         ...    ...     <- fib(2)/fib(3) computed repeatedly
```

This is exactly the kind of **overlapping subproblems** that **memoization** and
**dynamic programming** (Section 5.12) are designed to fix.

#### Faster: memoized (top-down) Fibonacci

Cache each answer the first time it is computed, so it is reused instead of
recomputed. This brings the cost down to `O(n)`.

```cpp
//Memoized Fibonacci -- O(n) by caching results.
#include <iostream>
#include <vector>
using namespace std;

long fib(int n, vector<long> &memo) {
    if (n < 2)
        return n;
    if (memo[n] != -1)                // already computed -> reuse it
        return memo[n];
    memo[n] = fib(n - 1, memo) + fib(n - 2, memo);
    return memo[n];
}

int main() {
    int n = 40;
    vector<long> memo(n + 1, -1);     // -1 marks "not computed yet"
    cout << fib(n, memo) << endl;     // prints 102334155 (instant)
    return 0;
}
```

#### Faster still: iterative (bottom-up) Fibonacci

For comparison, the same `O(n)` result with `O(1)` extra space and no recursion —
a reminder that **recursion is not always the best tool**.

```cpp
//Iterative Fibonacci -- O(n) time, O(1) space.
#include <iostream>
using namespace std;

long fib(int n) {
    if (n < 2) return n;
    long prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int main() {
    cout << fib(40) << endl;          // prints 102334155
    return 0;
}
```

> **Lesson:** Fibonacci shows both the elegance of recursion *and* its danger.
> The naive recursive form mirrors the math perfectly but is exponential; adding
> memoization (or switching to iteration) makes it practical.

---

## 5.10 Tower of Hanoi

**The puzzle (Édouard Lucas, 1883):** move a stack of disks from one pole to
another using a third pole, with two rules:
1. Move only **one disk at a time**.
2. **Never** place a larger disk on top of a smaller disk.

> Moving 64 disks at one move/second takes 2⁶⁴−1 = 18,446,744,073,709,551,615
> moves ≈ **584 billion years**.

### Recursive strategy (move a tower of height `n` from → to, using `with`)

1. Move a tower of `height - 1` to the **intermediate** pole (using the final pole).
2. Move the **single remaining disk** to the final pole.
3. Move the tower of `height - 1` from the intermediate pole to the final pole
   (using the original pole).

**Base case:** a tower of height 1 (or, in the code, height drops to 0 → do
nothing and return). The solution makes **two recursive calls** around a single
disk move, and needs **no explicit disk/pole data structure** — C++ provides the
stacks implicitly through the **call stack**.

> Full code and figures: https://runestone.academy/ns/books/published/cppds/Recursion/TowerofHanoi.html

---

## 5.11 Exploring a Maze

**Problem:** find an exit from a maze starting somewhere in the middle.

**Maze representation:** a `vector<string>`, where each character is:

| Char | Meaning            |
|------|--------------------|
| `+`  | wall / obstacle    |
| `S`  | start position     |
| `O`  | path out (success) |
| `.`  | already tried      |
| `-`  | dead end           |
| `X`  | exit marker        |

**Procedure from a square:** try **North, then South, then West, then East**,
recursively. Drop "bread crumbs" (mark `.`) so you don't revisit squares and get
stuck in an infinite loop. Backing up is just **returning** from a recursive call.

### Four base cases

1. We ran into a **wall** → return `false`.
2. We hit a square **already explored** → return `false` (avoid loops).
3. We found an **outside edge** not occupied by a wall → **exit found**, return `true`.
4. We've explored a square unsuccessfully in **all four directions** → dead end.

### How the search works (`searchFrom`)

The recursive `searchFrom(maze, row, col)` function:

1. Checks the base cases (wall, already-tried, or an exit on the edge).
2. Drops a "bread crumb" by marking the current square as tried (`.`).
3. Makes **four recursive calls** — North, South, West, East — joined by
   short-circuit OR (`||`): if North succeeds, the rest aren't evaluated. If all
   four return `false`, the square is a dead end (`-`).

> Full code (including `readMazeFile`, `findStart`, `onEdge`, `printMaze`, the
> complete program, and the `maze1.txt`/`maze2.txt` data files):
> https://runestone.academy/ns/books/published/cppds/Recursion/ExploringaMaze.html

---

## 5.12 Dynamic Programming

**Dynamic programming (DP)** breaks the main problem into smaller subproblems and
uses those subproblem answers to build the answer to the main problem — storing
results so they aren't recomputed.

### The motivating problem: making change with the fewest coins

For U.S. coins (1, 5, 10, 25), a **greedy** approach (take as many of the largest
coin as possible, then the next, …) works fine. But add a **21-cent** coin and
greedy **fails**: for 63 cents, greedy gives **6 coins** but the optimal answer is
**three 21-cent pieces**.

The chapter builds up the solution in stages:

1. **Greedy** — fast but can be wrong (gives 6 coins for 63¢).
2. **Naive recursion** — correct but takes **67,716,925** calls for 63¢ because it
   recomputes the same subproblems.
3. **Memoization** (top-down cache) — drops 63¢ to just **221 calls**.
4. **True DP / tabulation** (bottom-up, not recursive) — builds a table of the
   minimum coins for every amount from 0 up to the target.
5. **DP that also tracks which coins were used**, by remembering the last coin
   added for each amount and tracing backward.

> **Memoization vs. Dynamic Programming:** both avoid recomputing duplicate work.
> Memoization is *top-down and opportunistic* (compute on demand, cache the
> result). True DP is *bottom-up and systematic* (build a full table from the
> smallest subproblem up).
>
> Full code for all five variants and the worked 11-cent / 63-cent tables:
> https://runestone.academy/ns/books/published/cppds/Recursion/DynamicProgramming.html

---

## 5.13 Summary

Key points to remember from this chapter:

- All recursive algorithms must have a **base case**.
- A recursive algorithm must **change its state and make progress toward the base case**.
- A recursive algorithm must **call itself** (recursively).
- Recursion can **take the place of iteration** in some cases.
- Recursive algorithms often **map naturally** to a formal expression of the problem.
- Recursion is **not always the answer** — sometimes it's more computationally
  expensive than an alternative (iteration or DP).

---

## 5.14 Self-Check Answers

- **Why is a base case needed?** Without one, the function makes recursive calls
  forever → an **infinite loop** (eventually a runtime/stack-overflow error).
- **How many recursive calls to sum `{2,4,6,8,10}`?** **4.** The initial call
  isn't a recursive call; calls pass `{4,6,8,10}`, `{6,8,10}`, `{8,10}`, `{10}`.
- **Best base case for `fact(n)`?** `n <= 1` — most efficient and safe even if a
  negative number is passed.
- **The three laws (choose all correct):** must **move toward the base case**,
  must **have a base case**, must **call itself**.
- **Iteration vs. recursion choice:** counting items in a list → **iteration**;
  traversing an entire tree → **recursion**.
- **"Recursion can be more expensive than an alternative" — True or False?**
  **True.**
- **(5.5) Is stepping through a recursive function like a stack or a queue?**
  A **stack** — the final (deepest) call completes first (LIFO), because earlier
  calls wait on the results of the calls they made.

---

## 5.17 Glossary

| Term | Definition |
|------|------------|
| **base case** | A branch of the conditional in a recursive function that does *not* give rise to further recursive calls. |
| **data structure** | An organization of data for the purpose of making it easier to use. |
| **dynamic programming** | Solving complex problems by breaking them up, solving the smaller portions, and **storing** results to avoid re-calculating them. |
| **exception** | An error that occurs at runtime. |
| **handle an exception** | Prevent an exception from terminating a program by wrapping the code in a `try`/`except` (C++: `try`/`catch`) construct. |
| **immutable data type** | A data type that cannot be modified. |
| **infinite recursion** | A function that calls itself without ever reaching the base case; eventually causes a runtime error. |
| **mutable data type** | A data type that can be modified. |
| **raise** | To cause an exception (C++: `throw`). |
| **recursion** | The process of calling the function that is already executing. |
| **recursive call** | The statement that calls an already-executing function. Recursion can be **indirect**: `f` calls `g` calls `h`, and `h` calls back to `f`. |
| **recursive definition** | A definition that defines something in terms of itself; must include base cases (vs. a circular definition). |
| **stack frame** | A stack that contains a "frame" / group of data — for a call stack, a function and its arguments. |
| **tuple** | A sequence of elements of any type, like a list, but immutable. |
| **tuple assignment** | Assigning all elements of a tuple in a single statement (in parallel — useful for swapping). |

---

## Summary

**The 3 Laws:**
1. Have a **base case**.
2. **Change state**, moving toward the base case.
3. **Call itself.**

**Recursion ↔ Stack:** every recursive call pushes a **stack frame** (locals +
return address). The deepest call returns first → **LIFO**. This is why
`toStr` digits come out in order only when concatenation is *delayed* until after
the recursive call returns.

**Pattern: `f(problem) = combine(first_piece, f(smaller_problem))`**
- `vectsum`:   `numVect[0] + vectsum(rest)`
- `toStr`:     `toStr(n/base) + digit(n%base)`
- `factorial`: `n * factorial(n-1)`           (base: `n <= 1` → 1)
- `fib`:       `fib(n-1) + fib(n-2)`           (bases: `fib(0)=0`, `fib(1)=1`)

**Multi-way recursion:**
- Naive Fibonacci → **2** recursive calls (but `O(2^n)` due to overlap — memoize!).
- Fractal tree → **2** recursive calls (left + right).
- Sierpinski triangle → **3** recursive calls (each corner).
- Tower of Hanoi → **2** recursive calls around 1 disk move.
- Maze → **4** recursive calls (N/S/W/E), short-circuited with `||`.

**Tower of Hanoi:** moves required for `n` disks = `2^n − 1`.

**When NOT to use plain recursion:** when subproblems **overlap and repeat**
(e.g., making change, Fibonacci). Fix with **memoization** (top-down cache) or
**dynamic programming** (bottom-up table). Greedy is fast but can be **wrong**
(63¢ with a 21¢ coin).

**Common base-case bugs:** missing base case → infinite recursion → stack
overflow; base case that never gets hit because state isn't shrinking.
