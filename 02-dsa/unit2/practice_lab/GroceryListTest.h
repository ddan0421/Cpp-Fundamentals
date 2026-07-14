#ifndef GROCERYLISTTEST_H
#define GROCERYLISTTEST_H

#include <iostream>
#include <string>
#include "GroceryList.h"

class GroceryListTest {
protected:
   // Stores a list of commands, each of which is one of the five forms:
   // - add itemName
   // - removeat index
   // - swap index1 index2
   // - undo
   // - verify listItem1,listItem2,...,lastListItem
   std::vector<std::string> commands;
   
   bool showCommands;
   bool assertUndoCount;

   virtual bool ExecCommand(std::string command,
      GroceryList& groceryList, std::ostream& testFeedback) {
      using namespace std;
      
      // Record the undo stack size prior to executing the command
      const int undoCountBefore = groceryList.GetUndoStackSize();
      
      // Store the current undo stack size as the "expected" undo stack size.
      // The expected count is incremented for the add, removeat, and swap
      // commands, and is decremented for the undo command.
      auto expectedUndoCount = groceryList.GetUndoStackSize();
      
      // Check the command string
      if (0 == command.find("add ")) {
         string itemToAdd = command.substr(4);
         if (showCommands) {
            testFeedback << "Adding " << itemToAdd << endl;
         }
         groceryList.AddWithUndo(itemToAdd);
         expectedUndoCount++;
      }
      else if (0 == command.find("removeat ")) {
         int index = stoi(command.substr(9));
         if (showCommands) {
            testFeedback << "Removing at index " << index << endl;
         }
         groceryList.RemoveAtWithUndo(index);
         expectedUndoCount++;
      }
      else if (0 == command.find("swap ")) {
         int index1 = -1, index2 = -1;
         if (ParseIndices(command.substr(5), index1, index2)) {
            if (showCommands) {
               testFeedback << "Swapping at indices " << index1 << " and ";
               testFeedback << index2 << endl;
            }
            
            groceryList.SwapWithUndo(index1, index2);
         }
         else {
            testFeedback << "Malformed swap command: " << command << std::endl;
            return false;
         }
         expectedUndoCount++;
      }
      else if (command == "undo") {
         if (showCommands) {
            testFeedback << "Executing undo" << endl;
         }
         
         if (0 == groceryList.GetUndoStackSize()) {
            testFeedback << "FAIL: Cannot execute undo because undo stack " <<
               "is empty" << endl;
         }
         else {
            groceryList.ExecuteUndo();
         }
         expectedUndoCount--;
      }
      else if (0 == command.find("verify ")) {
         string listStr = command.substr(7);
         vector<string> expected = Split(listStr, ',');
         vector<string> actual = groceryList.GetVectorCopy();
         if (!AssertListContent(testFeedback, actual, expected)) {
            return false;
         }

         testFeedback << "PASS: Verified list content: " << listStr << endl;
      }
      else if (command == "verify") {
         // Special case for empty list
         int actualSize = groceryList.GetVectorCopy().size();
         if (0 == actualSize) {
            testFeedback << "PASS: List is empty" << endl;
         }
         else {
            testFeedback << "FAIL: List should be empty, but instead has " <<
               actualSize << " item" << (1 == actualSize ? "" : "s") << endl;
         }
      }
      
      // If the undo stack size should have changed, verify
      if (assertUndoCount && undoCountBefore != expectedUndoCount) {
         // Get the actual undo command count
         int actualCount = groceryList.GetUndoStackSize();
         
         if (expectedUndoCount != actualCount) {
            testFeedback << "FAIL: Expected undo stack size is ";
            testFeedback << expectedUndoCount << ", but actual size is ";
            testFeedback << actualCount << endl;
            return false;
         }
         else {
            testFeedback << "PASS: Undo stack size is " << actualCount << endl;
         }
      }
      
      return true;
   }
   
   static bool ParseIndices(std::string str, int& outIndex1, int& outIndex2) {
      auto spaceIndex = str.find(" ");
      if (spaceIndex == std::string::npos) {
         return false;
      }
      
      outIndex1 = stoi(str);
      outIndex2 = stoi(str.substr(spaceIndex + 1));
      return true;
   }
   
   static std::vector<std::string> Split(std::string source, char separator) {
      using namespace std;
      vector<string> result;
      size_t start = 0;
      for (size_t i = 0; i < source.length(); i++) {
         if (separator == source[i]) {
            result.push_back(source.substr(start, i - start));
            start = i + 1;
         }
      }
      result.push_back(source.substr(start));
      return result;
   }

public:
   GroceryListTest(const std::vector<std::string>& commandsToCopy) :
      commands(commandsToCopy) {
      showCommands = true;
      assertUndoCount = true;
   }
   
   virtual ~GroceryListTest() {
   }
   
   static bool AssertListContent(std::ostream& testFeedback,
      const std::vector<std::string>& actual,
      const std::vector<std::string> expected) {
      bool passed = true;
      // First ensure that the sizes match
      if (actual.size() != expected.size()) {
         passed = false;
      }

      if (passed) {
         // Now compare each item
         for (int i = 0; i < (int)actual.size(); i++) {
            if (actual[i] != expected[i]) {
               passed = false;
            }
         }
      }
      
      if (!passed) {
         testFeedback << "FAIL:" << std::endl;
         PrintVector(testFeedback, expected, ", ",
            "  Expected vector: { ", " }\n");
         PrintVector(testFeedback, actual, ", ",
            "  Actual vector:   { ", " }\n");
      }
      return passed;
   }
   
   virtual bool Execute(std::ostream& testFeedback) {
      // Create a GroceryList
      GroceryList groceryList;
      
      // Execute each command in the commands list
      for (std::string command : commands) {
         if (!ExecCommand(command, groceryList, testFeedback)) {
            return false;
         }
      }
      
      // All tests passed
      return true;
   }
   
   // Utility function to print a vector's contents in order
   template <typename T>
   static void PrintVector(std::ostream& output, const std::vector<T>& vec,
      std::string separator = ",", std::string prefix = "",
      std::string suffix = "") {
      // Print the prefix first
      output << prefix;
      
      // If the vector isn't empty, print the first element without a separator
      if (vec.size() > 0) {
         output << vec[0];
      }
      
      // Print each remaining element preceded by the separator
      for (int i = 1; i < (int)vec.size(); i++) {
         output << separator << vec[i];
      }
      
      // Print the suffix last
      output << suffix;
   }
};

#endif
