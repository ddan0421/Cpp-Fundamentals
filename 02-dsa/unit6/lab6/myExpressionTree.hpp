#ifndef MYEXPRESSIONTREE_HPP
#define MYEXPRESSIONTREE_HPP

#include "ExpressionNode.hpp"
#include <cctype>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

/*************************************************************************
 *  Name: Dan Dan        CSC 240
 *  Date: 07/19/26        Lab 6
 *************************************************************************
 *  Statement:
 *  This file defines a class named myExpressionTree that stores a
 *  mathematical expression as a binary expression tree.
 *
 *  Specifications:
 *  The myExpressionTree object is created from an INFIX expression string.
 *  The class must convert the infix expression to postfix form internally.
 *  The expression tree itself must then be built and evaluated from that
 *  postfix expression.
 *
 *  Input -
 *  A valid infix expression containing positive integer operands, operators
 *  +, -, *, /, optional parentheses, and ending with =.
 *
 *  Output -
 *  In-order, pre-order, and post-order traversal output and the evaluated
 *  value of the expression tree.
 *************************************************************************/

// ======================================================================
// LAB 6 STUDENT TEMPLATE FILE
// ======================================================================
//
// PUBLIC VS PRIVATE DESIGN
//
// PUBLIC METHODS are the interface used by the test driver:
// - constructors
// - destructor
// - operator=
// - getInput()
// - getPostFixInput()
// - resetInput()
// - build()
// - evaluate()
// - printIn()
// - printPre()
// - printPost()
// - getLevels()
// - getHeight()      // REQUIRED: returns tree height measured in edges
// - isEmpty()
// - operator<<
//
// PRIVATE HELPER METHODS are internal implementation details:
// - isOperator()
// - isNumberToken()
// - getPrecedence()
// - postFix()
// - buildTreeFromPostfix()
// - destroyTree()
// - copyTree()
// - printToken()
// - recursive traversal helpers
// - recursive level helper
// - recursive height helper
//
// Students should not call private helpers from main/test code.
// The public methods should coordinate calls to the private helpers.
//
// REQUIRED WORKFLOW:
// 1. The object receives an INFIX expression, such as 12+34*2=
// 2. The class converts the infix expression to POSTFIX form internally.
// 3. build() constructs the expression tree from the postfix expression.
// 4. evaluate() evaluates the expression tree.
// 5. printIn(), printPre(), and printPost() traverse the built tree.
//
// IMPORTANT:
// - Do NOT build the tree directly from infix.
// - Do NOT evaluate the infix expression directly.
// - Do NOT bypass postfix conversion.
// - You may reuse Lab 5 myCalc logic for infix-to-postfix conversion.
// - You may use std::stack for this lab.
// - Postfix tokens must be separated by spaces.
// - Operands may be multi-digit positive integers.
// - The '=' symbol belongs only to the original infix expression and should
//   NOT appear in the postfix expression.
//
// TOKEN PARSING REQUIREMENT:
// - buildTreeFromPostfix MUST read postfix as tokens, not characters.
// - Example postfix: 12 34 2 * +
// - Correct tokens are: "12", "34", "2", "*", "+"
// - Use stringstream or an equivalent token-reading approach.
//
// RECURSION REQUIREMENT:
// - Traversals MUST be recursive.
// - Evaluation should be recursive through ExpressionNode::getValue.
// - destroyTree should delete nodes recursively.
// - getLevels and getHeight are both required and should use recursion.
// - Iterative traversal solutions using loops or stacks will not receive
//   full credit.
//
// LEVELS VS HEIGHT:
// - getLevels() returns the number of layers/nodes vertically in the tree.
//   Empty tree levels = 0.
//   Single-node tree levels = 1.
// - getHeight() returns the number of edges on the longest path from the
//   root to a leaf.
//   Empty tree height = -1.
//   Single-node tree height = 0.
// - For any non-empty tree: height = levels - 1.
// - getHeight() is REQUIRED, not extra credit.
//
//
// HEIGHT-SPECIFIC COMMON MISTAKES:
// - Returning 0 for an empty tree height. For this lab, empty tree height is
// -1.
// - Returning getLevels() from getHeight(). Levels and height are different.
// - Returning 1 for a single-node tree height. A single-node tree height is 0.
// - Forgetting that height counts edges, while levels count node layers.
// - Using the correct recursive formula with the wrong base case.
// RECURSION PATTERNS:
// inorder:    left -> node -> right
// preorder:   node -> left -> right
// postorder:  left -> right -> node

class myExpressionTree {
private:
  ExpressionNode *root;
  std::string input;        // original infix expression
  std::string postFixInput; // internally converted postfix expression

  /******************************************************************
   * isOperator
   * PRE:
   *    ch is a character from an expression.
   * POST:
   *    Returns true if ch is +, -, *, or /.
   *    Returns false otherwise.
   ******************************************************************/
  bool isOperator(char ch) const {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
      return true;
    return false;
  }

