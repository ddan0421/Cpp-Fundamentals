# OOP in C++ — Comprehensive Notes (Chapter 13)

> Compiled from: `01-intro-oop.cpp`, `02-constructor-destructor.cpp`, `03-arrays-of-objects.cpp`, `Rectangle.h/.cpp`, `main.cpp`, `auto_graded_assignment_1.cpp`, `Unit7_Assignment_Dan/*`, the lab PDF (`Unit7-Lab08_Instructions.pdf`), and the chapter PowerPoint (`SOW_C++_CSO_Chapter_13_10e.ppt`).

---

## Table of Contents

1. [Procedural vs. Object-Oriented Programming](#1-procedural-vs-object-oriented-programming)
2. [Core OOP Terminology](#2-core-oop-terminology) — incl. [2.1 Object-Oriented Analysis Steps](#21-object-oriented-analysis--the-high-level-steps)
3. [Declaring a Class](#3-declaring-a-class)
4. [Access Specifiers: `public` and `private`](#4-access-specifiers-public-and-private) — incl. [4.1 Mixed access specifiers in one class](#41-mixed-access-specifiers-in-one-class-a-common-quiz-trap)
5. [Defining Member Functions — the Scope Operator `::`](#5-defining-member-functions--the-scope-operator-)
6. [`const` Member Functions, Accessors, and Mutators](#6-const-member-functions-accessors-and-mutators)
7. [Creating Objects and Using the Dot Operator](#7-creating-objects-and-using-the-dot-operator)
8. [Avoiding Stale Data](#8-avoiding-stale-data)
9. [Pointers to Objects and the Arrow Operator `->`](#9-pointers-to-objects-and-the-arrow-operator-)
10. [Dynamically Allocating Objects with `new`/`delete`](#10-dynamically-allocating-objects-with-newdelete)
11. [Why Have Private Members? Data Hiding](#11-why-have-private-members-data-hiding)
12. [Separating Specification from Implementation (three-file model)](#12-separating-specification-from-implementation-three-file-model)
13. [Include Guards (`#ifndef` / `#define` / `#endif`)](#13-include-guards-ifndef--define--endif)
14. [Inline Member Functions and Tradeoffs](#14-inline-member-functions-and-tradeoffs)
15. [Constructors](#15-constructors)
16. [In-Place Initialization (C++11)](#16-in-place-initialization-c11)
17. [Default Constructors](#17-default-constructors)
18. [Passing Arguments to Constructors](#18-passing-arguments-to-constructors) — incl. [18.1 Member Initializer Lists](#181-member-initializer-lists)
19. [Destructors](#19-destructors)
20. [Constructors, Destructors, and Dynamically Allocated Objects](#20-constructors-destructors-and-dynamically-allocated-objects)
21. [Overloading Constructors](#21-overloading-constructors)
22. [Constructor Delegation (C++11)](#22-constructor-delegation-c11)
23. [One Default Constructor, One Destructor](#23-one-default-constructor-one-destructor)
24. [Member Function Overloading](#24-member-function-overloading)
25. [Private Member Functions](#25-private-member-functions)
26. [Arrays of Objects](#26-arrays-of-objects)
27. [UML Class Diagrams](#27-uml-class-diagrams)
28. [Putting It All Together — The Full Rectangle Three-File Project](#28-putting-it-all-together--the-full-rectangle-three-file-project)
29. [Quick Reference — Fill-in-the-Blanks](#29-quick-reference--fill-in-the-blanks)

---

## 1. Procedural vs. Object-Oriented Programming

**Key difference — in two parts:**

1. **Where data and code live** — In procedural programming, **data and functions are separate** (data sits in variables/structures; functions are written apart from that data and act on it from the outside). In OOP, **data and the functions that operate on it are bundled together** in **objects** (defined by **classes**).
2. **How you structure the program** — Procedural programming **tells the computer what to do, step by step** — a sequence of instructions. OOP **models things in the real world** (or the problem you are solving) as **objects** that each **handle their own behavior** through their methods, instead of centralizing all actions in unconnected functions.

| Procedural | Object-Oriented |
|---|---|
| Focuses on the **process / actions** a program performs. | Focuses on **data and the functions that operate on it**, bundled together as objects. |
| Data lives in free-standing variables/structures; functions act on that data separately. | Data and behavior are **encapsulated** in a single unit (a class / object). |
| Scales poorly — when the data layout changes, many functions must change too. | Classes act as re-usable *blueprints*, so changes localize inside a class. |

> An analogy from the lab: a **class is like a plaster-of-Paris mold**; the **object is the figurine** produced from the mold. One mold, many figurines. One class, many objects.

**Limitations of procedural programming (PPT):**

- If the data structures change, many functions must also be changed.
- Programs based on complex function hierarchies are difficult to understand, maintain, modify, and extend, and are easy to break.

---

## 2. Core OOP Terminology

- **Class** — a user-defined Abstract Data Type (ADT). It combines data (**attributes / member variables**) with functions (**methods / member functions**).
- **Object** — a concrete *instance* of a class, with its own copies of the member data. Memory is allocated per object.
- **Instance** — synonym for "object"; stresses the link back to the class.
- **Attribute** (C++: *data member*) — a variable declared inside a class representing part of an object's state.
- **Method** (C++: *member function*) — a function inside a class describing something the object can do; can read/modify that object's data.
- **Encapsulation** — bundling data + the operations on it inside one unit.
- **Data hiding** — restricting outside access so users can only go through the class's **public interface**.
- **Public interface** — the set of public members through which client code interacts with an object.

**Class vs. struct (C++):** A `class` is very similar to a `struct` but by default `class` members are **private**, while `struct` members are **public**. Classes also traditionally bundle functions with data; structs traditionally do not.

### 2.1 Object-Oriented Analysis — the high-level steps

Before you start writing classes, you have to decide *what* the classes should be. The standard sequence of **object-oriented analysis** is:

1. **Identify the objects** in the problem domain (the "nouns" — a `Rectangle`, a `SavingsAccount`, an `InventoryItem`).
2. **Define each object's attributes** (the data it holds — a rectangle's `length` and `width`).
3. **Define each object's behaviors** (the operations it supports — `findArea`, `setLength`).
4. **Define the relationships** between objects (does one *contain* another? *use* another? *inherit from* another?).

Only after that do you write the classes, declare data members and prototype member functions, and finally write `main()`. Writing `main()` first and then "figuring out which classes are needed" is backwards — it is the procedural mindset, not the OO one.

---

## 3. Declaring a Class

Basic format (from the PPT):

```cpp
class ClassName
{
    // declaration;
    // declaration;
};   // <-- semicolon is REQUIRED
```

Complete example — a `Rectangle` class:

```cpp
class Rectangle               // Rectangle is the class's identity (name)
{
public:
    void   setLength(float side_l);
    void   setWidth(float side_w);
    float  getLength();
    float  getWidth();
    double findArea();
    double findPerimeter();

private:
    float length;             // member data (attributes)
    float width;
};
```

Two halves of every class:

1. **Member data** — the attributes (`length`, `width`). Usually `private`.
2. **Member functions** — the methods (`setLength`, `findArea`, …). Usually `public`.

---

## 4. Access Specifiers: `public` and `private`

Access specifiers control who may touch a member:

| Specifier | Who can access it |
|---|---|
| `public` | Code **outside** the class (any client). |
| `private` | **Only** other members of the same class. |

PPT rules you should remember:

- Specifiers can appear **in any order** inside a class.
- Specifiers can appear **multiple times**.
- If you write no specifier inside a `class`, the **default is `private`**.

Typical convention: data is `private`, functions are `public`. Clients then interact **only** through public member functions — which is the **public interface**.

### 4.1 Mixed access specifiers in one class (a common quiz trap)

Because specifiers can appear **in any order** and **multiple times**, each specifier applies only to the members listed **below it, until the next specifier changes the access level**. That means a single class can easily have some data members that are `public` and some that are `private`:

```cpp
class Point {
private:
    double y;
    double z;
public:
    double x;
};
```

Reading this carefully:

- `y` and `z` are under `private:` → **not** accessible outside the class.
- `x` is under `public:` → accessible outside the class.
- `y`, `z`, and `x` are all data members of `Point`.
- The class name is `Point`.

So **all four** of these statements are true at the same time:

1. `z` is not available to code written outside the class.
2. `x`, `y`, and `z` are called members of the class.
3. `x` *is* available to code written outside the class.
4. The name of the class is `Point`.

Moral: when a "which statement is NOT true?" question lists four plausible statements plus a "None of these / All of these are true" option, **verify every statement**. If all four hold, the answer is "All of these are true" — no statement is false.

---

## 5. Defining Member Functions — the Scope Operator `::`

When a member function body is written outside the class, you must tell the compiler which class it belongs to using the **scope-resolution operator** `ClassName::`.

```cpp
void Rectangle::setLength(float side_l) { length = side_l; }
void Rectangle::setWidth (float side_w) { width  = side_w; }

float  Rectangle::getLength()    { return length; }
float  Rectangle::getWidth()     { return width; }

double Rectangle::findArea()       { return length * width; }
double Rectangle::findPerimeter()  { return 2 * length + 2 * width; }
```

Two classes can both have a `setLength` — the `::` makes it unambiguous.

---

## 6. `const` Member Functions, Accessors, and Mutators

A **mutator** (a "setter") stores or changes a value in a private data member. An **accessor** (a "getter") retrieves a value without changing the object. Because accessors do not change the object, they should be marked `const`:

```cpp
float  getLength()   const { return length; }
double findArea()    const { return length * width; }
```

`const` after the parameter list tells the compiler:
> "This function promises not to modify any member variables of the calling object."

If you write `length = 0;` inside a `const` member function the compiler will refuse to compile it. That extra guarantee is why our `Rectangle.h` uses `const` on `getLength`, `getWidth`, `findArea`, and `findPerimeter` but not on `setLength`/`setWidth`.

> From `floatarray.cpp`: `printList()` is `const` (it just reads `values[]` to print), while `getList(ifstream&)` is not `const` because it writes into the array.

---

## 7. Creating Objects and Using the Dot Operator

Defining an object looks like defining a variable; the class is the type:

```cpp
Rectangle box1;      // default-constructed
Rectangle box2;
```

Call a public member with the **dot operator**:

```cpp
box1.setLength(20);
box1.setWidth(5);
cout << box1.getLength();   // 20
```

Attempting `box1.length` directly is a compile error because `length` is `private`.

---

## 8. Avoiding Stale Data

Some "data" is really a calculation from other data. A `Rectangle`'s area is just `length * width`.

- If we stored `area` as a data member and the user later changed `length`, the stored `area` would now be **stale** (out of date).
- The safe pattern is to **compute on demand**: make `findArea()` recalculate each time it is called. Same for perimeter, average, etc.

That is why our `Rectangle` never has an `area` field; it has `findArea()` instead.

---

## 9. Pointers to Objects and the Arrow Operator `->`

You can hold an object's address in a pointer, exactly like any other type:

```cpp
Rectangle box(10.0F, 5.0F);
Rectangle *rPtr = nullptr;   // pointer to Rectangle
rPtr = &box;                 // take the address of an existing object
```

Two equivalent ways to call a member through a pointer:

```cpp
// Long form: dereference, then dot:
(*rPtr).setLength(12.5);

// Short form: the arrow operator is exactly (*p).member
rPtr->setLength(12.5);
cout << rPtr->getLength() << endl;
```

**Mnemonic:** `ptr->member` is shorthand for `(*ptr).member`. Use `->` when you have a pointer; use `.` when you have an actual object.

`nullptr` (C++11) is the preferred null value — safer than the old `NULL` macro.

---

## 10. Dynamically Allocating Objects with `new`/`delete`

`new` allocates an object **on the heap** and returns a pointer to it. When you are done, you must release the memory with `delete`, which also calls the destructor.

```cpp
Rectangle *r = new Rectangle(10.0F, 20.0F);   // ctor runs for *r

r->setLength(15.0F);
cout << r->findArea() << endl;

delete r;        // dtor runs, then memory is released
r = nullptr;     // good habit: avoid a dangling pointer
```

Rules:

1. Every `new` **must** be matched by exactly one `delete` (or `new[]` by `delete[]`).
2. Construction/destruction are tied together:

   - `new Rectangle(a, b)` → the matching constructor runs on the heap object.
   - `delete r` → the destructor runs, then the memory is freed.

This is precisely why a class that allocates resources in its constructor should free them in its destructor — see §19 and §20.

---

## 11. Why Have Private Members? Data Hiding

- `private` members can only be read/modified through the class's `public` member functions.
- Client code must go through that public interface, so the class can validate inputs and enforce invariants (e.g., "width cannot be negative").
- This matches real-world abstraction: a driver does not need to know what happens under the hood of a car, just how to use the pedals. A TV remote user does not need to know IR protocols; they just press buttons.

---

## 12. Separating Specification from Implementation (three-file model)

A typical C++ class lives in **three files**:

| File | Role | Contains |
|---|---|---|
| `Rectangle.h`   | **Specification** (the interface)  | The class declaration — prototypes, member data, `const`-ness. |
| `Rectangle.cpp` | **Implementation**                  | Bodies of the member functions, using `Rectangle::`. Includes `Rectangle.h`. |
| `main.cpp`      | **Client**                          | Uses `Rectangle` objects. Includes `Rectangle.h`. |

Why split it? Changing how a member function works (edit only `.cpp`) does not force recompilation of every client; only `.cpp` files that `#include` the header and use the changed interface need rebuilding.

Build command (from `main.cpp`'s header comment):

```bash
g++ -Wall -Wextra -std=c++17 -o oop_three_file_example main.cpp Rectangle.cpp
./oop_three_file_example
```

Flags at a glance:

- `-Wall -Wextra` — turn on warnings.
- `-std=c++17` — pick the C++ standard.
- `-o name` — name the executable.
- Each `.cpp` is its own *translation unit*; `.h` files are pulled in via `#include`.

---

## 13. Include Guards (`#ifndef` / `#define` / `#endif`)

If two files both `#include "Rectangle.h"`, the class would get declared twice and the compiler would error. Prevent that with an **include guard**:

```cpp
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
    // ...
};

#endif
```

How it works:

- `#ifndef RECTANGLE_H` — "if the macro `RECTANGLE_H` is **not** defined …"
- `#define RECTANGLE_H` — define it the first time through.
- On the second `#include`, the macro already exists, so everything between `#ifndef` and `#endif` is skipped.

(Modern alternative: `#pragma once` at the top of the header — widely supported, but include guards are the most portable option.)

---

## 14. Inline Member Functions and Tradeoffs

If a member function's body is trivial, you can write it **inside** the class declaration. It is then called an *inline member function*:

```cpp
class Rectangle {
private:
    double width = 0.0;
    double length = 0.0;
public:
    double getWidth()  const { return width;  }
    double getLength() const { return length; }
    double getArea()   const { return width * length; }
};
```

**Tradeoffs (PPT):**

| Regular member function | Inline member function |
|---|---|
| The compiler stores a return address, allocates memory for local variables, jumps to the function body, then jumps back — small overhead per call. | The compiler copies the function body directly into the call site — no call overhead. |
| Smaller binary, slightly slower per call. | Potentially faster, but may produce a larger executable. |

Rule of thumb: inline only **short** functions (one-line getters/setters).

---

## 15. Constructors

A **constructor** is a member function that is **implicitly invoked** whenever an object is created. Its job is to guarantee the object starts life in a valid state.

Rules (the two things that make a constructor unique):

1. Its name is **exactly the class name**.
2. It has **no return type** (not even `void`).

```cpp
class Rectangle {
public:
    Rectangle(float side_l, float side_w);   // parameterized ctor
    Rectangle();                             // default ctor (no args)
    // ...
private:
    float length;
    float width;
};

Rectangle::Rectangle(float side_l, float side_w) {
    length = side_l;
    width  = side_w;
}

Rectangle::Rectangle() {
    length = 1;     // sensible defaults
    width  = 1;
}
```

Without a constructor, data members start with **garbage** values until a setter is called. Constructors eliminate that risk.

---

## 16. In-Place Initialization (C++11)

Since C++11 you can give a member variable a default value right at its declaration:

```cpp
class Rectangle {
private:
    double width  = 0.0;     // in-place initialization
    double length = 0.0;
public:
    // public member functions appear here…
};
```

If a constructor does not assign those members explicitly, the in-place values take effect. This is terse and less error-prone than writing an almost-empty default constructor.

---

## 17. Default Constructors

A **default constructor** is one that can be called with **no arguments**. Either of the following counts as a default constructor:

```cpp
Rectangle();                          // literally no parameters
Rectangle(double = 0, double = 0);    // every parameter has a default
```

Key facts:

- If you write a class with **no** constructors at all, the compiler synthesizes a trivial default constructor for you that does nothing.
- As soon as you write **any** constructor yourself, the compiler stops writing a default for you — if you still need a no-arg constructor, you must declare it explicitly.
- `Rectangle r;` invokes the default constructor.

---

## 18. Passing Arguments to Constructors

Declare parameters like any other function, and pass arguments when you create the object:

```cpp
// Declaration
Rectangle(double w, double len);

// Definition
Rectangle::Rectangle(double w, double len) {
    width  = w;
    length = len;
}

// Client code
Rectangle r(10, 5);   // invokes Rectangle(double, double)
```

> **Do not** use the dot operator to call a constructor — constructors are invoked only at object creation.

### 18.1 Member Initializer Lists

A **member initializer list** is a comma-separated list that appears between a constructor's parameter list and its body, introduced with a colon `:`. It initializes data members (and base-class sub-objects) **before** the constructor body runs:

```cpp
class Rectangle {
private:
    float length;
    float width;
public:
    Rectangle(float l, float w) : length(l), width(w) {   // member initializer list
        // body can still run extra setup here, but length/width are already set
    }
};
```

Why prefer initializer lists over assignment in the body?

1. **One-step initialization** — `length(l)` *constructs* `length` with the value `l`; the assignment form `length = l;` first default-initializes `length`, then overwrites it.
2. **Required** for `const` data members, reference data members, and data members of a class type that has no default constructor — you cannot assign these in the body.
3. **Clearer intent** — the list literally reads "these are the initial values of my members".
4. Constructor **delegation** (§22) is syntactically a special form of initializer list (`: OtherCtor(args)`).

> Exam-style phrasing: *"You can use the technique known as a member initialization list to initialize members of a class."* — **True.**

---

## 19. Destructors

A **destructor** runs automatically when an object is destroyed (e.g., when it goes out of scope, or when `delete` runs on a heap pointer).

Rules:

- Name is `~ClassName` — a tilde in front of the class name.
- **No return type** and **exactly zero parameters** (not "zero to many" — a destructor takes no arguments at all, which is *why* it cannot be overloaded).
- There is **only one** destructor per class — it **cannot be overloaded**.
- Primary purpose: release any resources (dynamic memory, files, network handles) the object owns.

> Exam-style trap: *"A destructor function can have zero to many parameters."* — **False.** A destructor always has zero parameters.

```cpp
class Demo {
public:
    Demo();         // default constructor
    ~Demo();        // destructor
};

Demo::Demo()  { cout << "The constructor has been invoked"  << endl; }
Demo::~Demo() { cout << "The destructor has been invoked"   << endl; }

int main() {
    Demo demoObj;                           // ctor prints first
    cout << "The program is now running\n"; // middle message
    return 0;                               // dtor runs last
}
```

Order of output:

```
The constructor has been invoked
The program is now running
The destructor has been invoked
```

> From `circles.cpp`, Exercise 4: if `main` creates 4 `Circles` objects, the destructor runs **4 times**, in **reverse order of construction** (last created, first destroyed).

---

## 20. Constructors, Destructors, and Dynamically Allocated Objects

The `new` / `delete` pair ties directly into the ctor/dtor lifecycle:

```cpp
Rectangle *r = new Rectangle(10, 20);  // ctor runs for the new object

// ... use r->... ...

delete r;    // dtor runs, then memory is freed
r = nullptr;
```

This is why classes that allocate dynamic memory **must** provide a destructor that frees it. Otherwise, every `new` without matching cleanup is a memory leak.

---

## 21. Overloading Constructors

A class may have **multiple** constructors, as long as each has a different parameter list (type or count must differ):

```cpp
class Rectangle {
public:
    Rectangle();                         // default
    Rectangle(double);                   // one value → square?
    Rectangle(double, double);           // width and length
};
```

Calls choose the ctor whose parameter list matches:

```cpp
Rectangle a;            // Rectangle()
Rectangle b(5.0);       // Rectangle(double)
Rectangle c(10.0, 4.0); // Rectangle(double, double)
```

**Cannot overload based on return type alone** (constructors have no return type anyway, and regular functions must also differ in parameters). For instance, these two signatures would conflict if both existed:

```cpp
Rectangle(float lengthOnly);   // "just length"
Rectangle(float widthOnly);    // "just width"  <-- ambiguous, same signature
```

The compiler can't tell them apart from the argument list, so you cannot have both.

---

## 22. Constructor Delegation (C++11)

**Constructor delegation** means one constructor reuses another constructor’s logic in the **same** class, so you do not copy the same assignments (or checks) in every overload.

You usually pick one constructor that does the real initialization; the others call it from the **member-initializer list**.

### Example (`Rectangle`)

```cpp
class Rectangle {
private:
    float length;
    float width;

public:
    Rectangle() : Rectangle(0, 0) {}

    Rectangle(float l) : Rectangle(l, 0) {}

    Rectangle(float l, float w) {
        length = l;
        width = w;
    }
};
```

`Rectangle box;` does not run an empty default-constructor body first — it **delegates**: the compiler runs `Rectangle(0, 0)`, which sets `length` and `width` in the two-parameter constructor.

### Without delegation (repetitive)

```cpp
class Rectangle {
private:
    float length;
    float width;

public:
    Rectangle() {
        length = 0;
        width = 0;
    }

    Rectangle(float l) {
        length = l;
        width = 0;
    }

    Rectangle(float l, float w) {
        length = l;
        width = w;
    }
};
```

Same data, but the same assignments appear in multiple constructors; delegation keeps the “real” setup in one place.

### How delegation is written

Delegation **must** appear in the initializer list, not in the constructor body:

```cpp
Rectangle() : Rectangle(0, 0) {}   // correct — delegates before the body runs
```

Wrong (does **not** delegate — it builds a temporary `Rectangle` and discards it):

```cpp
Rectangle() {
    Rectangle(0, 0);   // wrong
}
```

### Rules (short)

1. **Initializer list only** — `Ctor() : OtherCtor(args) { }`; a bare `OtherCtor(args);` in the body is not delegation.
2. **Order** — the delegated-to constructor runs first; then the body of the delegating constructor (if you wrote one) runs (e.g. `Rectangle(float l) : Rectangle(l, 0) { /* body here runs after */ }`).
3. **One target** — you may not list two constructor delegations in the same initializer list.
4. **No cycles** — e.g. `Rectangle()` delegates to `Rectangle(float)` and that constructor delegates back to `Rectangle()` is invalid / nonsensical.

---

## 23. One Default Constructor, One Destructor

Because these two rules coexist:

1. A no-argument constructor is a default constructor.
2. A constructor whose parameters all have default arguments is **also** a default constructor.

The following is illegal — the compiler cannot pick one when you write `Square s;`:

```cpp
class Square {
public:
    Square();                // default constructor #1
    Square(int = 0);         // default constructor #2  <-- compile error
};
```

Similarly, a destructor takes no arguments and cannot be overloaded, so each class has **exactly one** destructor.

---

## 24. Member Function Overloading

Non-constructor member functions can also be overloaded. Again, the parameter lists must differ:

```cpp
void setCost(double);
void setCost(const char*);
```

Same call site, the compiler picks the version whose parameters match the argument types.

---

## 25. Private Member Functions

Not every member function is for the outside world. Sometimes a class needs an internal helper — something the class uses to keep its own state consistent. Make those `private`:

```cpp
class SavingsAccount {
public:
    void deposit(int dollars, int cents);
    void withdraw(int dollars, int cents);

private:
    void normalize();   // helper — not part of the public interface
    int dollars;
    int cents;
};

void SavingsAccount::normalize() {
    dollars += cents / 100;
    cents    = cents % 100;
    if (cents < 0) {
        dollars -= 1;
        cents   += 100;
    }
}
```

`normalize` is called by `deposit` and `withdraw` to keep the internal (dollars, cents) representation canonical. Client code **cannot** call `normalize` directly.

---

## 26. Arrays of Objects

An array of a class type holds that many *separate* objects laid out contiguously in memory. Each slot must be constructed:

```cpp
const int NUMBEROFOBJECTS = 4;

Rectangle box[NUMBEROFOBJECTS];   // box[0] … box[3]
```

Rules:

1. Because no arguments are supplied at the declaration, **each element is default-constructed**. The class therefore **must have a default constructor** or the code will not compile.
2. Element access with the subscript, member access with the dot operator:

   ```cpp
   box[2].setLength(5.0F);
   cout << box[2].getLength();
   ```

3. To call a parameterized constructor per element, use an **initializer list**:

   ```cpp
   InventoryItem inventory[3] = { "Hammer", "Wrench", "Pliers" };
   ```

4. When a constructor takes more than one argument, each element needs function-call notation:

   ```cpp
   InventoryItem inventory[3] = {
       InventoryItem("Hammer",  10),
       InventoryItem("Wrench",   5),
       InventoryItem("Pliers",   3)
   };
   ```

5. You do **not** have to call the same constructor for every element — a mix is fine as long as each element matches some existing constructor.

**Full example — reading into an array of objects (from `inventory.cpp`):**

```cpp
const int NUMOFPROD = 10;

class Inventory {
public:
    void getId(int item);       // sets itemNumber
    void getAmount(int num);    // sets numOfItem
    void display();             // prints both
private:
    int itemNumber;
    int numOfItem;
};

int main() {
    ifstream infile("Inventory.dat");
    Inventory products[NUMOFPROD];   // default-constructed

    int pos = 0, id, total;
    while (infile >> id >> total) {
        products[pos].getId(id);
        products[pos].getAmount(total);
        pos++;
    }
    for (int i = 0; i < NUMOFPROD; i++) {
        products[i].display();
    }
    return 0;
}
```

---

## 27. UML Class Diagrams

**UML (Unified Modeling Language)** provides a set of standard diagrams for graphically depicting object-oriented systems. A **UML class diagram** summarizes a class in **three stacked sections**:

```
+-----------------------------+
|        ClassName            |   <-- 1. class name
+-----------------------------+
|  attributes (member data)   |   <-- 2. fields / data members
+-----------------------------+
|  operations (methods)       |   <-- 3. member functions
+-----------------------------+
```

### 27.1 Access specification notation

- `-` (minus) = **private**
- `+` (plus)  = **public**
- `#` (hash)  = protected *(introduced later; not required for Ch. 13)*

### 27.2 Attribute notation

```
visibility name : type
```

Example for the `Rectangle` class's member data:

```
- width  : double
- length : double
```

### 27.3 Operation / parameter notation

```
visibility name(paramName : paramType, …) : returnType
```

Example for `setWidth`:

```
+ setWidth(w : double) : void
```

### 27.4 The full UML diagram for the `Rectangle` class

Given this C++:

```cpp
class Rectangle {
private:
    double width;
    double length;
public:
    bool   setWidth(double);
    bool   setLength(double);
    double getWidth()  const;
    double getLength() const;
    double getArea()   const;
};
```

The equivalent UML class diagram is:

```
+----------------------------------+
|           Rectangle              |
+----------------------------------+
|  - width  : double               |
|  - length : double               |
+----------------------------------+
|  + setWidth(w : double)  : bool  |
|  + setLength(l : double) : bool  |
|  + getWidth()            : double|
|  + getLength()           : double|
|  + getArea()             : double|
+----------------------------------+
```

### 27.5 Constructors and destructors in UML

Constructors and destructors are shown by name **with no return type** (because they do not have one):

```
+----------------------------------+
|           Rectangle              |
+----------------------------------+
|  - width  : double               |
|  - length : double               |
+----------------------------------+
|  + Rectangle()                   |   <-- default constructor
|  + Rectangle(w : double,         |   <-- overloaded constructor
|              l : double)         |
|  + ~Rectangle()                  |   <-- destructor
|  + setWidth(w : double)  : void  |
|  + setLength(l : double) : void  |
|  + getWidth()            : double|
|  + getLength()           : double|
|  + getArea()             : double|
+----------------------------------+
```

Notice:

- `+ Rectangle()` — default ctor, no `: returnType`.
- `+ ~Rectangle()` — destructor (tilde in front), no return type.
- Every other function lists its parameters and return type.

---

## 28. Putting It All Together — The Full Rectangle Three-File Project

These three files together illustrate almost every topic above: header/implementation/client split, include guards, public interface, private data, parameterized + default constructors, destructor, `const` accessors, arrays of objects, and the dot operator.

**`Rectangle.h` — specification:**

```cpp
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
public:
    Rectangle(float side_l, float side_w);
    Rectangle();
    ~Rectangle();

    void setLength(float side_l);
    void setWidth (float side_w);

    float  getLength()    const;
    float  getWidth()     const;
    double findArea()     const;
    double findPerimeter()const;

private:
    float length;
    float width;
};

#endif
```

**`Rectangle.cpp` — implementation:**

```cpp
#include "Rectangle.h"

Rectangle::Rectangle(float side_l, float side_w) {
    length = side_l;
    width  = side_w;
}

Rectangle::Rectangle() {
    length = 1.0F;
    width  = 1.0F;
}

Rectangle::~Rectangle() {
    // Release resources here if any were acquired by the ctor.
    // No dynamic memory in this example, so the body is empty.
}

void Rectangle::setLength(float side_l) { length = side_l; }
void Rectangle::setWidth (float side_w) { width  = side_w; }

float  Rectangle::getLength() const { return length; }
float  Rectangle::getWidth()  const { return width;  }

double Rectangle::findArea() const {
    return static_cast<double>(length) * static_cast<double>(width);
}

double Rectangle::findPerimeter() const {
    return 2.0 * length + 2.0 * width;
}
```

**`main.cpp` — client:**

```cpp
#include <iostream>
#include "Rectangle.h"
using namespace std;

int main() {
    Rectangle box1;                 // default ctor → 1 x 1
    Rectangle box2(9.5F, 8.5F);     // parameterized ctor

    box1.setLength(20.0F);
    box1.setWidth(5.0F);

    cout << "box1: length=" << box1.getLength()
         << ", width="      << box1.getWidth()
         << ", area="       << box1.findArea()
         << ", perimeter="  << box1.findPerimeter() << "\n";

    // Pointer to object + arrow operator
    Rectangle *p = &box2;
    cout << "box2 via pointer: area=" << p->findArea() << "\n";

    // Dynamic allocation
    Rectangle *r = new Rectangle(10.0F, 12.0F);
    cout << "heap rectangle area: " << r->findArea() << "\n";
    delete r;
    r = nullptr;

    // Array of objects — every element default-constructed
    const int N = 4;
    Rectangle boxes[N];
    for (int i = 0; i < N; i++) {
        cout << "boxes[" << i << "] area = " << boxes[i].findArea() << "\n";
    }
    return 0;
}
```

Build & run:

```bash
g++ -Wall -Wextra -std=c++17 -o rect main.cpp Rectangle.cpp
./rect
```

---

## 29. Quick Reference — Fill-in-the-Blanks

Direct restatements of the pre-lab writing questions — memorize these:

1. A **constructor** is used in C++ to guarantee the initialization of a class instance.
2. A constructor has the **same** name as the class itself.
3. Member functions are sometimes called **methods** in other object-oriented languages.
4. A **destructor** is a member function that is automatically called to destroy an object.
5. To access a particular member function, the code must list the object name and the name of the function separated by a **period** (the dot operator).
6. A **default** constructor has no parameters.
7. A **tilde (`~`)** precedes the destructor name in the declaration.
8. An **inline** member function has its implementation given in the class declaration.
9. In an array of objects, if the default constructor is invoked, then it is applied to **each** object in the array.
10. A constructor is a member function that is **implicitly** invoked whenever a class instance is created.

---

### Appendix A — Quiz Gotchas & Clarifications

A condensed list of the true/false and multiple-choice patterns that the Unit 7 quiz tested — memorize the *reasoning*, not just the answer.

| # | Statement / Question | Answer | Why |
|---|---|---|---|
| 1 | Class objects can be defined prior to the class declaration. | **False** | The compiler has to see the class definition first so it knows the object's size and members. |
| 2 | The constructor function may not accept arguments. | **False** | Constructors *can* accept arguments — that is exactly what a parameterized / overloaded ctor is for. |
| 3 | A destructor function can have zero to many parameters. | **False** | A destructor has **exactly zero** parameters. That is why it cannot be overloaded. |
| 4 | More than one constructor function may be defined for a class. | **True** | Constructors can be overloaded, as long as each has a different parameter list (§21). |
| 5 | More than one destructor function may be defined for a class. | **False** | A class has **exactly one** destructor (§23). |
| 6 | A member initialization list can be used to initialize members of a class. | **True** | See §18.1. |
| 7 | A constructor always has the same name as … | **the class** | By definition. |
| 8 | What is automatically called when an object is destroyed? | **the destructor** | Runs on scope exit or `delete`. |
| 9 | How many default constructors can a class have? | **only one** | Because both `Ctor()` and `Ctor(T = ...)` count as default ctors; having both is ambiguous (§23). |
| 10 | Objects in an array are accessed with … | **subscripts** | `box[2].setLength(5);` — subscript to pick the element, dot to call the method (§26). |
| 11 | The process of OO analysis can be viewed as which steps? | **identify objects, then define each object's attributes, behaviors, and relationships** | See §2.1. |
| 12 | When a member function is defined outside the class declaration, its name must be qualified with … | **the class name, followed by the scope-resolution operator** | `ReturnType ClassName::funcName(...)` (§5). |
| 13 | If a local and global variable share a name, the ___ resolution operator must be used. | **scope** | `::globalVar` reaches the global one; the operator is called the scope-resolution operator. |
| 14 | Tricky *"which statement is NOT true?"* with mixed access sections. | **All of these are true** | See §4.1 — verify every option before picking; classes can freely mix `private:` and `public:` sections. |
| 15 | `double y = 5.70;` inside the class body is an example of … | **in-place initialization** | C++11 feature (§16). |
| 16 | In C++11, one constructor can call another in the same class using … | **constructor delegation** | Delegation is done in the initializer list, not in the body (§22). |
| 17 | Given `myCar` is an instance of `Car` with method `accelerate`, the valid call is … | **`myCar.accelerate();`** | Dot operator for an object. `->` is for pointers, `::` is for scope. |
| 18 | `TestClass` with ctors `TestClass(int)` and `TestClass()`, then `TestClass test;` prints … | **`Hello!`** | `test;` with no arguments invokes the default constructor, which prints `"Hello!"`. |
| 19 | Same class, but `TestClass test(77);` prints … | **`77`** | The `int`-argument constructor runs instead and prints `x`, which is 77. |
| 20 | Private `showVal()` called as `test.showVal();` in `main` … | **The program will not compile** | Private members cannot be accessed through the dot operator from outside the class. |

### Key decoding table — "which operator do I use?"

| You have … | Use | Example |
|---|---|---|
| an object | `.` (dot) | `myCar.accelerate();` |
| a pointer to an object | `->` (arrow) | `pCar->accelerate();` |
| a class/namespace name (to qualify a member or reach a global) | `::` (scope resolution) | `Rectangle::setLength`, `::globalVar` |

Mixing these up is the single most common small-syntax error on the quiz (see Q17, Q12, Q13).

---

### Appendix B — The "Big Picture" Mental Map

```
+-----------------------------------------------------------+
|                 Class (blueprint / ADT)                   |
|  - private data (attributes, hidden)                      |
|  - public member functions (interface)                    |
|  - constructors (build), destructor (tear down)           |
+-----------------------------------------------------------+
           |                                   |
     instantiate                          instantiate
           v                                   v
     Object box1                         Object box2
   (own copy of data)                 (own copy of data)

      Client code uses the public interface:
         box1.setLength(20);
         Rectangle *p = &box2;      // pointer to object
         p->setLength(10);          // arrow operator
         Rectangle *h = new Rectangle(3,4);   // heap
         delete h;                   // runs dtor, frees memory
```

That single mental map — **class is a blueprint, objects are instances, public interface is the only door in, constructors build, destructors clean up, pointers/`new`/`delete` let you work on the heap** — is the foundation of everything else in C++ OOP.
