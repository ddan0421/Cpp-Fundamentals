#ifndef RUNLENGTHTESTCASE_H
#define RUNLENGTHTESTCASE_H

#include <iostream>
#include <string>
#include <vector>
#include "NaturalMergeSorter.h"

// RunLengthTestCase represents a test case for the NaturalMergeSorter class's
// GetSortedRunLength() function.
class RunLengthTestCase {
private:
   std::vector<int> arrayData;
   int startIndex;
   int expectedReturnValue;
   
public:
   RunLengthTestCase(const std::vector<int>& arrayContent, int start,
      int expectedRet) : arrayData(arrayContent) {
      startIndex = start;
      expectedReturnValue = expectedRet;
   }
   
   RunLengthTestCase(int* array, int arrayLength, int start, int expectedRet) {
      startIndex = start;
      expectedReturnValue = expectedRet;
      for (int i = 0; i < arrayLength; i++) {
         arrayData.push_back(array[i]);
      }
   }
   
   // Executes the test case. If the test case passes, a message that starts
   // with "PASS" is printed and true is returned. Otherwise a message that
   // starts with "FAIL" is printed and false is returned.
   bool Execute(std::ostream& testFeedback) {
      using namespace std;
      
      // Convert the vector to an integer array
      int arrayLength = (int)arrayData.size();
      int* array = new int[arrayLength];
      for (int i = 0; i < arrayLength; i++) {
         array[i] = arrayData[i];
      }
      
      // Create a NaturalMergeSorter instance
      NaturalMergeSorter userSorter;
      
      // Call the GetSortedRunLength() function with the test case parameters
      int userRetVal = userSorter.GetSortedRunLength(
         array, arrayLength, startIndex);
      
      // The test passed only if the actual return value equals the expected
      // return value
      const bool passed = (userRetVal == expectedReturnValue);
      
      // Show a message about the test case's results
      testFeedback << (passed ? "PASS: " : "FAIL: ");
      testFeedback << "GetSortedRunLength()" << endl;
      testFeedback << "   Array: [";
      RunLengthTestCase::Print(arrayData, testFeedback);
      testFeedback << "]" << endl;
      testFeedback << "   Start index:           " << startIndex << endl;
      testFeedback << "   Expected return value: " << expectedReturnValue;
      testFeedback << endl;
      testFeedback << "   Actual return value:   " << userRetVal << endl;
      
      delete[] array;
      
      return passed;
   }
   
   // Utility function to print an integer vector's contents
   static void Print(const std::vector<int>& data, std::ostream& output,
      std::string separator = ", ", std::string prefix = "",
      std::string suffix = "") {
      // Get the data vector's size/length and print the prefix first
      int dataLength = (int)data.size();
      output << prefix;
      
      // Element output occurs only if at least one element exists
      if (dataLength > 0) {
         // Write the first element without a comma
         output << data[0];
         
         // Write each remaining element preceded by a comma
         for (int i = 1; i < dataLength; i++) {
            output << separator << data[i];
         }
      }
      
      // End with the suffix
      output << suffix;
   }
};

#endif