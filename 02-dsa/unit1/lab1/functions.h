#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

/*************************************************************************
 * Name: Dan Dan        CSC 240
 * Date: 06-13-26       Lab #1
 *************************************************************************
 * Statement:
 * This Program implements several functions that work with C-strings
 * including checking for digit-only strings, reversing strings in place,
 * printing ASCII values, counting character occurrences, checking for
 * palindromes, and converting numeric strings to integers. It also
 * provides template functions to swap two values and print the memory
 * addresses of array elements.

 * Specifications:
 * The program uses C-style strings (char *), loops, pointer traversal,
 * and template functions. Non-template functions are implemented in
 * functions.cpp; template functions are implemented in functions.h.
 * The reverse and isPalindrome functions use the two-pointer technique.
 * stringToInt uses "digit-by-digit" conversion. Only basic loops, arrays,
 * pointers, and strlen() are used; advanced STL features are not used.
 * Functions assume valid input where preconditions specify.
 * Modifying functions change their arguments in place: swapIt exchanges
 * two values passed by reference, and reverse reverses a C-string in place.
 * Non-modifying functions leave input data unchanged: isDigitString,
 * countOccurrences, isPalindrome, and stringToInt return a result; printASCII
 * and printAddresses write output to the console only.

 * Input -
 * C-strings, characters, and variables passed into functions by the test
 * driver (for example, null-terminated char arrays, a target character for
 * counting, and two values (a and b) or an array with a length for the template
 * functions).

 * Output -
 * Modifying functions update their arguments directly: swapIt changes the
 * values of a and b, and reverse changes the contents of the C-string.
 * Non-modifying functions return values without altering input: isDigitString
 * and isPalindrome return bool; countOccurrences and stringToInt return int.
 * Non-modifying functions that print only: printAddresses outputs memory
 * addresses of array elements, and printASCII outputs ASCII decimal values.

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
    std::cout << static_cast<const void *>(&item[i]) << std::endl;
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
