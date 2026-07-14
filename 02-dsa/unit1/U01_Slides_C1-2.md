# CSC 240 — Unit Summary

**Chapters Covered:**
- Chapter 1: Software Engineering Principles
- Chapter 2: Data Design and Implementation

---

## Chapter 1: Software Engineering Principles

### 1. The Software Process & Engineering
- **Software Engineering**: A disciplined approach to the design, production, and maintenance of computer programs, using tools to manage size/complexity and deliver projects on time and within budget.
- **Software Life Cycle**: Problem analysis → Requirements elicitation → High/low-level design → Implementation → Testing & verification → Delivery → Operation → Maintenance.
- **Life-Cycle Models**:
  - **Waterfall Model** — linear, sequential phases. *Example*: each stage produces documentation that feeds the next, like water cascading down — works only when requirements are well understood and stable.
  - **Spiral Model** — iterative, risk-driven cycles. *Example*: objective-setting, risk assessment, development, and validation are repeated as the project moves from concept to final form, addressing risks (e.g., unneeded features, confusing interfaces) at every loop.

### 2. Programmer's Toolbox
- **Hardware**: Computers and devices. *Example*: laptops, displays, keyboards, trackpads, network interfaces.
- **Software**: OS, IDEs, compilers, debuggers. *Example*: g++ to translate C++ into executable machine code; gdb to step through a crashing program.
- **Ideaware**: Shared programming knowledge — algorithms, methodologies, best practices. *Example*: knowing to use binary search instead of linear search when data is sorted; using UML diagrams and CRC cards to plan a design.
- **Algorithm**: A logical sequence of discrete steps that completely solves a problem in finite time. *Example*: a recipe for baking a cake (mix, bake, cool, ice) — each step is clear, ordered, and finite.

### 3. Goals of Quality Software
1. **It works** — complete and correct per specifications. *Example*: a word processor must update the screen as fast as the user types; if it lags, it fails its requirements.
2. **It can be modified** — readable, well-documented, understandable. *Example*: well-named variables and comments make it easy to fix a bug six months later or for another programmer to update the code.
3. **It is reusable** — extra design effort now saves time later. *Example*: writing a sort routine that takes the desired order (ascending or descending) as a parameter lets you reuse it across many projects.
4. **Completed on time and within budget**. *Example*: a hospital patient-record system must be installed before the hospital opens; missing the deadline costs money and may force monetary penalties from the contract.

### 4. Specifications & Design
- **Specification**: Written document describing *what* a program does (not *how*). *Example*: "Inputs are two integers; output is their greatest common divisor; on bad input, print an error and exit with status 1."
- **Scenario**: A sequence of events describing one full execution. *Example* (ATM): customer inserts card → ATM reads account → asks for PIN → customer enters 5683 → ATM verifies → customer picks "show balance" → ATM displays $1,204.35 → customer quits → ATM returns card.
- **Design Phase**: Decides *how* a program will achieve its specs. *Example*: deciding whether to store ATM accounts in a hash table (fast lookup) or sorted array (compact memory).

### 5. Key Design Concepts (Ideaware)
- **Abstraction**: A model containing only essential details; hides complexity. *Example*: a globe is a sphere even though Earth is actually an oblate ellipsoid — the polar bulge is irrelevant for studying political borders. Likewise, a driver views a car as transportation; a brake engineer views it as a mass with a small contact patch.
- **Information Hiding**: Restricting access to a module's internal details; each module serves one purpose. *Example*: you can stop a car without knowing whether it has disc or drum brakes; you can make a PB&J sandwich without thinking about growing peanuts and wheat.
- **Stepwise Refinement**:
  - *Top-down*: Break problem into pieces, defer details. *Example*: writing a book — first choose the theme, then chapters, then sections, then paragraphs.
  - *Bottom-up*: Build details first, then compose. *Example*: a cookbook author writes individual recipes first, then groups them into chapters.
  - *Functional Decomposition*: View program as cooperating functions. *Example*: `main()` calls `getInput()`, `compute()`, `printResults()`.
  - *Round-trip Gestalt*: Top-down with emphasis on objects/data. *Example*: identify candidate classes (Order, Customer, Invoice), define their relationships, then loop back when internal details reveal new classes.
- **Visual Tools**: UML diagrams, CRC cards. *Example*: a CRC index card has the **Class** name at top, **Responsibilities** (verbs/methods) on the left, **Collaborators** (other classes used) on the right.

