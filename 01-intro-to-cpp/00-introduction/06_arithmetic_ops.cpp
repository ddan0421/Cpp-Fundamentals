#include <iostream>

int main()
{
  // arithmetic operators = return the result of a specific arithmetic operation
  // (+ - * /)
  
  int students = 20;

  // students = students + 1;
  // students + = 1;
  students ++;
  std::cout << students << "\n";

  students --;
  std::cout << students << "\n";

  students *= 2;
  std::cout << students << "\n";

  double new_students = 20;
  new_students /= 3;
  std::cout << new_students << "\n";

  int new_students_2 = 41;
  int remainder = new_students_2 % 2;
  std::cout << remainder << "\n";

  //parenthesis
  //multiplication & division
  //addition & subtraction
  
  int students_order = 6-5+4*3/2;
  std::cout << students_order << "\n";

  return 0;
}
