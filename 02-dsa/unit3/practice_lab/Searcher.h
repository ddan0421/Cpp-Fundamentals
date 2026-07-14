#ifndef SEARCHER_H
#define SEARCHER_H

#include "Comparer.h"

template <typename T> class Searcher {
public:
  // Returns the index of the key in the sorted array, or -1 if the key is not
  // found
  static int BinarySearch(T *array, int arraySize, const T &key,
                          Comparer<T> &comparer) {
    // TODO: Type your code here
    int low = 0;
    int high = arraySize - 1;
    while (low <= high) {
      int middle = low + (high - low) / 2;
      if (comparer.Compare(array[middle], key) == 0) {
        return middle;
      } else if (comparer.Compare(array[middle], key) < 0) {
        low = middle + 1;
      } else {
        high = middle - 1;
      }
    }
    return -1;
  }
};

#endif
