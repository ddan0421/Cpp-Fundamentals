#include <iostream>
using namespace std;
// - instance variable: A member variable in a class. Each object has its own
// copy.
// - static variable: one variable shared among all objects of a class.
// - static member function: can be used to access static member variable; can
// be called before any objects are defined
//
class Tree {
private:
  static int objectCount; // Declaration of static member variable
public:
  // Constructor increments the shared count
  Tree() { objectCount++; }

  // Accessor function for objectCount
  int getObjectCount() const { return objectCount; }
};

// Static member function: Static member functions can only access static member
// data
class Car {
public:
  static int count;

  static int getCount() {
    return count; // OK (static accessing static)
  }
};

int Car::count = 0;

// Definition and initialization outside the class
int Tree::objectCount = 0;

int main() {
  Tree oak;
  Tree elm;
  Tree pine;
  cout << "We have " << pine.getObjectCount() << " trees in our program!"
       << endl;

  // static member function example
  cout << Car::getCount() << endl; // called without object

  Car a, b;
  Car::count = 2;

  cout << Car::getCount() << endl; // 2
  return 0;
}

// Friend: A friend function is not a member of the class but has access to its
// private members.

// A friend function can be a stand-alone function or a member function of
// another class It is declared a friend of a class with friend keyword in the
// function prototype

class NewClass {
private:
  int secret = 42;

public:
  // declare entire class as friend
  friend class FriendClass;
};

class FriendClass {
public:
  void revealSecret(NewClass obj) {
    cout << obj.secret << endl; // ✅ allowed
  }
};

// Memberwise Assignment
// Can use = to assign one object to another, or to initialize an object with
// object's data Copies member to member .e.g. instance2 = instance1; means:
// copy all member values from instance 1 and assign to the corresponding member
// variables of instance2; Use at initialization: Rectangle r2 = r1;

// int main() {
//     Rectangle box1(10.0, 20.0);
//     Rectangle box2(5.0, 5.0);
//
//     cout << "Before assignment:" << endl;
//     box1.display();
//     box2.display();
//
//     // Memberwise Assignment happens here
//     box2 = box1;
//
//     cout << "\nAfter box2 = box1:" << endl;
//     box2.display(); // box2 now has the same values as box1
//
//     return 0;
// }

// Copy Constructors
// Special constructor used when a newly created object is initialized to the
// data of another object of same class Default copy constructor copies
// field-to-field Default copy constructor works fine in many cases

/*
class Box {
public:
    int value;

    Box(int v) {
        value = v;
    }

    // Copy constructor
    Box(const Box& other) { //the parameter is another Box object
        value = other.value; //Copy the value from the old object into the new
one. This line value = other.value; is a manual copy. For pointers, not enough
(needs deep copy)
    }
};


int main() {
    Box b1(10);
    Box b2 = b1; // copy constructor is called. Whenever this happens, C++
automatically looks for a copy constructor

    cout << b2.value << endl; // 10
}
*/

/* however, with pointer is a little complicated:
class Box {
public:
    int* value; // pointer to an int. the variable value doest NOT store a
number but the address of a number in memory

    Box(int v) {
        value = new int(v); //input an actual value v and the variable "value"
is the pointer (address) to a new copy of v, not v itself
    }

      // SHALLOW COPY (default-style)
    Box(const Box& other) {
        value = other.value; // ❌ copies address only
    }

    ~Box() {
        delete value;
    }
};

Now copy it
Box b1(10);
Box b2 = b1; // copy constructor. This copies the pointer address, NOT the data
             // b2.value = b1.value.
             // Both objects point to the same memory
             // Modifying one affects the other
             // If you add a destructor then it will destruct both b1 and b2

so: value = other.value; // ❌ shallow copy

The fix:

class Box {
public:
    int* value;

    Box(int v) {
        value = new int(v);
    }

    // DEEP COPY
    Box(const Box& other) {
        value = new int(*other.value); // ✅ copy actual value
    }

    ~Box() {
        delete value;
    }
};

*/