### 6. Design Approaches
- **Top-Down Design**: Big-picture → broken into tasks → coded. *Example* (baking a cake): `MakeCake` → `GetIngredients`, `MixIngredients`, `Bake`, `Cool`, `ApplyIcing`; each further refined.
- **Object-Oriented Design**: Break program into *things* (objects/classes) rather than tasks. *Example* (baking a cake): identify classes like `Oven` (attributes: energy source, temp; operations: turn on/off, set temp), `Bowl`, `Egg`, `Baker` that collaborate.
- **Booch's Rule**: Underline *verbs* for procedural, *nouns* for object-oriented. *Example*: in "the **librarian checks out books to patrons**" — nouns (librarian, book, patron) → classes; verb (checks out) → method.

### 7. Verification of Software Correctness
- **Testing**: Run program with input to find errors. *Example*: feed `divide(10, 0)` to confirm it throws instead of crashing.
- **Debugging**: Investigate and remove known errors. *Example*: stepping through with a debugger to find where a counter is off by one.
- **Acceptance Test**: Test in real environment with real data. *Example*: install the new payroll system at the customer's site and process last month's real payroll alongside the old system.
- **Regression Test**: Re-test after modifications. *Example*: after fixing a date-formatting bug, re-run the full test suite to ensure no other features broke.
- **Verification**: "Are we doing the job right?" (matches spec). *Example*: confirming the program correctly computes BMI per the formula in the spec.
- **Validation**: "Are we doing the right job?" (matches purpose). *Example*: realizing the user actually wanted body-fat percentage, not BMI — the spec itself was wrong.

### 8. Types of Errors
- **Specification/Design Errors**: Cheapest to fix early, costliest after deployment. *Example*: a government contractor built a replacement system matching the spec exactly, but the spec was based on flawed documentation of the old system — fixing it cost millions.
- **Compile-Time Errors**: Syntactic; easier to fix. *Example*: missing semicolon, undeclared variable, type mismatch.
- **Run-Time Errors**: Occur during execution; **Robustness** = ability to recover gracefully. *Example*: a word processor catching a "disk full" error and prompting the user to free space, rather than crashing and losing work. Critical software (autopilot, ICU monitor) must be highly robust.

### 9. Designing for Correctness
- **Assertions**: Logical propositions about expected behavior. *Example*: after `sum = part + 1;`, we can assert "sum > part" — provable by logic without running the code (assuming `part != INT_MAX`).
- **Preconditions**: Must be true *before* an operation. *Example*: for `GetLast(list, value)` — precondition: the list is not empty.
- **Postconditions**: Must be true *after* an operation completes (given precondition). *Example*: for `GetLast` — `value` holds the last element, that element is removed, and list length is decremented.
- **Design Review Activities**:
  - *Deskchecking* — trace on paper. *Example*: writing down each variable's value as you walk through a loop by hand.
  - *Walk-through* — team simulates manually. *Example*: the group runs sample inputs through the design on a whiteboard to spark discussion about edge cases.
  - *Inspection* — line-by-line reading with error spotting. *Example*: one team member reads the code aloud while others check off a defect list (uninitialized variables, off-by-one loops, "magic" numbers).

### 10. Program Testing
- **Test Case**: Single test with inputs, expected behavior, observed behavior. *Example*: input `[3, 1, 2]` to `sort()`; expect `[1, 2, 3]`; if you got `[3, 1, 2]`, the test failed.
- **Unit Testing**: Test modules/functions in isolation. *Example*: testing `computeTax()` directly with a few salary values instead of running the whole payroll program.
- **Data Coverage** (Black-box): Test based on inputs (typical + edge cases). *Example*: for `PrintInteger(int)`, test a negative number, zero, and a positive number — three classes of input. For a `bool`, exhaustive testing (`true`, `false`) is feasible.
- **Code Coverage** (White-box): Test branches/paths in the code. *Example*: an `if/else` needs two test cases (one per branch); a `switch` with 4 cases needs at least 4.
- **Test Plan**: Document of cases, purposes, inputs, expected outputs. *Example*: a spreadsheet listing 20 numbered tests for `Stack`, each with input commands, expected stack state, and pass/fail criteria.
- **Test Driver**: Program that executes the test plan. *Example*: a `main()` that loops over commands in `tests.txt` (`Push 5`, `Pop`, `Top`) and writes results to `out.txt`.

### 11. Integration Testing
- **Top-Down Integration**: Test high-level logic first; use **stubs** for low-level modules. *Example*: testing the order-checkout flow while `chargeCreditCard()` is a stub that just prints "charged $X" and returns success.
- **Bottom-Up Integration**: Test lowest modules first using a **test driver**; build up. *Example*: thoroughly test the `LinkedList` class first, then test `Queue` (which uses `LinkedList`), then test the scheduler that uses `Queue`.

