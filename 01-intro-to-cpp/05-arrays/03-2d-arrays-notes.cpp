#include <iomanip>
#include <iostream>

using namespace std;

/* 2-dimensional arrays
 * can define one array for multiple sets of data
 * like a table in a a spreadsheet
 * use two size declarators in definition:
 * ex. const int ROWS = 4, COLS = 3;
 * int exams[ROWS][COLS];
 *
 */

const int NO_OF_ROWS = 3;
const int NO_OF_COLS = 4;
typedef float ProfitType[NO_OF_ROWS][NO_OF_COLS]; // declares a new data type
// which is a 2 dimensional
// array of floats

void showArray(float[][NO_OF_COLS], int);

int main() {
  ProfitType profit; // defines profit as a 2 dimensional array
  for (int row_pos = 0; row_pos < NO_OF_ROWS; row_pos++)
    for (int col_pos = 0; col_pos < NO_OF_COLS; col_pos++) {
      cout << "Please input a profit" << endl;
      cin >> profit[row_pos][col_pos];
    }
  // Print the array
  cout << "\nProfit table:\n";

  for (int row_pos = 0; row_pos < NO_OF_ROWS; row_pos++) {
    for (int col_pos = 0; col_pos < NO_OF_COLS; col_pos++) {
      cout << profit[row_pos][col_pos] << " ";
    }
    cout << endl; // move to next row
  }

  // can also be initalized like this
  const int ROWS = 2, COLS = 2;
  int exams[ROWS][COLS] = {{84, 78}, {92, 97}};

  // 2D array as parameter, argument
  showArray(profit, 3);

  /*
   * When passing a 2D array to a function in C++, the number of columns must be
   * specified in the parameter, while the number of rows can be left
   * unspecified. This is because the array decays into a pointer, and the
   * compiler needs to know the column size to correctly calculate memory
   * offsets when accessing elements. Without knowing how many columns each row
   * contains, it cannot properly move from one row to the next. Therefore, a
   * function parameter is typically declared like `void func(type
   * array[][COLS], int rows)`, where `COLS` is required but `rows` is passed
   * separately.
   */

  return 0;
}

void showArray(float array[][NO_OF_COLS], int rows) {
  for (int x = 0; x < rows; x++) {
    for (int y = 0; y < NO_OF_COLS; y++) {
      cout << setw(4) << array[x][y] << " ";
    }
    cout << endl;
  }
}
