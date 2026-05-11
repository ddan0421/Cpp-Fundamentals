# Unit 8 — More Classes & Objects (Advanced OOP in C++)

A consolidated reference of the advanced object-oriented concepts covered in this unit, with examples drawn from notes (`01-more-oop.cpp`), the auto-graded `Artifact` assignment, and the `Unit8_Assignment_Dan/` lab files.

---

## 1. Instance vs. Static Members

| Kind | Belongs to | Memory | Access |
| --- | --- | --- | --- |
| **Instance variable** | each individual object | one copy per object | `obj.x` |
| **Static variable** | the class itself | **one copy shared** by all objects | `ClassName::x` |
| **Static member function** | the class itself | — | callable **before any object exists**; can only access static data |

**Access rules to remember:**

- A **non-static** member function *can* access static data members (it has access to everything in the class).
- A **static** member function *cannot* access non-static data members — it has no `this` pointer, so there is no specific object to read from.

### Static variable example (`Tree.h` / `tree_main.cpp`)

```6:12:08-more-classes-objects/Unit8_Assignment_Dan/Tree.h
class Tree {
private:
  static int objectCount; // Static member variable
public:
  Tree() { objectCount++; }
  static int getObjectCount() { return objectCount; }
};
```

Static members **must be defined outside the class**:

```15:15:08-more-classes-objects/Unit8_Assignment_Dan/Tree.h
int Tree::objectCount = 0;
```

Each new `Tree` increments the shared counter — `objectCount` is *not* tied to an instance, it belongs to the class.

### Static member function

A `static` function can be called without an object (`Car::getCount()`) but **may only touch static data**.

---

## 2. Friend Functions and Friend Classes

A **friend** is not a member of the class, yet it is granted access to the class's private members. Declared with the `friend` keyword inside the class.

- Friend can be a free function, a member function of another class, or an entire class.

### Friend function (`MyClass.cpp`)

```5:17:08-more-classes-objects/Unit8_Assignment_Dan/MyClass.cpp
class MyClass {
private:
  int value;

public:
  MyClass(int v) : value(v) {}
  friend void showValue(MyClass &obj);
};

void showValue(MyClass &obj) {
  obj.value = 2; // update the private variable
  cout << "Value: " << obj.value << endl;
}
```

`showValue` is not a member of `MyClass`, but the `friend` declaration lets it read and modify `value` directly.

### Friend class

```cpp
class NewClass {
private:
    int secret = 42;
    friend class FriendClass; // entire class is a friend
};
```

---

## 3. Memberwise Assignment

C++ lets you assign one object to another with `=`; by default it copies **member-by-member**.

```cpp
Rectangle box1(10.0, 20.0);
Rectangle box2(5.0, 5.0);
box2 = box1;   // each field of box1 is copied into box2
```

This default works for plain data, but **breaks for pointers** (see Copy Constructor).

---

## 4. Copy Constructor — Shallow vs. Deep Copy

A **copy constructor** is invoked when a new object is initialized from an existing object of the same type.

```cpp
ClassName(const ClassName& other);
```

It is called automatically when:

- `Box b2 = b1;`
- An object is passed by value
- An object is returned by value

### Shallow copy (the danger)

```cpp
class Box {
public:
    int* value;
    Box(int v)              { value = new int(v); }
    Box(const Box& other)   { value = other.value; } // ❌ copies the pointer (address)
    ~Box()                  { delete value; }
};
```

Both `b1` and `b2` end up pointing to the **same memory**. When destructors run, the same address is `delete`d twice → undefined behavior.

### Deep copy (the fix) — same `Box` pattern

```cpp
class Box {
public:
    int* value;
    Box(int v)              { value = new int(v); }
    Box(const Box& other)   { value = new int(*other.value); } // ✅ new heap int, copy value
    ~Box()                  { delete value; }
};
```

Allocating fresh memory and copying the *pointed-to value* keeps the two objects independent — each destructor `delete`s its own block.

### Another deep-copy example — `Number.cpp`

```5:18:08-more-classes-objects/Unit8_Assignment_Dan/Number.cpp
class Number {
private:
    int* value;
public:
    Number(int v) {
        value = new int(v);
    }
    Number(const Number& obj) { // Copy constructor
        value = new int(*obj.value);
    }
    ~Number() { delete value; }
    void setValue(int v) { *value = v; }
    int getValue() const { return *value; }
};
```

