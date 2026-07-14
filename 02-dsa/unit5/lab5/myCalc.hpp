#ifndef MYCALC_H_
#define MYCALC_H_

#include "myStack.hpp"
#include <cctype>
#include <sstream>
#include <string>

/*************************************************************************
 *  Name: Dan Dan                              CSC 240
 *  Date: 07/09/2026                           Lab 5
 *************************************************************************
 *  Statement:
 *  This program implements a simple integer calculator using stacks.
 *  The calculator stores an infix expression, converts the expression to
 *  postfix notation, and evaluates the postfix expression.
 *
 *  Specifications:
 *  This lab must use the student-created myStack class. The expression is
 *  assumed to contain positive integers, the operators +, -, *, /,
 *  parentheses, and the ending symbol =.
 *
 *  Input -
 *  A valid infix expression stored as a string.
 *
 *  Output -
 *  The postfix form of the input expression and the evaluated integer value.
 *
 *  Example:
 *  Input expression:  (10+3)*(51/2)/(30-4)=
 *  Postfix form:      10 3 + 51 2 / * 30 4 - /
 *  Value:             12
 *************************************************************************/

/*************************************************************************
 *  HELPER FUNCTIONS REQUIREMENT
 *
 *  The private methods provided in this class are helper functions.
 *  You are expected to use them to organize your solution.
 *
 *  - Do NOT remove these functions.
 *  - Do NOT change their names or parameters.
 *  - Do NOT make them public.
 *  - You may call these functions from other methods in this class.
 *
 *  These functions are intended to:
 *  - break the problem into smaller pieces
 *  - simplify your logic
 *  - improve readability and debugging
 *
 *  Proper use of helper functions is part of code quality.
 *************************************************************************/

/*************************************************************************
 *  METHOD USAGE REQUIREMENTS
 *
 *  You must use the helper functions as intended when implementing the
 *  public methods.
 *
 *  REQUIRED RELATIONSHIPS:
 *
 *  - postFixInput()
 *        MUST call:
 *            postFix(input)
 *
 *  - evaluate()
 *        MUST call:
 *            postFix(input)
 *            evaluatePostFix(postfixString)
 *
 *  HELPER FUNCTION ROLES:
 *
 *  - postFix(...)
 *        Performs ALL infix to postfix conversion using myStack<char>.
 *
 *  - evaluatePostFix(...)
 *        Performs ALL postfix evaluation using myStack<int>.
 *
 *  - isOperator(...)
 *        Used to identify operators during parsing.
 *
 *  - getPrecedence(...)
 *        Used when comparing operator precedence in postFix(...).
 *
 *  - applyOperator(...)
 *        Used to compute results during postfix evaluation.
 *
 *  IMPORTANT CONSTRAINTS:
 *
 *  - Do NOT reimplement postfix logic inside evaluate().
 *  - Do NOT evaluate infix expressions directly.
 *  - Do NOT duplicate logic already handled by helper functions.
 *
 *  Proper use of helper functions and method structure is required.
 *************************************************************************/

// LAB 5 STUDENT TEMPLATE FILE
//
// IMPORTANT REQUIREMENTS:
// - You MUST use myStack.hpp.
// - Do NOT use the C++ standard library stack.
// - Do NOT create a separate .cpp file for this class.
// - Complete all myCalc method implementations in this header file.
// - You may assume all input expressions are valid.
// - All numbers are POSITIVE INTEGERS.
// - Multi-digit integers are required.
// - Decimal numbers are NOT required.
// - Unary minus / negative numbers are NOT required.
// - Parentheses must be supported.
// - The expression will end with the = symbol.
// - Supported operators: +, -, *, /
// - Division uses integer division.
//
// POSTFIX FORMAT REQUIREMENT:
// - Every operand and operator in the postfix string must be separated
//   by one space.
// - Do NOT include the final = symbol in the postfix string.
//
// Example:
//   Infix:    (2+3)*5=
//   Postfix:  2 3 + 5 *
//   Value:    25
//
// STACK REQUIREMENTS:
// - Use myStack<char> when converting infix to postfix.
// - Use myStack<int> when evaluating postfix.
//
// COMMON MISTAKES TO AVOID:
// - Do NOT treat each digit as a separate number.
//   Example: 244 is one number, not 2, 4, and 4.
// - Do NOT reverse operands for subtraction or division.
//   If postfix is "10 3 -", compute 10 - 3, not 3 - 10.
// - Do NOT forget to pop operators until '(' when handling ')'.
// - Do NOT leave '(' or ')' in the postfix output.
// - Do NOT include '=' in the postfix output.
// - Do NOT use std::stack.

class myCalc {
private:
  std::string input;

  /******************************************************************
   * isOperator
   * PRE:
   *    ch is a character from the input expression.
   * POST:
   *    Returns true if ch is one of +, -, *, or /.
   *    Returns false otherwise.
   ******************************************************************/
  // Helper: checks if a character is an operator
  bool isOperator(char ch) const;

  /******************************************************************
   * getPrecedence
   * PRE:
   *    theOperator is an arithmetic operator.
   * POST:
   *    Returns the precedence level of theOperator.
   *    + and - have lower precedence.
   *    * and / have higher precedence.
   ******************************************************************/
  // Helper: returns precedence of an operator
  int getPrecedence(char theOperator) const;

