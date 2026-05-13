#include <iostream>
#include <string>

int main(){

  // int and double types 
  int checking;
  int savings = 200;
  checking = 100;

  double mutiplier = 0.5;
  double final_money = savings * mutiplier;

  std::cout << "Final amount is " << final_money << "you fine with this? \n";
  std::cout << "Sure Dan! \n";

  // Determining the Size of a Data Type 
  // The sizeof operator gives the size of any data type or variable:
  std::cout << "A double is stored in "
            << sizeof(double) << "bytes \n";

  std::cout << "The variable final_money is stored in "
            << sizeof(final_money) << "bytes \n";


  // char type
  char grade = 'C';

  std::cout << "Damn bro your grade is " << grade << "Gotta study broski \n";


  //string type using class <string>
  std::string firstname = "Dan";
  std::string lastname = "Li";

  std::cout << "My name is " << firstname << " " << lastname << std::endl;


  // bool 
  bool female_flag = false;
  bool handsome_flag = true;
  std::cout << "I am a female? Response: " << female_flag << std::endl;
  std::cout << "I am handsome? Response: " << handsome_flag << std::endl;


  // auto key word
  /* 
   * The auto key word tells the compiler to determine the variable's
   * Data type from the initialization value.
   */  
  auto amount = 100;
  auto interestRate = 12.0;
  auto stockCode = 'D';
  auto customerNum = 459L; //Long

  std::cout << "This is customer Num which is long type: " << customerNum << "\n";

  // Basic operators other than + - * / 
  std::cout << 13 % 5 << std::endl;
  // the % calculates the remainder. It requires integers for both operands 

  /*
   * Named constant (constant variables) are those content cannot be 
   * changed during program execution
   */ 

  const double TAX_RATE = 0.0675;
  const int NUM_STATES = 50;

  return 0;
  
}
