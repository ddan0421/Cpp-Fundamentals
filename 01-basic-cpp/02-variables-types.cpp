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


  return 0;
  
}