### 12. C++ I/O Basics
- Streams via `<iostream>`: `cin`, `cout`, `cerr`.
- **Insertion operator `<<`**: writes to output stream. *Example*: `cout << "Sum = " << sum << endl;`
- **Extraction operator `>>`**: reads from input stream. *Example*: `cin >> intValue >> realValue;` reads an int and a float, skipping whitespace.
- File I/O via `<fstream>`: `ifstream`, `ofstream` — always close files. *Example*: `ifstream in; in.open("input.dat"); in >> x;`
- **Stream Failure**: Silent fail state from bad input, missing files, or write-protected files. *Example*: if `in.open("Data.in")` is misspelled `"In.dat"`, the stream enters the fail state and all later reads are silently ignored — guard with `if (!in) { /* handle */ }`.

---

## Chapter 2: Data Design and Implementation

### 1. Different Views of Data
- Data are the *nouns* of programming — objects manipulated, information processed.
- **Data Abstraction** separates the logical view from the implementation view. *Example*: you use `int` daily without caring whether the CPU stores it as two's-complement in 4 bytes — that detail is hidden.

### 2. Data Abstraction Levels
- **Logical view**: What are the values? What operations exist? *Example* (`int`): values are whole numbers in some range; operations are `+`, `-`, `*`, `/`, `%`, assignment.
- **Implementation view**: How is it stored? How is it coded in C++? *Example*: `int` is stored in one machine word; `+` becomes an assembly `ADD` instruction.

### 3. Data Encapsulation
- Separates representation from applications using the data. *Example*: think of a medicine capsule — you swallow it without knowing the exact chemistry inside; you just know what it does.
- **Abstract Data Type (ADT)**: Operations and values specified independently of implementation. *Example*: a `Stack` ADT has values (a sequence) and operations (`push`, `pop`, `top`, `isEmpty`) — whether it is built on an array or linked list is invisible to the user.
- **Data Structure**: A collection of data elements with operations to store/manipulate them; used to implement ADTs. *Example*: a singly linked list is one *data structure* that can implement the `Stack` ADT.

### 4. Three Levels of Data
| Level | Focus | Question |
|-------|-------|----------|
| **Application** | Problem domain modeling | Real-world context |
| **Logical** | Abstract view of values/ops | "What" |
| **Implementation** | Specific representation | "How" |

**Library Example**:
- *Application*: "Library of Congress" or "Baltimore County Public Library."
- *Logical*: a collection of books with operations — `CheckOut`, `CheckIn`, `Reserve`, `PayFine`, `PayForLostBook`.
- *Implementation*: books arranged by Dewey Decimal across 4 floors and 14 rows; `CheckInBook` checks due date, calculates fines, updates records, and either shelves the book or sets it aside for a reserve hold.

### 5. ADT Operator Categories
- **Constructors** — Create new instances. *Example*: `DateType today;` declares (constructs) a new `Date` object.
- **Transformers** — Change the object's state. *Example*: `stack.push(5)` mutates the stack; binary transformer: `merge(listA, listB) → listC`.
- **Observers** — View state (predicates, accessors, summaries). *Example*: `stack.isEmpty()` (predicate), `stack.top()` (accessor), `stack.size()` (summary).
- **Iterators** — Sequentially process elements. *Example*: `ResetList()` then repeated `GetNextItem()` calls to walk through every element of a list.

### 6. Composite Data Types
- **Unstructured**: Components unorganized (e.g., classes, records). *Example*: `struct Car { int year; string make; float price; };` — fields accessed by name, not position.
- **Structured**: Order/arrangement matters (e.g., arrays). *Example*: `int scores[100];` — element 0 comes before element 1, accessed by integer index.

### 7. Records (Structs)
- Finite collection of named fields, accessed by `mystruct.fieldname`. *Example*: `myCar.price = 20009.33;` or `pricePaid = myCar.price;`.
- Stored contiguously; each member at an offset. *Example*: if `CarType` lays out `year` (1 cell), `maker[10]` (10 cells), `price` (2 cells) and `myCar` starts at address 8500, then `myCar.year` is at 8500, `myCar.maker` at 8501, `myCar.price` at 8511.
- We said that the record is a nonstructured data type, yet the component selector depends on the relative positions of the members of the record. This is true: A record is a structured data type if viewed from the implementation perspective. However, from the user’s view, it is unstructured. The user accesses the members by name, not by position
- Passed to functions by **value** (copy) or **reference** (memory address). *Example*:

