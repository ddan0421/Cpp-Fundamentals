#include <iostream>
using namespace std;

class Rectangle {
public:
  Rectangle(float side_l, float side_w);
  // Constructor allowing a user to input the length and width
  Rectangle();
  // Constructor using default values for both length and width
  void setLength(float side_l);
  void setWidth(float side_w);
  float getLength();
  float getWidth();
  double findArea();
  double findPerimeter();

private:
  float length;
  float width;
};

// The function definitions of the two constructors for the Rectangle class are
// as follows:
Rectangle::Rectangle(float side_l, float side_w) {
  length = side_l;
  width = side_w;
}
Rectangle::Rectangle() {
  length = 1;
  width = 1;
}

// The first constructor allows the user to input a value for both length and
// width at the same time that the object is defined (shown later in the lab).
// The second constructor (the default constructor) sets both length and width
// to 1 whenever the object is defined. Actually they could be set to anything
// that the creator of the class wants to use as a default for an object of the
// class that is not initialized by the user.

// With the use of these constructors, every object of class Rectangle will
// have a value for both length and width. We still keep the two member
// functions setLength and setWidth to allow the user to change the values of
// length and width.
//
// Without a constructor:
// Variables might be uninitialized (garbage values)
// You’d have to manually set everything after creating the object

// A destructor is a member function that is automatically called to destroy an
// object. Just like constructors, a destructor has the same name as the class;
// however, it is preceded by a tilde (~). Destructors are used to free up
// memory when the object is no longer needed. The destructor is automatically
// called when an object of the class goes out of scope. This occurs when the
// function (such as main), where the object is defined, ends. The following
// example shows how constructors and destructors operate.

class Demo {
public:
  Demo();  // Default constructor
  ~Demo(); // Destructor
};
int main() {
  Demo demoObj; // demoObj is defined and invokes
  // the default constructor that
  // prints the message “The constructor has
  // been invoked”
  cout << "The program is now running" << endl;
  return 0;
}

// Now that the main program is over, the object demoObj is no
// longer active. The destructor is invoked and the message
// "The destructor has been invoked" is printed.
//***********************************************************
// The Default Constructor Demo
// Notice that constructors do not have to set member data
// This constructor prints a message that the constructor
// has been invoked.
//***********************************************************
Demo::Demo() { cout << "The constructor has been invoked" << endl; }
//***********************************************************
// The Destructor Demo
// Notice that destructors do not have to print anything but
// this destructor prints the message "The destructor has been
// invoked." The primary purpose of destructors is to free
// memory space once an object is no longer needed.
//************************************************************
Demo::~Demo() { cout << "The destructor has been invoked" << endl; }
