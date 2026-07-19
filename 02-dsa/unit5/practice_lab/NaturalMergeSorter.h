#ifndef NATURALMERGESORTER_H
#define NATURALMERGESORTER_H

class NaturalMergeSorter {
public:
   virtual int GetSortedRunLength(int* array, int arrayLength, int startIndex) {
      // Out-of-bounds starting index has no run
      if (startIndex < 0 || startIndex >= arrayLength) {
         return 0;
      }

      // Extend the run while each element is >= its predecessor
      int runLength = 1;
      for (int i = startIndex + 1; i < arrayLength; i++) {
         if (array[i] < array[i - 1]) {
            break;
         }
         runLength++;
      }
      return runLength;
   }
   
   virtual void NaturalMergeSort(int* array, int arrayLength) {
      int i = 0;
      while (true) {
         // Length of the first sorted run, starting at i
         int firstRunLength = GetSortedRunLength(array, arrayLength, i);

         // Entire array is one sorted run: done
         if (firstRunLength == arrayLength) {
            return;
         }

         // First run reaches the array's end: restart from the beginning
         if (i + firstRunLength >= arrayLength) {
            i = 0;
            continue;
         }

         // Length of the second sorted run, immediately after the first
         int secondRunStart = i + firstRunLength;
         int secondRunLength =
            GetSortedRunLength(array, arrayLength, secondRunStart);

         // Merge the two adjacent runs
         int leftFirst = i;
         int leftLast = secondRunStart - 1;
         int rightLast = secondRunStart + secondRunLength - 1;
         Merge(array, leftFirst, leftLast, rightLast);

         // Continue after the second run, or restart if it hit the array's end
         if (rightLast >= arrayLength - 1) {
            i = 0;
         }
         else {
            i = rightLast + 1;
         }
      }
   }
   
   virtual void Merge(int* numbers, int leftFirst, int leftLast,
      int rightLast) {
      int mergedSize = rightLast - leftFirst + 1;
      int* mergedNumbers = new int[mergedSize];
      int mergePos = 0;
      int leftPos = leftFirst;
      int rightPos = leftLast + 1;
         
      // Add smallest element from left or right partition to merged numbers
      while (leftPos <= leftLast && rightPos <= rightLast) {
         if (numbers[leftPos] <= numbers[rightPos]) {
            mergedNumbers[mergePos] = numbers[leftPos];
            leftPos++;
         }
         else {
            mergedNumbers[mergePos] = numbers[rightPos];
            rightPos++;
         }
         mergePos++;
      }
         
      // If left partition isn't empty, add remaining elements to mergedNumbers
      while (leftPos <= leftLast) {
         mergedNumbers[mergePos] = numbers[leftPos];
         leftPos++;
         mergePos++;
      }
      
      // If right partition isn't empty, add remaining elements to mergedNumbers
      while (rightPos <= rightLast) {
         mergedNumbers[mergePos] = numbers[rightPos];
         rightPos++;
         mergePos++;
      }
      
      // Copy merged numbers back to numbers
      for (mergePos = 0; mergePos < mergedSize; mergePos++) {
         numbers[leftFirst + mergePos] = mergedNumbers[mergePos];
      }
      
      // Free temporary array
      delete[] mergedNumbers;
   }
};

#endif