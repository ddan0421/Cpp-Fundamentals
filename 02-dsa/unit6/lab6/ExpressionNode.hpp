#ifndef EXPRESSIONNODE_HPP
#define EXPRESSIONNODE_HPP

#include <iostream>

/*************************************************************************
 *  Name: Dan Dan        CSC 240
 *  Date: 07/19/26        Lab 6
 *************************************************************************
 *  Statement:
 *  This file defines the ExpressionNode class hierarchy used by
 *  myExpressionTree. Each node represents either an operand or an operator
 *  in an arithmetic expression tree.
 *
 *  Specifications:
 *  ExpressionNode is the abstract base class.
 *  OperandNode stores a numeric value.
 *  OperatorNode stores an arithmetic operator and has left and right child
 *  pointers.
 *
 *  Input -
 *  Node values and operators are provided by myExpressionTree after the
 *  original infix expression has been converted to postfix.
 *
 *  Output -
 *  Node values and operators may be printed during tree traversal.
 *************************************************************************/

// IMPORTANT:
// Do NOT delete left/right in this destructor.
// The tree is deleted using destroyTree().
// Deleting children here will cause double deletion.
// IMPORTANT:
// Do NOT delete left/right in this destructor.
// The tree is deleted using destroyTree().
// Deleting children here will cause double deletion.

// IMPORTANT SERVER NOTE:
//
// The Oakton server compiler may not fully support the modern C++11
// keyword "override".
//
// If you receive compiler errors such as:
//
//     'override' does not name a type
//
// you may either:
//
// 1. Compile using:
//        g++ -std=c++0x
//    or
//        g++ -std=c++11
//
// OR
//
// 2. Simply comment out or remove the keyword "override".
//
// Example:
//
//     double getValue() const override
//
// becomes:
//
//     double getValue() const
//
// The program logic and polymorphism will still work correctly because
// the base-class functions are already declared virtual.

class ExpressionNode {
public:
  /******************************************************************
   * Destructor
   * PRE:
   *    An ExpressionNode object exists.
   * POST:
   *    The ExpressionNode object is destroyed.
   ******************************************************************/
  virtual ~ExpressionNode() {}

  /******************************************************************
   * getValue
   * PRE:
   *    The node is part of a valid expression tree.
   * POST:
   *    Returns the numeric value represented by this node or subtree.
   ******************************************************************/
  virtual double getValue() const = 0;

  /******************************************************************
   * print
   * PRE:
   *    out is a valid output stream.
   * POST:
   *    Prints the node's stored value or operator.
   ******************************************************************/
  virtual void print(std::ostream &out) const = 0;

  /******************************************************************
   * clone
   * PRE:
   *    This node is valid.
   * POST:
   *    Returns a dynamically allocated deep copy of this node/subtree.
   ******************************************************************/
  virtual ExpressionNode *clone() const = 0;
};

class OperandNode : public ExpressionNode {
private:
  double value;

public:
  /******************************************************************
   * Constructor
   * PRE:
   *    num is a valid numeric operand.
   * POST:
   *    value is initialized to num.
   ******************************************************************/
  OperandNode(double num) : value(num) {}

  /******************************************************************
   * getValue
   * PRE:
   *    This node stores a numeric operand.
   * POST:
   *    Returns the stored operand value.
   ******************************************************************/
  double getValue() const override { return value; }

  /******************************************************************
   * print
   * PRE:
   *    out is a valid output stream.
   * POST:
   *    Prints the operand value.
   ******************************************************************/
  void print(std::ostream &out) const override { out << value; }

  /******************************************************************
   * clone
   * PRE:
   *    This OperandNode is valid.
   * POST:
   *    Returns a new OperandNode containing the same value.
   ******************************************************************/
  ExpressionNode *clone() const override { return new OperandNode(value); }
};

class OperatorNode : public ExpressionNode {
private:
  char op;
  ExpressionNode *left;
  ExpressionNode *right;

public:
  /******************************************************************
   * Constructor
   * PRE:
   *    oper is one of +, -, *, or /.
   *    leftChild and rightChild point to valid subtrees.
   * POST:
   *    op, left, and right are initialized.
   ******************************************************************/
  OperatorNode(char oper, ExpressionNode *leftChild, ExpressionNode *rightChild)
      : op(oper), left(leftChild), right(rightChild) {}

  /******************************************************************
   * Destructor
   * PRE:
   *    This node exists.
   * POST:
   *    This node is destroyed.
   *
   * IMPORTANT:
   *    Full-tree deletion is handled by myExpressionTree::destroyTree.
   *    Do NOT delete left or right here.
   *    destroyTree() already deletes all nodes recursively.
   *    Deleting children here will cause double deletion errors.
   *
   *
   ******************************************************************/
  ~OperatorNode() override {}

  char getOperator() const { return op; }

  ExpressionNode *getLeft() const { return left; }

  ExpressionNode *getRight() const { return right; }

  /******************************************************************
   * getValue
   * PRE:
   *    left and right point to valid expression subtrees.
   * POST:
   *    Recursively evaluates left op right and returns the result.
   ******************************************************************/
  double getValue() const override {
    // TODO:
    // 1. Get the value of the left subtree.
    // 2. Get the value of the right subtree.
    // 3. Apply op to leftValue and rightValue.
    //
    // IMPORTANT:
    // Preserve operand order: left op right.
    // This matters for subtraction and division.
    // Division must use double arithmetic.
    if (op == '+') {
      return left->getValue() + right->getValue();
    } else if (op == '-') {
      return left->getValue() - right->getValue();
    } else if (op == '*') {
      return left->getValue() * right->getValue();
    } else {
      return left->getValue() / right->getValue();
    }
  }

  void print(std::ostream &out) const override { out << op; }

  /******************************************************************
   * clone
   * PRE:
   *    This OperatorNode is valid.
   * POST:
   *    Returns a deep copy of this operator node and its subtrees.
   ******************************************************************/
  ExpressionNode *clone() const override {
    // TODO:
    // Return a new OperatorNode with:
    // - the same operator
    // - a deep copy of the left subtree
    // - a deep copy of the right subtree
    //
    // HINT:
    // left->clone() and right->clone() may be useful.
    return new OperatorNode(op, left->clone(), right->clone());
  }
};

#endif
