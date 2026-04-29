/*
Exception Handling Write a program that prompts the user to enter a person’s
date of birth in numeric form. The input must be of the form month-day-year, for
example: 8-27-1980. The program then outputs the date of birth in the form:
August 27, 1980. Your program must contain at least two exception classes:
invalidDay and invalidMonth.  If the user enters an invalid value for day, then
the program should throw and catch an invalidDay object. Follow similar
conventions for the invalid values of month. Rules for a leap year are not
required for this lab, but can be implemented using code from a previous
assignment.

Read and store at least ten (10) birthdates entered from the user into a vector
of birthdates that only includes the year entered. The entered birthdate must be
valid before storing it. Sort the years entered and display them. Use following
function and signature to process the user input:  string convertDate(string
dateOfBirth, vector<int>& years).
*/

#include "InvalidDay.h"
#include "InvalidMonth.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string convertDate(string dateOfBirth, vector<int> &years);
int checkDay(const string &, const int &, const int &);
int checkMonth(const string &);

int main() {
  string inputDate;

  vector<int> validYears;

  while (true) {
    cout << "Please input date of birth in month-day-year format (-99 to "
            "quit): ";
    getline(cin, inputDate);
    if (inputDate == "-99") {
      break;
    }

    string result = convertDate(inputDate, validYears);
    cout << result << endl;
  }

  cout << "\nValid years entered: ";
  for (const auto &y : validYears) {
    cout << y << " ";
  }
  cout << endl;
  return 0;
}

int checkMonth(const string &ms) {
  int month = stoi(ms);
  if (month < 1 || month > 12)
    throw InvalidMonth("Month cannot be smaller than 1 or larger than 12!");
  return month;
}

int checkDay(const string &ds, const int &y, const int &m) {
  int day = stoi(ds);
  int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
    daysInMonth[2] = 29;
  }
  if (day < 1 || day > daysInMonth[m])
    throw InvalidDay("Day cannot be smaller than 1 or larger than " +
                     to_string(daysInMonth[m]) + " when month is " +
                     to_string(m));
  return day;
}

string convertDate(string dateOfBirth, vector<int> &years) {
  stringstream ss(dateOfBirth);
  string monthString, dayString, yearString;
  int month, day, year;

  getline(ss, monthString, '-');
  getline(ss, dayString, '-');
  getline(ss, yearString);

  year = stoi(yearString);

  try {
    month = checkMonth(monthString);
  } catch (const InvalidMonth &e) {
    return "Error: " + e.getMessage();
  }

  try {
    day = checkDay(dayString, year, month);
  } catch (const InvalidDay &e) {
    return "Error: " + e.getMessage();
  }

  years.push_back(year);

  return "This Date " + dateOfBirth +
         " is valid and add the year to the vector! ";
}
