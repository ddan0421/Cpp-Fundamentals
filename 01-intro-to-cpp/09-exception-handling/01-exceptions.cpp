#include <iostream>
#include <string>

using namespace std;

/*
Indicate that something unexpected has occurred or been detected␋
Allow program to deal with the problem in a controlled manner␋
Can be as simple or complex as program design requires


Terminology:

Exception: object or value that signals an error

Throw an exception: send a signal that an error has occurred

Catch/Handle an exception: process the exception; interpret the signal


Key Words:
throw – followed by an argument, is used to throw an exception
try – followed by a block { }, is used to invoke code that throws an exception
catch – followed by a block { }, is used to detect and process exceptions thrown
in preceding try block.  Takes a parameter that matches the type thrown.


Flow of Control:

1) A function that throws an exception is called from within a try block
2) If the function throws an exception, the function terminates and the try
block is immediately exited.  A catch block to process the exception is searched
for in the source code immediately following the try block.
3) If a catch block
is found that matches the exception thrown, it is executed.  If no catch block
that matches the exception is found, the program terminates.



*/

// // function that throws an exception
// int totalDays(int days, int weeks) {
//   if ((days < 0) || (days > 7))
//     throw "invalid number of days";
//   // the argument to throw is the
//   // character string
//   else
//     return (7 * weeks + days);
// }
//
// try // block that calls function
// {
//   totDays = totalDays(days, weeks);
//   cout << "Total days: " << days;
// } catch (char *msg) // interpret               //  exception
// {
//   cout << "Error: " << msg;
// }

/*
1) try block is entered.  totalDays function is called

2) If 1st parameter is between 0 and 7, total number of days is returned and
catch block is skipped over (no exception thrown)

3) If exception is thrown, function and
try block are exited, catch blocks are scanned for 1st one that matches the data
type of the thrown exception.  catch block executes

*/
double divide(int, int);
int main() {
  int num1, num2;
  double quotient;

  // Get two numbers.
  cout << "Enter two numbers: ";
  cin >> num1 >> num2;

  // Divide num1 by num2 and catch any potential exceptions
  try {
    quotient = divide(num1, num2);
    cout << "The quotient is " << quotient << endl;
  } catch (string exceptionString) // If the exception is a string, the program
                                  // jumps to this catch clause
  {
    cout << exceptionString;
  }
  cout << "End of the program.\n";

  return 0;
}
double divide(int numerator, int denominator) {
  if (denominator == 0) {
    string exceptionString = "Error: Cannot divide by zero.\n";
    throw exceptionString;
  }
  return static_cast<double>(numerator) / denominator;
}

/*
Predefined functions such as new may throw exceptions
The value that is thrown does not need to be used in catch block.  
in this case, no name is needed in catch parameter definition
catch block parameter definition does need the type of exception being caught

Predefined functions such as new may throw exceptions
The value that is thrown does not need to be used in catch block.  
in this case, no name is needed in catch parameter definition
catch block parameter definition does need the type of exception being caught

*/



/*
An exception class can be defined in a class and thrown as an exception by a member function
An exception class may have:
no members: used only to signal an error
members: pass error data to catch block 
A class can have more than one exception class

*/

// Specification file for the Rectangle class
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
private:
    double width;  // The rectangle's width
    double length; // The rectangle's length

public:
    // Exception class
    class NegativeSize
    { }; // Empty class declaration

    // Default constructor
    Rectangle()
    { 
        width = 0.0; 
        length = 0.0; 
    }

    // Mutator functions, defined in Rectangle.cpp
    void setWidth(double);
    void setLength(double);

    // Accessor functions
    double getWidth() const
    { 
        return width; 
    }

    double getLength() const
    { 
        return length; 
    }

    double getArea() const
    { 
        return width * length; 
    }
};

#endif

//Rectange.cpp
//The NegativeSize class has no members. The only important part of the class is its name,
//which will be used in the exception-handling code

// Implementation file for the Rectangle class.
#include "Rectangle.h"

//*********************************************************
// setWidth sets the value of the member variable width. *
// If the argument is negative, it throws an exception.   *
//*********************************************************

void Rectangle::setWidth(double w)
{
    if (w >= 0)
    {
        width = w;
    }
    else
    {
        throw NegativeSize();
    }
}

