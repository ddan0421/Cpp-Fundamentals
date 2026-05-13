// Write a program that prompts the user to enter the number of elements and the
// numbers themselves to be placed in an integer array that holds a maximum of
// 50 elements. The program should then prompt the user for an integer which
// will be searched for in the array using a binary search. Make sure to include
// the following steps along the way: i) A sort routine must be called before
// the binary search. You may use either the selection sort or the bubble sort.
// However, the sort must be implemented in its own function and not in main.
// ii) Next include a function called by main to implement the binary search.
// The ordered array produced by the sort should be passed to the search
// routine which returns the location in the sorted array of the sought value,
// or -1 if the value is not in the array.
// iii) Add a value returning function that computes the mean of your data set.
// Recall that the mean is the sum of the data values divided by the number
// of pieces of data. Your program should output the size of the array
// entered, the array as entered by the user, the sorted array, the integer
// being searched for, the location of that integer in the sorted array (or an
// appropriate message if it is not in the array), and the mean of the data set.
// iv) (Optional) Modify your program so that the data is entered from a file
// rather than from the keyboard. The first line of the file should be the size
// of the integer array. The second line should contain the integer searched
// for in the data set. Finally, the array elements are to start on the third
// line. Make sure you separate each array element with a space. The output, as
// described in iii), should be sent to a file.
//
// Optional modification: data is entered from a file
// rather than from the keyboard. The first line of the file should be the size
// of the integer array. The second line should contain the integer searched
// for in the data set. Finally, the array elements are to start on the third
// line. Make sure you separate each array element with a space. The output, as
// described in iii), should be sent to a file.

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

void SelectionSort(vector<int> &);
int BinarySearch(const vector<int> &, int);
void OutputArray(const vector<int> &, ostream &);
float findMean(const vector<int> &);
const int MAX_SIZE = 50;

int main() {
  ifstream inFile("input.txt");
  if (!inFile)
    return 1;

  ofstream outFile("output.txt");

  int size, target_val;

  inFile >> size;
  inFile >> target_val;

  if (size > MAX_SIZE) {
    outFile << "The size of array exceeds maximum size!";
    exit(1);
  }
  outFile << "The size of the array is " << size << endl;

  vector<int> arr(size);
  for (int i = 0; i < size; i++) {
    inFile >> arr[i];
  }
  outFile << "The array is: ";
  OutputArray(arr, outFile);

  // 1. sort the array
  SelectionSort(arr);
  outFile << "The array is sorted in ascending order: ";
  OutputArray(arr, outFile);

  // 2. search the value in the array
  int findIndex = BinarySearch(arr, target_val);
  if (findIndex != -1)
    outFile << "The value " << target_val << " is in position "
            << (findIndex + 1) << endl;
  else
    outFile << "The value " << target_val << " was not found in the array."
            << endl;

  // 3. find the mean
  outFile << fixed << setprecision(2) << showpoint;
  outFile << "The mean is " << findMean(arr) << endl;

  return 0;
}

void OutputArray(const vector<int> &v, ostream &out) {
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    out << v[i] << " ";
  }
  out << endl;
}

float findMean(const vector<int> &v) {
  int total = 0;
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    total += v[i];
  }
  return static_cast<float>(total) / (static_cast<int>(v.size()));
}

void SelectionSort(vector<int> &v) {
  int minValue, minIndex;
  for (int check = 0; check < (static_cast<int>(v.size()) - 1); check++) {
    minValue = v[check];
    minIndex = check;
    for (int index = check + 1; index < static_cast<int>(v.size()); index++) {
      if (v[index] < minValue) {
        minIndex = index;
        minValue = v[index];
      }
    }
    v[minIndex] = v[check];
    v[check] = minValue;
  }
}

int BinarySearch(const vector<int> &v, int value) {
  int first = 0;
  int last = static_cast<int>(v.size()) - 1;
  int middle;

  while (first <= last) {
    middle = first + (last - first) / 2;
    if (v[middle] == value) {
      return middle;
    } else if (v[middle] < value) {
      first = middle + 1;
    } else {
      last = middle - 1;
    }
  }
  return -1;
}
