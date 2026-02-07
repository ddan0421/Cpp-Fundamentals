#include <iostream>

using namespace std;

int main() {
  //Relational Operators: used to compare numbers to determine relative order
  // > < >= <= == !=
  // ex. 12 > 5 is true
  // Can be assigned to a variable: result = x <= y;
  // Assigns 0 for false, 1 for true 

  /*
   * The if Statement
   * Allows statements to be conditionally executed or skipped over
   *
   * General Format:
   * if (expression)
   *  statement;
   */ 

  float average;
  cout << "Input your average" << endl;
  cin >> average;

  if (average >= 60)
    cout << "You pass" << endl;
  if (average < 60)
    cout << "You Fail" << endl;


  //Execute more than one statement as part of an if statement,
  //enclose them in {}:
  //  {} creates a block of code
  int score = 100;
  string grade;
  if (score > 90)
  {
    grade = 'A';
    cout << "Good Job! \n";
  }


  // if else statements 
  // works well if there are only two possible paths to follow
  
  string name = "Dan";

  if (name == "Dan")
    cout << "You are smart man!" << endl;
  else
    cout << "You are not Dan broski" << endl;

  // if else if statements 

  float bonus;

  cout << "Please input the amout of your yearly bonus" << endl;
  cin >> bonus;

  if (bonus < 1000)
    cout << "Another vacation eating hot dogs on the lawn" << endl;
  else if (bonus < 10000)
    cout << "Off to Disney World!" << endl;
  else if (bonus == 10000)
    cout << "Let's go to Hawaii!" << endl;
  else
    cout << "You are rich bro!" << endl;




  // Nested if statements 
  char programmer, cPlusPlus;

  cout << "Before we consider your application, answer the following"
       << endl;
  cout << " yes (enter Y) or no ( enter N ) " << endl;
  cout << "Are you a computer programmer?" << endl;

  cin >> programmer;
  
  if (programmer == 'Y')
  {
    cout << "Do you program in C++?" << endl;
    cin >> cPlusPlus;

    if (cPlusPlus == 'Y')
      cout << " You look like a promising candidate for employment"
           << endl;
    else if (cPlusPlus == 'N')
      cout << " You need to learn C__ before further consideration"
           << endl;
    else 
      cout << " You must enter Y or N" << endl;
  }
  else if (programmer == 'N')
    cout << " You are not currently qualified for employment" << endl;
  else
    cout << " You must enter Y or N" << endl;

  
  // if statement initialization:
  // if statements can have an optional initialization
  // clause that is executed before the conditional expression is evaluated
  

  cin.ignore();
  string password;
  const int MIN_LENGTH = 9;

  cout << "Input password: " << endl;
  getline(cin, password);
  
  if (int len = password.length(); len < MIN_LENGTH)
  {
    cout << "Your password is too short." << endl;
  }
  else 
  {
    cout << "Your password has " << len
         << " characters." << endl;
  }


  /*
   * Flags
   * Variable that signals a condition 
   * Usually implemented as a bool variable 
   * Can also be an integer 
   *  0 is false and nonzero value is true
   *
   */ 

  //Logical Operators 
  //Used to create relational expressions from other relational expressions 
  //Operators, meaning, and explanation: 
  //&& And 
  //|| OR 
  //! Not - Good practice to enclose the operand after the (!) operator in parentheses.
  
  char employed, recentGrad;
  cout << "Are you emplopyed" << endl;
  cin >> employed;
  cout << "Are you a recent Grad?" << endl;
  cin >> recentGrad;

  if (employed == 'Y' && recentGrad == 'Y')
  {
    cout << "You qualifiy for the special "
         << "interest rate. \n";
  }
  else
  {
    cout << "You must be employed and have\n"
         << "graduated from college in the\n"
         << "past two years to qualifiy.\n";
  }
  
  const int MIN_INCOME = 10000;
  const int MIN_YEARS = 10;

  int income = 900000;
  int years = 8;

  if (!(income >= MIN_INCOME || years > MIN_YEARS))
  {
    cout << "You must ear at least $"
         << MIN_INCOME << " or have been "
         << "employed more than " << MIN_YEARS
         << " years.\n";
  }
  else 
    cout << "You qualified. \n";


  // The switch statement
  // Used to select among statements from several alternatives
  // can be used instead of if/else if statements


  return 0;
}
