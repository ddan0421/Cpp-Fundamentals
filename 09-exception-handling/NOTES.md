# Unit 9: Exception Handling and Templates in C++

Comprehensive notes covering exception handling, function templates, and class templates, based on `01-exceptions.cpp`, `02-function-templates.cpp`, and the Unit 9 birthdate-validation assignment.

---

## Part 1: Exception Handling

### 1.1 Why Exceptions?

Exceptions provide a controlled mechanism to:

- Indicate that something **unexpected** has occurred or been detected.
- Allow the program to deal with the problem in a controlled manner instead of crashing.
- Separate the *normal* logic of a program from its *error-handling* logic.

### 1.2 Core Terminology

| Term | Meaning |
| --- | --- |
| **Exception** | An object or value that signals an error. |
| **Throw** | Send a signal that an error has occurred. |
| **Catch / Handle** | Process the exception; interpret the signal. |

### 1.3 Key Words

- `throw` — followed by an argument, used to throw an exception.
- `try` — followed by a block `{ }`, used to invoke code that might throw.
- `catch` — followed by a block `{ }`, used to detect and process exceptions thrown in the preceding `try` block. The catch parameter must match the *type* thrown.

### 1.4 Flow of Control

1. A function that throws an exception is called from within a `try` block.
2. If the function throws, that function terminates and the `try` block is **immediately exited**. The compiler searches the `catch` blocks immediately following the `try` for one that matches the thrown type.
3. If a matching `catch` block is found, it executes. If no matching `catch` exists anywhere up the call stack, the program terminates.

### 1.5 Basic Example: Throwing a String

```cpp
double divide(int numerator, int denominator) {
    if (denominator == 0) {
        string exceptionString = "Error: Cannot divide by zero.\n";
        throw exceptionString;
    }
    return static_cast<double>(numerator) / denominator;
}

int main() {
    int num1, num2;
    double quotient;

    cout << "Enter two numbers: ";
    cin >> num1 >> num2;

    try {
        quotient = divide(num1, num2);
        cout << "The quotient is " << quotient << endl;
    }
    catch (string exceptionString) {
        cout << exceptionString;
    }

    cout << "End of the program.\n";
    return 0;
}
```

**What happens:**

1. The `try` block is entered and `divide()` is called.
2. If `denominator != 0`, the result is returned and the `catch` block is skipped.
3. If `denominator == 0`, `divide()` throws a `string`. The function (and the rest of the `try` block) terminates, and execution jumps to the `catch (string …)` block.

### 1.6 Throwing With No Value Used

A `catch` parameter only needs the **type** — the value itself is optional. If you don't need the value, you can leave the parameter nameless:

```cpp
catch (bad_alloc) {
    cout << "Insufficient memory.\n";
}
```

### 1.7 Exception Classes

An exception class can be defined inside another class and thrown as an exception by a member function.

An exception class may have:

- **No members** — used only to signal an error (a "tag" type).
- **Members** — used to pass error data back to the catch block.

A class can define **more than one** exception class.

#### Empty Exception Class — Tag-Style

```cpp
// Rectangle.h
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private:
    double width;
    double length;

public:
    class NegativeSize { };   // empty exception class

    Rectangle() { width = 0.0; length = 0.0; }

    void setWidth(double);
    void setLength(double);

    double getWidth()  const { return width; }
    double getLength() const { return length; }
    double getArea()   const { return width * length; }
};

#endif
```

```cpp
// Rectangle.cpp
void Rectangle::setWidth(double w) {
    if (w >= 0) width = w;
    else        throw NegativeSize();
}

void Rectangle::setLength(double len) {
    if (len >= 0) length = len;
    else          throw NegativeSize();
}
```

```cpp
// main.cpp
try {
    myRectangle.setWidth(width);
    myRectangle.setLength(length);
    cout << "Area: " << myRectangle.getArea() << endl;
}
catch (Rectangle::NegativeSize) {   // fully qualified — nested class
    cout << "Error: A negative value was entered.\n";
}
```

