#include <iostream>

using namespace std;

int searchList(char[], int, char); // function prototype
const int SIZE = 8;

int binarySearch(int[], int, int);

int main() {
  /*
   * linear search - starts at the beginning of the array and then steps through
   * the elements sequentially until either the desired value is found or the
   * end of the array is reached.
   *
   *
   * char word[8] = "Harpoon";
   * So word[0]='H', word[3]= 'p', and word[7] = '\0 '. The '\0' marks the end
   * of the string and is called the null character.
   *
   * It is customary to return –1 when we have not find any occurance of target
   * letter
   *
   * One advantage of the linear search is its simplicity. It is easy to step
   * sequentially through an array and check each element for a designated
   * value. Another advantage is that the elements of the array do not need to
   * be in any order to implement the algorithm.
   *
   * The main disadvantage of the linear search is that it is timeconsuming
   * for large arrays. If the desired piece of data is not in the array, then
   * the search has to check every element of the array before it returns –1.
   * Even if the desired piece of data is in the array, there is a very good
   * chance that a significant portion of the array will need to be checked to
   * find it. So we need a more efficient search algorithm for large arrays
   *
   */

  char word[SIZE] = "Harpoon";
  int found;
  char ch;
  cout << "Enter a letter to search for:" << endl;
  cin >> ch;
  found = searchList(word, SIZE, ch);
  if (found == -1)
    cout << "The letter " << ch << " was not found in the list" << endl;
  else
    cout << "The letter " << ch << " is in the " << found + 1
         << " position of the list" << endl;

  /*
   * Binary Seach
   * A more efficient algorithm for searching an array is the binary search
   * which eliminates half of the array every time it does a check. The drawback
   * is that the data in the array must be ordered to use a binary search. If we
   * are searching an array of integers, then the values stored in the array
   * must be arranged in order from largest to smallest or smallest to largest.
   */

  int array[] = {34, 19, 19, 18, 17, 13, 12, 12, 12, 11, 9, 5, 3, 2, 2, 0};

  int value_to_search = 19;
  found = binarySearch(array, 16, value_to_search);

  if (found == -1)
    cout << "The value " << value_to_search << " is not in the list" << endl;
  else {
  }
  cout << "The value " << value_to_search << " is in position number "
       << found + 1 << " of the list" << endl;

  return 0;
}

//*******************************************************************
// searchList
//
// task: This searches an array for a particular value
// data in: List of values in an array, the number of
// elements in the array, and the value searched for
// in the array
// data returned: Position in the array of the value or -1 if value
// not found
//
//*******************************************************************
int searchList(char list[], int numElems, char value) {
  for (int count = 0; count < numElems; count++) {
    if (list[count] == value)
      // each array entry is checked to see if it contains
      // the desired value.
      return count;
    // if the desired value is found, the array subscript
    // count is returned to indicate the location in the array
  }
  return -1; // if the value is not found, -1 is returned
}

// Another Linear search algo
int linearSearch(int arr[], int size, int value) {
  int index = 0;
  int position = -1;
  bool found = false;

  while (index < size && !found) {
    if (arr[index] == value) {
      found = true;
      position = index;
    }
    index++;
  }
  return position;
}

//*******************************************************************
// binarySearch
//
// task: This searches an array for a particular value
// data in: List of values in an orderd array, the number of
// elements in the array, and the value searched for
// in the array
// data returned: Position in the array of the value or -1 if value
// not found
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
    else if (array[middle] < value)
      last = middle - 1; // toss out the second remaining half of
    // the array and search the first
    else
      first = middle + 1; // toss out the first remaining half of
    // the array and search the second
  }

  return -1; // indicates that value is not in the array
}
