#ifndef INVALID_MONTH_H
#define INVALID_MONTH_H

#include <string>

using namespace std;

class InvalidMonth {
private:
  string message;

public:
  InvalidMonth(const string &msg) { message = msg; }
  string getMessage() const { return message; }
};

#endif
