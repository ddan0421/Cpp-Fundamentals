#include "functions.h"
#include <cctype>
#include <cstring>

// Student implementation file for the non-template functions declared in
// functions.h. Write only the required non-template function
// definitions in this file.

bool isDigitString(const char *theString) {
  // TODO: Return true only if the string is non-empty
  // and every character is a digit.

  // handling empty string
  if (theString[0] == '\0') {
    return false;
  }
  for (int i = 0; theString[i] != '\0'; i++) {
    if (!std::isdigit(static_cast<unsigned char>(theString[i]))) {
      return false;
    }
  }
  return true;
}

void reverse(char *theString) {
  // TODO: Reverse the contents of the modifiable C-string in place.
  int first = 0;
  int last = strlen(theString) - 1;

  while (first < last) {
    swapIt(theString[first], theString[last]);
    first++;
    last--;
  }
}

void printASCII(const char *theString) {
  // TODO: Output the ASCII decimal value of each character in the string.
  for (int i = 0; theString[i] != '\0'; i++) {
    std::cout << int(theString[i]) << " ";
  }
  std::cout << std::endl;
}

int countOccurrences(const char *theString, char target) {
  // TODO: Count and return how many times target appears in the string.
  int num = 0;
  for (int i = 0; theString[i] != '\0'; i++) {
    if (theString[i] == target) {
      num += 1;
    }
  }
  return num;
}

bool isPalindrome(const char *theString) {
  // TODO: Return true if the string reads the same forward and backward.

  int left = 0;
  int right = strlen(theString) - 1;

  while (left < right) {
    if (theString[left] != theString[right]) {
      return false;
    }
    left++;
    right--;
  }

  return true;
}

int stringToInt(const char *theString) {
  // TODO: Assume the string contains digits only.
  // Convert the C-string to its integer value and return it.
  int num = 0;
  for (int i = 0; theString[i] != '\0'; i++) {
    int currentNum = theString[i] - '0';
    num = currentNum + (10 * num);
  }
  return num;
}
