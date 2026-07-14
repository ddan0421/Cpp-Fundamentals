#include <iostream>
#include <cstring>
#include <string>
#include "functions.h"

// Test driver for Lab 1 functions.
// Each test compares expected behavior to actual output.
// The test driver uses std::string for formatting output.
// Students are still expected to avoid std::string in their implementations.

void printHeader(const std::string &title)
{
    std::cout << "\n==============================\n";
    std::cout << title << std::endl;
    std::cout << "==============================\n";
}

void test_isDigitString()
{
    printHeader("Testing isDigitString");

    const char *tests[] = {"12345", "0012", "12a45", "", "0", "987654321"};
    const bool expected[] = {true, true, false, false, true, true};

    for (int i = 0; i < 6; i++)
    {
        bool actual = isDigitString(tests[i]);
        std::cout << "Input: \"" << tests[i] << "\"\n"
                  << "Expected: " << std::boolalpha << expected[i]
                  << " | Actual: " << actual << "\n\n";
    }
}

void test_reverse()
{
    printHeader("Testing reverse");

    char test1[] = "hello";
    char test2[] = "racecar";
    char test3[] = "A";
    char test4[] = "data structures";

    reverse(test1);
    reverse(test2);
    reverse(test3);
    reverse(test4);

    std::cout << "Expected: olleh | Actual: " << test1 << std::endl;
    std::cout << "Expected: racecar | Actual: " << test2 << std::endl;
    std::cout << "Expected: A | Actual: " << test3 << std::endl;
    std::cout << "Expected: serutcurts atad | Actual: " << test4 << std::endl;
}

void test_printASCII()
{
    printHeader("Testing printASCII");

    const char test[] = "Ab3";
    std::cout << "Input: \"" << test << "\"\n";
    std::cout << "Expected output values: 65 98 51\n";
    printASCII(test);
}

void test_countOccurrences()
{
    printHeader("Testing countOccurrences");

    std::cout << "String: banana, target: a | Expected: 3 | Actual: "
              << countOccurrences("banana", 'a') << std::endl;
    std::cout << "String: banana, target: z | Expected: 0 | Actual: "
              << countOccurrences("banana", 'z') << std::endl;
    std::cout << "String: Mississippi, target: s | Expected: 4 | Actual: "
              << countOccurrences("Mississippi", 's') << std::endl;
}

void test_isPalindrome()
{
    printHeader("Testing isPalindrome");

    const char *tests[] = {"racecar", "level", "hello", "a", ""};
    const bool expected[] = {true, true, false, true, true};

    for (int i = 0; i < 5; i++)
    {
        bool actual = isPalindrome(tests[i]);
        std::cout << "Input: \"" << tests[i] << "\"\n"
                  << "Expected: " << std::boolalpha << expected[i]
                  << " | Actual: " << actual << "\n\n";
    }
}

void test_stringToInt()
{
    printHeader("Testing stringToInt");

    const char *tests[] = {"0", "7", "105", "0012", "999"};
    const int expected[] = {0, 7, 105, 12, 999};

    for (int i = 0; i < 5; i++)
    {
        int actual = stringToInt(tests[i]);
        std::cout << "Input: \"" << tests[i] << "\"\n"
                  << "Expected: " << expected[i]
                  << " | Actual: " << actual << "\n\n";
    }
}

int main()
{
    printHeader("Template Function Checks");

    int x = 2, y = 8;
    std::cout << "Before swap x = " << x << " and y = " << y << std::endl;
    swapIt(x, y);
    std::cout << "After swap x = " << x << " and y = " << y << std::endl;

    char sample[] = "test";
    std::cout << "\nAddress print for sample array:\n";
    // Quick check of the template address-printing function.
    printAddresses(sample, std::strlen(sample));    

    std::cout << "\nAddress print with labels:\n";
    int len = std::strlen(sample);
    // Show labeled addresses to visualize how array elements are stored in memory
    for (int i = 0; i < len; i++)
    {
        std::cout << "str[" << i << "] = "
                  << static_cast<const void*>(&sample[i])
                  << std::endl;
    }


    test_isDigitString();
    test_reverse();
    test_printASCII();
    test_countOccurrences();
    test_isPalindrome();
    test_stringToInt();

    return 0;
}
