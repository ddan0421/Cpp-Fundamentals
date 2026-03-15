#include <array>
#include <iostream>
#include <iterator>

using namespace std;

template <typename T, size_t N> void printArray(const T (&arr)[N]) {
  for (size_t i = 0; i < N; i++)
    cout << arr[i] << " ";

  cout << endl;
}

const int TOTALGRADES = 50; // TOTALGRADES is the maximum size of the array
// function prototypes
void getData(int array[], int &sizeOfArray);
// the procedure that will read values into the array
float findAverage(const int array[], int sizeOfArray);
// the procedure that will find the average of values
// stored in an array. The word const in front of the
// data type of the array prevents the function from
// altering the array

int main() {

  /*
   * int is the data type of the array elements
   * tests is the name of the array
   * 5, in [5], is the size declarator. It shows the number of elements in the
   * array. The size of an aray is (number of elements) * (size of each element)
   *
   * Again, array is a collection of memory locations, all of which have the
   * same data type. Each element of an array, consisting of a particular memory
   * location within the group, is accessed by giving the name of the array and
   * a position with the array (subscript).
   *
   */

  /*
   * Array initialization
   * - can be initialized with an initialization list:
   *   const int SIZE = 5;
   *   int tests[SIZE] = {1,2,3,4,5};
   */
  const int SIZE = 5;
  int tests[SIZE] = {90, 120, 20, 300, 91};
  printArray(tests);

  /*
   * Partial Array initialization
   * - If array is initilized with fewer initial values than the size
   * declarator, the remaining elements will be set to 0
   */

  int numbers[7] = {1, 2, 4, 8};
  printArray(numbers);

  /*
   * Implicit Array Sizing
   * Can determine array size by the size of the initialization list:
   */
  int quizzes[] = {12, 14, 23, 10};
  printArray(quizzes);

  return 0;
}

//***********************************************************************
// getData
//
// task: This function inputs and stores data in the grades array.
// data in: none (the parameters contain no information needed by the
// getData function)
// data out: an array containing grades and the number of grades
//***********************************************************************
void getData(int array[], int &sizeOfArray) {
  int pos = 0; // array index which starts at 0
  int grade;   // holds each individual grade read in
  cout << "Please input a grade or type -99 to stop: " << endl;
  cin >> grade;
  while (grade != -99) {
    array[pos] = grade; // store grade read in to next array location
    pos++;              // increment array index
    cout << "Please input a grade or type -99 to stop: " << endl;
    cin >> grade;
  }
  sizeOfArray = pos; // upon exiting the loop, pos holds the
  // number of grades read in, which is sent
  // back to the calling function
}

//****************************************************************************
// findAverage
//
// task: This function finds and returns the average of the values
//
// data in: the array containing grades and the array size
// data returned: the average of the grades contained in that array
//****************************************************************************
float findAverage(const int array[], int sizeOfArray) {
  int sum = 0; // holds the sum of all grades in the array
  for (int pos = 0; pos < sizeOfArray; pos++) {
    sum = sum + array[pos];
    // add grade in array position pos to sum
  }
  return float(sum) / sizeOfArray;
}
