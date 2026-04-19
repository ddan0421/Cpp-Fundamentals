#include "Appointment.h"
#include "Calendar.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  Appointment appt;
  int y, m, d, h, mn;
  string period, desc;

  cout << "=== Appointment Entry System ===" << endl;

  // --- Start Time Details ---
  cout << "\n[ START TIME ]" << endl;
  cout << "Enter Year: ";
  cin >> y;
  cout << "Enter Month: ";
  cin >> m;
  cout << "Enter Day: ";
  cin >> d;
  cout << "Enter Hour: ";
  cin >> h;
  cout << "Enter Minute: ";
  cin >> mn;
  cout << "Enter Period (AM/PM): ";
  cin >> period;

  appt.setStart(m, d, y, h, mn, period);

  // --- End Time Details ---
  cout << "\n[ END TIME ]" << endl;
  cout << "Enter Year: ";
  cin >> y;
  cout << "Enter Month: ";
  cin >> m;
  cout << "Enter Day: ";
  cin >> d;
  cout << "Enter Hour: ";
  cin >> h;
  cout << "Enter Minute: ";
  cin >> mn;
  cout << "Enter Period (AM/PM): ";
  cin >> period;

  appt.setEnd(m, d, y, h, mn, period);

  // --- Description ---
  // Simplified buffer clear: ignore the next 1000 characters or until a newline
  cin.ignore(1000, '\n');

  cout << "\nEnter Appointment Description: ";
  getline(cin, desc);
  appt.setDescription(desc);

  // --- Final Output ---
  cout << "\n================================" << endl;
  cout << "Description: " << appt.getDescription() << endl;
  cout << "Start ID:    " << appt.getStart() << endl;
  cout << "End ID:      " << appt.getEnd() << endl;
  cout << "================================" << endl;

  appt.printSingleApp();

  string testFile = "appointments.txt";

  Calendar myCalendar;
  myCalendar.loadAppointments(testFile);
  myCalendar.printAppointments();

  return 0;
}