  /******************************************************************
   * applyOperator
   * PRE:
   *    theOperator is one of +, -, *, or /.
   *    left and right are integer operands.
   * POST:
   *    Returns the result of:
   *       left theOperator right
   *
   *    Examples:
   *       applyOperator('-', 10, 3) returns 7
   *       applyOperator('/', 10, 3) returns 3 because integer
   *       division is used.
   ******************************************************************/
  // Helper: applies an operator to two operands
  int applyOperator(char theOperator, int left, int right) const;

  /******************************************************************
   * postFix
   * PRE:
   *    infixString is a valid infix expression containing positive
   *    integers, operators, parentheses, and ending with =.
   * POST:
   *    Returns the postfix version of infixString.
   *    Every token is separated by one space.
   *
   *    Example:
   *       infixString: "(2+3)*5="
   *       return:      "2 3 + 5 *"
   ******************************************************************/
  // Helper: converts infix to postfix
  std::string postFix(const std::string &infixString) const;

  /******************************************************************
   * evaluatePostFix
   * PRE:
   *    postfixString is a valid postfix expression.
   *    Every operand and operator is separated by whitespace.
   * POST:
   *    Returns the integer value of postfixString.
   ******************************************************************/
  // Helper: evaluates a postfix expression
  int evaluatePostFix(const std::string &postfixString) const;

public:
  /******************************************************************
   * Default constructor
   * POST:
   *    input is initialized to an empty string.
   ******************************************************************/
  myCalc();

  /******************************************************************
   * Assignment constructor
   * PRE:
   *    str is a valid infix expression.
   * POST:
   *    input is initialized to str.
   ******************************************************************/
  myCalc(const std::string &str);

  /******************************************************************
   * getInput
   * POST:
   *    Returns input without modifying the object.
   ******************************************************************/
  std::string getInput() const;

  /******************************************************************
   * resetInput
   * PRE:
   *    str is a valid infix expression.
   * POST:
   *    input is reset to str.
   ******************************************************************/
  void resetInput(const std::string &str);

  /******************************************************************
   * postFixInput
   * PRE:
   *    input is a valid infix expression.
   * POST:
   *    Returns the postfix version of input.
   ******************************************************************/
  std::string postFixInput() const;

  /******************************************************************
   * evaluate
   * PRE:
   *    input is a valid infix expression.
   * POST:
   *    Converts input to postfix notation and returns the integer
   *    value of the expression.
   ******************************************************************/
  int evaluate() const;
};

// ================= STUDENT IMPLEMENTATIONS =================

myCalc::myCalc() { input = ""; }

myCalc::myCalc(const std::string &str) { input = str; }

std::string myCalc::getInput() const { return input; }

void myCalc::resetInput(const std::string &str) { input = str; }

bool myCalc::isOperator(char ch) const {
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
    return true;
  }
  return false;
}
int myCalc::getPrecedence(char theOperator) const {
  if (theOperator == '+' || theOperator == '-') {
    return 1;
  } else if (theOperator == '*' || theOperator == '/') {
    return 2;
  } else {
    return 0;
  }
}

int myCalc::applyOperator(char theOperator, int left, int right) const {
  if (theOperator == '-') {
    return (left - right);
  } else if (theOperator == '+') {
    return (left + right);
  } else if (theOperator == '*') {
    return (left * right);
  } else {
    return (left / right);
  }
}

std::string myCalc::postFixInput() const { return postFix(input); }
int myCalc::evaluate() const {
  std::string postFixString = postFixInput();
  return evaluatePostFix(postFixString);
}

std::string myCalc::postFix(const std::string &infixString) const {
  myStack<char> operatorsStack;
  std::string result = "";

  size_t indx = 0;

  while (indx < infixString.size()) {
    if (isOperator(infixString[indx])) {
      while (!operatorsStack.isEmptyStack() && operatorsStack.getTop() != '(' &&
             getPrecedence(operatorsStack.getTop()) >=
                 getPrecedence(infixString[indx])) {
        result += operatorsStack.getTop();
        result += " ";
        operatorsStack.pop();
      }
      operatorsStack.push(infixString[indx]);
      indx++;
    }

    else if (infixString[indx] == ')') {
      while (operatorsStack.getTop() != '(') {
        result += operatorsStack.getTop();
        result += " ";
        operatorsStack.pop();
      }
      operatorsStack.pop();
      indx++;
    }

    else if (infixString[indx] == '=') {
      while (!operatorsStack.isEmptyStack()) {
        result += operatorsStack.getTop();
        result += " ";
        operatorsStack.pop();
      }
      indx++;
    }

    else {
      if (infixString[indx] == '(') {
        operatorsStack.push('(');
        indx++;
      } else {
        while (indx < infixString.size() && std::isdigit(infixString[indx])) {
          result += infixString[indx];
          indx++;
        }
        result += " ";
      }
    }
  }
  if (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
  return result;
}

int myCalc::evaluatePostFix(const std::string &postfixString) const {
  myStack<int> operandsStack;
  std::string token;
  std::istringstream iss(postfixString);

  while (iss >> token) {
    if (std::isdigit(token[0])) {
      operandsStack.push(std::stoi(token));
    } else if (isOperator(token[0])) {
      int right = operandsStack.getTop();
      operandsStack.pop();
      int left = operandsStack.getTop();
      operandsStack.pop();
      operandsStack.push(applyOperator(token[0], left, right));
    }
  }
  return operandsStack.getTop();
}

#endif /* MYCALC_H_ */
