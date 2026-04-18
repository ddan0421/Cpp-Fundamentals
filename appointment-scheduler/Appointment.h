#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

using namespace std;

class Appointment {
public:
  Appointment();

  void setStart(int sMonth, int sDay, int sYear, int sHour, int sMin,
                string sPeriod);
  void setEnd(int eMonth, int eDay, int eYear, int eHour, int eMin,
              string ePeriod);

  void setStart(long long ts); // Overloading to handle txt value

  void setEnd(long long ts); // Overloading to handle txt value

  void setDescription(string desc);

  long long getStart() const;
  long long getEnd() const;
  string getDescription() const;

private:
  int startMonth;
  int startDay;
  int startYear;

  int startHour;
  int startMin;
  string startPeriod;

  int endMonth;
  int endDay;
  int endYear;

  int endHour;
  int endMin;
  string endPeriod;

  string description;
  long long startTimeStamp;
  long long endTimeStamp;
};

#endif // APPOINTMENT_H