Notice we don't define a parameter name in the `catch` — for an empty class we only care about the *type*. Because `NegativeSize` is nested inside `Rectangle`, we must qualify it with the scope resolution operator: `Rectangle::NegativeSize`.

### 1.8 Extracting Data From an Exception Class

Sometimes you want the exception to carry data back to the handler — e.g., the invalid value the user entered.

```cpp
class NegativeWidth {
private:
    double value;
public:
    NegativeWidth(double val) { value = val; }
    double getValue() const   { return value; }
};
```

Inside the mutator, throw an instance constructed with the offending value:

```cpp
void Rectangle::setWidth(double w) {
    if (w >= 0) width = w;
    else        throw NegativeWidth(w);   // pass invalid value into the exception
}
```

Now the catch block can retrieve the value:

```cpp
catch (Rectangle::NegativeWidth e) {
    cout << "Error: " << e.getValue()
         << " is an invalid value for the rectangle's width.\n";
}
```

The `e` parameter is required here because we need to call the member function `getValue()`.

### 1.9 Unwinding the Stack

Once an exception is thrown, the program **cannot return to the throw point**.

1. **The throw point is a "point of no return."** Execution does not resume after `throw`. Think of it as an emergency exit — you don't go back to finish your coffee.
2. **The throwing function terminates immediately.** It doesn't even finish its own logic. Control jumps back to the caller looking for a matching `try`/`catch`.
3. **All code after the throw inside the enclosing `try` is skipped.** In the Rectangle example, if `setWidth` throws, `setLength` is never called.
4. **Stack unwinding** is the process of popping active functions off the call stack one by one, looking for a matching `catch`. If one is never found, the program terminates.
5. **Automatic destruction of objects (RAII).** Local objects created in the `try` block before the throw have their destructors called as the stack unwinds. This prevents memory leaks and is one of C++'s most powerful features.

### 1.10 Nested `try` / `catch` and Re-throwing

You can place a `try`/`catch` inside another `try`/`catch`. An inner handler can decide *not* to handle the exception and **re-throw** it with a bare `throw;` so that an outer handler gets a chance.

```cpp
// Outer
try {
    doSomething();
}
catch (exception1) { /* handle exception 1 */ }
catch (exception2) { /* handle exception 2 */ }
```

Suppose `doSomething()` calls `doSomethingElse()` which can throw `exception1` or `exception3`:

```cpp
// Inside doSomething — Inner
try {
    doSomethingElse();
}
catch (exception1) {
    throw;                  // rethrow — let the outer handler deal with it
}
catch (exception3) {
    // handle exception 3 here
}
```

Flow when `exception1` is thrown:

1. Inner `catch (exception1)` catches it.
2. It decides not to handle it and executes `throw;`.
3. The outer `catch (exception1)` receives the same exception.

### 1.11 Handling `bad_alloc`

When `new` fails to allocate memory, modern C++ does **not** return `nullptr` — it throws `std::bad_alloc` (defined in `<new>`).

```cpp
#include <iostream>
#include <new>          // bad_alloc
using namespace std;

int main() {
    double *ptr = nullptr;

    try {
        ptr = new double[10000];
        cout << "Memory successfully allocated." << endl;
    }
    catch (bad_alloc) {
        cout << "Insufficient memory.\n";
    }

    if (ptr != nullptr) {
        delete [] ptr;
    }

    return 0;
}
```

### 1.12 The `noexcept` Specifier (C++11+)

`noexcept` declares that a function does **not** throw and does **not** call any function that throws.

```cpp
void sayHello() noexcept {
    cout << "Hello world" << endl;
}
```

Its main purpose is to help the compiler produce **faster executable code** (it can skip the bookkeeping needed for exception propagation).

---

## Part 2: Function Templates

### 2.1 Why Templates?

A **function template** is a *pattern* for a function that can work with many data types. Instead of writing a separate overload for each type, write the function once with a generic type parameter and let the compiler generate the specific versions when needed.

### 2.2 Anatomy of a Template

```cpp
template <typename T>
T times10(T num) {
    return 10 * num;
}
```

- `template <typename T>` — the **template prefix**; `typename` declares a generic data type.
- `T` — the **type parameter**; stands in for whatever real type the caller uses.

