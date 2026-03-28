#include <iostream>

using namespace std;

void bubbleSortArray(int[], int);
void displayArray(int[], int);

const int SIZE = 5;
int main() {
  /*
   * The bubble sort
   * A simple algorithm used to arrange data in either ascending (lowest to
   * highest) or descending (highest to lowest) order.
   *
   * Concept:
   * Compare 1st two elements
   * If out of order, exchange them to put in order
   * Move down one element, compare 2nd and 3rd elements, exchange if necessary.
   * Continue until end of array. Pass through array again, exchanging as
   * necessary Repeat until pass made with no exchanges
   */

  int values[SIZE] = {9, 2, 0, 11, 5};
  cout << "The values before the bubble sort is performed are:" << endl;
  displayArray(values, SIZE);
  bubbleSortArray(values, SIZE);
  cout << "The values after the bubble sort is performed are:" << endl;
  displayArray(values, SIZE);

  return 0;
}

//******************************************************************
// displayArray
//
// task: to print the array
// data in: the array to be printed, the array size
// data out: none
//
//******************************************************************
void displayArray(int array[], int elems) // function heading
{                                         // displays the array
  for (int count = 0; count < elems; count++)
    cout << array[count] << " " << endl;
}
//******************************************************************
// bubbleSortArray
//
// task: to sort values of an array in ascending order
// data in: the array, the array size
// data out: the sorted array
//
//******************************************************************

void bubbleSortArray(int array[], int elems) {
  bool swap;
  int temp;
  int bottom = elems - 1; // bottom indicates the end part of the
  // array where the largest values have
  // settled in order
  do {
    swap = false;
    for (int count = 0; count < bottom; count++) {
      if (array[count] > array[count + 1]) { // the next three lines do a swap
        temp = array[count];
        array[count] = array[count + 1];
        array[count + 1] = temp;
        swap = true; // indicates that a swap occurred
      }
    }
    bottom--; // bottom is decremented by 1 since each pass through
    // the array adds one more value that is set in order
  } while (swap != false);
  // loop repeats until a pass through the array with
  // no swaps occurs
}

// Alternative bubble sort using for loops and swap()
void bubbleSort(int array[], int size) {
  int maxElement;
  int index;

  for (maxElement = size - 1; maxElement > 0; maxElement--) {
    for (index = 0; index < maxElement; index++) {
      if (array[index] > array[index + 1]) {
        swap(array[index], array[index + 1]);
      }
    }
  }
}

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}