  /******************************************************************
   * isNumberToken
   * PRE:
   *    token is a string read from a postfix expression.
   * POST:
   *    Returns true if token represents a positive integer.
   ******************************************************************/
  bool isNumberToken(const std::string &token) const {
    if (token.empty()) {
      return false;
    }
    for (const auto &eachToken : token) {
      if (!std::isdigit(eachToken)) {
        return false;
      }
    }
    return true;
  }

  /******************************************************************
   * getPrecedence
   * PRE:
   *    op is an operator or other character.
   * POST:
   *    Returns 1 for + and -, 2 for * and /, and 0 otherwise.
   ******************************************************************/
  int getPrecedence(char op) const {
    if (op == '+' || op == '-') {
      return 1;
    } else if (op == '*' || op == '/') {
      return 2;
    } else {
      return 0;
    }
  }

  /******************************************************************
   * postFix
   * PRE:
   *    infix is a valid infix expression ending with =.
   * POST:
   *    Returns a postfix expression with tokens separated by one
   *    space and no trailing space. The = symbol is not included.
   ******************************************************************/
  std::string postFix(const std::string &infix) const {
    std::stack<char> operatorStack;
    std::string result = "";
    size_t indx = 0;

    while (indx < infix.size()) {
      if (isOperator(infix[indx])) {
        while (!operatorStack.empty() && operatorStack.top() != '(' &&
               getPrecedence(operatorStack.top()) >=
                   getPrecedence(infix[indx])) {
          result += operatorStack.top();
          result += " ";
          operatorStack.pop();
        }
        operatorStack.push(infix[indx]);
        indx++;
      } else if (infix[indx] == ')') {
        while (operatorStack.top() != '(') {
          result += operatorStack.top();
          result += " ";
          operatorStack.pop();
        }
        operatorStack.pop();
        indx++;
      } else if (infix[indx] == '=') {
        while (!operatorStack.empty()) {
          result += operatorStack.top();
          result += " ";
          operatorStack.pop();
        }
        indx++;
      } else {
        if (infix[indx] == '(') {
          operatorStack.push('(');
          indx++;
        } else {
          while (indx < infix.size() && std::isdigit(infix[indx])) {
            result += infix[indx];
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

  /******************************************************************
   * buildTreeFromPostfix
   * PRE:
   *    postfix is a valid postfix expression with space-separated tokens.
   * POST:
   *    root points to a newly built expression tree.
   ******************************************************************/
  void buildTreeFromPostfix(const std::string &postfix) {
    std::stack<ExpressionNode *> nodes;
    std::istringstream iss(postfix);
    std::string token;
    while (iss >> token) {
      if (std::isdigit(token[0])) {
        nodes.push(new OperandNode(std::stod(token)));
      } else if (isOperator(token[0])) {
        ExpressionNode *right = nodes.top();
        nodes.pop();
        ExpressionNode *left = nodes.top();
        nodes.pop();

        nodes.push(new OperatorNode(token[0], left, right));
      }
    }
    root = nodes.top();
  }

  /******************************************************************
   * destroyTree
   * PRE:
   *    node points to the root of a subtree or is nullptr.
   * POST:
   *    All nodes in the subtree are deleted using post-order deletion.
   ******************************************************************/
  void destroyTree(ExpressionNode *node) {
    OperatorNode *OpterNode = dynamic_cast<OperatorNode *>(node);
    if (node != nullptr && OpterNode != nullptr) {
      destroyTree(OpterNode->getLeft());
      destroyTree(OpterNode->getRight());
    }
    delete node;
  }

  /******************************************************************
   * copyTree
   * PRE:
   *    node points to the root of a valid subtree or is nullptr.
   * POST:
   *    Returns a deep copy of the subtree.
   ******************************************************************/
  ExpressionNode *copyTree(ExpressionNode *node) const {
    if (node == nullptr) {
      return nullptr;
    } else {
      return node->clone();
    }
  }

  /******************************************************************
   * printToken
   * PRE:
   *    node is not nullptr and out is valid.
   * POST:
   *    Prints one token, inserting a leading space only if needed.
   ******************************************************************/
  void printToken(ExpressionNode *node, std::ostream &out, bool &first) const {
    if (first) {
      node->print(out);
    } else {
      out << " ";
    }
    first = false;
  }

  /******************************************************************
   * inorder
   * PRE:
   *    node points to the root of a subtree or is nullptr.
   *    out is a valid output stream.
   *    first tracks whether a token has already been printed.
   * POST:
   *    Prints recursive inorder traversal with one space between tokens.
   ******************************************************************/
  void inorder(ExpressionNode *node, std::ostream &out, bool &first) const {
    if (node == nullptr) {
      return;
    }
    OperatorNode *OpterNode = dynamic_cast<OperatorNode *>(node);
    if (OpterNode != nullptr) {
      inorder(OpterNode->getLeft(), out, first);
    }
    printToken(node, out, first);
    if (OpterNode != nullptr) {
      inorder(OpterNode->getRight(), out, first);
    }
  }

  /******************************************************************
   * preorder
   * PRE:
   *    node points to the root of a subtree or is nullptr.
   *    out is a valid output stream.
   *    first tracks whether a token has already been printed.
   * POST:
   *    Prints recursive preorder traversal with one space between tokens.
   ******************************************************************/
  void preorder(ExpressionNode *node, std::ostream &out, bool &first) const {
    if (node == nullptr) {
      return;
    }
    OperatorNode *OpterNode = dynamic_cast<OperatorNode *>(node);
    printToken(node, out, first);
    if (OpterNode != nullptr) {
      preorder(OpterNode->getLeft(), out, first);
    }
    if (OpterNode != nullptr) {
      preorder(OpterNode->getRight(), out, first);
    }
  }

  /******************************************************************
   * postorder
   * PRE:
   *    node points to the root of a subtree or is nullptr.
   *    out is a valid output stream.
   *    first tracks whether a token has already been printed.
   * POST:
   *    Prints recursive postorder traversal with one space between tokens.
   ******************************************************************/
  void postorder(ExpressionNode *node, std::ostream &out, bool &first) const {
    if (node == nullptr) {
      return;
    }
    OperatorNode *OpterNode = dynamic_cast<OperatorNode *>(node);
    if (OpterNode != nullptr) {
      postorder(OpterNode->getLeft(), out, first);
    }
    if (OpterNode != nullptr) {
      postorder(OpterNode->getRight(), out, first);
    }
    printToken(node, out, first);
  }

  /******************************************************************
   * getLevels
   * PRE:
   *    node points to the root of a subtree or is nullptr.
   * POST:
   *    Returns the number of levels in the subtree.
   *
   * DEFINITION:
   *    Levels count the number of node layers in the tree.
   *    Empty subtree levels = 0.
   *    Single-node subtree levels = 1.
   ******************************************************************/
  int getLevels(ExpressionNode *node) const {
    if (node == nullptr) {
      return 0;
    }
    OperatorNode *OpterNode = dynamic_cast<OperatorNode *>(node);
    if (OpterNode == nullptr) {
      return 1;
    } else {
      int leftLevels = getLevels(OpterNode->getLeft());
      int rightLevels = getLevels(OpterNode->getRight());
      return 1 + std::max(leftLevels, rightLevels);
    }
  }

  /******************************************************************
   * getHeight
   * PRE:
   *    node points to the root of a subtree or is nullptr.
   * POST:
   *    Returns the height of the subtree.
   *
   * DEFINITION:
   *    Height counts the number of edges on the longest path from
   *    the current node to a leaf.
   *    Empty subtree height = -1.
   *    Single-node subtree height = 0.
   *    This helper is REQUIRED and must be recursive.
   ******************************************************************/
  int getHeight(ExpressionNode *node) const {
    if (node == nullptr) {
      return -1;
    }
    OperatorNode *OpterNode = dynamic_cast<OperatorNode *>(node);
    if (OpterNode == nullptr) {
      return 0;
    } else {
      int leftHeight = getHeight(OpterNode->getLeft());
      int rightHeight = getHeight(OpterNode->getRight());
      return 1 + std::max(leftHeight, rightHeight);
    }
  }

public:
  /******************************************************************
   * Default Constructor
   * PRE:
   *    None.
   * POST:
   *    root is nullptr and both input strings are empty.
   ******************************************************************/
  myExpressionTree() {
    root = nullptr;
    input = "";
    postFixInput = "";
  }

  /******************************************************************
   * Constructor with infix expression
   * PRE:
   *    infixExpression is a valid infix expression ending with =.
   * POST:
   *    input stores the original infix expression.
   *    postFixInput stores the internally converted postfix expression.
   *    root remains nullptr until build() is called.
   ******************************************************************/
  myExpressionTree(const std::string &infixExpression) {
    root = nullptr;
    input = infixExpression;
    postFixInput = postFix(input);
  }

  /******************************************************************
   * Copy Constructor
   * PRE:
   *    otherTree is a valid myExpressionTree object.
   * POST:
   *    This tree is a deep copy of otherTree.
   ******************************************************************/
  myExpressionTree(const myExpressionTree &otherTree) {
    // TODO:
    // Copy input and postFixInput.
    // Deep copy otherTree.root using copyTree.
    root = nullptr;
  }

  /******************************************************************
   * Destructor
   * PRE:
   *    This tree exists.
   * POST:
   *    All dynamically allocated nodes are deleted.
   ******************************************************************/
  ~myExpressionTree() {
    // TODO:
    // Call destroyTree(root).
    // Set root to nullptr.
  }

  /******************************************************************
   * operator=
   * PRE:
   *    otherTree is a valid myExpressionTree object.
   * POST:
   *    This tree becomes a deep copy of otherTree.
   *    Self-assignment is handled safely.
   ******************************************************************/
  myExpressionTree &operator=(const myExpressionTree &otherTree) {
    // TODO:
    // 1. Check for self-assignment.
    // 2. Destroy the current tree.
    // 3. Copy input and postFixInput.
    // 4. Deep copy otherTree.root using copyTree.
    // 5. Return *this.
    return *this;
  }

  /******************************************************************
   * getInput
   * PRE:
   *    None.
   * POST:
   *    Returns the original infix input string.
   ******************************************************************/
  std::string getInput() const { return input; }

  /******************************************************************
   * getPostFixInput
   * PRE:
   *    The infix expression has been converted to postfix.
   * POST:
   *    Returns the internally stored postfix expression.
   ******************************************************************/
  std::string getPostFixInput() const { return postFixInput; }

  /******************************************************************
   * resetInput
   * PRE:
   *    infixExpression is a valid infix expression ending with =.
   * POST:
   *    Current tree is destroyed.
   *    input and postFixInput are updated.
   *    root is nullptr until build() is called.
   ******************************************************************/
  void resetInput(const std::string &infixExpression) {
    // TODO:
    // Destroy the current tree.
    // Set root to nullptr.
    // Store the new infix input.
    // Convert it to postfix and store in postFixInput.
  }

  /******************************************************************
   * build
   * PRE:
   *    postFixInput contains a valid postfix expression.
   * POST:
   *    Current tree is destroyed and rebuilt from postFixInput.
   ******************************************************************/
  void build() {
    if (root != nullptr) {
      destroyTree(root);
    } else {
      root = nullptr;
    }
    buildTreeFromPostfix(postFixInput);
  }

  /******************************************************************
   * evaluate
   * PRE:
   *    root points to a valid expression tree or is nullptr.
   * POST:
   *    Returns the evaluated value of the tree.
   *    Returns 0 if the tree has not been built.
   ******************************************************************/
  double evaluate() const {
    if (root == nullptr) {
      return 0;
    } else {
      return root->getValue();
    }
  }

  /******************************************************************
   * printIn
   * PRE:
   *    out is a valid output stream.
   * POST:
   *    Prints the inorder traversal of the tree.
   ******************************************************************/
  void printIn(std::ostream &out = std::cout) const {
    // TODO:
    // Create bool first = true.
    // Call inorder(root, out, first).
  }

  /******************************************************************
   * printPre
   * PRE:
   *    out is a valid output stream.
   * POST:
   *    Prints the preorder traversal of the tree.
   ******************************************************************/
  void printPre(std::ostream &out = std::cout) const {
    // TODO:
    // Create bool first = true.
    // Call preorder(root, out, first).
  }

  /******************************************************************
   * printPost
   * PRE:
   *    out is a valid output stream.
   * POST:
   *    Prints the postorder traversal of the tree.
   ******************************************************************/
  void printPost(std::ostream &out = std::cout) const {
    // TODO:
    // Create bool first = true.
    // Call postorder(root, out, first).
  }

  /******************************************************************
   * getLevels
   * PRE:
   *    None.
   * POST:
   *    Returns the number of levels in the tree.
   *
   * DEFINITION:
   *    Levels count node layers.
   *    Empty tree levels = 0.
   *    Single-node tree levels = 1.
   ******************************************************************/
  int getLevels() const { return getLevels(root); }

  /******************************************************************
   * getHeight
   * PRE:
   *    None.
   * POST:
   *    Returns the height of the tree.
   *
   * DEFINITION:
   *    Height counts edges on the longest root-to-leaf path.
   *    Empty tree height = -1.
   *    Single-node tree height = 0.
   *
   * IMPORTANT:
   *    This method is REQUIRED.
   *    Height is measured in edges, not node layers.
   *    For any non-empty tree, height = levels - 1.
   ******************************************************************/
  int getHeight() const { return getHeight(root); }

  /******************************************************************
   * isEmpty
   * PRE:
   *    None.
   * POST:
   *    Returns true if root is nullptr.
   ******************************************************************/
  bool isEmpty() const { return root == nullptr; }
};

/**********************************************************************
 * operator<<
 * PRE:
 *    out is a valid output stream.
 *    tree is a valid myExpressionTree object.
 * POST:
 *    Prints the tree using inorder traversal and returns out.
 **********************************************************************/
inline std::ostream &operator<<(std::ostream &out,
                                const myExpressionTree &tree) {
  // TODO:
  // Call tree.printIn(out).
  // Return out.
  return out;
}

#endif
