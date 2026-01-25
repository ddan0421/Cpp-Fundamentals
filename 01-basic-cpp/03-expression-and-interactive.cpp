#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

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

  //Need to use getline later so i need to use cin.ignore(...)
  /*
   * Because cin >> leaves the newline in the input buffer, and getline stops immediately when it sees that newline
   */ 
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  /*
   * Type Conversion
   */ 

  /*
   * Hierachy of Types
   * Highest: long double 
   * double
   * float
   * unsigned long
   * long
   * unsigned int
   * Lowest: int
   * Ranked by largest number they can hold.
   */

  /*
   * Type Coercion - automatic conversion of an operand to another data type
   * Promotion: convert to a higher type
   * Demotion: convert to a lower type 
   */ 

  /*
   * char, short, unsigned short automatically promoted to int
   *
   * when operating on values of different data types, 
   * the lower one is promoted to the type of the higher one.
   *
   * When using the = operator, the type of expression on right will
   * be converted to type of variable on left 
   *
   */ 


  /*
   * Overflow and underflow
   * occurs when assigning a value that is too large (overflow)
   * or too small (underflow) to be held in a variable 
   */ 


  /*
   * Type Casting
   * Used for manul data type conversion
   * Useful for floating point division using ints:
   */ 
  double m;
  int y2 = 4;
  int y1 = 3;
  int x2 = 10;
  int x1 = 12;
  m = static_cast<double> (y2 - y1)/(x2-x1);
  std::cout << "The Slope is " << m << std::endl;


  //Useful to see int value of a char variable:
  char ch = 'C';
  std::cout << ch << " is "
    << static_cast<int>(ch) << "\n";


  //Combined Assignment
  y2 = y2 + 1;
  y2 += 1;




  /*
   * Formatting Output
   * Can control how output displays for numeric, string data:
   * size
   * position
   * number of digits
   * Requires iomanip header file
   */ 

  /*
   * setw(x): print in a field at least x spaces wide.
   * Use more spaces if field is not wide enough
   */ 

  float price = 9.5;
  float rate = 8.76;
  std::cout << std::endl
    << std::setw(10) << price 
    << std::setw(7) << rate
    << std::endl;
  


  /*
   * fixed: use decimal notation for floating-point values
   * setprecision(x): when used with fixed, print floating-point value
   * using x digits after the decimal.  Without fixed, print floating-point value using x significant digits
   * showpoint: always print decimal for floating-point values 
   */ 


  double a = 12.34567;
  double b = 12.0;
  double c = 0.000123456;


  // fixed example
  std::cout << std::endl
    << std::fixed << a << std::endl;
  //out put is 12.345670
  //Default precision is 6 digits after the decimal when fixed is on. 
  //Without fixed: 12.3457
  

  // setprecisoin examples (without turning fixed off)
  std::cout << std::setprecision(4) << a << std::endl; 
  /*
   * outputs 12.3457 — and here’s why:
   *fixed is still active
   * With fixed, setprecision(4) means:
   * 4 digits after the decimal
   */ 

  // unfix
  std::cout.unsetf(std::ios::floatfield);

  //setprecision examples
  std::cout << std::setprecision(4) << a << std::endl; // 12.35
  std::cout << std::setprecision(4) << c << std::endl; // 0.0001235

  //Showpoint always shows decimal number even for a whole number
  //because precision(4) + defaultfloat means 4 significant digits
  //showpoint forces a decimal point so 12 has 2 significant digits 
  //needs 4 so pads with zeros -> 12.00
  std::cout << std::showpoint << b << std::endl;


  /*
   * GetLine
   * Using cin with the >> operator to input strings can cause problems
   * It passes over and ignores any leading whitespace
   * characters (spaces, tabs, or line breaks)
   *
   * To work around this problem, you can use a C++ function named getline 
   */ 

  std::string name, city;
  std::cout << "Please enter your name: ";
  std::getline(std::cin, name);
  std::cout << "Enter the city you lie in: ";
  std::getline(std::cin, city); 

  std::cout << "Hello, " << name << std::endl;
  std::cout << "You live in " << city << std::endl;


  return 0;

}