Same idea as `Box`: the copy constructor duplicates the integer on the heap so `num1` and `num2` never share one `int*`.

---

## 5. Operator Overloading

Operator overloading lets you redefine what built-in operators (`+`, `-`, `<<`, `=`, …) mean for your own classes. Because they work with programmer-defined data types, overloaded operators are sometimes simply called **operator** functions — the function name is literally the keyword `operator` followed by the symbol (e.g. `operator+`).

**Two rules that always hold when overloading:**

1. You **cannot change the number of operands** the operator takes (a binary operator stays binary, a unary one stays unary).
2. You cannot invent new operators or change operator precedence.

### Arithmetic operator overload — `Point2D.cpp`

```7:22:08-more-classes-objects/Unit8_Assignment_Dan/Point2D.cpp
class Point2D {
private:
    int x, y;
public:
    Point2D(int xVal, int yVal) : x(xVal), y(yVal) {}
    double operator-(const Point2D& right) {
        return sqrt(pow((x - right.x), 2) + pow((y - right.y), 2));
    }
    Point2D operator+(const Point2D& right) {
        return Point2D(x + right.x,  y + right.y);
    }    

    string printPoint2D(){
        return "point is (" + to_string(x) + ", " + to_string(y) + ")"; 
    }
};
```

`point1 - point2` calls `operator-` and yields the **distance** between the two points. `point1 + point2` calls `operator+` and yields a **new `Point2D`** whose coordinates are the sums of `x` and `y` (vector addition), not another distance.

### Stream insertion and extraction (`<<` / `>>`) — `Artifact` / `auto_graded_assignment_1.cpp`

