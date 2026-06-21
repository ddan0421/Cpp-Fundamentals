#ifndef INSERTATCOMMAND_H
#define INSERTATCOMMAND_H

#include "UndoCommand.h"
#include <string>
#include <vector>

class InsertAtCommand : public UndoCommand {
private:
  // TODO: Type your member variable declarations here
  std::vector<std::string> *sourceVector;
  int removalIndex;
  std::string removedItem;

public:
  // TODO: Type your constructor code here
  InsertAtCommand(std::vector<std::string> *vector, int index) {
    sourceVector = vector;
    removalIndex = index;
    removedItem = (*vector)[index];
  }

  void Execute() override {
    // TODO: Type your code here
    sourceVector->insert(sourceVector->begin() + removalIndex, removedItem);
  }
};

#endif
