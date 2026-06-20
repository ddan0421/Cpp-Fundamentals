#include <iostream>
#include <string>
#include "myList.hpp"

// Test driver for Lab 2.
// This driver aligns with the provided myList.hpp starter file and tests:
// - default, fill, array, and copy constructors
// - assignment operator
// - operator+= with a single item and another list
// - operator+ with a single item and another list
// - operator<<
// - print, isIn, find, insert, append, sort
// - getLength, isEmpty, removeAt, clear
//
// NOTE FOR STUDENTS:
// In addition to the core features listed in the handout, this starter
// version also tests clear() and find(). Be sure to implement those
// methods in myList.hpp.
// NOTE:
// Output formatting must match expected results exactly.
// Extra spaces or formatting differences may cause mismatches.

void printHeader(const std::string &title)
{
    std::cout << "\n==============================\n";
    std::cout << title << '\n';
    std::cout << "==============================\n";
}

int main()
{
    printHeader("Default Constructor / print / getLength / isEmpty");
    myList<int> l1;
    std::cout << "Expected: empty list\n";
    std::cout << "Actual:   ";
    l1.print(std::cout);
    std::cout << '\n';
    std::cout << "Expected length: 0 | Actual length: " << l1.getLength() << '\n';
    std::cout << "Expected empty: 1 (true) | Actual: " << l1.isEmpty() << '\n';

    printHeader("Fill Constructor");
    myList<float> f1(3, 12.0f);
    std::cout << "Expected: 12 12 12\n";
    std::cout << "Actual:   ";
    f1.print(std::cout);
    std::cout << '\n';
    std::cout << "Expected length: 3 | Actual length: " << f1.getLength() << '\n';

    printHeader("Array Constructor");
    int x[] = {1, 2, 3, 4, 5};
    myList<int> l2(5, x);
    std::cout << "Expected: 1 2 3 4 5\n";
    std::cout << "Actual:   ";
    l2.print(std::cout);
    std::cout << '\n';

    printHeader("Copy Constructor");
    myList<int> l3(l2);
    std::cout << "Expected copy: 1 2 3 4 5\n";
    std::cout << "Actual copy:   ";
    l3.print(std::cout);
    std::cout << '\n';

    // Deep-copy check
    l2.append(99);
    std::cout << "After changing original l2, copied l3 should stay unchanged.\n";
    std::cout << "l2 expected: 1 2 3 4 5 99\n";
    std::cout << "l2 actual:   ";
    l2.print(std::cout);
    std::cout << '\n';
    std::cout << "l3 expected: 1 2 3 4 5\n";
    std::cout << "l3 actual:   ";
    l3.print(std::cout);
    std::cout << '\n';

    printHeader("append");
    l3.append(6);
    std::cout << "Expected: 1 2 3 4 5 6\n";
    std::cout << "Actual:   ";
    l3.print(std::cout);
    std::cout << '\n';
    std::cout << "Expected length: 6 | Actual length: " << l3.getLength() << '\n';

    printHeader("isIn / find");
    std::cout << "Searching for 5 in l3\n";
    std::cout << "Expected isIn: 1 (true) | Actual: " << l3.isIn(5) << '\n';
    std::cout << "Expected find: 4 | Actual: " << l3.find(5) << '\n';
    std::cout << "Searching for 10 in l3\n";
    std::cout << "Expected isIn: 0 (false) | Actual: " << l3.isIn(10) << '\n';
    std::cout << "Expected find: -1 | Actual: " << l3.find(10) << '\n';

    printHeader("insert");
    l3.insert(99, 2);
    std::cout << "Expected: 1 2 99 3 4 5 6\n";
    std::cout << "Actual:   ";
    l3.print(std::cout);
    std::cout << '\n';
    std::cout << "Expected length: 7 | Actual length: " << l3.getLength() << '\n';

    std::cout << "\nInvalid insert tests (list should remain unchanged if handled safely)\n";
    l3.insert(123, -1);
    l3.insert(123, 100);
    std::cout << "Expected: 1 2 99 3 4 5 6\n";
    std::cout << "Actual:   ";
    l3.print(std::cout);
    std::cout << '\n';

    printHeader("sort");
    int y[] = {7, 2, 9, 1, 5};
    myList<int> l4(5, y);
    std::cout << "Before sort: ";
    l4.print(std::cout);
    std::cout << '\n';
    l4.sort();
    std::cout << "Expected after sort: 1 2 5 7 9\n";
    std::cout << "Actual after sort:   ";
    l4.print(std::cout);
    std::cout << '\n';

    printHeader("Assignment Operator");
    myList<int> l5;
    l5 = l4;
    std::cout << "Expected assigned copy: 1 2 5 7 9\n";
    std::cout << "Actual assigned copy:   ";
    l5.print(std::cout);
    std::cout << '\n';

    // Deep-copy check for assignment
    l4.append(100);
    std::cout << "After changing original l4, assigned l5 should stay unchanged.\n";
    std::cout << "l4 expected: 1 2 5 7 9 100\n";
    std::cout << "l4 actual:   ";
    l4.print(std::cout);
    std::cout << '\n';
    std::cout << "l5 expected: 1 2 5 7 9\n";
    std::cout << "l5 actual:   ";
    l5.print(std::cout);
    std::cout << '\n';

    printHeader("operator+= with Single Item");
    l5 += 15;
    std::cout << "Expected: 1 2 5 7 9 15\n";
    std::cout << "Actual:   ";
    l5.print(std::cout);
    std::cout << '\n';

    printHeader("operator+= with Another List");
    int z[] = {20, 25};
    myList<int> l6(2, z);
    l5 += l6;
    std::cout << "Expected: 1 2 5 7 9 15 20 25\n";
    std::cout << "Actual:   ";
    l5.print(std::cout);
    std::cout << '\n';

    printHeader("operator<<");
    std::cout << "Expected: 1 2 5 7 9 15 20 25\n";
    std::cout << "Actual:   " << l5 << '\n';

    printHeader("operator+ with Single Item");
    myList<int> l7 = l5 + 100;
    std::cout << "New list expected: 1 2 5 7 9 15 20 25 100\n";
    std::cout << "New list actual:   ";
    l7.print(std::cout);
    std::cout << '\n';
    std::cout << "Original l5 should remain unchanged: " << l5 << '\n';

    printHeader("operator+ with Another List");
    myList<int> l8 = l5 + l6;
    std::cout << "New list expected: 1 2 5 7 9 15 20 25 20 25\n";
    std::cout << "New list actual:   ";
    l8.print(std::cout);
    std::cout << '\n';
    std::cout << "Original l5 should remain unchanged: " << l5 << '\n';

    printHeader("getLength / isEmpty");
    std::cout << "Length of l5 | Expected: 8 | Actual: " << l5.getLength() << '\n';
    std::cout << "Is l5 empty? | Expected: 0 (false) | Actual: " << l5.isEmpty() << '\n';
    std::cout << "Is l1 empty? | Expected: 1 (true) | Actual: " << l1.isEmpty() << '\n';

    printHeader("removeAt");
    bool removed = l5.removeAt(2);
    std::cout << "Expected removal success: 1 (true) | Actual: " << removed << '\n';
    std::cout << "Expected list: 1 2 7 9 15 20 25\n";
    std::cout << "Actual:        ";
    l5.print(std::cout);
    std::cout << '\n';
    std::cout << "Expected length: 7 | Actual length: " << l5.getLength() << '\n';

    std::cout << "\nInvalid removeAt tests\n";
    bool badRemove1 = l5.removeAt(-1);
    bool badRemove2 = l5.removeAt(100);
    std::cout << "Expected results: 0 0 | Actual: " << badRemove1 << " " << badRemove2 << '\n';
    std::cout << "List should remain unchanged: " << l5 << '\n';

    printHeader("clear");
    l5.clear();
    std::cout << "Expected after clear: empty list\n";
    std::cout << "Actual:   ";
    l5.print(std::cout);
    std::cout << '\n';
    std::cout << "Expected length: 0 | Actual length: " << l5.getLength() << '\n';
    std::cout << "Expected empty: 1 (true) | Actual: " << l5.isEmpty() << '\n';

    return 0;
}