//***********************************************************
// setLength sets the value of the member variable length. *
// If the argument is negative, it throws an exception.     *
//***********************************************************

void Rectangle::setLength(double len)
{
    if (len >= 0)
    {
        length = len;
    }
    else
    {
        throw NegativeSize();
    }
}

/*
Exceptions and Objects
- An exception class can be defined in a class and thrown as an exception by a member function

- An exception class may have:
no members: used only to signal an error
members: pass error data to catch block 

- A class can have more than one exception class
*/

//Rectangle.h (Specification file)
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
private:
    double width;  // The rectangle's width
    double length; // The rectangle's length

public:
    // Exception class
    class NegativeSize
    { }; // Empty class declaration

    // Default constructor
    Rectangle()
    { 
        width = 0.0; 
        length = 0.0; 
    }

    // Mutator functions, defined in Rectangle.cpp
    void setWidth(double);
    void setLength(double);

    // Accessor functions
    double getWidth() const
    { return width; }

    double getLength() const
    { return length; }

    double getArea() const
    { return width * length; }
};

#endif

//Rectangle.cpp (Implementation File)
#include "Rectangle.h"

//*********************************************************
// setWidth sets the value of the member variable width. *
//*********************************************************
void Rectangle::setWidth(double w)
{
    if (w >= 0)
        width = w;
    else
        throw NegativeSize();
}

//***********************************************************
// setLength sets the value of the member variable length. *
//***********************************************************
void Rectangle::setLength(double len)
{
    if (len >= 0)
        length = len;
    else
        throw NegativeSize();
}

// main.cpp
#include <iostream>
#include "Rectangle.h"
using namespace std;

int main()
{
    double width;
    double length;

    // Create a Rectangle object.
    Rectangle myRectangle;

    // Get the width and length.
    cout << "Enter the rectangle's width: ";
    cin >> width;
    cout << "Enter the rectangle's length: ";
    cin >> length;

    // Store these values in the Rectangle object.
    try
    {
        myRectangle.setWidth(width);
        myRectangle.setLength(length);
        
        cout << "The area of the rectangle is "
             << myRectangle.getArea() << endl;
    }
    catch (Rectangle::NegativeSize) // Inside the catch statement’s parentheses is the
    // name of the NegativeSize class. Because the NegativeSize class is declared inside the
    // Rectangle class, we have to fully qualify the class name with the scope resolution operator
    {
        cout << "Error: A negative value was entered.\n";
    }

    cout << "End of the program.\n";

    return 0;
}

// Notice we did not define a parameter of the NegativeSize class in the catch statement. In
// this case, the catch statement only needs to specify the type of exception it handles



// Extracting Data from the Exception Class

/*
Sometimes we might want an exception object to pass data back to the exception handler.
For example, suppose we would like the Rectangle class not only to signal when a negative
value has been given, but also to pass the value back. This can be accomplished by
giving the exception class members in which data can be stored.
In our next modification of the Rectangle class, the NegativeWidth and NegativeLength
classes have been expanded, each with a member variable and a constructor. Here is the
code for the NegativeWidth class:
    class NegativeWidth
    {
        private:
            double value;
        public:
            NegativeWidth(double val) // constructor
            { value = val; }
            double getValue() const
            { return value; }
    };
When we throw this exception, we want to pass the invalid value as an argument to the class’s
constructor. This is done in the setWidth member function with the following statement:
throw NegativeWidth(w);
This throw statement creates an instance of the NegativeWidth class and passes a copy of the
w variable to the constructor. The constructor then stores this number in NegativeWidth’s
member variable, value. The class instance carries this member variable to the catch block
that intercepts the exception.
In the catch block, the value is extracted with code such as
    catch (Rectangle::NegativeWidth e)
    {
        cout << "Error: " << e.getValue()
        << " is an invalid value for the"
        << " rectangle's width.\n";
    }
Notice the catch block defines a parameter object named e. This is necessary because we
want to call the class’s getValue function to retrieve the value that caused the exception.
Here is the code for the NegativeLength class:
    class NegativeLength
    {
        private:
            double value;
        public:
            NegativeLength(double val)
            { value = val; }
            double getValue() const
            { return value; }
    };

*/

