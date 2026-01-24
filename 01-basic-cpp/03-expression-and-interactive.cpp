#include <iostream>
#include <string>
/*
* Using cin to input. It reads data from keyboard and stores
* it in one or more variables;
*/ 

int main(){

  std::string firstname, lastname;

  std::cout << "What is your first name? ";
  std::cin >> firstname;
  std::cout << "What is your last name? ";
  std::cin >> lastname;
  std::cout << "Your full name is " << firstname 
    << " " << lastname << ". \n";

  // read multiple values
  std::cout << "Enter the length and width of the rectangle ";
  std::cout << "separated by a space. \n";

  double length, width;
  std::cin >> length >> width;
  double area = length * width;

  std::cout << "The area of the rectangle is " << area << std::endl;

  return 0;

}



