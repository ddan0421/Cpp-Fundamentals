#include "Appointment.h"
#include "Calendar.h"
#include <iostream>
#include <string>

using namespace std;
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

  cout << "=== Test New Appointment Entry ===" << endl;

  cout << "\n[ START TIME ]" << endl;
  cout << "Year: ";
  cin >> y;
  cout << "Month: ";
  cin >> m;
  cout << "Day: ";
  cin >> d;
  cout << "Hour: ";
  cin >> h;
  cout << "Minute: ";
  cin >> mn;
  cout << "AM/PM: ";
  cin >> period;
  newAppt.setStart(m, d, y, h, mn, period);

  cout << "\n[ END TIME ]" << endl;
  cout << "Year: ";
  cin >> y;
  cout << "Month: ";
  cin >> m;
  cout << "Day: ";
  cin >> d;
  cout << "Hour: ";
  cin >> h;
  cout << "Minute: ";
  cin >> mn;
  cout << "AM/PM: ";
  cin >> period;
  newAppt.setEnd(m, d, y, h, mn, period);

  cin.ignore(1000, '\n');
  cout << "\nDescription: ";
  getline(cin, desc);
  newAppt.setDescription(desc);

  // 3. Print the user's entry for confirmation
  cout << "\n--- Your Entered Appointment ---" << endl;
  newAppt.printSingleApp();
  cout << "--------------------------------" << endl;

  // 4. Perform the Conflict Check
  cout << "\n--- Verifying Conflict ---" << endl;

  if (myCalendar.checkConflict(newAppt)) {
    cout << "Result: [!] CONFLICT DETECTED." << endl;
    cout << "This appointment overlaps with an existing one in your file."
         << endl;
  } else {
    cout << "Result: [OK] NO CONFLICT." << endl;
    cout << "The time slot is available." << endl;
  }

  return 0;
}
