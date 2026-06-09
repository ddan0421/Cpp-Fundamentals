# Problem Solving with Algorithms and Data Structures using C++  
## Comprehensive Summary: 1) Introduction, 2) Analysis, 3) Linear Structures

Source text: [Runestone C++DS](https://runestone.academy/ns/books/published/cppds/index.html)

---

## 1. Introduction

### 1.1 Core purpose of the chapter
Chapter 1 frames computer science as the discipline of solving problems with algorithms, not just writing code. It emphasizes:
- the difference between a *problem solution* (algorithm) and a *program* (coded implementation),
- abstraction as the main tool for managing complexity,
- C++ language fundamentals needed for later data-structure and algorithm work.

### 1.2 What computer science is (and is not)
- **Computer science** is the study of problems, algorithms, computability, and efficiency.
- A problem is **computable** if an algorithm exists that solves it.
- Some problems have no solutions; some are solvable but not in practical time.
- Hardware matters in practice, but core algorithmic ideas are machine-independent.

### 1.3 Programming as representation of algorithms
- **Programming** encodes an algorithm into a language executable by machines.
- Languages provide:
  - **control constructs** (sequence, selection, iteration),
  - **data types** (interpretation + valid operations on data).
- The chapter reinforces that good programming is necessary, but algorithmic thinking is deeper than syntax.

### 1.4 Abstraction, ADTs, and data structures
- **Procedural abstraction**: use a function by interface (name, parameters, return), hide internals.
- **Data abstraction**: define data by behavior and operations, hide storage details.
- **ADT (Abstract Data Type)**: logical model + allowed operations, implementation-independent.
- **Data structure**: concrete implementation of an ADT.
- Benefits:
  - encapsulation and information hiding,
  - easier reasoning about complex systems,
  - ability to swap implementations without changing client logic.

### 1.5 Why study algorithms and data structures
- To compare multiple correct solutions by **resource use** (time, space).
- To identify trade-offs (faster time may need more memory, and vice versa).
- To build reusable problem-solving patterns.
- To recognize intractable or impractical approaches early.

### 1.6 C++ review and foundational language points
- C++ is compiled and statically typed.
- Variables must be declared before use.
- Core atomic types: `int`, `float`, `double`, `bool`, `char`, pointers.
- Common operations and behaviors:
  - integer division truncates,
  - `%` is modulo,
  - exponentiation commonly uses `pow` from `cmath`,
  - Booleans use `true`/`false`, logical ops (`&&`, `||`, `!`),
  - `char` uses single quotes, strings use double quotes.

```cpp
#include <iostream>
#include <cmath>

int main() {
    int i = 10;
    double d = 3.14;
    bool b = true;
    char c = 'A';

    int sum = i + 5;           // Arithmetic
    double power = pow(d, 2);  // cmath function
    bool logic = b && (i > 5); // Logical operations

    std::cout << "Integer division: " << 10 / 3 << std::endl; // Truncates to 3
    return 0;
}
```

### 1.7 Pointers (important C++ distinction)
- Pointer stores a memory address.
- `&x` gives address of `x`; `*p` dereferences pointer `p`.
- Correct typing matters (pointer type should match pointed data type).
- Null pointers (`NULL`/`0`) indicate "points to nothing."
- Common pitfalls:
  - assigning raw integer as pointer address,
  - dereferencing invalid/dangling pointers,
  - segmentation faults from illegal memory access.

```cpp
int x = 42;
int *p = &x;     // p points to x

std::cout << p << std::endl;  // Prints memory address
std::cout << *p << std::endl; // Prints 42 (dereferencing)

*p = 100;        // Changes x through pointer
std::cout << x << std::endl;  // x is now 100
```

### 1.8 Collections in C++
#### Arrays
- Fixed-size, contiguous storage, homogeneous elements.
- Very fast indexed access.
- No built-in bounds safety; out-of-range access can silently corrupt memory.

```cpp
int scores[5] = {90, 85, 80, 75, 70};
std::cout << scores[0] << std::endl; // Fast indexing
```

#### Vectors
- Dynamic arrays with contiguous storage.
- Support growth (`push_back`) and many utility methods.
- Capacity and `reserve` matter for performance during growth.

```cpp
#include <vector>
std::vector<int> v = {1, 2, 3};
v.push_back(4); // Dynamic growth
```

#### Strings
- Sequence of characters; similar operational profile to vectors in modern C++.
- Rich method set (`find`, `insert`, `erase`, etc.).

```cpp
#include <string>
std::string s = "Hello";
s += " World";
```

#### Hash tables (`unordered_map`)
- Key-value storage with hash-based lookup.
- Fast average-case lookup and update.
- Not inherently ordered for iteration.

```cpp
#include <unordered_map>
std::unordered_map<std::string, int> ages;
ages["Alice"] = 25;
```

#### Unordered sets
- Unique values, hash-based containment checks.
- Efficient membership queries and set-style operations.

```cpp
#include <unordered_set>
std::unordered_set<int> primes = {2, 3, 5, 7};
if (primes.count(3)) { /* ... */ }
```

### 1.9 Functions and parameter passing
- C++ function definition includes name, parameters, return type, body.
- `void` for no return value.
- Pass-by-value vs pass-by-reference trade-offs:
  - value: copies data,
  - reference: allows in-place modification and efficient large-object handling.

```cpp
// Pass-by-value (copies)
void squareValue(int n) {
    n = n * n;
}

// Pass-by-reference (modifies original)
void squareRef(int &n) {
    n = n * n;
}

int main() {
    int x = 5;
    squareValue(x); // x remains 5
    squareRef(x);   // x becomes 25
    return 0;
}
```

### 1.10 OOP fundamentals in C++
- Class as blueprint (state + behavior), object as instance.
- Core OOP principles emphasized:
  1. **Abstraction**
  2. **Encapsulation**
  3. **Inheritance**
  4. **Polymorphism**

```cpp
class Animal {
public:
    virtual void speak() = 0; // Pure virtual function (abstraction)
};

class Dog : public Animal { // Inheritance
public:
    void speak() override { std::cout << "Woof!" << std::endl; }
};
```

### 1.10.1 Operator Overloading Detail
Operator overloading allows C++ operators to have user-defined meanings when applied to user-defined types (classes). This enables custom objects to use standard syntax (like `+`, `-`, `<<`), making the code more intuitive and readable.

#### Overloading the Stream Insertion Operator (`<<`)
To print a custom object using `std::cout`, we must overload the `<<` operator. This is typically done as a **non-member friend function**.

**Example:**
```cpp
friend std::ostream &operator<<(std::ostream &os, const Fraction &f) {
    os << f.num << "/" << f.den;
    return os;
}
```

**Detailed Explanation:**
1.  **`friend` Keyword**: Since the `<<` operator's left-hand operand is an `ostream` (not our class), it cannot be a member function of our class. By declaring it a `friend`, we grant it access to the class's `private` data members while keeping it as a non-member.
2.  **Return by Reference (`std::ostream &`)**: The function returns the `os` stream by reference. This is critical for **operator chaining**, allowing you to write `std::cout << f1 << " and " << f2 << std::endl;`.
3.  **The Parameters**:
    *   `std::ostream &os`: A reference to the output stream (like `std::cout`).
    *   `const Fraction &f`: A constant reference to the object we want to print. We use a reference to avoid a costly copy and `const` to guarantee the object isn't modified during printing.
4.  **The Body**: We use the standard `<<` on the internal members and then return the stream to allow further operations.

#### Overloading the Addition Operator (`+`)
Binary operators like `+` can be overloaded in two primary ways: as a **member function** or as a **non-member friend function**.

**1. Member Function Implementation:**
```cpp
#include <iostream>
using namespace std;

class Fraction {
    public:
        Fraction(int top = 0, int bottom = 1) {
            num = top;
            den = bottom;
        }
        // Member function: 'this' is the left operand
        Fraction operator +(const Fraction &otherFrac) {
            int newnum = otherFrac.num*den + otherFrac.den*num;
            int newden = den*otherFrac.den;
            return Fraction(newnum, newden);
        }

    friend ostream &operator << (ostream &stream, const Fraction &frac);

    private:
        int num, den;
};

ostream &operator << (ostream &stream, const Fraction &frac) {
    stream << frac.num << "/" << frac.den;
    return stream;
}
```
*   **What the compiler sees**: `f1 + f2` is translated to **`f1.operator+(f2)`**.
*   **Context**: The object on the left (`f1`) is the "host" or calling object. The keyword `this` points to `f1`.

**2. Non-member Friend Function Implementation:**
```cpp
#include <iostream>
using namespace std;

class Fraction {
    public:
        Fraction(int top = 0, int bottom = 1) {
            num = top;
            den = bottom;
        }

    friend ostream &operator << (ostream &stream, const Fraction &frac);
    // Friend function: both operands are passed explicitly
    friend Fraction operator +(const Fraction &frac1, const Fraction &frac2);

    private:
        int num, den;
};

ostream &operator << (ostream &stream, const Fraction &frac) {
    stream << frac.num << "/" << frac.den;
    return stream;
}

Fraction operator +(const Fraction &frac1, const Fraction &frac2) {
    int newnum = frac1.num * frac2.den + frac1.den * frac2.num;
    int newden = frac1.den * frac2.den;
    return Fraction(newnum, newden);
}
```
*   **What the compiler sees**: `f1 + f2` is translated to **`operator+(f1, f2)`**.
*   **Context**: Both operands are passed as explicit arguments. Neither is a "host" object; it behaves like a regular function that has access to `private` data via the `friend` declaration.

#### Comparison and Key Differences

| Feature | Member Function | Friend Function |
| :--- | :--- | :--- |
| **Translation** | `f1.operator+(f2)` | `operator+(f1, f2)` |
| **Parameters** | 1 explicit (the RHS) | 2 explicit (LHS and RHS) |
| **Implicit `this`** | Yes (`this` is the LHS) | No |
| **Symmetry** | Asymmetric | Symmetric |

**Why "Symmetry" is the deciding factor:**
The **Friend Function** is superior because it allows **Symmetry** when dealing with implicit type conversions.
- **With Friend**: Both `f1 + 5` and `5 + f1` work. In `5 + f1`, the compiler can convert `5` to a temporary `Fraction(5, 1)` and call `operator+(Fraction, Fraction)`.
- **With Member**: `f1 + 5` works (`f1.operator+(5)`), but **`5 + f1` fails** because the integer `5` cannot call a member method of the `Fraction` class.

### 1.11 Fraction class as class-design case study
Building a custom numeric ADT demonstrates how to manage state, enforce invariants (like canonical forms), and provide a natural API via operator overloading.

#### Full Implementation Example
```cpp
#include <iostream>
using namespace std;

// Helper function to find Greatest Common Divisor
int gcd(int m, int n) {
    while (m % n != 0) {
        int oldm = m;
        int oldn = n;
        m = oldn;
        n = oldm % oldn;
    }
    return n;
}

class Fraction {
public:
    // Parameterized constructor
    Fraction(int top, int bottom) {
        num = top;
        den = bottom;
    }
    // Single-parameter constructor (allows implicit conversion from int)
    Fraction(int top) {
        num = top;
        den = 1;
    }
    // Default constructor
    Fraction() {
        num = 1;
        den = 1;
    }

    // Overloading + (Member function)
    // Uses gcd to ensure the result is in simplest form
    Fraction operator +(const Fraction &otherFrac) {
        int newnum = num * otherFrac.den + den * otherFrac.num;
        int newden = den * otherFrac.den;
        int common = gcd(newnum, newden);
        return Fraction(newnum / common, newden / common);
    }

    // Overloading == for value comparison
    bool operator ==(const Fraction &otherFrac) {
        int firstnum = num * otherFrac.den;
        int secondnum = otherFrac.num * den;
        return firstnum == secondnum;
    }

    // Friend function for stream output
    friend ostream& operator<<(ostream& stream, const Fraction& fraction);

private:
    int num, den;
};

ostream& operator << (ostream& stream, const Fraction& fraction) {
    stream << fraction.num << "/" << fraction.den;
    return stream;
}

int main() {
    Fraction x(1, 2);
    Fraction y(2, 4);
    
    // Demonstrates operator+ and operator<<
    cout << x << " + " << y << " = " << x + y << endl;
    
    // Demonstrates operator==
    if (x == y) {
        cout << "x is equal to y" << endl;
    } else {
        cout << "x is not equal to y" << endl;
    }
    
    return 0;
}
```

#### Key Lessons from the Fraction Case Study
1.  **Multiple Constructors**: Providing default and single-parameter constructors improves usability and allows the compiler to treat integers as fractions automatically when needed.
2.  **Canonical Form**: Using `gcd` inside operations ensures that fractions like `2/4` are always represented/returned in their simplest form (`1/2`).
3.  **State Protection**: Keeping `num` and `den` `private` ensures that the internal state can only be modified through controlled class methods.
4.  **Natural Syntax**: Overloading `+` and `==` allows users of the class to treat `Fraction` objects like primitive numeric types.

### 1.12 Inheritance: Logic Gates and Circuits
Inheritance is a fundamental OOP concept that allows classes to reuse code and establish relationships. Two primary relationships are explored:

-   **IS-A Relationship (Inheritance)**: This relationship implies that a specialized class is a version of a more general class.
    -   *Example*: An `AndGate` **is-a** `BinaryGate`, and a `BinaryGate` **is-a** `LogicGate`. Subclasses inherit all data and behavior from their parent classes.
-   **HAS-A Relationship (Composition)**: This relationship occurs when one class uses another class as a component or member.
    -   *Example*: A `LogicGate` **has-a** `string` label. In complex simulations, a `Connector` (composition) **has-a** source gate and a target gate, allowing them to communicate without being in the same inheritance tree.

This example models logic gates using a "Template Method" pattern, where a base class provides a standard interface (`getOutput`) that calls a specialized internal method (`performGateLogic`).

#### 1. The LogicGate Base Class
The base class handles the label and the public interface for getting the output. Note how `getOutput` triggers the internal logic.

```cpp
class LogicGate {
public:
    LogicGate(string n) {
        label = n;
    }

    string getLabel() {
        return label;
    }

    bool getOutput() {
        output = performGateLogic();
        return output;
    }

    // Hook for subclasses to implement specific logic
    virtual bool performGateLogic() {
        cout << "ERROR! performGateLogic BASE" << endl;
        return false;
    }

protected:
    string label;
    bool output;
};
```

#### 2. Intermediate Classes (BinaryGate & UnaryGate)
These classes manage the input pins. They use "Taken" flags to track if a value has already been provided (either via `cin` or a connection), preventing multiple prompts.

```cpp
class BinaryGate : public LogicGate {
public:
    BinaryGate(string n) : LogicGate(n) {
        pinATaken = false;
        pinBTaken = false;
    }

    bool getPinA() {
        if (pinATaken == false) {
            cout << "Enter Pin A input for gate " << getLabel() << " : ";
            cin >> pinA;
            pinATaken = true;
        }
        return pinA;
    }

    bool getPinB() {
        if (pinBTaken == false) {
            cout << "Enter Pin B input for gate " << getLabel() << " : ";
            cin >> pinB;
            pinBTaken = true;
        }
        return pinB;
    }

protected:
    bool pinA, pinB;
    bool pinATaken, pinBTaken;
};

class UnaryGate : public LogicGate {
public:
    UnaryGate(string n) : LogicGate(n) {
        pinTaken = false;
    }

    bool getPin() {
        if (pinTaken == false) {
            cout << "Enter Pin input for gate " << getLabel() << " : ";
            cin >> pin;
            pinTaken = true;
        }
        return pin;
    }

protected:
    bool pin;
    bool pinTaken;
};
```

#### 3. Concrete Gate Implementations
These subclasses only need to override `performGateLogic` to provide the specific boolean operation.

```cpp
class AndGate : public BinaryGate {
public:
    AndGate(string n) : BinaryGate(n) {}

    virtual bool performGateLogic() override {
        bool a = getPinA();
        bool b = getPinB();
        return (a == 1 && b == 1);
    }
};

class OrGate : public BinaryGate {
public:
    OrGate(string n) : BinaryGate(n) {}

    virtual bool performGateLogic() override {
        bool a = getPinA();
        bool b = getPinB();
        return (a == 1 || b == 1);
    }
};

class NotGate : public UnaryGate {
public:
    NotGate(string n) : UnaryGate(n) {}

    virtual bool performGateLogic() override {
        return !getPin();
    }
};
```

#### Key Architecture Points:
1.  **Template Method Pattern**: `getOutput()` is the stable template; `performGateLogic()` is the variable hook.
2.  **State Tracking**: The `pinTaken` flags ensure the user is only prompted once for each input pin.
3.  **Constructors & Initialization**: Each subclass uses initializer lists (e.g., `: BinaryGate(n)`) to ensure the parent class's state (the label) is correctly set.


### 1.13 Optional graphics section (C-Turtle)
- Shows C++ use in graphics-oriented workflows.
- Introduces Turtle concepts, screen/object setup, drawing commands, shapes, stamps, speed/tracer tuning.

```cpp
#include <CTurtle.hpp>
namespace ct = cturtle;

int main() {
    ct::TurtleScreen scr;
    ct::Turtle turtle(scr);

    turtle.fillcolor({"purple"});
    turtle.begin_fill();
    for (int i = 0; i < 4; i++) {
        turtle.forward(50);
        turtle.right(90);
    }
    turtle.end_fill();

    scr.exitonclick();
    return 0;
}
```

### 1.15 Summary
The first chapter has provided a foundation in computer science principles and the C++ language. Key takeaways include:

-   **Computer science** is the study of problem solving.
-   Computer science uses **abstraction** as a tool for representing both processes and data.
-   **Abstract data types** allow programmers to manage the complexity of a problem domain by hiding the details of the data.
-   **C++** is a powerful object-oriented language.
-   All variables must be declared before use in C++.
-   C++ has typical built-in numeric types: `int` is for integers and `float` and `double` are used for floating point depending on the number of digits desired.
-   C++ has the Boolean type `bool` that holds `true` or `false`.
-   The character data type `char` holds a single character which is encased in single quotes.
-   **Pointers** are a type of variable that stores a memory address. To declare a pointer, an `*` is used before the variable name that is supposed to store the location.
-   A **statically allocated C++ array** is an ordered collection of one or more C++ data values of identical type stored in contiguous memory.
-   A **vector** is a dynamically allocated array with many useful methods.
-   **C++ strings** are a sequential collection of zero or more characters.
-   A **hash table** is used to store keys-value pairs. It applies a related hash function to the key in order to compute the location of the associated value. Look-up is typically very fast.
-   A **set** is an unordered collection of unique values.
-   Arrays, vectors, and strings are C++ **sequential collections**.
-   Hash tables and sets are **nonsequential collections** of data.
-   In C++, a **function definition** requires a name, a group of parameters, a return type, and a body.
-   **Non-fruitful functions** in C++ must contain the keyword `void` in its function definition.
-   You can **pass variables by value** as well as **by reference** in C++ functions. Passing by reference utilizes the use of pointers.
-   **Pass by reference** is useful when you require a function to return multiple variables.
-   To pass an array to a function you need to use an array parameter. The array parameter is denoted by the array variable name followed by set of square brackets (`[` and `]`).
-   Defining a new meaning for an already existing operator (such as the arithmetic operators plus “+” or times “*”) is called **overloading the operator**. The operators `::`, `#`, `.`, and `?` are reserved and cannot be overloaded.
-   Some operators such as `=`, `[]`, `()` and `->` can only be overloaded as member functions of a class and not as global functions.
-   **Classes** allow programmers to implement abstract data types.
-   Programmers can **override** standard methods as well as create new methods.
-   Classes can be organized into **hierarchies**.
-   A **class constructor** should always invoke the constructor of its parent before continuing on with its own data and behavior.

---

## 2. Analysis

### 2.1 Core purpose of the chapter
Chapter 2 formalizes how to evaluate algorithms independent of machine speed, compiler, or language. It transitions from runtime benchmarking to asymptotic analysis.

### 2.2 Program vs algorithm quality
- Two programs can differ in readability yet represent the same algorithm.
- Analysis focuses on algorithmic resource usage, not style alone.
- Primary resources:
  - **time** (operation counts),
  - **space** (memory requirements).

### 2.3 Benchmarking and its limits
- Practical timing via `clock` in `ctime` can compare runs.
- But measured time depends on environment factors (hardware, language, load, compiler).
- Therefore benchmarking is useful but not sufficient for theoretical comparison.

```cpp
#include <ctime>
#include <iostream>

void benchmark() {
    clock_t begin = clock();
    // ... code to be timed ...
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time: " << elapsed_secs << "s" << std::endl;
}
```

### 2.4 Big-O notation and order of growth
- Use `T(n)` to model operation count as function of input size `n`.
- Big-O keeps the dominant term; ignores constants and lower-order terms.
  - Example: `1 + n -> O(n)`
  - Example: `5n^2 + 27n + 1005 -> O(n^2)`
- Purpose: compare scalability as `n` grows large.

### 2.5 Common growth classes (in increasing cost)
- `O(1)` constant
- `O(log n)` logarithmic
- `O(n)` linear
- `O(n log n)` log-linear
- `O(n^2)` quadratic
- `O(n^3)` cubic
- `O(2^n)` exponential
- (`O(n!)` appears in brute-force combinatorial tasks and grows even faster)

### 2.6 Best, average, and worst case
- Some algorithms depend on input arrangement.
- Analysis may distinguish:
  - **best case** (most favorable input),
  - **average case** (expected input),
  - **worst case** (least favorable input).

### 2.7 Key worked example: summing 1..n
- Iterative summation does repeated additions: `O(n)`.
- Formula-based summation `(n(n+1))/2`: `O(1)`.
- Demonstrates that mathematically equivalent results can have very different scaling.

```cpp
// Iterative approach: O(n)
int sumOfN(int n) {
    int theSum = 0;
    for (int i = 1; i <= n; i++) {
        theSum = theSum + i;
    }
    return theSum;
}

// Closed-form approach: O(1)
int sumOfN2(int n) {
    return (n * (n + 1)) / 2;
}
```

### 2.8 Key worked example: anagram detection
Four approaches show dramatic complexity differences:

1. **Checking off matches**  
   Nested search per character -> `O(n^2)`

2. **Sort and compare**  
   Dominated by sort cost -> `O(n log n)` (or `O(n^2)` for slower sort strategies)

3. **Brute force permutations**  
   Try all permutations -> `O(n!)` (infeasible quickly)

4. **Count and compare character frequencies**  
   Count arrays + compare -> `O(n)` time, extra fixed-size space

```cpp
bool anagramSolution4(string s1, string s2) {
    int c1[26] = {0};
    int c2[26] = {0};

    for (int i = 0; i < s1.length(); i++) {
        int pos = s1[i] - 'a';
        c1[pos]++;
    }

    for (int i = 0; i < s2.length(); i++) {
        int pos = s2[i] - 'a';
        c2[pos]++;
    }

    for (int j = 0; j < 26; j++) {
        if (c1[j] != c2[j]) return false;
    }
    return true;
}
```

This section highlights the central **time-space trade-off** principle.

### 2.9 Analysis of C++ data-collection operations
The chapter ties complexity to implementation choices:

#### Vector / array analysis
- index access and assignment: `O(1)`
- `push_back`: typically `O(1)`, occasional resize cost `O(n)`
- `pop_back`: `O(1)`
- middle/front insert/erase: `O(n)` due to shifting
- `reserve`: can improve amortized growth behavior by reducing reallocations

#### String analysis
- Similar performance profile to vectors in modern C++ (contiguous, dynamic)
- indexing/assigning by index `O(1)`, front/middle structural edits generally `O(n)`

#### Hash table analysis (`unordered_map`)
- average-case find/insert/erase/contains: `O(1)`
- iteration: `O(n)`
- note: collision-heavy pathological cases can degrade, discussed later in implementation chapters

| Operation | Vector/Array | Unordered Map |
| :--- | :--- | :--- |
| Indexing | `O(1)` | `O(1)` (average) |
| Insert Front | `O(n)` | `O(1)` (average) |
| Insert End | `O(1)`* | `O(1)` (average) |
| Find Value | `O(n)` | `O(1)` (average) |
| Erase | `O(n)` | `O(1)` (average) |

\* Amortized for vector.

### 2.10 Chapter 2 high-value takeaways
- Big-O is about growth trend, not literal stopwatch time.
- Dominant term drives scalability.
- Data-structure choice strongly controls operation cost.
- "Correct" is not enough; scalable correctness is the real goal.

---

## 3. Linear Structures

### 3.1 Core purpose of the chapter
Chapter 3 introduces linear ADTs and shows how ordering rules (`LIFO`, `FIFO`, two-ended access) map to problem-solving patterns.

### 3.2 What linear structures are
- Ordered collections where relative item position matters.
- Distinguishing feature is where insertions/removals are allowed.
- Main ADTs in this chapter:
  - Stack
  - Queue
  - Deque

### 3.3 Stack
#### Concept
- LIFO (last in, first out)
- operations occur at top.

#### Core ADT operations
- `push`, `pop`, `top`, `empty`, `size`

```cpp
#include <vector>

template <class T>
class Stack {
private:
    std::vector<T> items;
public:
    void push(T item) { items.push_back(item); }
    T pop() {
        T item = items.back();
        items.pop_back();
        return item;
    }
    T peek() { return items.back(); }
    bool isEmpty() { return items.empty(); }
    int size() { return items.size(); }
};
```

#### STL usage
- `std::stack` provides these behaviors directly.

#### Typical use cases
1. **Balanced parentheses/symbol checking**  
   Push opening symbols, pop/match on closing symbols.

```cpp
bool parChecker(string symbolString) {
    Stack<char> s;
    bool balanced = true;
    int index = 0;
    while (index < symbolString.length() && balanced) {
        char symbol = symbolString[index];
        if (symbol == '(') {
            s.push(symbol);
        } else {
            if (s.isEmpty()) {
                balanced = false;
            } else {
                s.pop();
            }
        }
        index++;
    }
    return balanced && s.isEmpty();
}
```

2. **Base conversion (decimal to binary / base-N)**  
   Store remainders in stack to reverse output order.

3. **Expression conversion and evaluation**
   - convert infix -> postfix using operator stack and precedence rules,
   - evaluate postfix using operand stack.

#### Core stack insight
- Stacks naturally solve problems requiring reversal or "most recent unmatched item" tracking.

### 3.4 Expression notations and stack algorithms
#### Notations
- **Infix**: operator between operands (`A + B`)
- **Prefix**: operator before (`+ A B`)
- **Postfix**: operator after (`A B +`)

#### Why postfix/prefix are useful
- Remove ambiguity from precedence/parentheses.
- Operator position alone determines evaluation order.

#### Infix-to-postfix conversion
- Use operator stack.
- Pop higher/equal precedence operators before pushing new operator.
- Parentheses explicitly control pop boundaries.

```cpp
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

using namespace std;

string infixToPostfix(string infixExpr) {
    unordered_map<char, int> prec;
    prec['*'] = 3; prec['/'] = 3; prec['+'] = 2; prec['-'] = 2; prec['('] = 1;
    stack<char> opStack;
    vector<string> postfixList;
    stringstream ss(infixExpr);
    string token;

    while (ss >> token) {
        if (isalnum(token[0])) {
            postfixList.push_back(token);
        } else if (token == "(") {
            opStack.push('(');
        } else if (token == ")") {
            char topToken = opStack.top();
            opStack.pop();
            while (topToken != '(') {
                postfixList.push_back(string(1, topToken));
                topToken = opStack.top();
                opStack.pop();
            }
        } else {
            while (!opStack.empty() && (prec[opStack.top()] >= prec[token[0]])) {
                postfixList.push_back(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.push(token[0]);
        }
    }
    while (!opStack.empty()) {
        postfixList.push_back(string(1, opStack.top()));
        opStack.pop();
    }
    string result = "";
    for (const string& s : postfixList) result += s + " ";
    return result;
}
```

#### Postfix evaluation
- Push operands.
- On operator: pop two operands, compute, push result.
- End state: one item is final value.

```cpp
int doMath(char op, int op1, int op2) {
    if (op == '*') return op1 * op2;
    if (op == '/') return op1 / op2;
    if (op == '+') return op1 + op2;
    return op1 - op2;
}

int postfixEval(string postfixExpr) {
    stack<int> operandStack;
    stringstream ss(postfixExpr);
    string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            operandStack.push(stoi(token));
        } else {
            int operand2 = operandStack.top(); operandStack.pop();
            int operand1 = operandStack.top(); operandStack.pop();
            int result = doMath(token[0], operand1, operand2);
            operandStack.push(result);
        }
    }
    return operandStack.top();
}
```

### 3.5 Queue
#### Concept
- FIFO (first in, first out)
- enqueue at rear, dequeue at front.

#### Core ADT operations
- `push`, `pop`, `front`, `back`, `empty`, `size`

#### STL usage
- `std::queue`

#### Typical use cases
1. **Hot Potato (Josephus-style simulation)**  
   rotate queue repeatedly and eliminate by count.

```cpp
#include <queue>
#include <string>
#include <vector>

string hotPotato(std::vector<string> nameList, int num) {
    std::queue<string> simqueue;
    for (string name : nameList) {
        simqueue.push(name);
    }

    while (simqueue.size() > 1) {
        for (int i = 0; i < num; i++) {
            simqueue.push(simqueue.front());
            simqueue.pop();
        }
        simqueue.pop();
    }
    return simqueue.front();
}
```

2. **Printer queue simulation**  
   models task arrivals, printer service, queue wait times.
   - Demonstrates throughput, latency, and capacity planning.
   - Shows effect of pages-per-minute on average wait and backlog.

```cpp
class Printer {
public:
    Printer(int ppm) : pageRate(ppm), timeRemaining(0), currentTask(nullptr) {}
    void tick() {
        if (currentTask != nullptr) {
            timeRemaining--;
            if (timeRemaining <= 0) currentTask = nullptr;
        }
    }
    bool busy() { return currentTask != nullptr; }
    void startNext(Task* newTask) {
        currentTask = newTask;
        timeRemaining = (newTask->getPages() * 60) / pageRate;
    }
private:
    int pageRate, timeRemaining;
    Task* currentTask;
};
```

### 3.6 Deque (double-ended queue)
#### Concept
- Insert/remove at both front and back.
- Hybrid flexibility of stack + queue behavior.

#### Core ADT operations
- `push_front`, `push_back`, `pop_front`, `pop_back`, `empty`, `size`

#### STL usage
- `std::deque`

#### Typical use case
- **Palindrome checking**:
  compare front and back characters iteratively until mismatch or center reached.

```cpp
#include <deque>

bool palchecker(string aString) {
    std::deque<char> chardeque;
    for (char ch : aString) {
        chardeque.push_back(ch);
    }

    bool stillEqual = true;
    while (chardeque.size() > 1 && stillEqual) {
        char first = chardeque.front();
        chardeque.pop_front();
        char last = chardeque.back();
        chardeque.pop_back();
        if (first != last) {
            stillEqual = false;
        }
    }
    return stillEqual;
}
```

### 3.7 Performance themes in linear structures
- ADT behavior is conceptual; performance depends on implementation.
- In STL:
  - stack/queue/deque provide appropriate constant-time end operations for their intended patterns.
- Choosing the "right end-access model" (single-end, opposite-ends, both-ends) is central to clean and efficient algorithms.

### 3.8 Chapter 3 high-value takeaways
- Identify ordering policy first (`LIFO`, `FIFO`, or two-ended).
- Let ADT operations mirror problem rules directly.
- Simulations are practical tools for "what-if" decisions in systems.
- Expression parsing/evaluation is one of the most important classic applications of stacks.

---

## Cross-Chapter Synthesis (1 -> 2 -> 3)

1. **Chapter 1** gives the mindset: abstraction, ADTs, and C++ foundations.  
2. **Chapter 2** gives the measuring stick: Big-O and operation-level analysis.  
3. **Chapter 3** applies both: concrete ADTs (stack/queue/deque) solving real algorithmic problems.

Together, these chapters establish the core workflow of data-structures thinking:
- model the problem with the right abstraction,
- choose an implementation-aware ADT,
- analyze operations using asymptotic growth,
- validate behavior with examples/simulations.

---

## Quick Review Checklist

- Can you explain the difference between an ADT and a data structure?
- Can you identify dominant terms and simplify to Big-O?
- Can you classify code snippets as `O(1)`, `O(n)`, `O(n^2)`, or `O(log n)`?
- Can you decide when stack vs queue vs deque is the best fit?
- Can you convert infix to postfix and evaluate postfix by hand?
- Can you reason about time-space trade-offs in algorithm selection?

