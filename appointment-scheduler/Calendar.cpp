#include "Calendar.h"
#include "Appointment.h"
#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool Calendar::parseLine(const string &line, Appointment &out) {
  stringstream ss(line);
  string start, end, description;

  getline(ss, start, '|');
  getline(ss, end, '|');
  getline(ss, description);

  try {
    long long startTs = stoll(start);
    long long endTs = stoll(end);

    out.setStart(startTs);
    out.setEnd(endTs);
    out.setDescription(description);
    return true;
  } catch (...) {
    return false;
  }
}

vector<Appointment> Calendar::loadAppointments(const string &filename) {
  ifstream file(filename);
  if (!file) {
    cout << "Error opening file" << endl;
    return appointments;
  }

  string line;

  while (getline(file, line)) {
    if (line.empty())
      continue;
    Appointment a;
    if (parseLine(line, a)) {
      appointments.push_back(a);
    } else {
      cout << "Skipping problematic line: " << line << endl;
    }
  }
  return appointments;
}

void Calendar::printAppointments() const {
  for (const auto &singleApp : appointments) {
    singleApp.printSingleApp();
    cout << "---------------------------------" << endl;
  }
}
