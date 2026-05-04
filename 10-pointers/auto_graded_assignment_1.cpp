// Goal: Learn how to read an array from a file and process the data.
//
// Assignment: Write a function named expandArray. The function should accept an
// array of type int and the array’s size as arguments. The function should
// perform the following steps:
//
// The function should create a new int array that is twice the size of the
// argument array. The function should copy the contents of the argument array
// to the new array and initialize the unused elements of the second array with
// 0. The function should return a pointer to the new array. If the size of the
// argument array is 0 or negative, the expandArray function should return
// nullptr.
//
// Note: Do not write a complete program. Write only the code for the
// expandArray function.

int *expandArray(int[], int);

int *expandArray(int inputArray[], int inputSize) {
  if (inputSize <= 0)
    return nullptr;

  int *newArray = nullptr;
  int newSize = inputSize * 2;
  newArray = new int[newSize];

  for (int i = 0; i < newSize; i++) {
    if (i < inputSize)
      newArray[i] = inputArray[i];
    else
      newArray[i] = 0;
  }

  return newArray;
}
