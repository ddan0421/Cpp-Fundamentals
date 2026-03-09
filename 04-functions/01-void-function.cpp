#include <iostream>

using namespace std;

// Function Definition
/* ex. Function Definition
 * int main() {
 *   cout << "hello world\n";
 *    return 0;
 * }
 *
 * int - Return type
 * main - Function name
 * () - Parameter list (this one is empty)
 * cout << ... - The Function body
 *
 *
 * The line that reads int main() is the function header.
 */

/* Function Return Type
 * If a function returns a value, the type of the value must be indicated:
 * int main()
 *
 * If a function does not return a value, its return type is void:
 * void printHeading()
 * {
 *    cout << "Monthly Sales \n";
 * }
 *
 * The units or modules that do not return a value are called procedures or void
 * functions in C++
 */

void printDescription(); // Function prototype
                         // Function prototypes: ways to notify the compiler
                         // about a function before a call to the function:
                         // Place function definition before calling function's
                         // definition
                         //
                         // Place prototypes near top of program
                         // ***Program must include either prototype or full
                         // function definition before any call to the function
                         // - compiler error otherwise()! ***

/*
 * Function prototype is a promise (contract if you will) to the compiler that a
 * void function called printDescription will be defined after the main
 * function. If the printDescription function is placed in the file before the
 * main function which calls it, then the prototype is not necessary. However,
 * most C++ programs are written with prototypes so that main() can be the first
 * function
 */

void calPaycheck(float, int); // Values passed to a function are arguments.
                              // Variables in a function that hold the values
                              // passed as arguments are parameters.

int main() {
  float payRate;
  int hours;

  cout << "Welcome to the Payroll Program." << endl;
  printDescription(); // Cal lto the function

  cout << endl << "Please input the pay per hour." << endl;
  cin >> payRate;

  cout << endl << "Please input the number of hours worked." << endl;
  cin >> hours;
  cout << endl << endl;

  calPaycheck(payRate, hours); // Both payRate and hours are called actual
                               // parameters (arguments).

  cout << "We hoped you enjoyed this program." << endl;

  return 0;
}

void printDescription() {
  cout << "***************************************************" << endl << endl;
  cout << "This program takes two numbers (pay rate and hours)" << endl;
  cout << "and outputs gross pay. " << endl;
  cout << "***************************************************" << endl << endl;
}

void calPaycheck(float rate, int time) {
  float gross = rate * time;
  cout << "The pay is " << gross << endl;
}

/*
 * Compare Prototype: void calPaycheck(float, int);
 * vs Function Heading: void calPaycheck(float rate, int time)
 * vs Call: calPaycheck(payRate, hours);
 * The heading MUST have both data type and name for all its formal parameters.
 * The prototype must have the data type and can have the name for its formal
 * parameters (parameters).
 * The call MUST have the name but MUST NOT have the data type for its actual
 * parameters (arguments).
 *
 * ex:
 * void evenOrOdd(int); //prototype
 * void evenOrOdd(int num) // header
 * evenOrOdd(val); //call
 *
 *
 * Pass by value: when an argument is passed to a function, its value is copied
 * into the parameter.
 */
