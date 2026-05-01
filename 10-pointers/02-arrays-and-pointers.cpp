
/*

When arrays are passed to functions they are passed by pointer. An array name
is a pointer to the beginning of the array. Variables can hold just one value
and so we can reference that value by just naming the variable. Arrays, however,
hold many values. All of these values cannot be referenced just by naming the
array.


This is where pointers enter the picture. Pointers allow us to access all the
array elements.

!array name is really a pointer that holds the address of the first element in
the array.!
By using an array index, we dereference the pointer which gives us the contents
of that array location.


If grades is an array of 5 integers, as shown below, grades is actually a
pointer to the first location in the array, and grades[0] allows us to access
the contents of that first location.

so in most contexts, assume an array is passed to functions: void func(int
grades[]){}: grades is a pointer. grades == &grades[0]

deferencing happens like this:
so grades[0] is implicitly dereferencing

grades[0] == *(grades + 0)
grades[1] == *(grades + 1)
grades[2] == *(grades + 2)

grades → starting address
grades[i] → go i steps forward, then dereference

Summary
grades ≈ pointer to first element (&grades[0])
*grades = grades[0]
grades[i] = *(grades + i)
grades[i] is essentially dereferencing with pointer arithmetic


- Access of an individual element of an array through an index is done by
pointer arithmetic.


Example:
int vals[] = {4, 7, 11};
cout << vals; // displays 0x4a00
cout << *vals; // displays 4
cout << vals[0]; //displays 4



Pointer can be used as an array name:
int *valptr = vals;
cout << valptr[1]; // displays 7


However, outside the function, an array is a real array.

An array is not a pointer, but in many expressions it decays into a pointer to
its first element.

int arr[10];
sizeof(arr) -> 40. It outputs the total size of the entire array in bytes. If an
int is 4 bytes (which is typical in most systems) then 10 elements * 4 = 40;

But in a function like
void func(int arr[]){
    cout << sizeof(arr) << endl;
}

Inside a function parameter, this is automatically converted to: int *arr. This
arr is a pointer and sizeof(arr) will be the size of the pointer

*/

// Use pointer arithmetic

// This program illustrates how to use pointer arithmetic to
// access elements of an array.

#include <iostream>
using namespace std;

int main() {
  int grades[] = {90, 88, 76, 54, 34};
  // This defines and initializes an int array.
  // Since grades is an array name, it is really a pointer
  // that holds the starting address of the array.

  cout << "The first grade is " << *grades << endl;
  cout << "The second grade is " << *(grades + 1) << endl;
  cout << "The third grade is " << *(grades + 2) << endl;
  cout << "The fourth grade is " << *(grades + 3) << endl;
  cout << "The fifth grade is " << *(grades + 4) << endl;

  /*
   * The same is done for the other elements of the array. In each case, pointer
   * arithmetic gives us the address of the next array element. Then the
   * indirection operator * gives us the value of what is stored at the address.
   *
   * You cannot do grades = grades + 1;
   * But with a real pointer:
   * int *p = grades;
   * p = p + 1; // This is pointer arithmetic
   *            // meaning moves the pointer forward by 1 element
   *            // so now p points to grades[1]
   */
  return 0;
}

/*
Array Access
- Array elements can be accessed in many ways:

int vals[] = {4, 7, 17};
int *valptr = vals;

1) array name and [] : vals[2] = 17;
2) pointer to array and [] : valptr[2] = 17;
3) array name and subscript arithmetic : *(vals + 2) = 17;
4) pointer to array and subscript arithmetic : *(valptr + 2) = 17;


vals[i] = *(vals + i)


Pointer arithmetic

ex. int vals[] = {4,7,11};
int *valptr = vals;

++, -- :
valptr++; // points at 7
valptr--; // now points at 4;

+, - (pointer and int):
cout << *(valptr + 2);

+=, -= (pointer and int):
valptr = vals; // points at 4
valptr += 2; // points at 11

- (pointer from pointer):
cout << valptr - val; // difference (number of ints) between valptr and val;

*/