/*
Unwinding the Stack
Once an exception is thrown, the program cannot return to throw point.  
The function executing throw terminates (does not return), other calling functions in try block terminate, resulting in unwinding the stack

If objects were created in the try block and an exception is thrown, they are destroyed.


1. The Throw Point is a "Point of No Return"
When the line throw NegativeSize(); is executed, the normal flow of the program stops instantly.

The code does not go back to the next line after the throw.

Think of it like an emergency exit: you don't go back into the building to finish your coffee; you leave immediately.

2. Terminating the Functions
If setWidth throws an exception, setWidth stops immediately. It doesn't even finish its own logic. Control then jumps back to the main function (or whichever function called it) to see if there is a try/catch block.

If the call was inside a try block, the remaining code in that try block is skipped.

In your code, if setWidth throws an error, the program never even tries to run setLength. It jumps straight to the catch.

This concept is known as Stack Unwinding. It describes the process of "cleaning up" the computer's memory as the program searches for a way to handle an error.

To understand this, imagine your program is a series of nested boxes. When you call a function, you step into a smaller box. When that function calls another, you step into an even smaller one.

1. The Throw Point is a "Point of No Return"
When the line throw NegativeSize(); is executed, the normal flow of the program stops instantly.

The code does not go back to the next line after the throw.

Think of it like an emergency exit: you don't go back into the building to finish your coffee; you leave immediately.

2. Terminating the Functions
If setWidth throws an exception, setWidth stops immediately. It doesn't even finish its own logic. Control then jumps back to the main function (or whichever function called it) to see if there is a try/catch block.

If the call was inside a try block, the remaining code in that try block is skipped.

In your code, if setWidth throws an error, the program never even tries to run setLength. It jumps straight to the catch.

3. Unwinding the Stack
The "Stack" is the list of active functions currently running. "Unwinding" it means the computer starts popping those functions off the list one by one until it finds a catch block that knows how to handle the specific error.

4. Automatic Destruction of Objects
This is one of C++'s most powerful features (often called RAII).

If you created local objects inside the try block before the exception happened, the computer is smart enough to call their destructors as it unwinds the stack.

This prevents "memory leaks." The program cleans up the mess you made in the try block before it enters the catch block.
*/


// Nested Try/catch

// Ex. Outer: 
try
{
    doSomething();
}
catch(exception1)
{
    // code to handle exception 1
}
catch(exception2)
{
    // code to handle exception 2
}

// Suppose doSomething(); calls the doSomethingElse function, which potentially can throw exception1 or exception3.
// Ex. Inner:
try
{
    doSomethingElse();
}
catch(exception1)
{
    throw; // Rethrow the exception
}
catch(exception3)
{
    // Code to handle exception 3
}
/*
If doSomethingElse() throws exception1:

The inner catch(exception1) catches it.

It decides not to handle it.

It executes throw;

The outer catch(exception1) now receives the same exception.
*/




/*
Handling bad_alloc

When the new operator fails to allocate memory, a bad_alloc exception is thrown
General format of a try/catch construct that catches the bad_alloc exception:
    try
    {
        // Code that uses the new operator
    }
    catch (bad_alloc)
    {
        // Code that responds to the error
    }


*/
// This program demonstrates the bad_alloc exception.
#include <iostream>
#include <new> // Needed for bad_alloc
using namespace std;
// In modern C++, when new fails to allocate the requested memory, it doesn't return nullptr by default; instead, it throws a bad_alloc exception.

int main()
{
    double *ptr = nullptr; // Pointer to double

    try
    {
        // Attempt to allocate a block of memory
        ptr = new double[10000];
        cout << "Memory successfully allocated." << endl;
    }
    catch (bad_alloc)
    // The catch Block: This specific handler is looking for the bad_alloc type. If the computer runs out of RAM, the program jumps here rather than crashing.
    {
        // This block executes if 'new' fails
        cout << "Insufficient memory.\n";
    }

    // Clean up memory if it was successfully allocated
    if (ptr != nullptr)
    {
        delete [] ptr;
    }

    return 0;
}

/*
The noexcept Specifier
In C++ 11 and later, the noexcept specifier indicates that a function does not throw an exception 
and does not call any other functions that throw an exception:
    void sayHello() noexcept
    {
        cout << "Hello world" << endl;
    }
The primary purpose of the noexcept specifier is to help the compiler produce faster executable code

*/







