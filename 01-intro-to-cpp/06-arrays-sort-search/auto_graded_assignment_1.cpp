#include <iostream>

// Goal: Learn how to search for a value in an array.
//
// Assignment: Assume a randomly ordered array of int, of size n. The array arr
// contains the integers from 0 to n, except for one integer missing. For
// example, arr={3,0,1,4,5} is missing the number 2.
//
// Write a function findMissingNumber() which takes as parameters the array
// arr[] as well as the int n, and returns the integer missing from the array.
//
// Note: The swap function has already been defined and is available to be
// called from your code.
//
// Hint: First, sort the array. Then step through the array looking for the
// missing number.

using namespace std;

int findMissingNumber(int[], int);

int main() {

  // assume i have an int array with size n
  int n = 5;
  int arr[5] = {3, 0, 1, 4, 5};

  cout << "The missing number is " << findMissingNumber(arr, n) << endl;
  return 0;
}

int findMissingNumber(int array[], int n) {

  // Sort
  int minValue, minIndex;
  for (int i = 0; i < n - 1; i++) {
    minValue = array[i];
    minIndex = i;
    for (int check = i + 1; check < n; check++) {
      if (array[check] < minValue) {
        minValue = array[check];
        minIndex = check;
      }
    }
    swap(array[i], array[minIndex]);
  }

  // Find missing number
  for (int i = 0; i < n; i++) {
    if (array[i] != i) {
      return i;
    }
  }
  return n;
}

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}
