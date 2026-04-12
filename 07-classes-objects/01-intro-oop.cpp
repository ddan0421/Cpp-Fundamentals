#include <iostream>

using namespace std;

// Procedural programming focuses on the process/actions that occur in a
// program
//
// Object-Oriented programming is based on the data and the functions
// that operate on it.  Objects are instances of ADTs that represent the data
// and its functions
//
// class is an abstract data type (ADT) which is a user defined data type that
// combines a collection of variables and operations
//
//
// A class consists of a name (its identity), its member data which describes
// what it is and its member functions which describe what it does.
//
// class: like a struct (allows bundling of related variables),  but variables
// and functions in the class can have different properties than in a struct
//
// object: an instance of a class, in the same way that a variable can be an
// instance of a struct
//
// In object-oriented programming (OOP), a **class** is a blueprint or template
// used to define the structure and behavior of a type of object. It specifies
// what data the object will store (attributes) and what actions it can perform
// (methods). In C++, a class is declared using the `class` keyword and
// typically contains variables and functions grouped together to model a
// real-world concept.
//
// An **object** is a concrete instance created from a
// class. While a class defines the general idea, an object represents an actual
// usable entity with specific values. When you create an object in C++, memory
// is allocated for it, and it can then be used to access the attributes and
// methods defined in its class.
//
// An **instance** is simply another term for an
// object. Saying that an object is an instance of a class emphasizes that it
// was created from that class. In practice, “object” and “instance” are used
// interchangeably in most programming contexts.
//
// An **attribute** (also called a data member in C++) is a variable defined
// inside a class that represents the state or properties of an object. Each
// object has its own copy of these attributes, allowing different objects of
// the same class to store different data.
//
// A **method** (also called a member function) is a function defined
// inside a class that describes the behaviors or actions an object can perform.
// Methods can access and modify the object’s attributes, allowing the object to
// operate on its own data.
//
//
//
// Data and functions that are defined as public can be directly accessed by
// code outside the class, while functions and data defined as private can be
// accessed only by functions belonging to the class. Usually, classes make data
// members private and require outside access to them through member functions
// that are defined as public. Member functions are thus usually defined as
// public and member data as private.used

// Class declaration (header file)
class Rectangle // Rectangle is the name of the class (its identity).
{
public:
  // The following are labeled as public.
  // Usually member functions are defined public
  // and are used to describe what the class can do.
  void setLength(float side_l);
  // This member function receives the length of the
  // Rectangle object that calls it and places that value in
  // the member data called length.
  void setWidth(float side_w);
  // This member function receives the width of the Rectangle
  // object that calls it and places the value in the member
  // data called width.
  float getLength();
  // This member function returns the length of the Rectangle
  // object that calls it.
  float getWidth();
  // This member function returns the width of the Rectangle
  // object that calls it.
  double findArea();
  // This member function finds the area of the Rectangle object
  // that calls it.
  double findPerimeter();
  // This member function finds the perimeter of the Rectangle
  // object that calls it.

private:
  // The following are labeled as private.
  // Member data are usually declared private so they can
  // ONLY be accessed by functions that belong to the class.
  // Member data describe the attributes of the class
  float length;
  float width;
};

// It is not necessary for someone to understand how a television remote control
// works in order to use the remote to change the stations or the volume. The
// user of the remote could be called a client that only knows how to use the
// remote to accomplish a certain task. The details of how the remote control
// performs the task are not necessary for the user to operate the remote.
// Likewise, an automobile is a complex mechanical machine with a simple
// interface that allows users without any (or very little) mechanical knowledge
// to start, drive, and use it for a variety of functions. Drivers do not need
// to know what goes on under the hood. In the same way, a program that uses
// Rectangle does not need to know the details of how its member functions
// perform their operations.
//
// The use of an object (an instance of a class) is thus separated into two
// parts: the interface (client file) which calls the functions and the
// implementation which contains the details of how the functions accomplish
// their task.

// An object not only combines data and functions, but also restricts other
// parts of the program from accessing member data and the inner workings of
// member functions. Having programs or users access only certain parts of an
// object is called data hiding
//
//
//
// The class declaration is usually placed in the global section of a program or
// in a special file (called a header file). As noted earlier, the class
// declaration acts very much like a prototype or data type for an object. An
// object is defined much like a variable except that it uses the class name as
// the data type. This definition creates an instance (actual occurrence) of the
// class. Implementation of the member functions of a class are given either
// after the main function of the program or in a separate file called the
// implementation file. Use of the object is usually in the main function, other
// specialized functions, or in a separate program file called the client file.

// To access a member function (method) of an object, we use the dot operator,
// just as we do to access data members of structures. The name of the object is
// given first, followed by the dot operator and then the name of the member
// function. The following example shows a complete main function (or client
// file) that defines and uses objects which call member functions.