### 2.3 Calling a Template Function

You call it like a normal function — the compiler **deduces** the type from the argument:

```cpp
int    ival = 3;
double dval = 2.55;

cout << times10(ival) << endl;   // 30
cout << times10(dval) << endl;   // 25.5
```

In the background the compiler effectively writes:

```cpp
int times10(int num)       { return 10 * num; }
double times10(double num) { return 10 * num; }
```

### 2.4 Overloading Templates

Templates can be overloaded as long as each version has a **unique parameter list**:

```cpp
template <typename T>
T sumAll(T num);

template <typename T1, typename T2>
T1 sumAll(T1 num1, T2 num2);
```

### 2.5 Rules of the Road

- Every type listed in the template prefix must be **used** in the template definition.
- A function call must supply arguments for **all** types in the prefix (so they can be deduced).
- Like normal functions, templates must be **defined before being called**.
- A function template is just a *pattern* — no machine code is produced until it is called. A template that is never called consumes **no memory**.
- When passing a class object to a template, every operator the template uses must be **defined or overloaded** in that class.

### 2.6 How to Approach Writing a Template

1. First, write the function using **concrete** data types (e.g., `int` everywhere).
2. Get it working and tested.
3. Convert it to a template:
   - Add the template prefix `template <typename T>`.
   - Replace the concrete type names with the type parameter `T`.

This is the safest path: solve the problem for one type, then generalize.

---

## Part 3: Class Templates

### 3.1 Concept

Just like functions, **classes** can be parameterized over types. When you create an object, you supply the actual type to be used for the class's data members.

```cpp
template <typename T>
class grade {
private:
    T score;
public:
    grade(T);
    void setGrade(T);
    T    getGrade();
};
```

### 3.2 Instantiating Class Templates

Unlike function templates, the type **must be supplied explicitly** at object definition time:

```cpp
grade<int>    testList[20];
grade<double> quizList[20];
```

Once defined, they are used like ordinary objects.

### 3.3 Class Templates and Inheritance

A class template can inherit from another class template. The type parameter `T` must be passed through everywhere the base class name appears in the derived class:

```cpp
template <typename T>
class Rectangle { /* ... */ };

template <typename T>
class Square : public Rectangle<T> { /* ... */ };
```

---

## Part 4: Unit 9 Assignment — Birthdate Validator

### 4.1 The Problem

Prompt the user for a date of birth in `month-day-year` numeric form (e.g., `8-27-1980`) and output it in long form (e.g., `August 27, 1980`).

Requirements:

- Define **at least two exception classes**: `InvalidDay` and `InvalidMonth`.
- If the user enters an invalid day, throw and catch an `InvalidDay`.
- If the user enters an invalid month, throw and catch an `InvalidMonth`.
- Read **at least 10 valid birthdates**, store the **years only** in a `vector<int>`, sort them, and display.
- Use the signature: `string convertDate(string dateOfBirth, vector<int>& years);`.

### 4.2 Exception Classes With Data Members

Both exception classes follow the "carry data to the handler" pattern from §1.8. They each hold a message string and expose it through `getMessage()`.

```cpp
// InvalidDay.h
class InvalidDay {
private:
    string message;
public:
    InvalidDay(const string &msg) { message = msg; }
    string getMessage() const { return message; }
};
```

```cpp
// InvalidMonth.h
class InvalidMonth {
private:
    string message;
public:
    InvalidMonth(const string &msg) { message = msg; }
    string getMessage() const { return message; }
};
```

This lets the `throw` site build a context-rich error string and the `catch` site display it.

### 4.3 Validating the Month

```cpp
int checkMonth(const string &ms) {
    int month = stoi(ms);
    if (month < 1 || month > 12)
        throw InvalidMonth("Month cannot be smaller than 1 or larger than 12!");
    return month;
}
```

The function converts the string to an int and throws a fully-constructed `InvalidMonth` carrying a descriptive message.

### 4.4 Validating the Day (with Leap Year)