```cpp
void AdjustForInflation(CarType& car, float pct) { car.price = car.price * pct + car.price; }  // by reference: modifies caller's car
bool LateModel(CarType car, int year)            { return car.year >= year; }                  // by value: car is a copy
```

### 8. One-Dimensional Arrays
- Finite, fixed-size, ordered, **homogeneous** elements with random access via index. *Example*: `int numbers[10];` declares 10 ints; `numbers[2] = 5;` writes the third slot.
- Always passed **by reference** (use `const` to prevent modification). *Example*: `int SumValues(const int values[], int n)` — `values` cannot be modified inside the function.
- Implementation: `Address = base + index * size_of_element`. *Example*: if `int data[10]` has base 100 and each int is 1 cell, then `data[8]` is at `100 + 8*1 = 108`.

### 9. Two-Dimensional Arrays
- Tables of rows/columns: `table[row][col]`. *Example*: `int grid[3][4];` is a 3-row, 4-column table; `grid[1][2] = 7;` writes row 1, column 2.
- When passing as parameter, must specify second dimension: `int Process(int values[][5])` — the compiler needs the row width to compute offsets.
- **Row-major order** in C++: stored row-by-row in contiguous memory. *Example*: a 2×3 array `a` is laid out as `a[0][0], a[0][1], a[0][2], a[1][0], a[1][1], a[1][2]`.

### 10. C++ Classes
- Encapsulate data + functions that operate on them.
- **Specification** (`.h`) separated from **implementation** (`.cpp`). *Example*:

```cpp
// DateType.h
class DateType {
public:
    void Initialize(int newMonth, int newDay, int newYear);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
private:
    int year, month, day;
};
```

- Use scope resolution `::` to define member functions: `int DateType::GetMonth() const`. *Example*: `void DateType::Initialize(int m, int d, int y) { month = m; day = d; year = y; }`
- **Object/Instance** — a variable of a class type. *Example*: `DateType today; today.Initialize(9, 24, 2003);`
- **Client** — software that uses class instances; needs `#include "ClassName.h"`. *Example*: a `main.cpp` that does `#include "DateType.h"` then `cout << today.GetMonth();`. The client can only call *public* members.
- **`self`** keyword refers to the object on which a method is called. *Example*: in `today.ComparedTo(anotherDay)`, inside `ComparedTo`, `year` refers to `today.year` (self) and `aDate.year` refers to `anotherDay.year` (the parameter).

### 11. Classes vs. Structs
| Feature | Class | Struct |
|---------|-------|--------|
| Default access | Private | Public |
| Typical use | Object with methods | Plain data container |
| Operations | Member functions | Global functions |

*Example*: a `struct Point { double x, y; };` is typically used as plain coordinates passed to a global `distance(a, b)`; a `class BankAccount { ... };` keeps `balance` private and exposes `deposit()`/`withdraw()` as member functions that enforce rules.

### 12. Object-Oriented Concepts
- **Inheritance**: Derived class inherits from base class — an *"is-a"* relationship. *Example*: `Vehicle` → `WheeledVehicle` → `Car` → `SportsCar`. A `Car` *is a* `WheeledVehicle`, which *is a* `Vehicle`.
- **Polymorphism**: Statically/dynamically choose between overloaded functions. *Example*: `Shape* s = new Circle(); s->draw();` — at run time the `Circle::draw` is called even though `s` is typed as `Shape*` (requires `virtual draw()`).
- **Overloading**: Multiple functions sharing a name (unique signatures). *Example*: the built-in `+` is overloaded — `3 + 4` does integer add; `3.0 + 4.0` does floating-point add; the compiler picks based on operand types.
- **Binding**:
  - *Static* — compile time. *Example*: the compiler chooses which overloaded `print(int)` vs `print(string)` to call based on the argument type.
  - *Dynamic* — run time. *Example*: a `virtual area()` call through a `Shape*` is resolved at run time to `Circle::area` or `Square::area` based on the actual object.
- **C++ OOP Constructs**:
  - **Composition** (containment) — class contains object of another class. *Example*: `class PersonType { string name; DateType birthdate; ... };` — a `PersonType` *has a* `DateType`.
  - **Inheritance** — `class Derived : public Base`. *Example*: `class StudentType : public PersonType { string status; ... };` — `student` has `name`, `birthdate` (from `PersonType`), plus `status` of its own.
  - **Virtual Methods** — enable dynamic binding. *Example*: `virtual void Initialize(...)` in the base class so derived overrides are selected at run time.

### 13. Exception Handling
- `try` block contains code that may throw.
- `throw` triggers an exception.
- `catch` handles it gracefully.
- C++ standard library provides many predefined exception classes (`logic_error`, `out_of_range`, `runtime_error`, `overflow_error`, ...).