// Client file
int main() {

  Rectangle box1;
  Rectangle box2;

  box1.setLength(20); // This instruction has the object box1 calling the
  // setLength member function which sets the member data
  // length associated with box1 to the value of 20
  box1.setWidth(5);
  box2.setLength(9.5); // This instruction has the object box2 calling the
  // setLength member function which sets the member data
  // length associated with box2 to the value of 9.5
  box2.setWidth(8.5);
  cout << "The length of box1 is " << box1.getLength() << endl;
  cout << "The width of box1 is " << box1.getWidth() << endl;
  cout << "The area of box1 is " << box1.findArea() << endl;
  cout << "The perimeter of box1 is " << box1.findPerimeter() << endl;
  cout << "The length of box2 is " << box2.getLength() << endl;
  cout << "The width of box2 is " << box2.getWidth() << endl;
  cout << "The area of box2 is " << box2.findArea() << endl;
  cout << "The perimeter of box2 is " << box2.findPerimeter() << endl;
  return 0;
}

//
// Since findArea and findPerimeter must have length and width before they
// can do the calculation, an object must call setLength and setWidth first. The
// user must remember to initialize both length and width by calling both set
// functions. It is not good programming practice to assume that a user will do
// the necessary initialization. Constructors (discussed later) solve this
// problem.
//
//

// As previously noted, the implementation of the member function can be hidden
// from the users (clients) of the objects. However, they must be implemented by
// someone, somewhere. The following shows the implementation of the Rectangle
// member functions.

// Implementation file

//*******************************************************************
// setLength
//
// task: This member function of the class Rectangle receives
// the length of the Rectangle object that calls it and
// places that value in the member data called length.
// data in: the length of the rectangle
// data out: none
//
//********************************************************************

void Rectangle::setLength(float side_l) { length = side_l; }
//*******************************************************************
// setWidth
//
// task: This member function of the class Rectangle receives the
// the width of the Rectangle object that calls it and
// places that value in the member data called width.
// data in: the width of the rectangle
// data out: none
//
//********************************************************************
void Rectangle::setWidth(float side_w) { width = side_w; }

//*******************************************************************
//
// getLength
// task: This member function of the class Rectangle returns
// the length of the Rectangle object that calls it.
// data in: none
// data returned: length
//
//********************************************************************

float Rectangle::getLength() { return length; }
//*******************************************************************
// getWidth
//
// task: This member function of the class Rectangle returns
// the width of the Rectangle object that calls it.
// data in: none
// data returned: width
//
//********************************************************************

float Rectangle::getWidth() { return width; }
//*******************************************************************
// findArea
//
// task: This member function of the class Rectangle
// calculates the area of the object that calls it.
// data in: none (uses the values of member data length &
// width)
// data returned: area
//
//********************************************************************
double Rectangle::findArea() { return length * width; }
//*******************************************************************
// findPerimeter
//
// task: This member function of the class Rectangle
// calculates the perimeter of the object that calls it
// data in: none (uses the values of member data length &
// width)
// data returned: perimeter
//
//********************************************************************
double Rectangle::findPerimeter() { return ((2 * length) + (2 * width)); }

// Notice that in the heading of each member function the name of the function
// is preceded by the name of the class to which it is a member followed by a
// double colon. In the above example each name is preceded by Rectangle::. This
// is necessary to indicate in which class the function is a member. There can
// be more than one function with the same name associated with different
// classes. The :: symbol is called the scope operator. It acts as an indicator
// of the class association.
//
// Usually classes are declared in a header file,
// while member functions are stored in an implementation file and objects are
// defined and used in a client file. These files are often bound together in a
// project. Various development environments have different means of creating
// and storing related files in a project. All could be located in three
// different sections of the same file.
//
//
//
// Accessors and Mutators
// Mutator: a member function that stores a value in a private membner variable,
// or changes its value in some way.
//
// Accessor: function that retrieves a value
// from a private member variable. Accessors do not change an object's data, so
// they should be marked const.
//
//
// Possibly, it's more intuitive to have this order:
// 1. class declaration (header file) (ex. separate header file in .h extension)
// 2. implementation file (ex. Implementation file in .cpp)
// 3. client file (main) (ex. main.cpp that has int main(){})

// Sometimes the implementation of member functions is so simple that they can
// be defined inside a class declaration. Such functions are called inline
// member functions. In the Rectangle class, findArea and findPerimeter are so
// simple that they can be defined in the class declaration as follows:

// double findArea(){ return length * width; }
// double findPerimeter() { return 2 * length + 2 * width; }

// These inline member functions are:
//
// Fully defined inside the class
// Automatically inline
// Already “implemented” → no .cpp version needed
//
//
// Big picture intuition
// Header (.h) → interface + small inline logic
// .cpp file → heavier implementation
// Inline functions blur that boundary for convenience