// Operator Overloading
/*
class Complex {
public:
    int real, imag;

    Complex(int r = 0, int i = 0) {
        real = r;
        imag = i;
    }

    // operator overloading for +
    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }
};


Complex c1(2, 3);
Complex c2(1, 4);

Complex c3 = c1 + c2;


This happends internally: c1.operator+(c2);

*/

// The this Pointer
// when you call obj.show(); Inside show(), C++ automatically poasses a hidden
// pointer: this -> points to obj
// So the function can konw whic object is being used.
/*
class Test {
private:
    int x;

public:
    Test(int x) {
        this->x = x;  // disambiguation
    }

    void show() {
        cout << this->x << endl;
    }
};
*/
// this -> x is the object's member variable
// x is the parameter

// Object Conversion
// For your own classes (like FeetInches), C++ has no idea how to convert them.
//
// So you must teach it how using an operator function.
//
/*
class FeetInches {
private:
    int feet;
    int inches;

public:
    FeetInches(int f, int i) {
        feet = f;
        inches = i;
    }

    // conversion operator
    operator int() {
        return feet * 12 + inches;
    }
};

FeetInches distance(6, 8);

int d = distance;   // ← automatic conversion! I need to convert FeetInches →
int. So it looks for a conversion operator 'operator int()'
// so int d = distinace is doing this behind: int d = distance.operator int();

*/

/*
Aggregation: a class is a member of a class
Supports the modeling of ‘has a’ relationship between classes – enclosing class
‘has a’ enclosed class Same notation as for structures within structures

class Engine {
public:
    int horsepower;
};

class Car {
private:
    Engine engine;  // ← aggregation (Car HAS an Engine)

public:
    Car(int hp) {
        engine.horsepower = hp;
    }
};

Cleaner, reusable, and more realistic modeling.
Instead of doing this:
class Car {
    int engineHorsepower;
    int engineCylinders;
};

you can do this:

class Engine {
public:
    int horsepower;
    int cylinders;
};

class Car {
    Engine engine;
};


*/

/*
An lvalue refers to something that exists in memory and has a name (or address).

int x = 10;
x → lvalue (has memory location)
10 → rvalue

Rule of Thumb: If it can appear on the left side of =, it’s usually an lvalue.

An rvalue is a temporary value that doesn’t stick around.


*/

/*

Why Move Assignment exists:
class MyArray {
private:
    int* data;
};

a = b; // Copy assignment. very expensive

Copy Assignment VS Move Assignment

Copy:
MyClass& operator=(const MyClass& other);
a = b;

Before:
a → old data
b → data

After:
a → copy of b's data
b → unchanged



Move:
MyClass& operator=(MyClass&& other);
a = std::move(b);

Before:
a → old data
b → data

After:
a → b's data
b → nullptr



example move assignment:
class MyArray {
private:
    int* data;
    int size;

public:
    // Move assignment operator
    MyArray& operator=(MyArray&& other) {
        // 1. Clean up current object
        delete[] data;

        // 2. Steal resources
        data = other.data;
        size = other.size;

        // 3. Leave other in safe state
        other.data = nullptr;
        other.size = 0;

        return *this;
    }
};





// Copy constructor
MyClass(const MyClass& other);

// Move constructor
MyClass(MyClass&& other);

// Copy assignment
MyClass& operator=(const MyClass& other);

// Move assignment
MyClass& operator=(MyClass&& other);

In any class that contains a pointer or reference to an outside piece of data,
the class should also have: copy constructor move constructor copy assignment
operator move assignment operator


*/

/*
Default keyword:

class MyClass {
public:
    MyClass(int x) {}   // custom constructor
};

// the compiler won't generate a default constructor
MyClass a;  // ❌ error


Fix:
class MyClass {
public:
    MyClass() = default;   // bring it back
    MyClass(int x) {}
};



Delete keyword:
class A {
public:
    A(const A&) = delete;  // no copying allowed
};

A a;
A b = a;   // ❌ compile error


example:
class FileHandle {
public:
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
};

A file handle shouldn’t be copied:

two objects pointing to same file resource
double close → crash

*/
