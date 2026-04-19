#include "Appointment.h"
#include "Calendar.h"
#include <iostream>
#include <string>

using namespace std;

// Helper function prototype
bool isValidInput(int, int, int, int, int, string &);
void getValidDateTime(int &, int &, int &, int &, int &, string &, string);

int main() {
  string testFile = "appointments.txt";
  Calendar myCalendar;

  // 1. Load and Display existing appointments
  cout << "--- Loading Existing Schedule from File ---" << endl;
  myCalendar.loadAppointments(testFile);
  myCalendar.printAppointments();
  cout << "-------------------------------------------\n" << endl;

  // 2. Get new appointment data from user
  Appointment newAppt;
  int y, m, d, h, mn;
  string period, desc;

  getValidDateTime(y, m, d, h, mn, period, "START TIME");
  newAppt.setStart(m, d, y, h, mn, period);

  getValidDateTime(y, m, d, h, mn, period, "END TIME");
  newAppt.setEnd(m, d, y, h, mn, period);

  cin.ignore(1000, '\n');
  cout << "\nDescription: ";
  getline(cin, desc);
  newAppt.setDescription(desc);

  // 3. Print the user's entry for confirmation
  cout << "\n--- Your Entered Appointment ---" << endl;
  newAppt.printSingleApp();
  cout << "--------------------------------" << endl;

  if (myCalendar.addAppointments(newAppt, testFile)) {
    cout << "Check your appointments.txt—it should have the new line!" << endl;
  } else {
    cout << "Nothing was saved due to a conflict." << endl;
  }

  return 0;
}

// Function heading
bool isValidInput(int y, int m, int d, int h, int mn, string &p) {
  // 1. Month only between Jan and Dec.
  if (m < 1 || m > 12)
    return false;

  // 2. Minute check
  if (mn < 0 || mn > 59)
    return false;

  // 3. Hour check regardless of AM or PM
  if (h < 1 || h > 12)
    return false;

  // 4. Force period to be all uppercase
  for (char &c : p)
    c = toupper(c);
  if (p != "AM" && p != "PM")
    return false;

  // 5. Day check by putting max day for each month in an array
  int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // Leap year adjustment for February
  // A year is a leap year if it is divisible by 4, unless it is divisible by
  // 100 but not by 400
  if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
    daysInMonth[2] = 29;
  }

  if (d < 1 || d > daysInMonth[m])
    return false;

  return true;
}

void getValidDateTime(int &y, int &m, int &d, int &h, int &mn, string &p,
                      string label) {
  while (true) {
    cout << "\n[ " << label << " ]" << endl;
    cout << "Year: ";
    cin >> y;
    cout << "Month (1-12): ";
    cin >> m;
    cout << "Day: ";
    cin >> d;
    cout << "Hour (1-12): ";
    cin >> h;
    cout << "Minute (0-59): ";
    cin >> mn;
    cout << "AM/PM: ";
    cin >> p;

    if (isValidInput(y, m, d, h, mn, p)) {
      break;
    } else {
      cout << ">> INVALID DATE/TIME. Please try again." << endl;
      cin.ignore(1000, '\n');
    }
  }
}
