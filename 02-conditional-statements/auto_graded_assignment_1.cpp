#include <iostream>

using namespace std;

// Program that identifies the meteorological season
// based on the calendar month and hemisphere entered by the user

/*
Assignment: You are programming a simple utility that identifies the meteorological season based on the calendar month and hemisphere entered by the user. The program asks for the hemisphere (N for North, S for South), asks for the month as a number (1 for January, 2 for February, etc.), and then displays the corresponding meteorological season.

Note: From now on, NH stands for Northern Hemisphere, and SH stands for Southern Hemisphere.

For this program, assume:

Winter (NH), Summer (SH): Dec-Feb
Spring (NH), Fall (SH): Mar-May
Summer (NH), Winter (SH): Jun- Aug
Fall (NH), Spring (SH): Sep-Nov

*/ 

int main(){

  char hemisphere;
  int month;

  cout << "Enter a hemisphere (N - S): ";
  cin >> hemisphere;

  switch (hemisphere){
    case 'N':
    case 'S':
      break;
    default:
      cout << "Please enter a valid hemisphere (N - S)." << endl;
      return 0;
  }
  


  cout << "Enter a month number (1 - 12): ";
  cin >> month;


  switch (hemisphere) {
    case 'N':
      switch (month){
        case 12:
        case 1:
        case 2: 
          cout << "The Season is Winter." << endl;
          break;
        case 3:
        case 4:
        case 5:
          cout << "The Season is Spring." << endl;
          break;
        case 6:
        case 7:
        case 8:
          cout << "The Season is Summer." << endl;
          break;
        case 9:
        case 10:
        case 11:
          cout << "The Season is Fall." << endl;
          break;
        default:
          cout << "Please enter a valid month number (1 - 12)." << endl;
      }
      break;

    case 'S':
      switch (month){
        case 12:
        case 1: 
        case 2: 
          cout << "The Season is Summer." << endl;
          break;
        case 3:
        case 4:
        case 5:
          cout << "The Season is Fall." << endl;
          break;
        case 6:
        case 7:
        case 8:
          cout << "The Season is Winter." << endl;
          break;
        case 9:
        case 10:
        case 11:
          cout << "The Season is Spring." << endl;
          break;
        default:
          cout << "Please enter a valid month number (1 - 12)." << endl;
      }
      break;
  }
  
  return 0;

}
