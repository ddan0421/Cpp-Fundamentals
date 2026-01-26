#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <random>

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
  



  // Stream Manipulators
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

  // Do not mix cin >> with getline 
  /*
   * cin >> age leaves a \n in the buffer
   * getline immediately consumes it
   */ 


  /*
   * Use cin.get()
   *
   * Use cin:
   * char ch;
   * cout << "Strike any key to continue"
   * cin >> ch; 
   * Problem: will skip over blanks, tabs, <CR>
   *
   * Use cin.get():
   * cin.get(ch);
   * Will read the next character entered, even whitespace
   */ 

  char chr;

  std::cout << "This program has paused. Press Enter to contniue. ";
  std::cin.get(chr);
  std::cout << "It has paused a second time. Please press Enter again. ";
  chr = std::cin.get();
  std::cout << "It has paused a third time. Please press Enter again. ";
  std::cin.get();
  std::cout << "Thank you!";

 /*
  * Mixing cin >> and cin.get() in the same program
  * can cause input errors that are hard to detect 
  *
  * To skip over unneeded characters that are still in 
  * the keyboard buffer, use cin.ignore():
  */ 

  // skip next char
  std::cin.ignore();

  // skip the next 10 chars or until '\n'
  std::cin.ignore(10, '\n');

  /*
   * string member functions and operators 
   */ 

  // To find the length of a string: 
  std::string state = "Texas";
  int size = state.length();

  // Toe concatenate (join) multiple strings:
  std::string greeting2, greeting1, name1;
  greeting1 = "Hi";
  name1 = "Dan";
  greeting2 = greeting1 + name1;
  
  std::cout << "greeting2 is " << greeting2 << std::endl;




  /* More Math Library functions
   *
   * Require cmath header file 
   * Take double as input, return a double
   * commonly used functions:
   * sin
   * cos 
   * tan 
   * sqrt
   * log 
   * abs 
   *
   *
   * These requires cstdlib header file
   * rand(): return a random number (int)
   * between 0 and the largest int the compute holds.
   * Yields same sequence of numbers each time program is run 
   *
   * srand(x): initalizes random number generator with unsigned int x 
   *
   */ 




  /*
   * Generating Random Number
   * Must have #include <random>
   *
   * Create the following objects:
   * A random number engine to generate a random sequence of bits 
   * A distribution object to format the bits into numbers of a specific data type,
   * within a specified ranged 
   */ 

  std::random_device myEngine;
  std::uniform_int_distribution<int> randomInt(0,100);
  int number = randomInt(myEngine);

  std::cout << "Random generated num: " << number << std::endl;

  const int MIN = 1;
  const int MAX = 6;
  
  std::random_device engine;

  std::uniform_int_distribution<int> diceValue(MIN, MAX);

  std::cout << "Rolling the dice ... \n";
  std::cout << diceValue(engine) << std::endl;
  std::cout << diceValue(engine) << std::endl;
  std::cout << diceValue(engine) << std::endl;


  return 0;

}



