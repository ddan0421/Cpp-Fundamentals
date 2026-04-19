#include "Appointment.h"
#include "Calendar.h"
#include <iostream>
#include <string>

using namespace std;

// Helper function prototype
bool isValidInput(int, int, int, int, int, string &);
bool getValidDateTime(int &, int &, int &, int &, int &, string &, string);

int main() {
  string inputFile = "appointments.txt";
  Calendar myCalendar;

  // 1. Print out existing Calendar
  cout << "--- Loading Existing Schedule from File ---" << endl;
  myCalendar.loadAppointments(inputFile);
  myCalendar.printAppointments();

  while (true) {
    cout << "\n===================================================" << endl;
    cout << " NEW APPOINTMENT ENTRY (Enter -99 for Year to Quit)" << endl;
    cout << "===================================================" << endl;

    int y, m, d, h, mn;
    string period, desc;

    // 2. Get start time - if returns false, user entered -99
    if (!getValidDateTime(y, m, d, h, mn, period, "START TIME")) {
      break;
    }

    Appointment newAppt;
    newAppt.setStart(m, d, y, h, mn, period);

    // 3. Get end time
    // We don't check for -99 here because they already committed to this entry
    getValidDateTime(y, m, d, h, mn, period, "END TIME");
    newAppt.setEnd(m, d, y, h, mn, period);

    // 4. Get Description
    cin.ignore(1000, '\n');
    cout << "\nDescription: ";
    getline(cin, desc);
    newAppt.setDescription(desc);

    // 5. Logic: End must be after Start
    if (newAppt.getEnd() <= newAppt.getStart()) {
      cout << "\n!!!!!ERROR: Appointment cannot end before it starts. Entry "
              "discarded."
           << endl;
      continue; // Go back to start of loop
    }

    // 6. conflict check and add
    if (myCalendar.addAppointments(newAppt, inputFile)) {
      cout << "\n>> success: appointment added to " << inputFile << endl;

    } else {
      cout << "\n>> FAILURE: Conflict detected with existing schedule." << endl;
    }
  }

  cout << "\nExiting... Have a productive day!" << endl;
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

bool getValidDateTime(int &y, int &m, int &d, int &h, int &mn, string &p,
                      string label) {
  while (true) {
    cout << "\n[ " << label << " ]" << endl;
    cout << "Year (or -99 to quit): ";
    cin >> y;

    if (y == -99) // Only Start Time prompts allows user to enter -99
      return false;

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
      return true;
    } else {
      cout << ">> INVALID DATE/TIME. Please try again." << endl;
      cin.ignore(1000, '\n');
    }
  }
}