By default, the **stream insertion** (`<<`) and **stream extraction** (`>>`) operators are only defined for built-in types. **Overloading** them for a class like `Artifact` lets your objects use **`cout`** and **`cin`** with the same readable syntax as `int` or `string`, and supports **chaining** several reads or writes in one expression. The usual rules and rationale are summarized well in [GeeksforGeeks — Overloading stream insertion operators in C++](https://www.geeksforgeeks.org/cpp/overloading-stream-insertion-operators-c/):

- **Return the stream by reference** (`ostream&` or `istream&`) so the result of one `<<` or `>>` becomes the left-hand operand of the next — that is what makes **`cout << a << b`** or **`cin >> a >> b`** work.
- **Pass the stream by reference** — `istream` and `ostream` are **not copyable**; value parameters would try to copy them.
- **Pass the object by reference** — avoid copying something you are only printing or filling in.
- Use **`const`** for the object in **`operator<<`** (output must not logically change what you are printing). Use a **non-const** object in **`operator>>`** (input **must** modify the object to store the values read).
- Implement **`operator<<`** and **`operator>>`** as **non-member functions** (often **`friend`**s if they need direct access to **`private`** members). As [GeeksforGeeks](https://www.geeksforgeeks.org/cpp/overloading-stream-insertion-operators-c/) explains, an expression like **`cout << art`** has **`ostream`** on the **left**, not your class, so these operators cannot be ordinary **member** functions of `Artifact` — you would have to add them to `ostream` / `istream`, which you do not control. A **free function** with two parameters matches how the compiler calls them: **`operator<<(cout, art)`** and **`operator>>(cin, art)`**.

Your **`Artifact`** overload uses **public getters** for **`operator<<`**, so **`friend`** is not required there.

---

#### What the `&` means (`ostream&`, `istream&`, …)

In a **declaration**, a type followed by **`&`** is a **reference** (an alias to an existing object), not a copy. Spacing is style-only: **`ostream&`**, **`ostream &`**, and **`ostream &operator<<`** are equivalent. Do **not** confuse this with unary **`&`** in an *expression* (e.g. **`&x`**), which means “address of” and yields a pointer.

**Streams:** **`istream`** and **`ostream`** are **non-copyable**. Parameters and return types must be **references** (e.g. **`ostream& os`**, **`return os`**) so you never copy the stream and chaining still refers to the **same** `cout` or `cin`.

**Recap for `<<`:** first parameter **`ostream&`** (left operand); second **`const`** object (right operand, not mutated); return **`ostream&`**.

**Recap for `>>`:** first parameter **`istream&`**; second **non-const** object (it is **filled in**); return **`istream&`**.

---

#### Output — `operator<<` (assignment file)

The compiler rewrites **`cout << art`** as **`operator<<(cout, art)`** — same idea as the comment in your file:

```91:101:08-more-classes-objects/auto_graded_assignment_1.cpp
/*
When you write: cout << "hello"; the compiler turns it into:
cout.operator<<("hello"); (this uses built-in overloads provided by the standard
library)

cout is an object of type ostream. So cout is an instance of a class ostream

so when you overload << for a custom type, you define a function like:
operator<<(ostream& os, const Artifact& artifact); and then the expression:
cout << artifact becomes operator<<(cout, artifact);
*/
```

Write to **`os`** so the overload works for **`cerr`**, **`ofstream`**, or any **`ostream`**, not only **`cout`**.

```102:106:08-more-classes-objects/auto_graded_assignment_1.cpp
ostream &operator<<(ostream &os, const Artifact &obj) {
  os << "Name: " << obj.getName() << ", Category: " << obj.getCategory()
     << ", Age: " << obj.getAge() << " years" << endl;
  return os;
}
```

**Chaining:** `cout << "\nArtifact Details:" << endl;` evaluates the first `<<`, gets **`cout`** back by reference, then applies the next `<<`.

```126:133:08-more-classes-objects/auto_graded_assignment_1.cpp
  cout << "\nArtifact Details:" << endl;
  cout << art;

  cout << "\nUpdate artifact's category: ";
  getline(cin, ArtCat);
  art.setCategory(ArtCat);
  cout << "Updated Artifact Details: " << endl;
  cout << art;
```

---

#### `<<` and `>>` with **`friend`** (GeeksforGeeks pattern)

The same article’s **`Complex`** example shows both **insertion** and **extraction** in one place: **`operator<<`** formats **`real`** and **`imag`** for output; **`operator>>`** reads them from input. Because those fields are **`private`**, the class declares both operators as **`friend`** so the non-member functions may touch **`c.real`** and **`c.imag`** directly (no getters/setters required). Adapted from [GeeksforGeeks — Overloading stream insertion operators in C++](https://www.geeksforgeeks.org/cpp/overloading-stream-insertion-operators-c/):

```cpp
class Complex {
private:
    int real, imag;
public:
    Complex(int r = 0, int i = 0) : real(r), imag(i) {}
    friend ostream& operator<<(ostream& out, const Complex& c);
    friend istream& operator>>(istream& in, Complex& c);
};

ostream& operator<<(ostream& out, const Complex& c) {
    out << c.real << " + i" << c.imag;
    return out;
}

istream& operator>>(istream& in, Complex& c) {
    in >> c.real >> c.imag;
    return in;
}
```

**Usage:** `cin >> c1;` becomes `operator>>(cin, c1);` **`cout << c1;`** becomes **`operator<<(cout, c1);`** — same “global / non-member” idea as with **`Artifact`**, but here **`friend`** is what unlocks **`private`** data for both directions.

### The "dummy parameter" — distinguishing prefix from postfix

`++` and `--` come in two flavors: prefix (`++x`) and postfix (`x++`). They have the same name and the same number of real operands, so C++ uses a **dummy parameter** of type `int` purely as a *tag* to tell the two overloads apart.

```cpp
class FeetInches {
public:
    FeetInches operator++();      // prefix:  ++obj
    FeetInches operator++(int);   // postfix: obj++   ← the (int) is the dummy parameter
};
```

The `int` parameter has no name and is never used inside the function body — its only job is to give the postfix version a unique signature. The compiler automatically passes a `0` when you write `obj++`.

---

## 6. The `this` Pointer

Every non-static member function receives a hidden pointer named `this` that points to the object the function was called on.

```cpp
class Test {
private:
    int x;
public:
    Test(int x) {
        this->x = x;   // disambiguate member from parameter
    }
};
```

- `this->x` → the **member variable**
- `x` → the **parameter**

---

## 7. Object Conversion

C++ knows how to convert between built-in types, but not between built-ins and your own classes — you must teach it with a **conversion operator**.

```cpp
class FeetInches {
    int feet, inches;
public:
    FeetInches(int f, int i) : feet(f), inches(i) {}
    operator int() { return feet * 12 + inches; } // conversion to int
};

FeetInches distance(6, 8);
int d = distance;          // calls distance.operator int()
```

---

## 8. Aggregation — "Has-a" Relationship

Aggregation models a **"has-a"** relationship by making one class a *member* of another.

### Example — `Address.cpp`

```6:24:08-more-classes-objects/Unit8_Assignment_Dan/Address.cpp
class Address {
public:
    string city;
    string street;
    int zip;
    Address(string c, string s, int z) : city(c), street(s), zip(z) {}
};

class Person {
private:
    Address address;
public:
    Person(string city, string street, int zip) : address(city, street, zip) {}
    void showAddress() {
        cout << "City: " << address.city << endl; 
        cout << "Street: " << address.street << endl;
        cout << "Zip: " << address.zip << endl;
    }
};
```

A `Person` **has an** `Address`. Note how `Person`'s constructor uses an **initializer list** to construct the contained `Address` — required because `Address` has no default constructor.

Benefits:

- Cleaner, reusable design
- Real-world modeling
- Each class has a single responsibility

---

## 9. lvalues and rvalues

Every expression in C++ is either an **lvalue** or an **rvalue**. Knowing the difference is what makes move semantics make sense.

| Term | What it is | Examples |
| --- | --- | --- |
| **lvalue** | A value that **persists beyond the statement that created it** and has a name/address that other statements can use. Can appear on the left side of `=`. | `x`, `myObj`, `arr[3]`, `*ptr` |
| **rvalue** | A **temporary** value with no name and no persistent address — it disappears at the end of the expression. | `5`, `x + 1`, `square(5)`, the return of a function returning by value |

```cpp
int x = 10;        // x is an lvalue; 10 is an rvalue (a literal temporary)
int y = x + 1;     // y and x are lvalues; (x + 1) is an rvalue
```

### Tracing temporaries — a worked example

```cpp
int square(int a) { return a * a; }

int main() {
    int x = 0;
    x = square(5);       // line in question
    cout << x << endl;
}
```

When `x = square(5);` runs:

1. `square` is **called** and `5` is passed as the argument.
2. It computes `5 * 5` and stores `25` as a **temporary value** (an rvalue — it has no name).
3. That temporary is **assigned (copied) to `x`**.
4. After the assignment, the temporary is **discarded** by the system.

That short-lived `25` is exactly the kind of value that move semantics targets — there's no point in deep-copying something that's about to disappear.

### The role of `&` (ampersand) in references

The `&` symbol in a *type* declares a **reference** — an alias for an existing object. C++11 splits references into two flavors based on what they can bind to:

| Syntax | Name | Binds to |
| --- | --- | --- |
| `T&`  | **lvalue reference** (single ampersand) | named, persistent objects (lvalues) |
| `T&&` | **rvalue reference** (double ampersand) | temporaries / unnamed objects (rvalues) |

```cpp
int  a = 10;
int& lref  = a;     // OK — a is an lvalue
int& bad   = 10;    // ❌ can't bind lvalue ref to a temporary
int&& rref = 10;    // OK — 10 is an rvalue
int&& bad2 = a;     // ❌ can't bind rvalue ref to a named lvalue
```

This is the mechanism that lets the compiler choose between a copy constructor (takes `const T&`) and a move constructor (takes `T&&`) automatically.

---

## 10. Move Semantics — Move Constructor & Move Assignment

Copying a heavy object (one that owns heap memory) is expensive. A **move** *transfers ownership of the resources* from a source object to a target object instead of duplicating them. The source is left in a valid but empty state.

The double ampersand `&&` is the syntactic gateway to move semantics — a parameter declared `T&&` tells the compiler "I will only accept a temporary, and I'm allowed to gut it."

### Move constructor — `Buffer.cpp`

```5:19:08-more-classes-objects/Unit8_Assignment_Dan/Buffer.cpp
class Buffer {
private:
    int* data;
public:
    Buffer(int size) { data = new int[size]; }
    Buffer(Buffer&& other) noexcept : data(other.data) {
        other.data = nullptr;
    }

    int* getPointer() const {
        return data;
    } // Add a getter

    ~Buffer() { delete[] data; }
};
```

Calling `Buffer b = move(a);` **steals** `a`'s pointer:

- `b.data` now holds what was `a.data`
- `a.data` is set to `nullptr` so its destructor doesn't double-free

### Copy vs. Move at a glance

| Operation | Signature | Effect of `a = b;` |
| --- | --- | --- |
| Copy assignment | `MyClass& operator=(const MyClass& other);` | `a` gets a copy of `b`; `b` unchanged |
| Move assignment | `MyClass& operator=(MyClass&& other);` | `a` takes `b`'s data; `b` left in valid empty state |

### Move assignment skeleton

```cpp
MyArray& operator=(MyArray&& other) {
    delete[] data;            // 1. release current resources
    data = other.data;        // 2. steal
    size = other.size;
    other.data = nullptr;     // 3. leave other in safe state
    other.size = 0;
    return *this;
}
```

A common idiomatic implementation is the **swap assignment**: instead of releasing-then-stealing, the move-assignment operator simply *swaps* the members of `*this` with the temporary `other`. Whatever `*this` used to own ends up inside `other`, and `other`'s destructor then cleans it up automatically when the temporary dies.

```cpp
MyArray& operator=(MyArray&& other) noexcept {
    std::swap(data, other.data);
    std::swap(size, other.size);
    return *this;
}
```

### The "Rule of Five"

Any class that owns a pointer / external resource should provide:

1. Destructor
2. Copy constructor
3. Copy assignment operator
4. Move constructor
5. Move assignment operator

---

## 11. `= default` and `= delete`

These let you explicitly control which special member functions the compiler generates.

### `= default` — bring back the compiler-generated version

If you write any custom constructor, the compiler stops generating the default one. Restore it with `= default`:

```cpp
class MyClass {
public:
    MyClass() = default;   // compiler-generated default constructor
    MyClass(int x) {}
};
```

### `= delete` — forbid an operation

```cpp
class FileHandle {
public:
    FileHandle(const FileHandle&) = delete;            // no copy
    FileHandle& operator=(const FileHandle&) = delete; // no copy assign
};
```

Useful for non-copyable resources (file handles, sockets, mutexes) where copying would cause double-close / double-free bugs.

---

## 12. Forward Declarations

A **forward declaration** informs the compiler that a class will be declared later in the program. It's needed when two classes refer to each other, or when a header only needs to know that a type *exists* (e.g. to declare a pointer or reference to it) without seeing its full definition.

```cpp
class Address;            // forward declaration — "Address exists, full definition is coming"

class Person {
    Address* home;        // OK: pointer to an incomplete type is fine
};

class Address {           // full definition follows
    string city;
    string street;
};
```

Without the forward declaration, the compiler would see `Address*` inside `Person` before it has ever heard of `Address` and reject the code.

---

## 13. Putting It All Together — `Artifact` (auto_graded_assignment_1)

The Artifact program exercises many of these concepts in one place:

- **Default + parameterized constructors** (overloaded constructors)
- **Mutators / accessors** with `const` correctness on getters
- **Member initializer list** in the default constructor
- **Operator overloading** of `<<` for formatted output (GeeksforGeeks **`Complex`** example in the summary shows **`>>`** and **`friend`**)
- **Interactive I/O** with `getline`, `cin >>`, and `cin.ignore()` to mix line-based and token-based input

```56:73:08-more-classes-objects/auto_graded_assignment_1.cpp
class Artifact {
private:
  string name;
  string category;
  int age;

public:
  Artifact();
  Artifact(string n, string c, int a);

  void setName(string n);
  void setCategory(string c);
  void setAge(int a);

  string getName() const;
  string getCategory() const;
  int getAge() const;
};
```

```75:75:08-more-classes-objects/auto_graded_assignment_1.cpp
Artifact::Artifact() : name("Unknown"), category("None"), age(0) {}
```

---

## Quick-Reference Cheat Sheet

| Concept | Keyword / Syntax | Use it when… |
| --- | --- | --- |
| Shared class data | `static` member + out-of-class definition | counting instances, app-wide config |
| Access without object | `static` member function | factory helpers, accessing static state |
| Grant private access | `friend` function / class | tight coupling between two collaborating types |
| Copy with owned resources | custom **copy constructor** (deep copy) | class holds raw pointer / dynamic array |
| Cheap transfer | **move constructor** / move assignment + `std::move` | avoid expensive copies of large objects |
| Custom operators | `operator+`, `operator<<`, `operator>>`, `operator int()` | natural syntax for your types |
| Postfix vs. prefix | `operator++(int)` (dummy parameter) | distinguish `obj++` from `++obj` |
| lvalue vs. rvalue reference | `T&` vs. `T&&` | bind to named objects vs. temporaries |
| Self reference | `this->` | resolve name conflicts, return `*this` for chaining |
| "Has-a" modeling | object as a data member | composition of concepts |
| Cross-referencing classes | forward declaration `class Foo;` | break circular header dependencies |
| Force / forbid defaults | `= default`, `= delete` | precise control of special member functions |
