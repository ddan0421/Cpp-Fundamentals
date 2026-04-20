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
