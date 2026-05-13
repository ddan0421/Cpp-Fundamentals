#include <iostream>

using namespace std;

/*
 * normally, in function prototypes, you can write the prototypes without named
 * parameters ex. float findAverage(const int[], int);
 *
 * The use of brackets in function prototypes and headings can be avoided by
 * declaring a programmer defined data type. This is done in the global section
 * with a typedef statement.
 *
 * ex. typedef int GradeType[50];
 *
 * This declares a data type, called GradeType, that is an array containing 50
 * integer memory locations. Since GradeType is a data type, it can be used in
 * defining variables.
 *
 * This defines grades as an integer array with 50 elements
 * - ex. GradeType grades;
 * It has become a standard practice (although not a requirement) to use an
 * uppercase letter to begin the name of a data type.
 *
 * This method of using typedef to eliminate brackets in function prototypes and
 * headings is especially useful for multi-dimensional arrays
 */

const int TOTALGRADES = 50; // maximum size of the array
// function prototypes
typedef int GradeType[TOTALGRADES]; // declaration of an integer array data type
// called GradeType

void getData(GradeType array, int &sizeOfArray);
// the procedure that will read values into the array
float findAverage(const GradeType array, int sizeOfArray);
// the procedure that will find the average of values
// stored in an array. The word const in front of the
// data type of the array prevents the function from
// altering the array
int main() {
  GradeType grades;                // defines an array that holds up to 50 ints
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
  return 0;
}
//***********************************************************************
// getData
//
// task: This function inputs and stores data in the grades array.
// data in: none
// data out: an array containing grades and the number of grades
//***********************************************************************
void getData(GradeType array, int &sizeOfArray) {
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
float findAverage(const GradeType array, int sizeOfArray) {
  int sum = 0; // holds the sum of all grades in the array
  for (int pos = 0; pos < sizeOfArray; pos++) {
    sum = sum + array[pos];
    // add grade in array position pos to sum
  }
  return float(sum) / sizeOfArray;
}