```cpp
int checkDay(const string &ds, const int &y, const int &m) {
    int day = stoi(ds);
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
        daysInMonth[2] = 29;        // leap-year February
    }

    if (day < 1 || day > daysInMonth[m])
        throw InvalidDay("Day cannot be smaller than 1 or larger than " +
                         to_string(daysInMonth[m]) + " when month is " +
                         to_string(m) + " in the year " + to_string(y));
    return day;
}
```

Notice index `0` is a sentinel (`"deadbeef"`-style) so months map naturally `1..12`.

### 4.5 `convertDate` — Tying It Together

```cpp
string convertDate(string dateOfBirth, vector<int> &years) {
    stringstream ss(dateOfBirth);
    string monthString, dayString, yearString;
    int month, day, year;
    string monthList[] = {"deadbeef", "January",  "February", "March",
                          "April",    "May",      "June",     "July",
                          "August",   "September","October",  "November",
                          "December"};

    getline(ss, monthString, '-');
    getline(ss, dayString,   '-');
    getline(ss, yearString);

    year = stoi(yearString);

    try {
        month = checkMonth(monthString);
    } catch (const InvalidMonth &e) {
        return "Error: " + e.getMessage();
    }

    try {
        day = checkDay(dayString, year, month);
    } catch (const InvalidDay &e) {
        return "Error: " + e.getMessage();
    }

    years.push_back(year);

    string dateOutputFormat =
        monthList[month] + " " + dayString + ", " + yearString;

    return "This Date " + dateOutputFormat +
           " is valid and add the year to the vector! ";
}
```

Key design points:

- Uses `stringstream` + `getline(..., '-')` to split the input on `-`.
- Two separate `try`/`catch` blocks — one per validation step. This means a bad month doesn't even attempt the day check.
- Catches by `const &` — the conventional, efficient way to catch exception objects (no copy, no slicing).
- Only pushes the year to the vector **after** both validations succeed.

### 4.6 Sort + Display

A simple selection sort orders the collected years ascending:

```cpp
void selectionSort(vector<int> &years) {
    int elems = years.size();
    int minIndex, minValue;

    for (int i = 0; i < elems; i++) {
        minIndex = i;
        minValue = years[i];
        for (int j = i + 1; j < elems; j++) {
            if (years[j] < minValue) {
                minIndex = j;
                minValue = years[j];
            }
        }
        int temp = years[i];
        years[i] = minValue;
        years[minIndex] = temp;
    }
}
```

The driver loop in `main` keeps reading dates until the sentinel `-99` is entered, then sorts and prints all valid years.

### 4.7 Lessons This Assignment Reinforces

- **Define exception classes that carry data** so the handler can produce useful, contextual messages.
- **Catch by `const` reference** (`catch (const InvalidDay &e)`) — best practice for class-based exceptions.
- **Localize `try`/`catch` to the smallest meaningful scope** — separate try blocks for month and day validation give cleaner control flow.
- **Do work conditional on success** — only mutate `years` after validation passes. Exceptions help keep program state consistent.
- **Combine units of the course** — selection sort (Unit 6), vectors (Unit 5), and stringstream parsing all show up alongside the new exception material.

---

## Quick Reference Cheat Sheet

```cpp
// 1. Throw a built-in type
if (bad) throw "message";

// 2. Throw a custom exception class with data
class MyError {
    string msg;
public:
    MyError(const string& m) : msg(m) {}
    string what() const { return msg; }
};
if (bad) throw MyError("details here");

// 3. Try / catch (catch by const reference)
try {
    riskyCall();
}
catch (const MyError& e) {
    cout << e.what();
}
catch (bad_alloc) {           // out of memory
    cout << "no memory";
}

// 4. Re-throw from a nested handler
catch (const SomeError&) {
    throw;                    // let an outer handler take it
}

// 5. Function template
template <typename T>
T maxOf(T a, T b) { return a > b ? a : b; }

// 6. Class template
template <typename T>
class Box {
    T value;
public:
    Box(T v) : value(v) {}
    T get() const { return value; }
};
Box<int>    bi(5);
Box<string> bs("hi");

// 7. noexcept (won't throw)
void greet() noexcept { cout << "hi"; }
```
