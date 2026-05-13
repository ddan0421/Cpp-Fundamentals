// This program demonstrates a Binary Search

// Dan Dan

/*
 * Exercise 1: the right side of this statement is integer in computer memory.
 * Middle is determined by compute the distance first and then divide by 2 using
 * integer division. Then add back to firs Middle is determined by compute the
 * distance first and then divide by 2 using integer division. Then add back to
 * first. This line that calculates middle is important because it allows us to
 * split the search space roughly in half, effectively shrink the search space
 *
 * Exercise 2: If I search 19, it will return position 2 (index 1) and for 12,
 * it will return position 8 (index 7). Since the array is not sorted, the
 * search will find whatever that lands at the middle.
 */

#include <iostream>
using namespace std;

int binarySearch(int[], int, int); // function prototype
const int SIZE = 16;

int main() {
  int found, value;

  int array[] = {0, 2, 2, 3, 5, 9, 11, 12, 12, 12, 13, 17, 18, 19, 19, 34};
  // array to be searched

  cout << "Enter an integer to search for:" << endl;
  cin >> value;

  found = binarySearch(array, SIZE, value);
  // function call to perform the binary search
  // on array looking for an occurrence of value

  if (found == -1)
    cout << "The value " << value << " is not in the list" << endl;
  else
    cout << "The value " << value << " is in position number " << found + 1
         << " of the list" << endl;

  return 0;
}

//*******************************************************************
//	binarySearch
//
//  task:	       This searches an array for a particular value
//  data in:	   List of values in an orderd array, the number of
//	               elements in the array, and the value searched for
//	               in the array
//  data returned: Position in the array of the value or -1 if value
//	               not found
//
//*******************************************************************

int binarySearch(int array[], int numElems, int value) // function heading
{
  int first = 0;           // First element of list
  int last = numElems - 1; // last element of the list
  int middle;              // variable containing the current
                           // middle value of the list

  while (first <= last) {
    middle = first + (last - first) / 2;

    if (array[middle] == value)
      return middle; // if value is in the middle, we are done

    else if (array[middle] > value)
      last = middle - 1; // toss out the second remaining half of

    else
      first = middle + 1; // toss out the first remaining half of
                          // the array and search the second
  }

  return -1; // indicates that value is not in the array
}
