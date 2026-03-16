#include <iomanip>
#include <iostream>

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
// float findAverage (const int [], int); // prototype without named parameters

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

  /* No Bounds Checking in C++
   * When you use a value as an array subscript, C++ does not check it to make
   * sure it is a valid subscript. In other words, you can use subscripts that
   * re beyond the bounds of the array. Be careful not to use invalid
   * subscripts. Doing so can correupt other memory locations, crash program, or
   * lock up computer, and cause elusive bugs.
   */

  /* Arrays as Arguments
   * Arrays can be passed as arguments (parameters) to functions. Although
   * varaiables can be passed by value or reference, arrays are always passed by
   * pointer, which is similar to pass by reference, since it is not efficient
   * to make a "copy" of all elements of the array.
   *
   * Pass by Pointer, similar to pass by reference parameters, can be altered by
   * the calling function. However, they NEVER have the & symbol between the
   * data type and name, as pass by reference parameters do.
   */

  int grades[TOTALGRADES];         // defines an array that holds up to 50 ints
  int numberOfGrades = 0;          // the number of grades read in
  float average;                   // the average of all grades read in
  getData(grades, numberOfGrades); // getData is called to read the grades into
                                   // the array and store how many grades there
                                   // are in numberOfGrades
  average = findAverage(grades, numberOfGrades);
  cout << endl
       << "The average of the " << numberOfGrades << " grades read in is "
       << average << "." << endl
       << endl;

  /* The Rnage-Based for loop
   *  - a loop that iterates once for each element in an array.
   *  - Each time the loop iterates, it copies an element from the array to a
   * built-in variable, known as the range variable
   *  - automatically knows the number of elements in an array.
   *  - Do not have to use a counter variable.
   *  - Do not have to worry about stepping outside the bounds of the array.
   *
   *  Example:
   *  for (dataType rangeVariable : array)
   *    statement;
   *   - dataType is the data type of the range variable.
   *   - rangeVariable is the name of the range variable. This variable will
   * receive the value of a different array element during each loop iteration.
   *   - array is the name of an array on which you wish the loop to operate.
   *   - statement is a statement that executes during a loop iteration. If you
   * need to execute more than one statement in the loop, enclose the statements
   * in a set of braces.
   *
   */

  //  ex to print out a array's value: alternative to printArray():
  int testsNums[] = {10, 20, 45, 29};
  for (const auto &val : testsNums) {
    cout << val << endl;
  }
  /* Note:
   * treating val as a refernce (add &) avoids copying elements
   * having const prevents modification
   * using auto works for any type if reused
   */

  /*
   * When using ++, -- operators, don't confuse the element with the subscript:
   * tests[i]++; // add 1 to tests[i]
   * tests[i++]; // increment i, no effect on tests
   */

  // Summing and Averaging array elements (operate on testsNums[])
  double average_testsNums, sum_testsNums = 0;
  for (int i = 0; i < 4; i++) {
    sum_testsNums += testsNums[i];
  }
  average_testsNums = sum_testsNums / 4;
  cout << "The average of testsNums[] array is " << average_testsNums << endl;

  // Finding the Highest and Lowest Value in an array (using testsNums[])
  // int testsNums[] = {10, 20, 45, 29};
  int highest, lowest;
  highest = testsNums[0];
  lowest = testsNums[0];
  for (int i = 1; i < 4; i++) {
    if (testsNums[i] > highest) {
      highest = testsNums[i];
    } else if (testsNums[i] < lowest) {
      lowest = testsNums[i];
    }
  }
  cout << "highest number in {10, 20, 45, 29} is " << highest << endl;
  cout << "lowerest number in {10, 20, 45, 29} is " << lowest << endl;

  /*
   * Comparing arrays
   * - must compare element-by-element;
   */
  const int SIZE_2 = 5;
  int firstArray[SIZE_2] = {5, 10, 15, 20, 25};
  int secondArray[SIZE_2] = {5, 10, 15, 20, 25};
  bool arraysEqual = true; // Flag variable
  int count = 0;           // Loop counter variable
  // Compare the two arrays.
  while (arraysEqual && count < SIZE_2) {
    if (firstArray[count] != secondArray[count])
      arraysEqual = false;
    count++;
  }
  if (arraysEqual)
    cout << "The arrays are equal.\n";
  else
    cout << "The arrays are not equal.\n";

  /*
   * Structured Binding Declarations
   *  - A structured binding declaration defines a set of variables and
   * initializes them with the values that are stored in an array.
   *  - introduced in C++ 17
   *  - General format: auto [var1, var2, etc...] = array;
   *
   *
   *  If an array has been passed as an argument into a function, you cannot use
   * a structured binding declaration in the receiving function to unpack the
   * array.␋ This is because the compiler does not know the size of the array
   * that might be passed into the parameter. You can only use a structured
   * binding declaration to unpack an array that has a known size. For example,
   * one that has been defined in the same function as where the structured
   * binding declaration is used.
   */

  int testScores[] = {80, 90, 100};
  auto [score1, score2, score3] =
      testScores; // testScores are unpacked into three variables
  cout << score1 << endl;
  cout << score2 << endl;
  cout << score3 << endl;

  /* Using parallel arrays
   *  - parallel arrays: two or more arrays that contain related data
   *  - A subscript is used to relate arrays: elements at same subscript are
   * related
   *  - Arrays may be of different types
   */

  const int NUM_EMPLOYEES = 5;
  int hours[NUM_EMPLOYEES];
  double payRate[NUM_EMPLOYEES];

  cout << "Enter the hours worked by " << NUM_EMPLOYEES
       << " employees and their \n"
       << "hourly pay rates.\n";
  for (int index = 0; index < NUM_EMPLOYEES; index++) {
    cout << "Hours worked by employee #" << (index + 1) << ": ";
    cin >> hours[index];
    cout << "Hourly pay rate for employee #" << (index + 1) << ": ";
    cin >> payRate[index];
  }

  cout << "Here is gross pay for each employee:\n";
  cout << fixed << showpoint << setprecision(2);
  for (int index = 0; index < NUM_EMPLOYEES; index++) {
    double grossPay = hours[index] * payRate[index];
    cout << "Employee #" << (index + 1);
    cout << ": $" << grossPay << endl;
  }

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
