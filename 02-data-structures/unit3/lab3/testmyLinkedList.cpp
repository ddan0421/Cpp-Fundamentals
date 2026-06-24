#include "myLinkedList.hpp"
#include <iostream>

using namespace std;

int main() {
  int i[] = {-9, 7, 11, 6, 7};
  char ch[] = {'a', 'b', 'c', 'd', 'e', 'f'};
  float fl[] = {1.2f, -9.0f, 7.0f};

  cout << "==============================" << endl;
  cout << "Default Constructor / print / getCount / isEmpty" << endl;
  cout << "==============================" << endl;
  myLinkedList<int> I;
  cout << "List I after default construction:" << endl;
  I.print(cout);
  cout << endl;
  cout << "Count of I: " << I.getCount() << endl;
  cout << "Is I empty? " << std::boolalpha << I.isEmpty() << endl << endl;

  cout << "==============================" << endl;
  cout << "addFirst / addLast / getFirst / getLast" << endl;
  cout << "==============================" << endl;
  I.addFirst(23);
  I.addFirst(12);
  I.addFirst(-8);
  I.addLast(23);
  I.addLast(12);
  I.addLast(-8);
  cout << "List I after addFirst/addLast:" << endl;
  I.print(cout);
  cout << endl;
  cout << "First element of I: " << I.getFirst() << endl;
  cout << "Last element of I: " << I.getLast() << endl;
  cout << "Count of I: " << I.getCount() << endl << endl;

  cout << "==============================" << endl;
  cout << "Array Constructors" << endl;
  cout << "==============================" << endl;
  myLinkedList<float> F(3, fl);
  cout << "List F built from float array:" << endl;
  F.print(cout);
  cout << endl;
  myLinkedList<char> C(6, ch);
  cout << "List C built from char array:" << endl;
  C.print(cout);
  cout << endl << endl;

  cout << "==============================" << endl;
  cout << "search / indexOf" << endl;
  cout << "==============================" << endl;
  cout << "Searching for 7 in I: " << std::boolalpha << I.search(7) << endl;
  cout << "Index of 7 in I: " << I.indexOf(7) << endl;
  cout << "Searching for 100 in I: " << std::boolalpha << I.search(100) << endl;
  cout << "Index of 100 in I: " << I.indexOf(100) << endl << endl;

  cout << "==============================" << endl;
  cout << "insertAt" << endl;
  cout << "==============================" << endl;
  cout << "Insert 99 at index 2 in I." << endl;
  cout << "Success? " << std::boolalpha << I.insertAt(2, 99) << endl;
  I.print(cout);
  cout << endl;
  cout << "Insert 500 at the front of I." << endl;
  cout << "Success? " << std::boolalpha << I.insertAt(0, 500) << endl;
  I.print(cout);
  cout << endl;
  cout << "Insert 700 at the end of I." << endl;
  cout << "Success? " << std::boolalpha << I.insertAt(I.getCount(), 700)
       << endl;
  I.print(cout);
  cout << endl;
  cout << "Try invalid insertAt(-1, 4)." << endl;
  cout << "Success? " << std::boolalpha << I.insertAt(-1, 4) << endl;
  I.print(cout);
  cout << endl << endl;

  cout << "==============================" << endl;
  cout << "Copy Constructor / Assignment" << endl;
  cout << "==============================" << endl;
  myLinkedList<int> I2(I);
  cout << "List I2 after copy construction from I:" << endl;
  I2.print(cout);
  cout << endl;

  myLinkedList<char> C2;
  C2 = C;
  cout << "List C2 after assignment from C:" << endl;
  C2.print(cout);
  cout << endl;

  cout << "Modify originals to verify deep copy." << endl;
  I.deleteItem(12);
  C.deleteItem('c');
  cout << "Original I:" << endl;
  I.print(cout);
  cout << endl;
  cout << "Copied I2 (should stay unchanged):" << endl;
  I2.print(cout);
  cout << endl;
  cout << "Original C:" << endl;
  C.print(cout);
  cout << endl;
  cout << "Assigned C2 (should stay unchanged):" << endl;
  C2.print(cout);
  cout << endl << endl;

  cout << "==============================" << endl;
  cout << "operator== / operator!=" << endl;
  cout << "==============================" << endl;
  cout << "I == I2 ? " << std::boolalpha << (I == I2) << endl;
  cout << "I != I2 ? " << std::boolalpha << (I != I2) << endl;
  cout << "C == C2 ? " << std::boolalpha << (C == C2) << endl;
  cout << "C != C2 ? " << std::boolalpha << (C != C2) << endl << endl;

  cout << "==============================" << endl;
  cout << "operator<<" << endl;
  cout << "==============================" << endl;
  cout << "List I2 using operator<<:" << endl;
  cout << I2 << endl << endl;

  cout << "==============================" << endl;
  cout << "deleteItem / deleteAt" << endl;
  cout << "==============================" << endl;
  myLinkedList<int> D(5, i);
  cout << "Original list D:" << endl;
  D.print(cout);
  cout << endl;

  cout << "Delete first occurrence of 7 from D." << endl;
  D.deleteItem(7);
  D.print(cout);
  cout << endl;

  cout << "Delete item at index 2 from D." << endl;
  cout << "Success? " << std::boolalpha << D.deleteAt(2) << endl;
  D.print(cout);
  cout << endl;

  cout << "Try invalid deleteAt(100)." << endl;
  cout << "Success? " << std::boolalpha << D.deleteAt(100) << endl;
  D.print(cout);
  cout << endl << endl;

  cout << "==============================" << endl;
  cout << "destroyList" << endl;
  cout << "==============================" << endl;
  cout << "Destroy list D." << endl;
  D.destroyList();
  D.print(cout);
  cout << endl;
  cout << "Count of D after destroyList: " << D.getCount() << endl;
  cout << "Is D empty after destroyList? " << std::boolalpha << D.isEmpty()
       << endl
       << endl;

  return 0;
}