*Example* (reading and summing only positive values from a file):

```cpp
try {
    infile >> value;
    do {
        if (value < 0)
            throw string("Negative value");
        sum = sum + value;
    } while (infile);
}
catch (string message) {
    cout << message << " found in file. Program aborted.";
    return 1;
}
cout << "Sum of values on the file: " << sum;
```

### 14. Namespaces
- Prevent name clashes between libraries by scoping identifiers. *Example*: two libraries may each define `GetData` — namespaces let both coexist.
- Defined with `namespace myNames { ... }`. *Example*:

```cpp
namespace myNames   { void GetData(int&); }
namespace yourNames { void GetData(int&); }
```

- **Access options**:
  - Scope resolution: `myNames::GetData(x);` — unambiguous, fully qualified.
  - **Using Declaration**: `using myNames::GetData;` — afterward, `GetData(x)` means `myNames::GetData`.
  - **Using Directive**: `using namespace myNames;` — brings in *all* identifiers from the namespace (most prone to clashes).
- Avoid **namespace pollution** — qualify in headers; use directives only inside blocks. *Example*: in a `.h` file always write `std::string`, never `using namespace std;` (which would pollute every file that includes the header).

### 15. Algorithm Analysis & Big-O Notation
- Compare algorithms by **work done in critical loop** as a function of input size N.
- **Big-O**: Expresses complexity by the fastest-growing term, ignoring constants/lower-order terms. *Example*: `f(N) = 2N⁴ + 100N² + 10N + 50` → `O(N⁴)`. The `2` is dropped (constant) and `100N² + 10N + 50` are dropped (lower-order); for large `N` they're noise.

### 16. Common Orders of Magnitude
| Notation | Name | Description |
|----------|------|-------------|
| **O(1)** | Constant | Independent of N |
| **O(log₂ N)** | Logarithmic | Each step halves the work (e.g., binary search) |
| **O(N)** | Linear | Process each element once |
| **O(N log₂ N)** | Linearithmic | Logarithmic op applied N times |
| **O(N²)** | Quadratic | Compare every element with every other |
| **O(N³)** | Cubic | 3D matrix processing |
| **O(2ᴺ)** | Exponential | Computation explodes with input |

*Examples per row*: `O(1)` — `arr[i] = 0;` (direct index); `O(log N)` — binary search; `O(N)` — print every element; `O(N log N)` — Mergesort/Quicksort/Heapsort; `O(N²)` — Bubble/Selection sort, comparing every pair; `O(N³)` — naive multiplication of two N×N matrices; `O(2ᴺ)` — brute-force subset enumeration (so slow that for N = 128 it exceeds the age of the universe).

**Elephants vs. Goldfish analogy**: Lower-order terms are noise compared to the dominant term. *Example*: buying 10 elephants and 10 goldfish — the goldfish price is negligible.

**Sum 1..N — two algorithms**:

```cpp
// Sum1: O(N) — loop
sum = 0;
for (count = 1; count <= n; count++) sum = sum + count;

// Sum2: O(1) — closed-form formula
sum = ((n + 1) * n) / 2;
```

Both produce the same answer, but `Sum2` does the same amount of work whether N = 5 or N = 5,000,000.

### 17. Example: Phone Book Search
- **Linear Search** (Lookup1) — start at the front, check names one by one.
  - Best O(1) (first name), Avg/Worst O(N).
- **Binary Search** (Lookup2, requires sorted data) — check middle, then halve the search area.
  - Best O(1), Avg/Worst O(log₂ N).
- *Concrete comparison*: in a New York City phone book of ~8.5 million people, worst case Linear takes **8,500,000** steps; Binary takes only **24** steps.
- **Takeaway**: Data structures matter — algorithm efficiency depends on how data is organized (Binary search only works because the phone book is sorted).

**Best / Worst / Average case complexity**: many algorithms behave differently depending on input. *Example*: Lookup1 is O(1) if the name is first in the book, O(N) if it is last, O(N/2) → O(N) on average.

---

## Key Themes Across Both Chapters

1. **Abstraction & Encapsulation** — manage complexity by hiding details.
2. **Modularity** — break large problems into small, single-purpose units.
3. **Separation of Concerns** — *what* (spec/logical) vs. *how* (implementation).
4. **Quality through Process** — design, verification, and testing are deliberate phases, not afterthoughts.
5. **Cost of Errors Grows Over Time** — find and fix bugs early.
6. **Object-Oriented Thinking** — model the world as objects with state and behavior.
7. **Choose the Right Data Structure** — efficiency (Big-O) depends on representation.
