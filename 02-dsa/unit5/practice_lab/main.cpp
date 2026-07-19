#include <iostream>
#include <string>
#include <vector>
#include "NaturalMergeSorter.h"
#include "RunLengthTestCase.h"
using namespace std;

bool IsArraySorted(int* array, int arrayLength);
void WriteArray(int* array, int arrayLength);

int main() {
   // The following code declares test data in vectors. Each vector's content
   // is converted to an int* array before calling code in NaturalMergeSorter.
   
   // v1 is sorted in ascending order
   vector<int> v1 = { 15, 23, 23, 23, 31, 64, 77, 87, 88, 91 };
   int v1Size = (int) v1.size();

   // v2 has a sorted run of 3 followed by sorted run of 6
   vector<int> v2 = { 64, 88, 91, 12, 21, 34, 43, 56, 65 };

   // v3 has 5 elements in descending order, so 5 runs of length 1
   vector<int> v3 = { -10, -20, -30, -40, -50 };

   // v4 has 8 equal elements, so 1 run of 8
   vector<int> v4 = { -99, -99, -99, -99, -99, -99, -99, -99 };
   int v4Size = (int) v4.size();
   
   // v5 has 11 elements in descending order
   vector<int> v5 = { 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5 };
   int v5Size = (int) v5.size();
   
   // v6 has only one element
   vector<int> v6 = { 123456789 };
   
   // v7 has 6 sorted runs
   vector<int> v7 = { 92, 71, 18, 26, 54, 73, 89, 10, 39, 99, 64, 22 };
   
   // v8 has 2 sorted runs, lengths 6 and 1
   vector<int> v8 = { 333, 444, 555, 666, 777, 888, 111 };

   // Test cases:
   RunLengthTestCase testCases[] = {
      // First test case uses an out-of-bounds starting index. Remaining test
      // cases do not.
      RunLengthTestCase(v1, v1Size, 0),
      RunLengthTestCase(v1, 0, v1Size),
      RunLengthTestCase(v1, 3, v1Size - 3),
      RunLengthTestCase(v2, 0, 3),
      RunLengthTestCase(v2, 2, 1),
      RunLengthTestCase(v2, 3, 6),
      RunLengthTestCase(v3, 0, 1),
      RunLengthTestCase(v3, 3, 1),
      RunLengthTestCase(v3, 4, 1),
      RunLengthTestCase(v4, 0, v4Size),
      RunLengthTestCase(v4, 4, v4Size - 4),
      RunLengthTestCase(v4, 5, v4Size - 5),
      RunLengthTestCase(v5, 0, 1),
      RunLengthTestCase(v5, v5Size - 1, 1),
      RunLengthTestCase(v6, 0, 1),
      RunLengthTestCase(v7, 0, 1),
      RunLengthTestCase(v7, 1, 1),
      RunLengthTestCase(v7, 2, 5),
      RunLengthTestCase(v7, 7, 3),
      RunLengthTestCase(v7, 10, 1),
      RunLengthTestCase(v7, 11, 1),
      RunLengthTestCase(v8, 0, 6),
      RunLengthTestCase(v8, 6, 1)
   };

   // Execute each test case
   int runLengthPassCount = 0;
   int runLengthFailCount = 0;
   int testCasesLength = sizeof(testCases) / sizeof(testCases[0]);
   for (int i = 0; i < testCasesLength; i++) {
      RunLengthTestCase& testCase = testCases[i];

      // Execute the test case, using std::cout to write messages
      if (testCase.Execute(std::cout)) {
         runLengthPassCount++;
      }
      else {
         runLengthFailCount++;
      }
   }
   
   // Test sorting
   int sortPassCount = 0;
   int sortFailCount = 0;
   vector<vector<int>*> sources = { &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8 };
   for (vector<int>* source : sources) {
      // Copy the vector's contents to an array
      int arrayLength = (int)source->size();
      int* array = new int[arrayLength];
      for (int i = 0; i < arrayLength; i++) {
         array[i] = source->at(i);
      }
      
      NaturalMergeSorter sorter;
      sorter.NaturalMergeSort(array, arrayLength);
      bool passed = IsArraySorted(array, arrayLength);
      if (passed) {
         cout << "PASS";
         sortPassCount++;
      }
      else {
         cout << "FAIL";
         sortFailCount++;
      }
      cout << ": NaturalMergeSort()" << endl;
      cout << "   Array before calling NaturalMergeSort(): ";
      RunLengthTestCase::Print(*source, std::cout, ", ", "[", "]\n");
      cout << "   Array after calling NaturalMergeSort():  [";
      WriteArray(array, arrayLength);
      cout << "]" << endl;
      delete[] array;
   }
   
   // Print summaries
   cout << endl;
   cout << "GetSortedRunLength() tests summary:" << endl;
   cout << "   Passed: " << runLengthPassCount << endl;
   cout << "   Failed: " << runLengthFailCount << endl;
   cout << "NaturalMergeSort() tests summary:" << endl;
   cout << "   Passed: " << sortPassCount << endl;
   cout << "   Failed: " << sortFailCount << endl;
   
   return 0;
}

bool IsArraySorted(int* array, int arrayLength) {
   for (int i = 1; i < arrayLength; i++) {
      if (array[i] < array[i - 1]) {
         return false;
      }
   }
   return true;
}

void WriteArray(int* array, int arrayLength) {
   // Output occurs only if at least one array element exists
   if (arrayLength > 0) {
      // Write the first element without a comma
      cout << array[0];

      // Write each remaining element preceded by a comma
      for (int i = 1; i < arrayLength; i++) {
         cout << ", " << array[i];
      }
   }
}