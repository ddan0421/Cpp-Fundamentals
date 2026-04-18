#include "Appointment.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

Appointment::Appointment()
    : startMonth(0), startDay(0), startYear(0), startHour(0), startMin(0),
      startPeriod(""), endMonth(0), endDay(0), endYear(0), endHour(0),
      endMin(0), endPeriod(""), startTimeStamp(0), endTimeStamp(0),
      description("") {}

void Appointment::setStart(int sMonth, int sDay, int sYear, int sHour, int sMin,
                           string sPeriod) {
  startMonth = sMonth;
  startDay = sDay;
  startYear = sYear;
  startHour = sHour;
  startMin = sMin;
  startPeriod = sPeriod;
}

void Appointment::setEnd(int eMonth, int eDay, int eYear, int eHour, int eMin,
                         string ePeriod) {
  endMonth = eMonth;
  endDay = eDay;
  endYear = eYear;
  endHour = eHour;
  endMin = eMin;
  endPeriod = ePeriod;
}

void Appointment::setStart(long long ts) {
  startMin = ts % 100;
  ts /= 100;

  startHour = ts % 100;
  ts /= 100;

  startDay = ts % 100;
  ts /= 100;

  startMonth = ts % 100;
  ts /= 100;

  startYear = static_cast<int>(ts);

  if (startHour >= 12) {
    startPeriod = "PM";
    if (startHour > 12)
      startHour -= 12;
  } else {
    startPeriod = "AM";
    if (startHour == 0)
      startHour = 12;
  }
}

void Appointment::setEnd(long long ts) {
  endMin = ts % 100;
  ts /= 100;

  endHour = ts % 100;
  ts /= 100;

  endDay = ts % 100;
  ts /= 100;

  endMonth = ts % 100;
  ts /= 100;

  endYear = static_cast<int>(ts);

  if (endHour >= 12) {
    endPeriod = "PM";
    if (endHour > 12)
      endHour -= 12;
  } else {
    endPeriod = "AM";
    if (endHour == 0)
      endHour = 12;
  }
}

void Appointment::setDescription(string desc) { description = desc; }

long long Appointment::getStart() const {
  int h24 = startHour;
  if (tolower(startPeriod[0]) == 'p' && startHour != 12) {
    h24 += 12;
  } else if (tolower(startPeriod[0]) == 'a' && startHour == 12) {
    h24 = 0;
  }

  long long timestamp = 0;
  timestamp += static_cast<long long>(startYear) * 100000000LL; // YYYY00000000
  timestamp += static_cast<long long>(startMonth) * 1000000LL;  // YYYYMM000000
  timestamp += static_cast<long long>(startDay) * 10000LL;      // YYYYMMDD0000
  timestamp += static_cast<long long>(h24) * 100LL;             // YYYYMMDDHH00
  timestamp += static_cast<long long>(startMin);                // YYYYMMDDHHMM

  return timestamp;
}

long long Appointment::getEnd() const {
  int h24 = endHour;
  if (tolower(endPeriod[0]) == 'p' && endHour != 12) {
    h24 += 12;
  } else if (tolower(endPeriod[0]) == 'a' && endHour == 12) {
    h24 = 0;
  }

  long long timestamp = 0;
  timestamp += static_cast<long long>(endYear) * 100000000LL; // YYYY00000000
  timestamp += static_cast<long long>(endMonth) * 1000000LL;  // YYYYMM000000
  timestamp += static_cast<long long>(endDay) * 10000LL;      // YYYYMMDD0000
  timestamp += static_cast<long long>(h24) * 100LL;           // YYYYMMDDHH00
  timestamp += static_cast<long long>(endMin);                // YYYYMMDDHHMM

  return timestamp;
}

string Appointment::getDescription() const { return description; }

void Appointment::printSingleApp() const {
  cout << "Start: " << startYear << "/" << setfill('0') << setw(2) << startMonth
       << "/" << setw(2) << startDay << " - " << setw(2) << startHour << ":"
       << setw(2) << startMin << " " << startPeriod;

  cout << " , ";

  cout << "End: " << endYear << "/" << setw(2) << endMonth << "/" << setw(2)
       << endDay << " - " << setw(2) << endHour << ":" << setw(2) << endMin
       << " " << endPeriod;

  cout << " , ";
  cout << description << endl;
}
