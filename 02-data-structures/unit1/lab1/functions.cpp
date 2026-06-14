#include "functions.h"
#include <cctype>
#include <cstring>

// Student implementation file for the non-template functions declared in
// functions.h. Write only the required non-template function
// definitions in this file.

bool isDigitString(const char *theString) {
  // TODO: Return true only if the string is non-empty
  // and every character is a digit.

  if (theString[0] == '\0') {
    return false;
  }
  for (int i = 0; theString[i] != '\0'; i++) {
    if (theString[i] < '0' || theString[i] > '9') {
      return false;
    }
  }
  return true;
}

void reverse(char *theString) {
  // TODO: Reverse the contents of the modifiable C-string in place.
}

void printASCII(const char *theString) {
  // TODO: Output the ASCII decimal value of each character in the string.
}

int countOccurrences(const char *theString, char target) {
  // TODO: Count and return how many times target appears in the string.
  return 0;
}

bool isPalindrome(const char *theString) {
  // TODO: Return true if the string reads the same forward and backward.
  return false;
}

int stringToInt(const char *theString) {
  // TODO: Assume the string contains digits only.
  // Convert the C-string to its integer value and return it.
  return 0;
}
