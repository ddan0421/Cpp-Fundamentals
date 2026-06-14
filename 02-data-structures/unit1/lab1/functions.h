#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

/*************************************************************************
 * Name: Dan Dan        CSC 240
 * Date: 06-13-26       Lab #1
 *************************************************************************
 * Statement:
 * Specifications:
 * Input -
 * Output -
 *************************************************************************/

/**********************************************************************
 * IMPORTANT IMPLEMENTATION NOTES
 *
 * - All template functions MUST be fully implemented in this header file.
 *   (Templates cannot be separated into a .cpp file.)
 *
 * - All non-template functions MUST be implemented in functions.cpp.
 *
 * - Do NOT write function bodies in this file for non-template functions.
 **********************************************************************/

/**********************************************************************
 * TEMPLATE FUNCTIONS
 * These must be implemented in this header file.
 **********************************************************************/

// Precondition: a and b are valid references to objects of the same type.
// Postcondition: The values of a and b are exchanged.
template <class type> void swapIt(type &a, type &b) {
  type stored = a;
  a = b;
  b = stored;
}

// Precondition: item points to a valid array of at least n elements, and n >=
// 0. Postcondition: Outputs the memory address of each element in the array,
// one address per element.
template <class type> void printAddresses(type *item, int n) {
  for (int i = 0; i < n; i++) {
    std::cout << static_cast<const void *>(item + i) << std::endl;
  }
}

/**********************************************************************
 * NON-TEMPLATE FUNCTIONS
 * These must be implemented in functions.cpp.
 **********************************************************************/

// Precondition: theString is a valid null-terminated C-string (not null).
// Postcondition: Returns true if theString is non-empty and every character
// is a digit ('0' through '9'). Returns false otherwise.
bool isDigitString(const char *theString);

// Precondition: theString is a non-null, modifiable null-terminated C-string.
// Postcondition: The characters in theString are reversed in place.
void reverse(char *theString);

// Precondition: theString is a valid null-terminated C-string (not null).
// Postcondition: Outputs the ASCII decimal value of each character in
// theString.
void printASCII(const char *theString);

// Precondition: theString is a valid null-terminated C-string (not null).
// Postcondition: Returns the number of times target appears in the string.
int countOccurrences(const char *theString, char target);

// Precondition: theString is a valid null-terminated C-string (not null).
// Postcondition: Returns true if the string reads the same forward and
// backward. Empty string is considered a palindrome.
bool isPalindrome(const char *theString);

// Precondition: theString is a valid null-terminated C-string representing
// a non-negative integer using digits only.
// Postcondition: Returns the integer value represented by the string.
int stringToInt(const char *theString);

#endif
