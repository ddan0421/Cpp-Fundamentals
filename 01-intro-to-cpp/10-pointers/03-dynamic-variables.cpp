/*

The programmer must estimate the maximum number of elements
that will be used by the array and this size is static, i.e., it cannot change
during the execution of the program. Consequently, if the array is defined to be
larger than is needed, memory is wasted. If it is defined to be smaller than is
needed, there is not enough memory to hold all of the elements. The use of
pointers (and the new and delete operators described below) allows us to
dynamically allocate enough memory for an array so that memory is not wasted.

This leads us to dynamic variables. Pointers allow us to use dynamic variables,
which can be created and destroyed as needed within a program. We have studied
scope rules, which define where a variable is active. Related to this is the
concept of lifetime, the time during which a variable exists.

The lifetime of dynamic variables is controlled by the program through explicit
commands to allocate (i.e., create) and deallocate (i.e., destroy) them.

The operator new is used to allocate and the operator delete is used to
deallocate dynamic variables

The compiler keeps track of where in memory non-dynamic variables (variables
discussed thus far in this book) are located. Their contents can be accessed by
just naming them. However, the compiler does not keep track of the address of a
dynamic variable. When the new command is used to allocate memory for a dynamic
variable, the system returns its address and the programmer stores it in a
pointer variable. Through the pointer variable we can access the memory
location.




Example:
int *one = nullptr; // one and two are defined to be pointer
int *two = nullptr; // variables that point to ints
int result;         // defines an int variable that will hold
                    // the sum of two values.
one = new int;      // These statements each dynamically
two = new int;      // allocate enough memory to hold an int
                    // and assign their addresses to pointer
                    // variables one and two, respectively.
*one = 10;          // These statements assign the value 10
*two = 20;          // to the memory location pointed to by one
                    // and 20 to the memory location pointed to
                    // by two.
result = *one + *two;
                    // This adds the contents of the memory
                    // locations pointed to by one and two.
cout << "result = " << result << endl;

delete one;         // These statements deallocate the dynamic
delete two;         // variables. Their memory is freed and
                    // they cease to exist.



*/

// By using the new operator to create the array, we can wait until
// we know how big the array needs to be before creating it. The following
// program demonstrates this idea. First the user is asked to input the number
// of grades to be processed. Then that number is used to allocate exactly
// enough memory to hold an array with the required number of elements for the
// grades.

// This program finds the average of a set of grades.
// It dynamically allocates space for the array holding the grades.
#include <iomanip>
#include <iostream>
using namespace std;
// function prototypes
void sortIt(float *grades, int numOfGrades);
void displayGrades(float *grades, int numOfGrades);

int main() {
  float *grades = nullptr; // a pointer that will be used to point
                           // to the beginning of a float array
  float total = 0;         // total of all grades
  float average;           // average of all grades
  int numOfGrades;         // the number of grades to be processed
  int count;               // loop counter
                           //
  cout << fixed << showpoint << setprecision(2);

  cout << "How many grades will be processed " << endl;
  cin >> numOfGrades;

  while (numOfGrades <= 0) // checks for a legal value
  {
    cout << "There must be at least one grade. Please reenter.\n";
    cout << "How many grades will be processed " << endl;
    cin >> numOfGrades;
  }
  grades = new float[numOfGrades];
  // allocation memory for an array
  // new is the operator that is allocating
  // an array of floats with the number of
  // elements specified by the user. grades
  // is the pointer holding the starting
  // address of the array.
  if (grades == nullptr) // nullptr is a special identifier
  {                      // to equal 0. It indicates a non-valid
                         // address. If grades is 0 it means the
                         // the operating system was unable to
                         // allocate enough memory for the array.
    cout << "Error allocating memory!\n";
    // The program should output an appropriate
    return 1; // error message and return with a value
  } // other than 0 to signal a problem.
  cout << "Enter the grades below\n";

  for (count = 0; count < numOfGrades; count++) {
    cout << "Grade " << (count + 1) << ": " << endl;
    cin >> grades[count];
    total = total + grades[count];
  }
  average = total / numOfGrades;
  cout << "Average Grade is " << average << "%" << endl;
  sortIt(grades, numOfGrades);
  displayGrades(grades, numOfGrades);
  delete[] grades; // deallocates all the array memory
  return 0;
}
//***************************************************
// sortIt
//
// task: to sort numbers in an array
// data in: an array of floats and
// the number of elements in the array
// data out: sorted array
//
//****************************************************
void sortIt(float *grades, int numOfGrades) {
  // Sort routine placed here
}
//***************************************************
// displayGrades
//
// task: to display numbers in an array
// data in: an array of floats and
// the number of elements in the array
// data out: none
//
//****************************************************
void displayGrades(float *grades, int numOfGrades) {
  // Code to display grades of the array
}

// Notice how the dynamic array is passed as a parameter to the sortIt and
// displayGrades functions. In each case, the call to the function simply passes
// the name of the array, along with its size as an argument. The name of the
// array holds the array’s starting address. sortIt(grades, numOfGrades);

/*
In the function header, the formal parameter that receives the array is defined
to be a pointer data type. void sortIt(float* grades, int numOfGrades) Since the
compiler treats an array name as a pointer, we could also have written the
following function header. void sortIt(float grades[], int numOfGrades)


In this program, dynamic allocation of memory was used to save memory. This
is a minor consideration for the type of programs done in this course, but a
major concern in professional programming environments where large fluctuating
amounts of data are used.

*/
