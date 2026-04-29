#ifndef INVALID_DAY_H
#define INVALID_DAY_H

#include <string>

using namespace std;

class InvalidDay {
private:
  string message;

public:
  InvalidDay(const string &msg) { message = msg; }
  string getMessage() const { return message; }
};

#endif
