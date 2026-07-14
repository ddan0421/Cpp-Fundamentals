#ifndef SWAPCOMMAND_H
#define SWAPCOMMAND_H

#include "UndoCommand.h"
#include <string>
#include <vector>

class SwapCommand : public UndoCommand {
private:
  // TODO: Type your member variable declarations here
  std::vector<std::string> *sourceVector;
  int index1, index2;

public:
  // TODO: Type your constructor code here
  SwapCommand(std::vector<std::string> *vector, int a, int b) {
    sourceVector = vector;
    index1 = a;
    index2 = b;
  }

  void Execute() override {
    // TODO: Type your code here
    std::string tmp = (*sourceVector)[index1];
    (*sourceVector)[index1] = (*sourceVector)[index2];
    (*sourceVector)[index2] = tmp;
  }
};

#endif
