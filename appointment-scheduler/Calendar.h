#ifndef CALENDAR_H
#define CALENDAR_H

#include "Appointment.h"
#include <string>
#include <vector>

using namespace std;

class Calendar {

public:
  vector<Appointment>
  loadAppointments(const string &filename); // pass by reference more efficient
                                            // though can be pass by value
  // bool checkConflict(const Appointment &a);
  // void addAppointments(const Appointment &a, const string &filename,
  //                      bool writeIfNoConflict);

  void printAppointments() const;

private:
  vector<Appointment> appointments;
  bool parseLine(const string &line, Appointment &out);
  void sortAppointment();
};

#endif // CALENDAR_H
