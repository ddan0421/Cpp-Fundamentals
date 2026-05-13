#include <iostream>

using namespace std;

void bubbleSortArray(int[], int);
void displayArray(int[], int);
void selectionSortArray(int[], int);

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

  /*
   * Selection Sort
   * - locate the smallest element in array. Exchange it with element in
   * position 0
   * - locate next smallest elelemtn in array. Exchange it with element in
   * position 1.
   * - Continue until all elements are arranged in order
   * A generally more efficient algorithm for large arrays is the selection
   * sort. As before, let us assume that we want to arrange numerical data in
   * ascending order. The idea of the selection sort algorithm is to first
   * locate the smallest value in the array and move that value to the beginning
   * of the array (i.e., position 0). Then the next smallest element is located
   * and put in the second position (i.e., position 1). This process continues
   * until all the data is ordered. An advantage of the selection sort is that
   * for n data elements at most n-1 moves are required. The disadvantage is
   * that n(n-1)/2 comparisons are always required.
   *
   */
  int values_selection[SIZE] = {9, 2, 0, 11, 5};
  cout << "The values before the selection sort is performed are:" << endl;
  displayArray(values_selection, SIZE);
  selectionSortArray(values_selection, SIZE);
  cout << "The values after the selection sort is performed are:" << endl;
  displayArray(values_selection, SIZE);

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

//******************************************************************
// selectionSortArray
//
// task: to sort values of an array in ascending order
// data in: the array, the array size
// data out: the sorted array
//
//******************************************************************
void selectionSortArray(int array[], int elems) {
  int seek;     // array position currently being put in order
  int minCount; // location of smallest value found
  int minValue; // holds the smallest value found
  for (seek = 0; seek < (elems - 1); seek++) // outer loop performs the swap
  // and then increments seek
  {
    minCount = seek;
    minValue = array[seek];
    for (int index = seek + 1; index < elems; index++) {
      // inner loop searches through array
      // starting at array[seek] searching
      // for the smallest value. When the
      // value is found, the subscript is
      // stored in minCount. The value is
      // stored in minValue.
      if (array[index] < minValue) {
        minValue = array[index];
        minCount = index;
      }
    }
    // the following two statements exchange the value of the
    // element currently needing the smallest value found in the
    // pass(indicated by seek) with the smallest value found
    // (located in minValue)
    array[minCount] = array[seek];
    array[seek] = minValue;
  }
}

// Alternative selectionSort using swap()
void selectionSort(int array[], int size) {
  int minIndex, minValue;
  for (int start = 0; start < (size - 1); start++) {
    minIndex = start;
    minValue = array[start];
    for (int index = start + 1; index < size; index++) {
      if (array[index] < minValue) {
        minValue = array[index];
        minIndex = index;
      }
    }
    swap(array[minIndex], array[start]);
  }
}
