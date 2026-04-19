#include "Calendar.h"
#include "Appointment.h"
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

void Calendar::sortAppointment() {
  int elems = appointments.size();

  int minIndex;
  long long minValue;

  for (int i = 0; i < (elems - 1); i++) {

    minIndex = i;
    minValue = appointments[i].getStart();

    for (int j = i + 1; j < elems; j++) {
      if (appointments[j].getStart() < minValue) {
        minIndex = j;
        minValue = appointments[j].getStart();
      }
    }

    // swap
    Appointment temp = appointments[i];
    appointments[i] = appointments[minIndex];
    appointments[minIndex] = temp;
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
  sortAppointment();
  return appointments;
}

bool Calendar::checkConflict(const Appointment &a) {
  long long ns = a.getStart();
  long long ne = a.getEnd();

  for (const auto &existingApp : appointments) {
    long long es = existingApp.getStart();
    long long ee = existingApp.getEnd();

    if (es >= ne)
      break;
    if (ns < ee && es < ne) {
      return true;
    }
  }
  return false;
}

void Calendar::printAppointments() const {
  for (const auto &singleApp : appointments) {
    singleApp.printSingleApp();
    cout << "---------------------------------" << endl;
  }
}
