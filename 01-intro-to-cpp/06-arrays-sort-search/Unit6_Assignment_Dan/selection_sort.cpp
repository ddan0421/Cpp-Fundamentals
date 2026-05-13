// This program uses a selection sort to arrange an array of integers in
// ascending order

// Dan Dan

#include <iostream>
using namespace std;

// function prototypes
void selectionSortArray(int[], int);
void displayArray(int[], int);

const int SIZE = 8;

int main() {
  int values[SIZE] = {23, 0, 45, -3, -78, 1, -1, 9};

  cout << "The values before the selection sort is performed are:" << endl;
  displayArray(values, SIZE);

  cout << endl;

  selectionSortArray(values, SIZE);

  cout << "The values after the selection sort is performed are:" << endl;
  displayArray(values, SIZE);

  cout << endl;

  return 0;
}

//******************************************************************
//  displayArray
//
//  task:   to print the array
//  data in:  the array to be printed, the array size
//  data out: none
//
//******************************************************************

void displayArray(int array[], int elems) // function heading
{
  // Displays array
  for (int count = 0; count < elems; count++)
    cout << array[count] << " ";
  cout << endl;
}

//******************************************************************
//  selectionSortArray
//
//  task:   to sort values of an array in descending order
//  data in:  the array, the array size
//  data out: the sorted array
//
//******************************************************************

void selectionSortArray(int array[], int elems) {
  int seek;     // array position currently being put in order
  int maxCount; // location of smallest value found
  int maxValue; // holds the smallest value found

  for (seek = 0; seek < (elems - 1); seek++) // outer loop performs the swap
                                             // and then increments seek
  {
    maxCount = seek;
    maxValue = array[seek];

    for (int index = seek + 1; index < elems; index++) {
      // inner loop searches through array
      // starting at array[seek] searching
      // for the smallest value. When the
      // value is found, the subscript is
      // stored in minCount. The value is
      // stored in minValue.

      if (array[index] > maxValue) {
        maxValue = array[index];
        maxCount = index;
      }
    }

    // the following two statements exchange the value of the
    // element currently needing the smallest value found in the
    // pass(indicated by seek) with the smallest value found
    // (located in minValue)

    array[maxCount] = array[seek];
    array[seek] = maxValue;

    displayArray(array, SIZE);
    cout << endl;
  }
}
