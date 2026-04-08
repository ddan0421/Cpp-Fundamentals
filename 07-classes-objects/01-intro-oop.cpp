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
