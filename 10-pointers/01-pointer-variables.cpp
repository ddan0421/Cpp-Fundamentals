#include <iostream>

using namespace std;

// Pointers - addresses of variables

/*
The address of a variable is given by preceding the variable name with the C++
address operator (&):

cout << &sum; // This outputs the address of the variable sum

The & operator in front of the variable sum indicates that the address itself,
and not the data stored in that location, is the value used. On most systems the
above address will print as a hexadecimal value representing the physical
location of the variable.

To define a variable to be a pointer, we precede it with an asterisk (*) and
initialize it with the special value nullptr:
int *ptr = nullptr;

The asterisk in front of the variable indicates that ptr holds the address of a
memory location.

Assigning nullptr to a pointer variable makes the variable
point to the address 0. When a pointer is set to the address 0, it is referred
to as a null pointer because it points to "nothing."

The int indicates that the memory location that ptr points to holds integer
values. ptr is NOT an integer data type, but rather a pointer that holds the
address of a location where an integer value is stored. This distinction is most
important!


int sum; // sum holds an integer value.
int *sumPtr = nullptr; // sumPtr holds an address where an
                       // integer can be found.

*/

/*
Using the & Symbol

1)
The most frequent use we have seen is between the data type and the
variable name of a pass by reference parameter in a function heading/
prototype. This is called a reference variable. The memory address of the
parameter is sent to the function instead of the value at that address. When
the parameter is used in the function, the compiler automatically dereferences
the variable. Dereference means that the location of that reference
variable (parameter in this case) is accessed to retrieve or store a value.

While a pointer itself stores a memory address, dereferencing it allows you to
work with the actual data at that location.

We have looked at the swap function on several occasions. We revisit
this routine to show that the & symbol is used in the parameters that need
to be swapped. The reason is that these values need to be changed by the
function and, thus, we give the address (location in memory) of those
values so that the function can write their new values into them as they
are swapped.

Example:
void swap(int &first, int &second)
{     // The & indicates that the parameters
      // first and second are being passed by
      // reference.
int temp;
temp = first; // Since first is a reference variable,
              // the compiler retrieves the value
              // stored there and places it in temp.
first = second // New values are written directly into
second = temp; // the memory locations of first and second.


2)
The & symbol is also used whenever we are interested in the address of a
variable rather than its contents.
Example:
cout << sum;  // This outputs the value stored in the
              // variable sum.
cout << &sum; // This outputs the address where
              // sum is stored in memory.
Using the & symbol to get the address of a variable comes in handy when
we are assigning values to pointer variables.

}

*/

/*
Using the * Symbol

The * symbol is also basically used on two occasions.
1. It is used to define pointer variables:
int *ptr = nullptr;
2. It is also used whenever we are interested in the contents of the memory
location pointed to by a pointer variable, rather than the address itself.
When used this way * is called the indirection operator, or dereferencing
operator.


Example:
cout << *ptr; // Since ptr is a pointer variable, *
              // dereferences ptr. The value stored at the
              // location ptr points to will be printed.


*/

int main() {
  int one = 10;
  int *ptr1 = nullptr; // ptr1 is a pointer variable that points to an int
  ptr1 = &one;         // &one indicates that the address, not the
                       // contents, of one is being assigned to ptr1.
                       // Remember that ptr1 can only hold an address.
                       // Since ptr1 holds the address where the variable
                       // one is stored, we say that ptr1 "points to" one.
  cout << "The value of one is " << one << endl << endl;
  cout << "The value of &one is " << &one << endl << endl;
  cout << "The value of ptr1 is " << ptr1 << endl << endl;
  cout << "The value of *ptr1 is " << *ptr1 << endl << endl;
  return 0;
}
